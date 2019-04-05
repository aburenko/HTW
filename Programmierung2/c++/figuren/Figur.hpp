class Figur  {
private:
    
public:
    virtual double area() { return 0; }
    virtual double scope() { return 0; }
    virtual void show() { std::cout << "Figur" << std::endl;}
    friend std::ostream& operator<< (std::ostream&, Figur& f) { f.show(); f.draw();}
    virtual void draw() = 0;
};


// class Figur  {
// private:
//     
// public:
//     virtual double area() = 0;
//     virtual double scope() = 0;
// }

class Square : public Figur {
private:
    double s;
public:
    Square(double side) { this->s = side; }
    double area() { return s*s; }
    double scope() { return 4*s; }
    void show() { std::cout << "s: " << s << " area: " << area() << " scope: " << scope() << std::endl; }
    void draw() {
        for (int i = 0; i < s; i++) {
            for (int i = 0; i < s; i++) {
                std::cout << '0';
            }
            std::cout << std::endl;
        }
    }
};

class Circle : public Figur {
private:
    double d;
public:
    Circle(double diameter) { this->d = diameter; }
    double area() { return 3.14*d; }
    double scope() { return 3.14*d*d/4; }
    void show() { std::cout << "d: " << d << " area: " << area() << " scope: " << scope() << std::endl; }
    void draw() {
        std::cout << 'o' << std::endl;
    }
};

class Rectangle : public Figur {
private:
    double sTop;
    double sLeft;
public:
    Rectangle(double sideLeft, double sideTop) { 
        this->sTop = sideTop; 
        this->sLeft = sideLeft;
    }
    double area() { return sTop*sLeft; }
    double scope() { return 2*sTop+2*sLeft; }
    void show() { std::cout << "sideLeft: " << sLeft << " sideTop: " << sTop << " area: " << area() << " scope: " << scope() << std::endl; }
    void draw() {
        for (int i = 0; i < sTop; i++) {
            for (int i = 0; i < sLeft; i++) {
                std::cout << '0';
            }
            std::cout << std::endl;
        }
    }
};
