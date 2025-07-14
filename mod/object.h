#include <vector>
#include <string>
#include <fstream>
using namespace std;
#ifndef OBJECT_H
#define OBJECT_H

class Object{
    private:
        string name;
        double mass;
        double radius;
        double electrical_charge;
        vector<double> position;
        vector<double> velocity;
        vector<double> acceleration;
        vector<double> force_net;
    public:
        Object(string name, double mass, double radius, double electrical_charge, vector<double> position, vector<double> velocity);
        string get_name();
        void set_name(string);
        double get_mass(void);
        void set_mass(double);
        double get_radius(void);
        void set_radius(double);
        double get_electrical_charge(void);
        void set_electrical_charge(double);
        vector<double> get_position(void);
        void set_position(vector<double>);
        vector<double> get_velocity(void);
        void set_velocity(vector<double>);
        vector<double> get_acceleration(void);
        void set_acceleration(vector<double>);
        vector<double> get_force_net(void);
        void set_force_net(vector<double>);
        void add_force(vector<double> force);
        void eval_acceleration(void);
        bool check_impact(Object b);
        void impact(Object &b);
        void move(double time_iteration);
};

#endif