//
// Created by Filip Hrenic on 01/06/16.
//

#ifndef LAB11_2_LSYSTEM_H
#define LAB11_2_LSYSTEM_H

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <iostream>


using namespace std;

class LSystem {

    string actions;

    double delta_angle;
    double pen_factor;
    double segment_factor;

    double x, y, angle, pen_size, segment_size; // for turtle

public:

    LSystem(string filepath) {

        double ANGLE_FACT = M_PI / 180;

        ifstream file(filepath, fstream::in);
        string str;

        getline(file, str);
        istringstream iss2(str);
        int recursion_depth;
        iss2 >> recursion_depth >> delta_angle >> pen_factor >> segment_factor;
        delta_angle *= ANGLE_FACT;

        getline(file, str);
        istringstream iss1(str);

        iss1 >> x >> y >> angle >> pen_size >> segment_size;
        //segment_size *= pow(1.0 / 3, recursion_depth);
        angle *= ANGLE_FACT;


        string alphabet, axiom, rule;
        getline(file, alphabet);
        getline(file, axiom);

        // build actions
        map<char, string> rules;
        while (getline(file, rule)) {
            rules[rule[0]] = rule.substr(2);
        }

        actions = axiom;
        while (recursion_depth--) {
            string buff;
            for (int i = 0; i < actions.size(); ++i) {
                char sign = actions[i];
                if (rules.find(sign) == rules.end())
                    buff += sign;
                else
                    buff += rules[sign];
            }
            actions = buff;
        }
    }

    void render();

};


#endif
