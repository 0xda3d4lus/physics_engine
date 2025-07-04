#include <cmath>
#include <vector>
#include <math.h>
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