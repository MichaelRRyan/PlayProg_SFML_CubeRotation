#include <Game.h>

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(2);

	m_faceColours.at(0) = { 1.0f, 0.0f, 0.0f };
	m_faceColours.at(1) = { 0.0f, 1.0f, 0.0f };
	m_faceColours.at(2) = { 1.0f, 0.0f, 1.0f };
	m_faceColours.at(3) = { 1.0f, 1.0f, 0.0f };
	m_faceColours.at(4) = { 0.0f, 1.0f, 1.0f };
	m_faceColours.at(5) = { 1.0f, 0.0f, 1.0f };
	m_faceColours.at(6) = { 0.5f, 0.5f, 0.5f };
	m_faceColours.at(7) = { 0.0f, 0.5f, 0.5f };

	m_cubeVertices.at(0) = { -1, -1, 1 };
	m_cubeVertices.at(1) = { 1, -1, 1 };
	m_cubeVertices.at(2) = { 1, 1, 1 };
	m_cubeVertices.at(3) = { -1, 1, 1 };
	m_cubeVertices.at(4) = { -1, -1, -1 };
	m_cubeVertices.at(5) = { 1, -1, -1 };
	m_cubeVertices.at(6) = { 1, 1, -1 };
	m_cubeVertices.at(7) = { -1, 1, -1 };

	m_cubePoints.at(0) = 0;
	m_cubePoints.at(1) = 1;
	m_cubePoints.at(2) = 2;
	m_cubePoints.at(3) = 2;
	m_cubePoints.at(4) = 3;
	m_cubePoints.at(5) = 0;

	m_cubePoints.at(6) = 0;
	m_cubePoints.at(7) = 3;
	m_cubePoints.at(8) = 4;
	m_cubePoints.at(9) = 4;
	m_cubePoints.at(10) = 3;
	m_cubePoints.at(11) = 7;

	m_cubePoints.at(12) = 7;
	m_cubePoints.at(13) = 4;
	m_cubePoints.at(14) = 5;
	m_cubePoints.at(15) = 5;
	m_cubePoints.at(16) = 6;
	m_cubePoints.at(17) = 7;

	m_cubePoints.at(18) = 5;
	m_cubePoints.at(19) = 6;
	m_cubePoints.at(20) = 1;
	m_cubePoints.at(21) = 1;
	m_cubePoints.at(22) = 2;
	m_cubePoints.at(23) = 6;

	m_cubePoints.at(24) = 2;
	m_cubePoints.at(25) = 3;
	m_cubePoints.at(26) = 6;
	m_cubePoints.at(27) = 6;
	m_cubePoints.at(28) = 7;
	m_cubePoints.at(29) = 3;

	m_cubePoints.at(30) = 0;
	m_cubePoints.at(31) = 1;
	m_cubePoints.at(32) = 5;
	m_cubePoints.at(33) = 5;
	m_cubePoints.at(34) = 4;
	m_cubePoints.at(35) = 0;
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;
	updatable = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		float colour = 0;

		for (int i : m_cubePoints)
		{
			//glColor3f(m_faceColours.at(colour).x, m_faceColours.at(colour).y, m_faceColours.at(colour).z); // Colour

			if (i % 4 == 0)
			{
				colour += 0.1f;
				glColor3f(colour, 0.0f, 0.0f);
			}

			glVertex3f(m_cubeVertices.at(i).x, m_cubeVertices.at(i).y, m_cubeVertices.at(i).z);
		}
	}
	glEnd();
	glEndList();

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		for (int i = 0; i < m_cubePoints.size(); i++)
		{
			if (i % 2 == 1 && i < 35)
			{
				glVertex3f(m_cubeVertices.at(m_cubePoints.at(i + 1)).x, m_cubeVertices.at(m_cubePoints.at(i + 1)).y, m_cubeVertices.at(m_cubePoints.at(i + 1)).z);
			}

			glVertex3f(m_cubeVertices.at(m_cubePoints.at(i)).x, m_cubeVertices.at(m_cubePoints.at(i)).y, m_cubeVertices.at(m_cubePoints.at(i)).z);
		}
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= (1.0f / 60.0f)) // Update every 60th of a second
	{
		clock.restart();

		if (updatable)
		{
			rotationAngle += 0.5f;

			if (rotationAngle > 360.0f)
			{
				rotationAngle -= 360.0f;
			}
		}
	}

	
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis
	glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis

	glCallList(1);
	glCallList(2);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}