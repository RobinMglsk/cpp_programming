#include "./std_lib_facilities.h"

bool checkIfUnitValid(string unit){
    vector<string> validUnits {"cm", "m", "in", "ft"};
    return !(find(validUnits.begin(), validUnits.end(),unit) != validUnits.end());
}

int main(){

    double number {0};
    string unit {""};

    double smallest {0};
    double largest {0};
    int count {0};

    while(cin >> number >> unit){

        if(checkIfUnitValid(unit)){
            cout << "Invalid unit enterd. Please use cm, m, in or ft." << endl;
            continue;
        }

        cout << number;

        if(count == 0){
            smallest = number;
            largest = number;
        }

        if(number < smallest){
            smallest = number;
            cout << " the smallest so far";
        }

        if(number > largest){
            largest = number;
            cout << " the largest so far";
        }

        cout << endl;
        
        ++count;
    }

    return 0;

}