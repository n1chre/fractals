//
// Created by Filip Hrenic on 01/06/16.
//

#include <GLUT/glut.h>
#include <cstdlib>
#include "IFSFractal.h"

// returns number from [0,1] interval
inline double drand() {
    return 1.0 * (rand() % RAND_MAX) / (RAND_MAX - 1);
}

void IFSFractal::render() {

    double x, y;

    glPointSize(1.0);
    glColor3f(0.0, 0.7, 0.3);
    glBegin(GL_POINTS);
    for (int point = 0; point < points_number; ++point) {
        x = 0;
        y = 0;

        for (int iter = 0; iter < limit; ++iter) {
            AffineTransform* at = getForProbability(drand());
            double x_ = at->getX(x, y);
            double y_ = at->getY(x, y);
            x = x_;
            y = y_;
        }

        x = x * sx + tx;
        y = y * sy + ty;
        glVertex2d(x, y);
    }
    glEnd();

}


IFSFractal::AffineTransform* IFSFractal::getForProbability(double p) {
    double p_lo = 0.0;
    for (AffineTransform* at : ats) {
        double atp = at->getProbability();
        if (p_lo <= p && p < p_lo + atp)
            return at;
        p_lo += atp;
    }
}

