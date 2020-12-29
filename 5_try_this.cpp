#include "./std_lib_facilities.h"

int area(int x, int y){
    return x*y;
}

void errorFunction(){
    error("Test error");
}

int main(){

    int a = area(7,2);              // ok

    // 5.3.1 Syntax errors

    // int s1 = area(7;             // expected ')'
    // int s2 = area(7,2)           // candidate function not viable: requires 2 arguments, but 1 was provided int area(int x, int y){
    // Int s3 = area(7,2);          // use of undeclared identifier 'Int'; did you mean 'int'? Int s3 = area(7,2);
    // int s4 = area('7,2);         // warning: missing terminating \' character [-Winvalid-pp-token]


    // 5.3.2 Type errors

    // int x0 = arena(7);           // use of undeclared identifier 'arena'
    // int x1 = area(7);            // no matching function for call to 'area'
    // int x2 = area("seven", 2);   // no matching function for call to 'area'


    // 5.3.3 Non errors

    int x4 = area(10,-7);           // No warning but a negative area does not exist
    int x5 = area(10.7, 9.3);       // warning: implicit conversion from 'double' to 'int' changes value from 9.300000000000001 to 9 [-Wliteral-conversion]
    char x6 = area(100, 9999);      // No warning but truncated
    

    // 5.6.3 Bad input

    // errorFunction(); // Uncaught error

    try{
        errorFunction(); // Caught error
    }catch(runtime_error& e){
        cerr << "Runtime error occured: " << e.what(); // Print error msg for runtime errors
    }catch(...){
        cerr << "An error occurred"; // Print error for al other exeptions
    }
}