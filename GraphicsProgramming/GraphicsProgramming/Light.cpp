#include "Light.h"
#include "SolarSystem.h"
#include "Scene.h"
// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Light::Light(Input* in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.


	// Initialise scene variables

}

void Light::handleInput(float dt)
{
	// Handle user input
}

void Light::update(float dt)
{
	// update scene related variables.

	rotation += speed * dt;
	// Calculate FPS for output
	calculateFPS();
}

void Light::PushVertex(Vertex v) {

	//glColor3f(v.color.x, v.color.y, v.color.z);
	glVertex3f(v.position.x, v.position.y, v.position.z);


}
void Light::drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
{
	const int numberOfVertices = 55 + 2;

	GLfloat twicePi = 2.0f * 3.14f;

	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(numberOfVertices) * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Light::drawTriangle(Vertex v1, Vertex v2, Vertex v3) {
	glBegin(GL_TRIANGLES);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v3);
	glEnd();


}
void Light::drawSquare(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
	glBegin(GL_QUADS);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v4);
	PushVertex(v3);
	glEnd();
}

void Light::drawCube(Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6, Vertex v7, Vertex v8) {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	PushVertex(v1);
	PushVertex(v2);
	PushVertex(v3);
	PushVertex(v4);
	// right face
	glColor3f(0.0f, 1.0f, 0.0f);
	PushVertex(v2);
	PushVertex(v3);
	PushVertex(v6);
	PushVertex(v7);
	// bottom face
	glColor3f(0.0f, 0.0f, 1.0f);
	PushVertex(v1);
	PushVertex(v8);
	PushVertex(v7);
	PushVertex(v2);

	//left
	glColor3f(5.0f, 7.0f, 1.0f);
	PushVertex(v1);
	PushVertex(v8);
	PushVertex(v5);
	PushVertex(v4);

	//top
	glColor3f(2.0f, 0.0f, 1.0f);
	PushVertex(v4);
	PushVertex(v3);
	PushVertex(v6);
	PushVertex(v5);

	//back
	glColor3f(0.0f, 2.0f, 1.0f);
	PushVertex(v5);
	PushVertex(v8);
	PushVertex(v7);
	PushVertex(v6);
	
	glEnd();
}

void Light::Animate() {

}

void Light::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(3.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//glPolygonMode(GL_FRONT, GL_LINE);

	// Render geometry/scene here -------------------------------------

	Vertex v1(Vector3(0,0,0), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v2(Vector3(1, 0, 0), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v3(Vector3(1,1,0), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v4(Vector3(0,1,0), Vector3(1.0f, 0.0f, 0.0f));
	Vertex v5(Vector3(0,1,1), Vector3(0.0f, 1.0f, 0.0f));
	Vertex v6(Vector3(1, 1.f,1), Vector3(0.0f, 1.0f, 0.0f));
	Vertex v7(Vector3(1,0,1), Vector3(0.0f, 1.0f, 0.0f));
	Vertex v8(Vector3(0,0,1), Vector3(0.0f, 1.0f, 0.0f));

	//glTranslatef(1.0, 0.0, 0.0);
	//glTranslatef(0.0, 1.0, 0.0);
	//glTranslatef(-2.0, 1.0, 0.0);
	//glTranslatef(0.0, 0.0, -4.0);

	//glScalef(2, 2, 2);
	//glScalef(0.5, 0.5, 0.5);
	//glScalef(2, 0.5, 0.0);



	glRotatef(rotation, 0, 1, 0);

	if (input->isKeyDown('o')) {

		drawTriangle(v1, v2, v3);
	}

	//drawCircle(-2.1f, 0.1f, 0.1f, 1, 50);
	drawCube(v1,v2,v3,v4,v5,v6,v7,v8);

	

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Light::initialiseOpenGL()
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
void Light::resize(int w, int h)
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
void Light::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Light::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Light::displayText(float x, float y, float r, float g, float b, char* string) {
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
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}