//
// Created by Filip Hrenic on 01/06/16.
//

#include "Turtle.h"
#include <cmath>

inline double max(double a, double b) {
    return a > b ? a : b;
}

Turtle* Turtle::copy() {
    return new Turtle(x, y, angle, penSize, segmentSize);
}

void Turtle::move() {
    x += segmentSize * cos(angle);
    y += segmentSize * sin(angle);
}

void Turtle::rotateLeft(double angle) {
    this->angle -= angle;
}

void Turtle::rotateRight(double angle) {
    this->angle += angle;
}

void Turtle::changePenSize(double factor) {
    penSize = max(1, penSize * factor);
}

void Turtle::changeSegmentSize(double factor) {
    segmentSize = max(1, segmentSize * factor);
}



