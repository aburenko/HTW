#include <iostream>
#include "buffer.hpp"
#include <string>

using namespace std;

int main() {
    
    Buffer <int,5> intBuf;

    intBuf.store(5);
    intBuf.store(7);
    intBuf.store(12);
//     intBuf.store(2);
//     intBuf.store(42);
//     intBuf.store(-42);
//     intBuf.store(30);
    
    
        intBuf.show();
            
            
cout << intBuf[2] << endl;
    
    Buffer <string ,5> strBuf;
    strBuf.store("Lucas");
    strBuf.store("ist");
    strBuf.store("Lucas");
    strBuf.show();
cout << strBuf[3] << endl;
    return 0;
}
