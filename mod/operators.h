#include <vector>
#include "object.h"
using namespace std;

vector<double> vec_sum (vector<double> v1, vector<double> v2);
vector<double> vec_sub (vector<double> v1, vector<double> v2);
vector<double> vec_cross (vector<double> v1, vector<double> v2);
double vec_dot (vector<double> v1, vector<double> v2);
double vec_norm (vector<double> v);
vector<double> vec_unital (vector<double> v);
bool check_impact(Object o1, Object o2);