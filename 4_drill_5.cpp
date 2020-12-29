#include "./std_lib_facilities.h"

constexpr double TOLERANCE = 1.0/100;

double min(double a, double b){
    return a <= b ? a : b;
}

double max(double a, double b){
    return a >= b ? a : b;
}

bool withinTolerance(double a, double b){
    return (abs(a-b) < TOLERANCE) ? true : false;
}

int main(){

    double input1 {0};
    double input2 {0};

    while(cin >> input1 >> input2){

        if(input1 == input2){
            cout << "The numbers ar equal" << endl;
        } else {

            cout << "The smaller value is: " << min(input1, input2) << endl;
            cout << "The bigger value is: " << max(input1, input2) << endl;

            if(withinTolerance(input1, input2)){
                cout << "The numbers ar almost equal" << endl;
            }
        }

        cout << "Inputs where: " << input1 << " & "<< input2 << endl;
    }

    return 0;

}