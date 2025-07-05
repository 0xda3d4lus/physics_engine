#include <cmath>
#include <vector>
#include <math.h>
#include "laws.h"
#include "object.h"
using namespace std;

vector<double> vec_sum (vector<double> v1, vector<double> v2){
    vector<double> res = {  v1[0]+v2[0], 
                            v1[1]+v2[1],
                            v1[2]+v2[2],
                        };
    return res;
}
vector<double> vec_sub (vector<double> v1, vector<double> v2){
    vector<double> res = {  v1[0]-v2[0], 
                            v1[1]-v2[1],
                            v1[2]-v2[2],
                        };
    return res;
}
vector<double> vecnum_mult (double num, vector<double> v){
    return {v[0]*num, v[1]*num, v[2]*num};
}
vector<double> vec_cross (vector<double> v1, vector<double> v2){
    vector<double> res = {  (v1[1]*v2[2])-(v2[1]*v1[2]), 
                            (v2[0]*v1[2])-(v1[0]*v2[2]),
                            (v1[0]*v2[1])-(v2[0]*v1[1]),
                        };
    return res;
}
double vec_dot (vector<double> v1, vector<double> v2){
    double res = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    return res;
}
double vec_norm (vector<double> v){
    double res = sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
    return res;
}
vector<double> vec_unital (vector<double> v){
    double n = vec_norm(v);
    vector<double> res = {v[0]/n,v[1]/n,v[2]/n};
    return res;
}
void gravitational_force_by_field(double gravital_acceleration, Object o){
    vector<double> force = {0,0,-gravital_acceleration*o.get_mass()};
    o.set_force_net(vec_sum(o.get_force_net(), force));
}
void coulombic_force_by_field(vector<double> electrical_field, Object o){
    vector<double> force = {electrical_field[0]*o.get_electrical_charge(), electrical_field[1]*o.get_electrical_charge(), electrical_field[2]*o.get_electrical_charge()};
    o.add_force(force);
}
void magnetical_force_by_field(vector<double> magnetic_field, Object o){
    vector<double> force = vecnum_mult(o.get_electrical_charge(), vec_cross(o.get_velocity(), magnetic_field));
    o.add_force(force);
}
void gravitational_force_by_object_b_to_a(Object a, Object b){
    vector<double> unital_direction = vec_unital(vec_sub(b.get_position(), a.get_position()));
    double size = G * a.get_mass() * b.get_mass() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2);
    a.add_force(vecnum_mult(size, unital_direction));
}
void coulombic_force_by_object_b_to_a(Object a, Object b){
    vector<double> unital_direction = vec_unital(vec_sub(a.get_position(), b.get_position()));
    double size = a.get_electrical_charge() * b.get_electrical_charge() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2) / 4 / PI / E0;
    a.add_force(vecnum_mult(size, unital_direction));
}
void magnetical_force_by_object_b_to_a(Object a, Object b){
    vector<double> dirvec = vec_cross(b.get_velocity(),(vec_unital(vec_sub(a.get_position(), b.get_position()))));
    double factor = MU0 * b.get_electrical_charge() / 4 / PI / vec_norm(vec_sub(a.get_position(), b.get_position()));
    vector<double> field = vecnum_mult(factor, dirvec);
    vector<double> force = vecnum_mult(a.get_electrical_charge(), vec_cross(a.get_velocity(), field));
    a.add_force(force);
}