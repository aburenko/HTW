#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    
    char buf[4+1];
    string str;
    
    signed char my_sc;
    unsigned char my_uc;
    signed short my_ss;
    unsigned short my_us;
    signed int my_si;
    unsigned int my_ui;
    signed long my_sl;
    unsigned long my_ul;
    float my_f;
    double  my_d;
    
//     cout << "signed char: ";
//     cin >> my_sc;
//     cout << "unsigned char: ";
//     cin >> my_uc;
//     cout << "signed short: ";
//     cin >> my_ss;
//     cout << "unsigned short: ";
//     cin >> my_us;
//     cout << "signed int: ";
//     cin >> my_si;
//     cout << "unsigned int: ";
//     cin >> my_ui;
//     cout << "signed long: ";
//     cin >> my_sl;
//     cout << "unsigned long: ";
//     cin >> my_ul;
//     cout << "float: ";
//     cin >> my_f;

     cout << "buf: ";    
     cin.get(buf, (4+1));
//     cin.get(buf, (4+1));
//     cin >> str;
    
     cout << "double: ";
     cin >> my_d;
    
//     cout << setw(15) << left << "signed char " << (void *) &my_sc << ' ' <<  setw(4) << dec << my_sc << ' ' << hex << my_sc << endl;
//     cout << setw(15) << left << "unsigned char " << (void *) &my_uc << ' ' <<  setw(4) << dec << my_uc << ' ' << hex << my_uc << endl;
//     cout << setw(15) << left << "signed short " << (void *) &my_ss << ' ' <<  setw(4) << dec << my_ss << ' ' << hex << my_ss << endl;
//     cout << setw(15) << left << "unsigned short " << (void *) &my_us << ' ' <<  setw(4) << dec << my_us << ' ' << hex << my_us << endl;
//     cout << setw(15) << left <<"signed int " << (void *) &my_si << ' ' <<  setw(4) << dec << my_si << ' ' << hex << my_si << endl;
//     cout << setw(15) << left <<"unsigned int " << (void *) &my_ui  << ' ' <<  setw(4) << dec << my_ui << ' ' << hex << my_ui << endl;
//     cout << setw(15) << left <<"signed long " << (void *) &my_sl << ' ' <<  setw(4) << dec << my_sl << ' ' << hex << my_sl << endl;
//     cout << setw(15) << left <<"unsigned long " << (void *) &my_ul << ' ' <<  setw(4) << dec << my_ul << ' ' << hex << my_ul << endl;
//     cout << endl;
//     cout << setw(15) << left <<"float " << (void *) &my_f << ' ' <<  setw(4) << dec << my_f << ' ' << hex << my_f << endl;
     cout << setw(15) << left <<"double " << (void *) &my_d << ' ' <<  setw(4) << dec << my_d << ' ' << hex << my_d << endl;
//     cout << endl;
     cout << "buf: " << setw(4) << buf << endl;
//     cout << "string: " << str << endl;
    
    
    return 0;
}
