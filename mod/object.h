#include <vector>
using namespace std;

class Object{
    public:
        double mass;
        double raduce;
        double electrical_charge;
        double magnetical_charge;
        vector<double> position[3];
        vector<double> velocity[3];
        vector<double> force_net[3];
};