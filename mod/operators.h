#include <vector>
#include "object.h"
using namespace std;

vector<double> sum (vector<double> v1, vector<double> v2);
vector<double> sub (vector<double> v1, vector<double> v2);
vector<double> cross (vector<double> v1, vector<double> v2);
double dot (vector<double> v1, vector<double> v2);
double norm (vector<double> v);
vector<double> unital (vector<double> v);
bool check_impact(Object o1, Object o2);