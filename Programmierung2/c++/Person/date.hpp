class Date { 
private: 
    unsigned int year, month, day;
public:
    //constructor functions
    Date (unsigned int day, unsigned int month, unsigned int year);
    //getter
    void show () const;
    //setter
    void updateDate(unsigned int day, unsigned int month, unsigned int year); 
};
