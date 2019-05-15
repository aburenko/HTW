#include <cstdlib>

using namespace std;

class rechteck {
    int h,w;
    int posT,posL;
public:
    rechteck();
    rechteck(int h, int w);
    rechteck(int h, int w, int pL, int pT);
    
    int setPosition(int pL, int pT) {
        posL=pL;
        posL=pT;
        draw();
    };
    int setSize(int h, int w) {
        this->w=abs(w);
        this->h=abs(h);
        draw();
    };
    int setH(int h) {
        this->h=abs(h);
        draw();
    };
    int setW(int w) {
        this->w=abs(w);
        draw();
    };
    
    int moveRight() {
        posL += 1;
        draw();
    };
    int moveDown() {
        posT += 1;
        draw();
    };
    int moveLeft() {
        if(posL >= 1 )posL -= 1;
        draw();
    };
    int moveUp() {
        if(posT >= 1 )posL -= 1;
        draw();
    };
    
    int draw();
    int area() { return h*w; };
};
