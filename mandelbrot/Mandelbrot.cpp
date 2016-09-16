//
// Created by Filip Hrenic on 01/06/16.
//

#include <GLUT/glut.h>
#include "Mandelbrot.h"

void Mandelbrot::render() {
    double u, v;

    ComplexPlane* cp = stack.front();
    double ufact = (cp->umax - cp->umin) / (xmax - xmin);
    double vfact = (cp->vmax - cp->vmin) / (ymax - ymin);

    glPointSize(1.0);
    glBegin(GL_POINTS);
    for (int x = xmin; x <= xmax; ++x) {
        for (int y = ymin; y <= ymax; ++y) {
            u = (x - xmin) * ufact + cp->umin;
            v = (y - ymin) * vfact + cp->vmin;
            int n = this->divergenceTest(u, v, limit);
            this->colorScheme(n, limit);
            glVertex2d(x, y);
        }
    }
    glEnd();
}

void Mandelbrot::viewChanged(int xmin, int xmax, int ymin, int ymax) {
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
}


void Mandelbrot::trimComplexPlane(int x, int y) {
    double cx, cy;
    ComplexPlane* cp = stack.front();
    cx = (x - xmin) * (cp->umax - cp->umin) / (xmax - xmin) + cp->umin;
    cy = (y - ymin) * (cp->vmax - cp->vmin) / (ymax - ymin) + cp->vmin;

    double dx = (cp->umax - cp->umin) / 16.0;
    double dy = (cp->vmax - cp->vmin) / 16.0;

    ComplexPlane* newCP = new ComplexPlane(cx - dx, cx + dx, cy - dy, cy + dy);
    stack.push_front(newCP);
}

void Mandelbrot::removeLastPlane() {
    if (stack.size() > 1)
        stack.pop_front();
}

void Mandelbrot::removeAllPlanes() {
    while (stack.size() > 1)
        stack.pop_front();
}

