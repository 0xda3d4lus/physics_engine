#include <type_traits>
#include <vector>
#include "object.h"
using namespace std;

// constants
const long double PI = 3.1415926535;
const long double G = 6.67428e-11;
const long double E0 = 8.85418781e-12;
const long double MU0 = PI * 4e-7;

// vector operators
vector<long double> vec_sum (vector<long double> v1, vector<long double> v2);
vector<long double> vec_sub (vector<long double> v1, vector<long double> v2);
vector<long double> vec_cross (vector<long double> v1, vector<long double> v2);
vector<long double> vecnum_mult (long double num, vector<long double> v);
long double vec_dot (vector<long double> v1, vector<long double> v2);
long double vec_norm (vector<long double> v);
vector<long double> vec_unital (vector<long double> v);

// physical principles
void gravitational_force_by_field(long double gravitational_acceleration, Object &o);
void coulombic_force_by_field(vector<long double> electrical_field, Object &o);
void magnetical_force_by_field(vector<long double> magnetic_field, Object &o);
void gravitational_force_by_object_b_to_a(Object &a, Object &b);
void coulombic_force_by_object_b_to_a(Object &a, Object &b);
void magnetical_force_by_object_b_to_a(Object &a, Object &b);

// program cycle
void eval_force_net_field(vector<Object*> &object_vector, long double gravitational_acceleration, vector<long double> electrical_field, vector<long double> magnetic_field);
void eval_force_net_objects(vector<Object*> &object_vector);
double runner(vector<Object*> &object_vector, long double gravitational_acceleration, vector<long double> electrical_field, vector<long double> magnetic_field, double time, double time_iteration);