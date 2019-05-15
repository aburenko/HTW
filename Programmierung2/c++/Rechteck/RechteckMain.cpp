#include<iostream>
#include "Rechteck.hpp"
#include <cstdlib>

using namespace std;

rechteck::rechteck() {
    this->h=this->w=0;
    posL=posT=0;
}

rechteck::rechteck(int h, int w) {
    this->h=abs(h);
    this->w=abs(w);
    posL=posT=0;
    draw();
}

rechteck::rechteck(int h, int w, int pL, int pT) {
    this->h=abs(h);
    this->w=abs(w);
    posL=pL;
    posT=pT;
    draw();
}

int rechteck::draw(){
    system("clear");
    for(int t = 0; t < posT; t++)
        cout << endl;
    for(int i = 0; i<h; i++) {
        for(int t = 0; t < posL; t++)
            cout << ' ';
        for(int j = 0; j<w; j++) {
            cout << 'O';
        }
        cout << endl;
    }
    cout << endl << "area: " << this->area() << endl;
}

int main() {
    
    rechteck r(5,3, 5, 5);
    
    return 0;
}
