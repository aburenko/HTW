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
    STRING& operator=(const STRING& other);
};
