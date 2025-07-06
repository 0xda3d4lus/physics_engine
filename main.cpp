#include <iostream>
#include <vector>
#include "mod/laws.h"
#include "mod/object.h"
using namespace std;

int main(){
    Object a(3, 2,3,{1,5,0}, {1,-2,3});
    Object b(5, 3,6,{1,0,7}, {8,7,1});
    cout << a.get_force_net()[0] << endl;
    cout << a.get_force_net()[1] << endl;
    cout << a.get_force_net()[2] << endl;
    cout << endl;
    return 0;
}