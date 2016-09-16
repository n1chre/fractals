#include <iostream>
#include <GLUT/glut.h>
#include "Mandelbrot.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define UMIN -2
#define UMAX 1
#define VMIN -1.2
#define VMAX 1.2

#define MAX_LIMIT 200

typedef unsigned char Color;

using namespace std;

void reshape(int, int);

void display();

void keyPressed(unsigned char, int, int);

void mousePressed(int, int, int, int);

int divergenceTest1(double, double, int);

int divergenceTest2(double, double, int);

void colorScheme1(int, int);

void colorScheme2(int, int);

Mandelbrot* mandelbrot;

int main(int argc, char** argv) {

    // general settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Lab 11 fh47758");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mousePressed);

    mandelbrot = new Mandelbrot(
            0, WINDOW_WIDTH, 0, WINDOW_HEIGHT,
            UMIN, UMAX, VMIN, VMAX,
            MAX_LIMIT, divergenceTest1, colorScheme2
    );

    glutMainLoop();
    return 0;
}

// divergence

int divergenceTest1(double cx, double cy, int limit) {
    // z_{n+1} = z_n^2 + c
    double zx = 0, zy = 0, x, y;
    for (int i = 1; i <= limit; ++i) {
        x = zx * zx - zy * zy + cx;
        y = 2 * zx * zy + cy;
        zx = x;
        zy = y;
        if (zx * zx + zy * zy > 4) return i;
    }
    return -1;
}

int divergenceTest2(double cx, double cy, int limit) {
    // z_{n+1} = z_n^3 + c
    double zx = 0, zy = 0, x, y;
    for (int i = 1; i <= limit; ++i) {
        x = zx * zx * zx - 3 * zx * zy * zy + cx;
        y = 3 * zx * zx * zy - zy * zy * zy + cy;
        zx = x;
        zy = y;
        if (zx * zx + zy * zy > 4) return i;
    }
    return -1;
}

// color

void colorScheme1(int n, int) {
    if (n == -1)
        glColor3ub(0, 0, 0);
    else
        glColor3ub(255, 255, 255);
}

void colorScheme2(int n, int max_limit) {
    if (n == -1) {
        glColor3ub(0, 0, 0);
        return;
    }

    Color r, g, b;
    n--;

    if (max_limit < 16) {
        r = (Color) ((int) (1.0 * n / (max_limit - 1) * 255 + 0.5));
        g = (Color) (255 - r);
        b = (Color) ((n % (max_limit / 2)) * 255 / (max_limit / 2));
    } else {
        int lim = max_limit < 32 ? max_limit : 32;
        r = (Color) (n * 255 / lim);
        g = (Color) ((n % (lim / 4)) * 255 / (lim / 4));
        b = (Color) ((n % (lim / 8)) * 255 / (lim / 8));
    }

    glColor3ub(r, g, b);
}


void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, height - 1, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    mandelbrot->viewChanged(0, width, 0, height);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    mandelbrot->render();
    glutSwapBuffers();
}

void keyPressed(unsigned char key, int, int) {
    switch (key) {
        case '1':
            mandelbrot->setDivergenceTest(divergenceTest1);
            break;
        case '2':
            mandelbrot->setDivergenceTest(divergenceTest2);
            break;
        case 'b':
            mandelbrot->setColorScheme(colorScheme1);
            break;
        case 'c':
            mandelbrot->setColorScheme(colorScheme2);
            break;
        case 27:
            mandelbrot->removeAllPlanes();
            break;
        case 'x':
            mandelbrot->removeLastPlane();
            break;
        default:
            return;
    }
    glutPostRedisplay();
}

void mousePressed(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
    mandelbrot->trimComplexPlane(x, y);
    glutPostRedisplay();
}