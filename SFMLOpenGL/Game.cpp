#include <Game.h>

bool updatable = false;

Game::Game() :
	window(VideoMode(800, 600), "OpenGL Cube"),
	m_cubeFaceIndices{
		{ 1, 5, 6, 2 },
		{ 4, 0, 3, 7 },
		{ 3, 2, 6, 7 },
		{ 0, 4, 5, 1 },
		{ 0, 1, 2, 3 },
		{ 4, 7, 6, 5 },
	}
{
	index = glGenLists(2);

	m_faceColours.at(0) = { 1.0f, 0.0f, 0.0f };
	m_faceColours.at(1) = { 0.0f, 1.0f, 0.0f };
	m_faceColours.at(2) = { 0.0f, 0.0f, 1.0f };
	m_faceColours.at(3) = { 1.0f, 1.0f, 0.0f };
	m_faceColours.at(4) = { 0.0f, 1.0f, 1.0f };
	m_faceColours.at(5) = { 1.0f, 0.0f, 1.0f };

	m_baseCubeCorners.at(0) = { -1, -1, 1 };
	m_baseCubeCorners.at(1) = { 1, -1, 1 };
	m_baseCubeCorners.at(2) = { 1, 1, 1 };
	m_baseCubeCorners.at(3) = { -1, 1, 1 };
	m_baseCubeCorners.at(4) = { -1, -1, -1 };
	m_baseCubeCorners.at(5) = { 1, -1, -1 };
	m_baseCubeCorners.at(6) = { 1, 1, -1 };
	m_baseCubeCorners.at(7) = { -1, 1, -1 };

	m_cubeVertices = m_baseCubeCorners;
	m_rotations = { 0.0f, 0.0f, 0.0f };
	m_scale = 100.0f;
}

Game::~Game(){}

void Game::run()
{

	initialize();

	sf::Clock runClock;
	const float FPS{ 60.0f };
	sf::Time timePerFrame = sf::seconds( 1.0f / FPS);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	Event event;
	while (isRunning){

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}

		timeSinceLastUpdate += runClock.restart();

		if (timeSinceLastUpdate >= timePerFrame)
		{
			update();
			draw();

			timeSinceLastUpdate -= timePerFrame;
		}
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -8.0f);

	setupCube();
}

void Game::update()
{
	m_cubeVertices = m_baseCubeCorners;

	// Create a basic identity matrix
	cube::Matrix3f transformMatrix { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// Take the user input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // Reset the cube to starting transformations
	{
		m_rotations = { 0.0f, 0.0f, 0.0f };
		m_scale = 100.0f;
	}

	// Scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		m_scale += 10.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		m_scale -= 10.0f;

	// Rotations
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		m_rotations.x += 0.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		m_rotations.y += 0.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		m_rotations.z += 0.5f;

	// Apply the transformations
	transformMatrix = transformMatrix * cube::Matrix3f::Scale(m_scale, m_scale);

	transformMatrix = transformMatrix * cube::Matrix3f::RotationX(m_rotations.x);
	transformMatrix = transformMatrix * cube::Matrix3f::RotationY(m_rotations.y);
	transformMatrix = transformMatrix * cube::Matrix3f::Rotation(m_rotations.z);

	// Rotate all the cube points
	for (cube::Vector3f& vector : m_cubeVertices)
		vector = transformMatrix * vector;

	// Re-set up all the points on the cube with the new coords
	setupCube();
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCallList(1); // Draw the cube
	glCallList(2); // Draw the edges

	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

bool Game::checkFace(int t_faceIndex)
{
	cube::Vector3f distanceVectorOne = m_cubeVertices[m_cubeFaceIndices[t_faceIndex][2]] - m_cubeVertices[m_cubeFaceIndices[t_faceIndex][1]]; // Find the distance from corner B to C
	cube::Vector3f distanceVectorTwo = m_cubeVertices[m_cubeFaceIndices[t_faceIndex][0]] - m_cubeVertices[m_cubeFaceIndices[t_faceIndex][1]]; // Find the distance from corner B to A
	cube::Vector3f crossProduct = distanceVectorOne ^ distanceVectorTwo; // Get the cross product of the two distance vectors

	return (crossProduct.z > 0); // Return the result of the checks
}

void Game::setupCube()
{
	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		// Loop for each face
		for (int face = 0; face < 6; face++)
		{
			if (checkFace(face))
			{
				// Change the colour depending on the face
				glColor3f(m_faceColours.at(face).x, m_faceColours.at(face).y, m_faceColours.at(face).z);

				// First triangle of this face
				for (int corner = 0; corner < 3; corner++)
				{
					glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][corner]).x, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).y, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).z);
				}

				// Lighten the colour for the second triangle
				glColor3f(m_faceColours.at(face).x / 2.0f, m_faceColours.at(face).y / 2.0f, m_faceColours.at(face).z / 2.0f);

				// Second triangle of the face
				for (int corner = 2; corner < 4; corner++)
				{
					glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][corner]).x, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).y, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).z);
				}

				// Finish by going back to start
				glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][0]).x, m_cubeVertices.at(m_cubeFaceIndices[face][0]).y, m_cubeVertices.at(m_cubeFaceIndices[face][0]).z);
			}
		}
	}
	glEnd();
	glEndList();

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_LINES);
	{
		// Set the colour to white
		glColor3f(1.0f, 1.0f, 1.0f);

		// Loop for each face
		for (int face = 0; face < 6; face++)
		{
			if (checkFace(face))
			{
				// Loop for each of the corners
				for (int corner = 1; corner < 4; corner++)
				{
					glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][corner - 1]).x, m_cubeVertices.at(m_cubeFaceIndices[face][corner - 1]).y, m_cubeVertices.at(m_cubeFaceIndices[face][corner - 1]).z);
					glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][corner]).x, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).y, m_cubeVertices.at(m_cubeFaceIndices[face][corner]).z);
				}

				// Last edge from last vertice to the first
				glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][3]).x, m_cubeVertices.at(m_cubeFaceIndices[face][3]).y, m_cubeVertices.at(m_cubeFaceIndices[face][3]).z);
				glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][0]).x, m_cubeVertices.at(m_cubeFaceIndices[face][0]).y, m_cubeVertices.at(m_cubeFaceIndices[face][0]).z);

				// Diagonal edge between the triangles
				glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][0]).x, m_cubeVertices.at(m_cubeFaceIndices[face][0]).y, m_cubeVertices.at(m_cubeFaceIndices[face][0]).z);
				glVertex3f(m_cubeVertices.at(m_cubeFaceIndices[face][2]).x, m_cubeVertices.at(m_cubeFaceIndices[face][2]).y, m_cubeVertices.at(m_cubeFaceIndices[face][2]).z);
			}
		}
	}
	glEnd();
	glEndList();
}