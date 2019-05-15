

template <class T, int bufSizeMax>
class Buffer {
private:
    T vBuf[bufSizeMax];
    int iterator;
    short int sizeInput;
    int sizeMax;
    void iteratorNext () {
        iterator = (iterator+1)% bufSizeMax; 
    }
public:
    Buffer() {
        iterator = 0;
        sizeMax = bufSizeMax;
    }
    void show() {
        for(int i = 0; i < sizeMax && i < sizeInput-1; i++) {
            std::cout << i << "]: " << vBuf[i] << std::endl;
        }
    }
    void store(T newElement) {
        vBuf[iterator] = newElement;
        iteratorNext();
        if(sizeInput < sizeMax)sizeInput++;
    }
    // >0 found, -1 no such element
    int find(T searchElement) {
        for(int i = 0; i < sizeMax; i++) {
            if(searchElement == vBuf[i])
                return i;
        }
        return -1;
    }
    
    T& operator[] (int elemNum) {
        T * Dummy = new T(); 
        if(elemNum > sizeMax) return *Dummy;
        return vBuf[elemNum];
    }
};
