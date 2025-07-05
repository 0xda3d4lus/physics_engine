#include <iostream>
#include <vector>
#include "mod/laws.h"
#include "mod/object.h"
using namespace std;

int main(){
    Object a(3, 2,0,0,{1,0,0}, {1,-2,3});
    Object b(5, 3,0,0,{1,0,0}, {8,7,1});
    while (true) {
        a.move(0.01);
        cout << a.get_position()[0] << endl;
        cout << a.get_position()[1] << endl;
        cout << a.get_position()[2] << endl;
        cout << endl;
    }
        return 0;
}