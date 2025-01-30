#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	

	// Initialise scene variables
	
}

void Scene::handleInput(float dt)
{
	// Handle user input
}

void Scene::update(float dt)
{
	// update scene related variables.

	// Calculate FPS for output
	calculateFPS();
}

void Scene::PushVertex(Vertex v) {

	glColor3f(v.color.x, v.color.y, v.color.z);
	glVertex3f(v.position.x,v.position.y, v.position.z);
	

}


void Scene::drawTriangle(Vertex v1,Vertex v2,Vertex v3) {
	glBegin(GL_TRIANGLES);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v3);
	glEnd();


}

void Scene::drawFan(Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6) {
	glBegin(GL_TRIANGLE_FAN);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v3);
	PushVertex(v4);
	PushVertex(v5);
	PushVertex(v6);
	glEnd();
}

void Scene::drawSquare(Vertex v1, Vertex v2, Vertex v3, Vertex v4,Vertex v5,Vertex v6) {
	glBegin(GL_POLYGON);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v3);
	PushVertex(v4);
	PushVertex(v5);
	PushVertex(v6);
	glEnd();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	glPolygonMode(GL_FRONT, GL_LINE);

	// Render geometry/scene here -------------------------------------

	Vertex v1(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v2(Vector3(0.3f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v3(Vector3(0.5f, 0.3f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v4(Vector3(0.3f, 0.6f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v5(Vector3(0.0f, 0.6f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v6(Vector3(-0.2f, 0.3f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	//Vertex v7(Vector3(3.0f, 0.1f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

	//drawTriangle(v1, v2, v3);
	drawSquare(v1, v2, v3, v4,v5,v6);
	//drawFan(v1, v2, v3, v4, v5, v6);
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
