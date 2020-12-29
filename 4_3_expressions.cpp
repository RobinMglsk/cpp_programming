#include "./std_lib_facilities.h"

int length  {3};
int width {2};

int main(){
    cout << "### Expressions ###" << endl << endl;

    cout << "(length + width) * 2 = " << (length+width)*2 << endl;
    cout << "length*2+width*2 = " << length*2+width*2 << endl;
    cout << "length + width * 2 = " << length+width*2 << endl;


    cout  << endl << "### Conversions ###" << endl << endl;

    cout << "5/2 = " << 5/2 << endl;
    cout << "5.0/2 = " << 5.0/2 << endl;
    cout << "'*'+0x01 = " << '*'+ 0x01 << endl;
}

