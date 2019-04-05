#include <iomanip>
#include <iostream>

using namespace std;



int main() {
    int i,j;
    cout << "|dec hex Char |dec hex Char |dec hex Char |dec hex Char |" << endl;
    for(i=0;i<=31;i++) {
        cout << '|';
        for(j=0;j<=3*32;j+=32) {
            cout << right << dec << setw(4) << i+j << hex << setw(4) << i+j;
            if(isgraph(i+j)) {
                cout << setw(5) << (char) (j+i);
            } else {
                cout << setw(5) << '.';
            }
            cout << '|';
        }
        cout << endl;
    }
    
    return 0;
}
