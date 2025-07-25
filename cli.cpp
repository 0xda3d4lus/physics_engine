#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <fmt/core.h>
#include <yaml-cpp/yaml.h>
#include "mod/laws.h"
#include "mod/object.h"
#include "yaml-cpp/emittermanip.h"
using namespace std;

#define ansireset "\e[0m"
#define ansired "\e[31m"
#define ansigreen "\e[32m"
#define ansiyellow "\e[33m"
#define ansiblue "\e[34m"
#define ansimagenta "\e[35m"
#define ansicyan "\e[36m"

#define ansicursorhome "\e[H"
#define ansiclear "\e[2J"
#define ansibold "\e[1m"
#define ansifaint "\e[2m"
#define ansiitalic "\e[3m"
#define ansiunderlined "\e[4m"


void print_objects(vector<Object*> objects){
    for (int i = 0; i < int(objects.size()); i++){
        Object obj = *objects.at(i);
        cout << ansimagenta << "OBJECT: " << obj.get_name() << "    " << "m = " << obj.get_mass() << "kg , " << "r = " << obj.get_radius() << "m , " << "q = " << obj.get_electrical_charge()*1e+6 << "μC"<< ansireset << endl;
        cout << ansiyellow;
        cout << "position:" << ansireset << "        " << "(" << obj.get_position()[0]  << " , " << obj.get_position()[1] << " , " << obj.get_position()[2] << ")" << endl;
        cout << ansiyellow;
        cout << "velocity:" << ansireset << "        " << "(" << obj.get_velocity()[0]  << " , " << obj.get_velocity()[1] << " , " << obj.get_velocity()[2] << ")" << endl;
        cout << ansiyellow;
        cout << "acceleration:" << ansireset << "    "  << "(" << obj.get_acceleration()[0]  << " , " << obj.get_acceleration()[1] << " , " << obj.get_acceleration()[2] << ")" << endl;
        cout << endl<< endl;
    }
}
bool is_double(const std::string& s) {
    istringstream iss(s);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}
string generate_unique_filename(const std::string& baseName = "file", const std::string& extension = "txt") {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y%m%d_%H%M%S");
    int randomNumber = std::rand() % 1000;
    std::ostringstream filename;
    filename << baseName << "_" << timestamp.str() << "_" << randomNumber << "." << extension;
    return filename.str();
}

