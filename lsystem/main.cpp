#include <iostream>
#include <GLUT/glut.h>
#include <err.h>
#include "LSystem.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

using namespace std;

void reshape(int, int);

void display();

LSystem* ls;

int main(int argc, char** argv) {

    if (argc != 2) errx(1, "Usage: %s <fractal_file>", argv[0]);
    string base = "/Users/fhrenic/Programming/fractals/";
    string path = argv[1];

    path = "koch.txt"; // koch.txt, ls{1,2,3,4}.txt

    path = base + path;
    ls = new LSystem(path);

    // general settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("L-system fractals");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, 0, height - 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ls->render();
    glutSwapBuffers();
}
