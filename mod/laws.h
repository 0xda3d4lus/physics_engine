#include <type_traits>
#include <vector>
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
void gravitational_force_by_field(double gravital_acceleration, Object o);
void coulombic_force_by_field(vector<double> electrical_field, Object o);
void magnetical_force_by_field(vector<double> magnetic_field, Object o);
void gravitational_force_by_object_b_to_a(Object a, Object b);
void coulombic_force_by_object_b_to_a(Object a, Object b);
void magnetical_force_by_object_b_to_a(Object a, Object b);