int main(){
    double gravitational_acceleration = 0;
    vector<double> electrical_field = {0,0,0};
    vector<double> magnetic_field = {0,0,0};
    vector<Object*> objects ;
    vector<Object*> objects_cpy ;
    int objects_amount = 0;

    cout << ansiclear << ansicursorhome;
    cout << ansiyellow;
    cout << "       _               _                             _            \n _ __ | |__  _   _ ___(_) ___ ___    ___ _ __   __ _(_)_ __   ___ \n| '_ \\| '_ \\| | | / __| |/ __/ __|  / _ \\ '_ \\ / _` | | '_ \\ / _ \\\n| |_) | | | | |_| \\__ \\ | (__\\__ \\ |  __/ | | | (_| | | | | |  __/\n| .__/|_| |_|\\__, |___/_|\\___|___/  \\___|_| |_|\\__, |_|_| |_|\\___|\n|_|          |___/                             |___/              " << endl;
    cout << "Welcome to physics engine!" << endl << endl << endl;
    cout << ansireset;

    cout << ansiblue <<"Enter f if you want to use a *.dat file as input data or enter m for manual input (q for quit)." << endl << ansigreen << "if you choose manual input, a *.dat file will be generated in current working directory which you can use in your further runs." << ansireset << endl;
    while (1) {
        cout << "~> ";
        bool start_run = 0;
        string input ;
        getline(cin , input);
        if (input == "f"){
            cout << ansiblue << "Enter file path:" << ansireset << endl;
            string path;
            regex path_regex(R"(^([a-zA-Z]:)?(\/|\\)?([^<>:"|?*\r\n]+(\/|\\)?)*[^<>:"|?*\r\n]*$)");
            while (1) {
                cout << "~> ";
                getline(cin , path);
                ifstream f(path);
                if (regex_match(input, path_regex) && f.good()){
                    cout  << ansired << "deserializing ..." << ansireset;
                    deserialize(f, objects, objects_amount, gravitational_acceleration, electrical_field, magnetic_field);
                    for (int i = 0; i < objects_amount; i++) {
                        Object* obj = new Object("", 0, 0, 0, {}, {});
                        obj_copy(objects[i], obj);
                        objects_cpy.push_back(obj);
                    }
                    f.close();
                    start_run = 1;
                    break;
                }
                else {
                    cout << ansired << "Unable to read file. Please enter a valid file path:"<< ansireset << endl;
                }
            }
        }else if (input == "m"){
            cout << ansigreen;
            cout << "Please enter thease properties about field." << endl;
            cout <<ansiblue << "Enter gravitational acceleration(g) : (m/(s^2))"  << ansireset<< endl;
            cout << "~> ";
            while (!(cin >> gravitational_acceleration)) {
                cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";        cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << ansiblue<<"Enter electrical field (format: x then y then z): (V/m)" << ansireset << endl;
            for (int i = 0; i<3; i++) {
                cout << "~> ";
                while (!(cin >> electrical_field[i])) {
                    cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cout <<ansiblue << "Enter magnetic field (format: x then y then z): (T)" << ansireset << endl;
            for (int i = 0; i<3; i++) {
                cout << "~> ";
                while (!(cin >> magnetic_field[i])) {
                    cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cout << ansigreen;
            cout << endl << "Please enter thease properties about objects." << endl;
            cout << ansireset;
            cout <<ansiblue << "Enter amount of objects:" <<ansireset << endl;
            cout << "~> ";
            while (!(cin >> objects_amount)) {
                cout << ansired << "Invalid input. Please enter an integer value:"<< ansireset << endl << "~> ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            for (int j = 1; j <= objects_amount; j++) {
                string name = "";
                cout << ansiblue << "Enter a name for object number " << j << ":" << ansireset <<endl;
                cin >> name;
                cin.clear();
                cin.ignore(10000, '\n');
                double mass = 0;
                cout << ansiblue <<"Enter it's mass: (kg)" <<ansireset << endl;
                cout << "~> ";
                while (!(cin >> mass) || mass <= 0) {
                    cout << ansired << "Invalid input. Please enter a positive numeric value:"<< ansireset << endl << "~> ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                double radius = 0;
                cout << ansiblue <<"Enter it's radius: (m)" <<ansireset << endl;
                cout << "~> ";
                while (!(cin >> radius) || radius <= 0) {
                    cout << ansired << "Invalid input. Please enter a positive numeric value:"<< ansireset << endl << "~> ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                double electrical_charge = 0;
                cout << ansiblue <<"Enter it's electrical charge: (μC - micro coulomb)" <<ansireset << endl;
                cout << "~> ";
                while (!(cin >> electrical_charge)) {
                    cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                vector<double> initial_position = {0,0,0};
                cout << ansiblue << "Enter it's initial position (format: x then y then z): (m)" <<ansireset << endl;
                for (int i = 0; i<3; i++) {
                    cout << "~> ";
                    while (!(cin >> initial_position[i])) {
                        cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                vector<double> initial_velocity = {0,0,0};
                cout << ansiblue << "Enter it's initial velocity (format: x then y then z): (m/s)" << ansireset << endl;
                for (int i = 0; i<3; i++) {
                    cout << "~> ";
                    while (!(cin >> initial_velocity[i])) {
                        cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                Object *obj_ptr = new Object(name, mass, radius, electrical_charge * 1e-6, initial_position, initial_velocity);
                Object *obj_ptr_cpy = new Object(name, mass, radius, electrical_charge * 1e-6, initial_position, initial_velocity);
                objects.push_back(obj_ptr);
                objects_cpy.push_back(obj_ptr_cpy);
                start_run = 1;
                cout << ansiblue << "Do you want to have input data you just entered as a file ? (y/N)" << ansireset << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string inp;
                getline(cin, inp);
                if (inp == "y"){
                    string file_name = generate_unique_filename("PH_idata", "dat");
                    ofstream f(file_name, ios::binary);
                    serialize(f, objects, objects_amount, gravitational_acceleration,electrical_field,  magnetic_field);
                    f.close();
                }
            }
            }else if (input == "q"){
            cout << ansired << "quiting ..." << ansireset << endl;
            return 0;
        }
        else{
            cout <<ansired << "Invalid input. Please enter f, m or q:" << ansireset << endl;
        }
        if (start_run) break;
    }

    cout << ansiblue << endl << "Enter time iteration (evaluate forces each t seconds)" << ansireset << endl;
    cout << "~> ";
    double time_iteration = 0.01;
    while (!(cin >> time_iteration)) {
        cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl << "~> ";        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    double t = 0;
    while(1){
        cout << ansiclear << ansicursorhome << endl;
        vector<impact*> impacts;
        double passedt = runner(objects,gravitational_acceleration, electrical_field, magnetic_field,t,time_iteration,impacts);
        for (int i = 0; i < objects_amount; i++){
            objects[i] -> eval_acceleration();
        }
        cout << ansimagenta<< "FIELD:" << "    "  << "g = " << gravitational_acceleration << " (m/s^2)" << "    "<< "E = (" << electrical_field[0]  << " , " << electrical_field[1] << " , " << electrical_field[2] << ")(V/m)    " << "B = (" << magnetic_field[0]  << " , " << magnetic_field[1] << " , " << magnetic_field[2] << ")(T)" <<endl << endl;

        print_objects(objects);
        cout << ansimagenta <<  "moment: t = " << passedt << ansireset << endl;
        if (impacts.size()){
            for (int i =0; i < int(impacts.size()); i++) {
                cout << ansired << "object " << (impacts.at(i) -> o1) -> get_name() << " impacted object " << (impacts.at(i) -> o2) -> get_name() << " at t = " << (impacts.at(i) -> time) << ansireset << endl;
            }
        }
        for (int i = 0; i < objects_amount; i++) {
            obj_copy(objects_cpy[i], objects[i]);
        }
        cout << ansiblue << endl << "Enter t to view objects stats at the moment t (w for writing output to a file, q for quit)." << ansireset << endl;
        while(1){
            cout << "~> ";
            string input = "";
            getline(cin , input);
            if (input == "q"){
                cout << ansired << "quiting ..." << ansireset << endl;
                return 0;
            }else if(input == "w"){
                cout << ansired <<  "writing ..." << ansireset << endl;
                YAML::Emitter out;
                out << YAML::BeginMap;

                out << YAML::Key << "field" << YAML::Value ;
                out << YAML::BeginMap;
                out << YAML::Key << "gravitational acceleration" << YAML::Value << gravitational_acceleration ;
                out << YAML::Key << "electrical field" << YAML::Value << fmt::format("({} , {} , {})", electrical_field[0], electrical_field[1], electrical_field[2]);
                out << YAML::Key << "magnetic field" << YAML::Value << fmt::format("({} , {} , {})", magnetic_field[0], magnetic_field[1], magnetic_field[2]) ;
                out << YAML::EndMap;

                out << YAML::Key << "object(s)" << YAML::Value ;
                out << YAML::BeginSeq;
                for (int i = 0; i < objects_amount ; i++){
                    Object obj = *objects[i];
                    out << YAML::BeginMap;
                    out << YAML::Key << "name" << YAML::Value << obj.get_name();
                    out << YAML::Key << "mass" << YAML::Value << obj.get_mass();
                    out << YAML::Key << "radius" << YAML::Value << obj.get_radius();
                    out << YAML::Key << "electrical charge" << YAML::Value << obj.get_electrical_charge();
                    out << YAML::Key << "position" << YAML::Value << fmt::format("({} , {} , {})", obj.get_position()[0], obj.get_position()[1], obj.get_position()[2]);
                    out << YAML::Key << "velocity" << YAML::Value << fmt::format("({} , {} , {})", obj.get_velocity()[0], obj.get_velocity()[1], obj.get_velocity()[2]);
                    out << YAML::Key << "acceleration" << YAML::Value << fmt::format("({} , {} , {})", obj.get_acceleration()[0], obj.get_acceleration()[1], obj.get_acceleration()[2]);
                    out << YAML::EndMap;
                }
                out << YAML::EndSeq;

                out << YAML::Key << "t" << YAML::Value << t;

                out << YAML::EndMap;

                ofstream fout(generate_unique_filename("PH_odata", "yaml"));
                fout << out.c_str();
                fout.close();
            }else if(is_double(input)){
                t = stod(input);
                break;
            }else{
                cout << ansired << "Invalid input. Please enter a numeric value:"<< ansireset << endl;
            }
        }
    }
    return 0;
}