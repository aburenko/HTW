#include <iostream>
#include <iomanip>

using namespace std;

int divide(int x, int y, int & rest);
double divide(int x, int y);

int main() {
    int rest = -1;
    
    int quot = divide(5,3,rest);
    double d_quot = divide(5,3);
    cout << "quot: " << quot << endl;
    cout << "rest: " << rest << endl;
    cout << endl;
    cout << "d_quot: " << d_quot << endl;
    return 0;
}


int divide(int x, int y, int & rest) {
    rest = x%y;
    return x/y;
}

double divide(int x, int y) {
    return (double) x / (double) y;
}
