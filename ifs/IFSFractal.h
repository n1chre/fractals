//
// Created by Filip Hrenic on 01/06/16.
//

#ifndef LAB11_2_IFSFRACTAL_H
#define LAB11_2_IFSFRACTAL_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class IFSFractal {

    int points_number;
    int limit;
    int sx, tx;
    int sy, ty;

    class AffineTransform {
        double a, b, c, d, e, f;
        double probability;
    public:
        AffineTransform(double a, double b, double c, double d, double e, double f, double probability)
                : a(a), b(b), c(c), d(d), e(e), f(f), probability(probability) { }

        double getX(double x, double y) { return x * a + y * b + e; }

        double getY(double x, double y) { return x * c + y * d + f; }

        double getProbability() { return probability; };
    };

    vector<AffineTransform*> ats;

    AffineTransform* getForProbability(double);

public:

    IFSFractal(string filepath) {

        double a, b, c, d, e, f, p;
        ifstream file(filepath, fstream::in);
        string str, values;

        while (getline(file, str)) {
            if (str[0] == '#') continue;
            istringstream iss(str);
            iss >> points_number;
            break;
        }

        while (getline(file, str)) {
            if (str[0] == '#') continue;
            istringstream iss(str);
            iss >> limit;
            break;
        }

        while (getline(file, str)) {
            if (str[0] == '#') continue;
            istringstream iss(str);
            iss >> sx >> tx;
            break;
        }

        while (getline(file, str)) {
            if (str[0] == '#') continue;
            istringstream iss(str);
            iss >> sy >> ty;
            break;
        }

        while (getline(file, str)) {
            if (str[0] == '#') continue;
            istringstream iss(str);
            iss >> a >> b >> c >> d >> e >> f >> p;
            AffineTransform* at = new AffineTransform(a, b, c, d, e, f, p);
            ats.push_back(at);
        }
    }


    void render();

};


#endif
