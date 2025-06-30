#include <vector>
using namespace std;
#ifndef OBJECT_H
#define OBJECT_H

class Object{
    private:
        double mass;
        double raduce;
        double electrical_charge;
        double magnetical_charge;
        vector<double> position;
        vector<double> velocity;
        vector<double> force_net;
        vector<double> acceleration;
    public:
        Object(double mass, double raduce, double electrical_charge, double magnetical_charge, vector<double> position, vector<double> velocity);
        double get_mass(void);
        void set_mass(double);
        double get_raduce(void);
        void set_raduce(double);
        double get_electrical_charge(void);
        void set_electrical_charge(double);
        double get_magnetical_charge(void);
        void set_magnetical_charge(double);
        vector<double> get_position(void);
        void set_position(vector<double>);
        vector<double> get_velocity(void);
        void set_velocity(vector<double>);
        vector<double> get_force_net(void);
        void set_force_net(vector<double>);
        void eval_acceleration(void);
};

#endif