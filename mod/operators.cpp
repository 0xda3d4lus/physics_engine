#include <cmath>
#include <vector>
#include <math.h>
#include "object.h"
using namespace std;

vector<double> vec_sum (vector<double> v1, vector<double> v2){
    vector<double> res = {  v1[0]+v2[0], 
                            v1[1]+v1[1],
                            v1[2]+v2[2],
                        };
    return res;
}
vector<double> vec_sub (vector<double> v1, vector<double> v2){
    vector<double> res = {  v1[0]-v2[0], 
                            v1[1]-v1[1],
                            v1[2]-v2[2],
                        };
    return res;
}
vector<double> vec_cross (vector<double> v1, vector<double> v2){
    vector<double> res = {  v1[1]*v2[2]-v2[1]*v1[2], 
                            v2[0]*v1[2]-v1[0]*v2[0],
                            v1[0]*v2[1]-v2[0]*v1[1],
                        };
    return res;
}
double vec_dot (vector<double> v1, vector<double> v2){
    double res = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    return res;
}
double vec_norm (vector<double> v){
    double res = sqrt(pow(v[0],2.0)+pow(v[1],.0)+pow(v[2],.0));
    return res;
}
vector<double> vec_unital (vector<double> v){
    double n = vec_norm(v);
    vector<double> res = {v[0]/n,v[1]/n,v[2]/n};
    return res;
}
bool check_impact (Object o1, Object o2){
    if (vec_norm(vec_sub(o1.position, o2.position)) <= o1.raduce + o2.raduce)
        return true;
    return false;
}