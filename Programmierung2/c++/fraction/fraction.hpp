

class Fraction {
private:
    long top, down;
    
    // größter gemeinsamer Teiler
    long gcf(long first, long second);
    // Bruchkürzer
    void simplify();
public:
    //constructors
    Fraction () { top=0; down=1; }
    Fraction (long, long);
    Fraction ( const Fraction& );
    //destrurktor 
    ~Fraction() {}
    
    //get methodes
    void show() const;
    
    //set methodes
    void setValue(long, long);
    
    //math operations
    Fraction add(const Fraction&) const;
    Fraction subtract(const Fraction&) const;
    Fraction multiply(const Fraction&) const;
    Fraction divide(const Fraction&) const;
};
