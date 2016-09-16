//
// Created by Filip Hrenic on 01/06/16.
//

#ifndef LAB11_2_TURTLE_H
#define LAB11_2_TURTLE_H


class Turtle {

public:

    double x;
    double y;
    double angle;
    double penSize;
    double segmentSize;

    Turtle(double x, double y, double angle, double penSize, double segmentSize) :
            x(x), y(y), angle(angle), penSize(penSize), segmentSize(segmentSize) { }

    Turtle* copy();

    void move();

    void rotateLeft(double);

    void rotateRight(double);

    void changePenSize(double);

    void changeSegmentSize(double);

};


#endif //
