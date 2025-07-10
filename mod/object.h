#include <vector>
#include <string>
using namespace std;
#ifndef OBJECT_H
#define OBJECT_H

class Object{
    private:
        string name;
        long double mass;
        long double radius;
        long double electrical_charge;
        vector<long double> position;
        vector<long double> velocity;
        vector<long double> force_net;
        vector<long double> acceleration;
    public:
        Object(string name, long double mass, long double radius, long double electrical_charge, vector<long double> position, vector<long double> velocity);
        string get_name();
        void set_name(string);
        long double get_mass(void);
        void set_mass(long double);
        long double get_radius(void);
        void set_radius(long double);
        long double get_electrical_charge(void);
        void set_electrical_charge(long double);
        vector<long double> get_position(void);
        void set_position(vector<long double>);
        vector<long double> get_velocity(void);
        void set_velocity(vector<long double>);
        vector<long double> get_acceleration(void);
        void set_acceleration(vector<long double>);
        vector<long double> get_force_net(void);
        void set_force_net(vector<long double>);
        void add_force(vector<long double> force);
        void eval_acceleration(void);
        bool check_impact(Object b);
        void impact(Object &b);
        void move(double time_iteration);
};

#endif