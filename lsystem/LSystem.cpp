//
// Created by Filip Hrenic on 01/06/16.
//

#include "LSystem.h"
#include "Turtle.h"
#include <GLUT/glut.h>
#include <list>

using namespace std;

void LSystem::render() {

    Turtle* turtle = new Turtle(x, y, angle, pen_size, segment_size);
    list<Turtle*> turtleStack;

    glColor3ub(124, 24, 199);
    glPointSize(1);

    for (int i = 0; i < actions.size(); ++i) {
        switch (actions[i]) {
            case 'F':
                glLineWidth((float) turtle->penSize);
                glBegin(GL_LINE_STRIP);
                glVertex2d(turtle->x, turtle->y);
                turtle->move();
                glVertex2d(turtle->x, turtle->y);
                glEnd();
                break;
            case '+':
                turtle->rotateRight(delta_angle);
                break;
            case '-':
                turtle->rotateLeft(delta_angle);
                break;
            case 's':
                turtle->changeSegmentSize(segment_factor);
                break;
            case 'w':
                turtle->changePenSize(pen_factor);
                break;
            case '[':
                turtleStack.push_front(turtle->copy());
                break;
            case ']':
                delete turtle;
                turtle = turtleStack.front();
                turtleStack.pop_front();
                break;
            default:
                break;
        }

    }

    delete turtle;
}