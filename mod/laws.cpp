#include <cmath>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
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
void gravitational_force_by_field(double gravitational_acceleration, Object &o){
    vector<double> force = {0,0,-gravitational_acceleration*o.get_mass()};
    o.add_force(force);
}
void coulombic_force_by_field(vector<double> electrical_field, Object &o){
    vector<double> force = {electrical_field[0]*o.get_electrical_charge(), electrical_field[1]*o.get_electrical_charge(), electrical_field[2]*o.get_electrical_charge()};
    o.add_force(force);
}
void magnetical_force_by_field(vector<double> magnetic_field, Object &o){
    vector<double> force = vecnum_mult(o.get_electrical_charge(), vec_cross(o.get_velocity(), magnetic_field));
    o.add_force(force);
}
void gravitational_force_by_object_b_to_a(Object &a, Object &b){
    vector<double> unital_direction = vec_unital(vec_sub(b.get_position(), a.get_position()));
    double size = G * a.get_mass() * b.get_mass() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2);
    a.add_force(vecnum_mult(size, unital_direction));
}
void coulombic_force_by_object_b_to_a(Object &a, Object &b){
    vector<double> unital_direction = vec_unital(vec_sub(a.get_position(), b.get_position()));
    double size = a.get_electrical_charge() * b.get_electrical_charge() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2) / 4 / PI / E0;
    a.add_force(vecnum_mult(size, unital_direction));
}
void magnetical_force_by_object_b_to_a(Object &a, Object &b){
    vector<double> dirvec = vec_cross(b.get_velocity(),(vec_unital(vec_sub(a.get_position(), b.get_position()))));
    double factor = MU0 * b.get_electrical_charge() / 4 / PI / pow(vec_norm(vec_sub(a.get_position(), b.get_position())), 2);
    vector<double> field = vecnum_mult(factor, dirvec);
    vector<double> force = vecnum_mult(a.get_electrical_charge(), vec_cross(a.get_velocity(), field));
    a.add_force(force);
}
void eval_force_net_field(vector<Object*> &object_vector, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field){
    int size = object_vector.size();
    for (int i = 0; i < size; i++){
        gravitational_force_by_field(gravitational_acceleration, *(object_vector.at(i)));
        coulombic_force_by_field(electrical_field, *(object_vector.at(i)));
        magnetical_force_by_field(magnetic_field, *(object_vector.at(i)));
    }
}
void eval_force_net_objects(vector<Object*> &object_vector){
    int size = object_vector.size();
    for (int i = 0; i < size ; i++){
        for (int j = 0; j < size ; j++) {
            if (&object_vector[i] == &object_vector[j]) continue;
            gravitational_force_by_object_b_to_a(*(object_vector.at(i)), *(object_vector.at(j)));
            coulombic_force_by_object_b_to_a(*(object_vector.at(i)), *(object_vector.at(j)));
            magnetical_force_by_object_b_to_a(*(object_vector.at(i)), *(object_vector.at(j)));
        }
    }
}
void obj_print(Object o){
    cout << "name: " << o.get_name() << endl;
    cout << "mass: " << o.get_mass() << endl;
    cout << "radius: " << o.get_radius() << endl;
    cout << "electrical charge: " << o.get_electrical_charge() << endl;
    cout << "position: (" << o.get_position()[0] << " , " << o.get_position()[1] << " , " << o.get_position()[2] << ")" << endl;
    cout << "velocity: (" << o.get_velocity()[0] << " , " << o.get_velocity()[1] << " , " << o.get_velocity()[2] << ")" << endl;
}
void obj_copy(Object *from, Object *to){
    to -> set_mass(from->get_mass());
    to -> set_radius(from->get_radius());
    to -> set_electrical_charge(from->get_electrical_charge());
    to -> set_position(from->get_position());
    to -> set_velocity(from->get_velocity());
    to -> set_acceleration(from->get_acceleration());
    to -> set_force_net(from->get_force_net());
}
double runner(vector<Object*> &object_vector, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field, double time, double time_iteration, vector<impact*> &impacts){
    double time_passed = 0;
    int objects_amount = object_vector.size();
    eval_force_net_field(object_vector, gravitational_acceleration, electrical_field, magnetic_field);
    eval_force_net_objects(object_vector);
    for (int i = 0; i < int(time/time_iteration); i++){
        time_passed += time_iteration;
        for (int j = 0; j < objects_amount; j++){
            Object *obj_ptr = object_vector.at(j);
            obj_ptr -> move(time_iteration);
        }
        for (int j = 0; j < objects_amount; j++){
            for (int k = 0; k < objects_amount; k++){
                if (object_vector.at(j) == object_vector.at(k)) continue;
                if (object_vector.at(j) -> check_impact(*(object_vector.at(k)))){
                    object_vector.at(j) -> impact(*(object_vector.at(k)));
                    impact *imp = new impact;
                    (imp -> o1) = object_vector.at(j);
                    (imp -> o2) = object_vector.at(k);
                    (imp -> time) = time_passed;
                    impacts.push_back(imp);
                }
            }
        }
        for (int j = 0; j < objects_amount; j++) object_vector.at(j) -> set_force_net({0, 0 ,0});
        eval_force_net_field(object_vector, gravitational_acceleration,electrical_field, magnetic_field);
        eval_force_net_objects(object_vector);
    }
    return time_passed;
}
void obj_serialize(ofstream &out, Object o){
    size_t name_length = o.get_name().size();
    double mass = o.get_mass();
    double radius = o.get_radius();
    double electrical_charge = o.get_electrical_charge();

    double position_x = o.get_position()[0];
    double position_y = o.get_position()[1];
    double position_z = o.get_position()[2];   

    double velocity_x = o.get_velocity()[0];
    double velocity_y = o.get_velocity()[1];
    double velocity_z = o.get_velocity()[2];

    out.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
    out.write(o.get_name().c_str(), name_length);
    out.write(reinterpret_cast<const char*>(&mass), sizeof(mass));
    out.write(reinterpret_cast<const char*>(&radius), sizeof(radius));
    out.write(reinterpret_cast<const char*>(&electrical_charge), sizeof(electrical_charge));

    out.write(reinterpret_cast<const char*>(&position_x), sizeof(position_x));
    out.write(reinterpret_cast<const char*>(&position_y), sizeof(position_y));
    out.write(reinterpret_cast<const char*>(&position_z), sizeof(position_z));

    out.write(reinterpret_cast<const char*>(&velocity_x), sizeof(velocity_x));
    out.write(reinterpret_cast<const char*>(&velocity_y), sizeof(velocity_y));
    out.write(reinterpret_cast<const char*>(&velocity_z), sizeof(velocity_z));
}
void obj_deserialize(ifstream &in, Object* o){
    size_t name_length;
    string name;

    double mass ;
    double radius;
    double electrical_charge;

    double position_x;
    double position_y;
    double position_z;   

    double velocity_x;
    double velocity_y;
    double velocity_z;

    in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
    name.resize(name_length);
    in.read(&name[0], name_length);
    in.read(reinterpret_cast<char*>(&mass), sizeof(mass));
    in.read(reinterpret_cast<char*>(&radius), sizeof(radius));
    in.read(reinterpret_cast<char*>(&electrical_charge), sizeof(electrical_charge));

    in.read(reinterpret_cast<char*>(&position_x), sizeof(position_x));
    in.read(reinterpret_cast<char*>(&position_y), sizeof(position_y));
    in.read(reinterpret_cast<char*>(&position_z), sizeof(position_z));

    in.read(reinterpret_cast<char*>(&velocity_x), sizeof(velocity_x));
    in.read(reinterpret_cast<char*>(&velocity_y), sizeof(velocity_y));
    in.read(reinterpret_cast<char*>(&velocity_z), sizeof(velocity_z));
    
    o -> set_name(name);
    o -> set_mass(mass);
    o -> set_radius(radius);
    o -> set_electrical_charge(electrical_charge);
    o -> set_position({position_x, position_y, position_z});
    o -> set_velocity({velocity_x, velocity_y, velocity_z});
}
void serialize(ofstream &out, vector<Object*> &object_vector, int objects_amount, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field){
    double electrical_field_x = electrical_field[0];
    double electrical_field_y = electrical_field[1];
    double electrical_field_z = electrical_field[2];

    double magnetic_field_x = magnetic_field[0];
    double magnetic_field_y = magnetic_field[1];
    double magnetic_field_z = magnetic_field[2];

    out.write(reinterpret_cast<const char*>(&gravitational_acceleration), sizeof(gravitational_acceleration));

    out.write(reinterpret_cast<const char*>(&electrical_field_x), sizeof(electrical_field_x));
    out.write(reinterpret_cast<const char*>(&electrical_field_y), sizeof(electrical_field_y));
    out.write(reinterpret_cast<const char*>(&electrical_field_z), sizeof(electrical_field_z));

    out.write(reinterpret_cast<const char*>(&magnetic_field_x), sizeof(magnetic_field_x));
    out.write(reinterpret_cast<const char*>(&magnetic_field_y), sizeof(magnetic_field_y));
    out.write(reinterpret_cast<const char*>(&magnetic_field_z), sizeof(magnetic_field_z));

    out.write(reinterpret_cast<const char*>(&objects_amount), sizeof(objects_amount));
    for (int i = 0; i < objects_amount; i++) obj_serialize(out, *(object_vector.at(i)));
}
void deserialize(ifstream &in, vector<Object*> &object_vector, double &gravitational_acceleration, vector<double> &electrical_field, vector<double> &magnetic_field){
    double electrical_field_x;
    double electrical_field_y;
    double electrical_field_z;   

    double magnetic_field_x;
    double magnetic_field_y;
    double magnetic_field_z;

    int objects_amount;

    in.read(reinterpret_cast<char*>(&gravitational_acceleration), sizeof(gravitational_acceleration));

    in.read(reinterpret_cast<char*>(&electrical_field_x), sizeof(electrical_field_x));
    in.read(reinterpret_cast<char*>(&electrical_field_y), sizeof(electrical_field_y));
    in.read(reinterpret_cast<char*>(&electrical_field_z), sizeof(electrical_field_z));

    in.read(reinterpret_cast<char*>(&magnetic_field_x), sizeof(magnetic_field_x));
    in.read(reinterpret_cast<char*>(&magnetic_field_y), sizeof(magnetic_field_y));
    in.read(reinterpret_cast<char*>(&magnetic_field_z), sizeof(magnetic_field_z));

    electrical_field = {electrical_field_x, electrical_field_y, electrical_field_z};
    magnetic_field = {magnetic_field_x, magnetic_field_y, magnetic_field_z};

    in.read(reinterpret_cast<char*>(&objects_amount), sizeof(objects_amount));
    for (int i = 0; i < objects_amount; i++) {
        Object *obj = new Object("", 0,0,0,{},{});
        obj_deserialize(in , obj);
        object_vector.push_back(obj);
    }
}