#include "./std_lib_facilities.h"

vector<uintmax_t>  fibonacci(int length, vector<uintmax_t> values = {}){
    
    if(values.size() == 0 && length < 2){
        throw runtime_error("Length needs to be atleast 2");
    }

    
    if(values.size() == 0){
        values.push_back(1);
        values.push_back(1);
    }else{
        values.push_back(values[values.size()-2] + values[values.size()-1]);
    }

    --length;
    if(length == 0){
        return values;
    }

    return fibonacci(length, values);
}

int main(){
    int length {};

    cin >> length;

    try{
        vector<uintmax_t> values = fibonacci(length-1);

        for(const int& value : values){
            cout << (uintmax_t) value << " ";
        }

        cout << endl;
        return 0;
    }catch(exception& e){
        cout << "Exception: " << e.what() << endl;
        return 1;
    }catch(...){
        cout << "Unknown exception" << endl;
        return 2;
    }
}