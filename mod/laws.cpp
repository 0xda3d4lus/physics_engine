#include <cmath>
#include <vector>
#include <math.h>
#include "laws.h"
#include "object.h"
using namespace std;

vector<long double> vec_sum (vector<long double> v1, vector<long double> v2){
    vector<long double> res = {  v1[0]+v2[0], 
                            v1[1]+v2[1],
                            v1[2]+v2[2],
                        };
    return res;
}
vector<long double> vec_sub (vector<long double> v1, vector<long double> v2){
    vector<long double> res = {  v1[0]-v2[0], 
                            v1[1]-v2[1],
                            v1[2]-v2[2],
                        };
    return res;
}
vector<long double> vecnum_mult (long double num, vector<long double> v){
    return {v[0]*num, v[1]*num, v[2]*num};
}
vector<long double> vec_cross (vector<long double> v1, vector<long double> v2){
    vector<long double> res = {  (v1[1]*v2[2])-(v2[1]*v1[2]), 
                            (v2[0]*v1[2])-(v1[0]*v2[2]),
                            (v1[0]*v2[1])-(v2[0]*v1[1]),
                        };
    return res;
}
long double vec_dot (vector<long double> v1, vector<long double> v2){
    long double res = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    return res;
}
long double vec_norm (vector<long double> v){
    long double res = sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
    return res;
}
vector<long double> vec_unital (vector<long double> v){
    long double n = vec_norm(v);
    vector<long double> res = {v[0]/n,v[1]/n,v[2]/n};
    return res;
}
void gravitational_force_by_field(long double gravitational_acceleration, Object &o){
    vector<long double> force = {0,0,-gravitational_acceleration*o.get_mass()};
    o.add_force(force);
}
void coulombic_force_by_field(vector<long double> electrical_field, Object &o){
    vector<long double> force = {electrical_field[0]*o.get_electrical_charge(), electrical_field[1]*o.get_electrical_charge(), electrical_field[2]*o.get_electrical_charge()};
    o.add_force(force);
}
void magnetical_force_by_field(vector<long double> magnetic_field, Object &o){
    vector<long double> force = vecnum_mult(o.get_electrical_charge(), vec_cross(o.get_velocity(), magnetic_field));
    o.add_force(force);
}
void gravitational_force_by_object_b_to_a(Object &a, Object &b){
    vector<long double> unital_direction = vec_unital(vec_sub(b.get_position(), a.get_position()));
    long double size = G * a.get_mass() * b.get_mass() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2);
    a.add_force(vecnum_mult(size, unital_direction));
}
void coulombic_force_by_object_b_to_a(Object &a, Object &b){
    vector<long double> unital_direction = vec_unital(vec_sub(a.get_position(), b.get_position()));
    long double size = a.get_electrical_charge() * b.get_electrical_charge() / pow(vec_norm(vec_sub(b.get_position(), a.get_position())), 2) / 4 / PI / E0;
    a.add_force(vecnum_mult(size, unital_direction));
}
void magnetical_force_by_object_b_to_a(Object &a, Object &b){
    vector<long double> dirvec = vec_cross(b.get_velocity(),(vec_unital(vec_sub(a.get_position(), b.get_position()))));
    long double factor = MU0 * b.get_electrical_charge() / 4 / PI / pow(vec_norm(vec_sub(a.get_position(), b.get_position())), 2);
    vector<long double> field = vecnum_mult(factor, dirvec);
    vector<long double> force = vecnum_mult(a.get_electrical_charge(), vec_cross(a.get_velocity(), field));
    a.add_force(force);
}
void eval_force_net_field(vector<Object*> &object_vector, long double gravitational_acceleration, vector<long double> electrical_field, vector<long double> magnetic_field){
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
void obj_copy(Object *from, Object *to){
    to -> set_mass(from->get_mass());
    to -> set_radius(from->get_radius());
    to -> set_electrical_charge(from->get_electrical_charge());
    to -> set_position(from->get_position());
    to -> set_velocity(from->get_velocity());
    to -> set_acceleration(from->get_acceleration());
    to -> set_force_net(from->get_force_net());
}
double runner(vector<Object*> &object_vector, long double gravitational_acceleration, vector<long double> electrical_field, vector<long double> magnetic_field, double time, double time_iteration, vector<impact*> &impacts){
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