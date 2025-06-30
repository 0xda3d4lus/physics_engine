#include "object.h"
#include <vector>

Object::Object(double mass, double raduce, double electrical_charge, double magnetical_charge, vector<double> position, vector<double> velocity){
    this -> mass = mass;
    this -> raduce = raduce;
    this -> electrical_charge = electrical_charge;
    this -> magnetical_charge = magnetical_charge;
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
double Object::get_magnetical_charge(){
    return (this -> magnetical_charge);
}
void Object::set_magnetical_charge(double nv){
    this -> magnetical_charge = nv;
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
void Object::eval_acceleration(){
    this -> acceleration = {(this -> get_force_net())[0]/(this -> get_mass()),
                            (this -> get_force_net())[1]/(this -> get_mass()),
                            (this -> get_force_net())[2]/(this -> get_mass()),
                        };
}