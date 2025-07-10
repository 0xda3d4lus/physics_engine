#include <vector>
#include <iostream>
#include "mod/laws.h"
#include "mod/object.h"
using namespace std;

int main(){
    Object a ("a",2,3,4,{1,2,1}, {2,2,3});
    Object b ("b",3,6,-7,{5,10,2}, {4,2,3});
    vector<Object*> obvec = {&a,&b};
    vector<impact*> impacts;
    runner(obvec, 9.8, {3,2,5.5}, {4,0,0}, 2, 0.01,impacts);

    cout << a.get_position()[0] << endl;
    cout << a.get_position()[1] << endl;
    cout << a.get_position()[2] << endl;
    cout << endl;
    cout << b.get_position()[0] << endl;
    cout << b.get_position()[1] << endl;
    cout << b.get_position()[2] << endl;
    return 0;
}