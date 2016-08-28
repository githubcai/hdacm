#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

map<string, double> table = {
    {"A", 4.0},
    {"B", 3.0},
    {"C", 2.0},
    {"D", 1.0},
    {"F", 0},
};

int main(){
    string line;
    while(getline(cin, line)){
        double GPA = 0;
        unsigned int cnt = 0;
        string grade;
        istringstream record(line);
        bool flag = true;
        while(record >> grade){
            cnt++;
            try{
                GPA += table.at(grade);
            }catch(out_of_range){
                cout << "Unknown letter grade in input" << endl;
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        GPA /= cnt;
        cout << fixed << setprecision(2) << GPA << endl;
    }
    return 0;
}
