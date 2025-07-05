#include "object.h"
#include "laws.h"
#include <cmath>
#include <vector>
#include <math.h>

Object::Object(double mass, double raduce, double electrical_charge, double magnetical_charge, vector<double> position, vector<double> velocity){
    this -> mass = mass;
    this -> raduce = raduce;
    this -> electrical_charge = electrical_charge;
    this -> position = position;
    this -> velocity = velocity;
    this -> force_net = {0,0,0};
    this -> acceleration = {0,0,0};
}
double Object::get_mass(){
    return (this -> mass);
}
void Object::set_mass(double nv){
    this -> mass = nv;
    return;
}
double Object::get_raduce(){
    return (this -> raduce);
}
void Object::set_raduce(double nv){
    this -> raduce = nv;
    return;
}
double Object::get_electrical_charge(){
    return (this -> electrical_charge);
}
void Object::set_electrical_charge(double nv){
    this -> electrical_charge = nv;
    return;
}
vector<double> Object::get_position(){
    return (this -> position);
}
void Object::set_position(vector<double> nv){
    this -> position = nv;
}
vector<double> Object::get_velocity(){
    return (this -> velocity);
}
void Object::set_velocity(vector<double> nv){
    this -> velocity = nv;
}
vector<double> Object::get_force_net(){
    return (this -> force_net);
}
void Object::set_force_net(vector<double> nv){
    this -> force_net = nv;
}
void Object::add_force(vector<double> force){
    this -> set_force_net(vec_sum(this -> get_force_net(), force));
}
void Object::eval_acceleration(){
    this -> acceleration = {(this -> get_force_net())[0]/(this -> get_mass()),
                            (this -> get_force_net())[1]/(this -> get_mass()),
                            (this -> get_force_net())[2]/(this -> get_mass()),
                        };
}
bool Object::check_impact (Object b){
    if (vec_norm(vec_sub(this -> get_position(), b.get_position())) < (this -> get_raduce()) + b.get_raduce())
        return true;
    return false;
}
void Object::impact(Object &b){
    double ma = this -> get_mass();
    double mb = b.get_mass();
    vector<double> va1 = this -> get_velocity();
    vector<double> vb1 = b.get_velocity();
    vector<double> va2 = vec_sum(vecnum_mult((ma-mb)/(ma+mb), va1), vecnum_mult((2*mb)/(ma+mb), vb1));
    vector<double> vb2 = vec_sum(vecnum_mult((2*ma)/(ma+mb), va1), vecnum_mult((mb-ma)/(ma+mb), vb1));
    this -> set_velocity(va2);
    b.set_velocity(vb2);
    while((vec_norm(vec_sub(this -> get_position(), b.get_position())))<((this -> get_raduce() + b.get_raduce()))){
        this -> set_position(vec_sum(this -> get_position(), vecnum_mult(.001, vec_unital(va2))));
        b.set_position(vec_sum( b.get_position(), vecnum_mult(.001, vec_unital(vb2))));
    }
}
void Object::move(double time_iteration){
    this -> eval_acceleration();
    this -> set_position(vec_sum(vec_sum(vecnum_mult(pow(time_iteration, 2)*0.5, this -> acceleration), vecnum_mult(time_iteration, this -> get_velocity())), this -> get_position()));
    this -> set_velocity(vec_sum(vecnum_mult(time_iteration, this -> acceleration), this -> get_velocity()));
}