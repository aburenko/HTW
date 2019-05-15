class STRING {
    char * pBuf;
    int	 Len;
public:
    STRING ();
    STRING (const char* pStr);
    STRING (const STRING& other);
    STRING (char C, int n);
    ~STRING();
    void show () const;
    char& CIdx(unsigned int i);
    int getLength();
    //Operatorüberladugen
    STRING& operator= (const STRING& other);
    
    STRING operator+ (const STRING& other);
    STRING operator+ (const char *other);

    friend std::ostream& operator<< (std::ostream& os, const STRING& other);
    
    char& operator[] (unsigned int index);
};
