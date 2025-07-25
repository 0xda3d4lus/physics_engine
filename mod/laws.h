#include <type_traits>
#include <vector>
#include <fstream>
#include "object.h"
using namespace std;

// constants
const double PI = 3.1415926535;
const double G = 6.67428e-11;
const double E0 = 8.85418781e-12;
const double MU0 = PI * 4e-7;

// vector operators
vector<double> vec_sum (vector<double> v1, vector<double> v2);
vector<double> vec_sub (vector<double> v1, vector<double> v2);
vector<double> vec_cross (vector<double> v1, vector<double> v2);
vector<double> vecnum_mult (double num, vector<double> v);
double vec_dot (vector<double> v1, vector<double> v2);
double vec_norm (vector<double> v);
vector<double> vec_unital (vector<double> v);

// physical principles
void gravitational_force_by_field(double gravitational_acceleration, Object &o);
void coulombic_force_by_field(vector<double> electrical_field, Object &o);
void magnetical_force_by_field(vector<double> magnetic_field, Object &o);
void gravitational_force_by_object_b_to_a(Object &a, Object &b);
void coulombic_force_by_object_b_to_a(Object &a, Object &b);
void magnetical_force_by_object_b_to_a(Object &a, Object &b);

// program cycle
typedef struct{Object *o1 ; Object *o2 ; double time;} impact;
void eval_force_net_field(vector<Object*> &object_vector, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field);
void eval_force_net_objects(vector<Object*> &object_vector);
void obj_print(Object o);
void obj_copy(Object *a, Object *b);
double runner(vector<Object*> &object_vector, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field, double time, double time_iteration, vector<impact*> &impacts);
void obj_serialize(ofstream &out, Object o);
void obj_deserialize(ifstream &in, Object *o);
void serialize(ofstream &out, vector<Object*> &object_vector,int objects_amount, double gravitational_acceleration, vector<double> electrical_field, vector<double> magnetic_field);
void deserialize(ifstream &in, vector<Object*> &object_vector, int &objects_amount, double &gravitational_acceleration, vector<double> &electrical_field, vector<double> &magnetic_field);