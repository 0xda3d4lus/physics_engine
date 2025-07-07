#include <vector>
using namespace std;
#ifndef OBJECT_H
#define OBJECT_H

class Object{
    private:
        long double mass;
        long double raduce;
        long double electrical_charge;
        vector<long double> position;
        vector<long double> velocity;
        vector<long double> force_net;
        vector<long double> acceleration;
    public:
        Object(long double mass, long double raduce, long double electrical_charge, vector<long double> position, vector<long double> velocity);
        long double get_mass(void);
        void set_mass(long double);
        long double get_raduce(void);
        void set_raduce(long double);
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