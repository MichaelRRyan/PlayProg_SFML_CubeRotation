#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3f.h>
#include <Matrix3f.h>
#include <array>


using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	void setupCube();

	GLuint index;

	array<cube::Vector3f, 6> m_faceColours;
	array<cube::Vector3f, 8> m_baseCubeCorners;
	array<cube::Vector3f, 8> m_cubeVertices;
	int m_cubeFaceIndices[6][4]; // Faces and corners

	cube::Vector3f m_rotations;
	cube::Vector3f m_translations;
	float m_scale;

	bool m_wireframe;
};