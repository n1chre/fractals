//
// Created by Filip Hrenic on 01/06/16.
//

#ifndef LAB11_MANDELBROT_H
#define LAB11_MANDELBROT_H

#include <list>

using namespace std;


typedef int (* DivFunc)(double, double, int);

typedef void (* ColorScheme)(int, int);

class Mandelbrot {
    int xmin, xmax, ymin, ymax;
    int limit;

    DivFunc divergenceTest;
    ColorScheme colorScheme;

    class ComplexPlane {
    public:
        double umin, umax;
        double vmin, vmax;


        ComplexPlane(double umin, double umax, double vmin, double vmax)
                : umin(umin), umax(umax), vmin(vmin), vmax(vmax) { }
    };

    list<ComplexPlane*> stack;

public:


    Mandelbrot(int xmin, int xmax, int ymin, int ymax,
               double umin, double umax, double vmin, double vmax,
               int limit, const DivFunc divergenceTest, const ColorScheme colorScheme)
            : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax),
              limit(limit), divergenceTest(divergenceTest), colorScheme(colorScheme) {

        ComplexPlane* cp = new ComplexPlane(umin, umax, vmin, vmax);
        stack.push_front(cp);
    }

    void setDivergenceTest(const DivFunc divergenceTest) {
        this->divergenceTest = divergenceTest;
    }

    void setColorScheme(const ColorScheme colorScheme) {
        this->colorScheme = colorScheme;
    }

    void trimComplexPlane(int, int);

    void removeLastPlane();

    void removeAllPlanes();

    void viewChanged(int xmin, int xmax, int ymin, int ymax);

    void render();
};


#endif //LAB11_MANDELBROT_H
