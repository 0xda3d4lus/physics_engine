#include <iostream>
#include <vector>
#include "mod/laws.h"
#include "mod/object.h"
using namespace std;

int main(){
    Object a(3, 2,0,0,{1,0,0}, {1,2,3});
    Object b(5, 3,0,0,{1,0,0}, {8,7,1});
    a.impact(b);
    cout << a.get_position()[0] << endl;
    cout << a.get_position()[1] << endl;
    cout << a.get_position()[2] << endl;
    cout << endl;
    cout << b.get_position()[0] << endl;
    cout << b.get_position()[1] << endl;
    cout << b.get_position()[2] << endl;
    cout << endl;
    cout << vec_norm(vec_sub(a.get_position(), b.get_position()));
    cout << endl;
    return 0;
}