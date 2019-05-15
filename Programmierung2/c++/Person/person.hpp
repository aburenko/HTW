class Person 
{ 
private: 
    std::string name;
    Date bornDate;
public: 
    //constructors
    Person (std::string nameStr, int year, int month, int day);
    
    //getter functions
    void show ();

};
