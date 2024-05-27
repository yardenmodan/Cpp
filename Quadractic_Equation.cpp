#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <stdexcept>
#include <math.h>
#include <iomanip>

class Equation{
    private:
    double m_a;
    double m_b;
    double m_c;
    double * solutions=nullptr;
    std::size_t solutions_size=0;
    
    void update_solutions(){
        int discriminant=pow(m_b,2) -4*m_a*m_c;
        if (solutions!=nullptr){
            delete[] solutions;
        }
        if (discriminant>0){
            solutions_size=2;
            solutions= new double[2];
            solutions[0]=static_cast<double>(-m_b+sqrt(discriminant))/2*m_a;
            solutions[1]=static_cast<double>(-m_b-sqrt(discriminant))/2*m_a;
            
        }
        else if (discriminant==0){
            solutions_size=1;
            solutions=new double[1];
            
            solutions[0]=static_cast<double>(-m_b)/(2*m_a);
            printf("%f", solutions[0]);
            
        }
        else{
            solutions_size=0;
           
        }
        
    }
    // std::size_t get_solutions_size(){
    //     int discriminant=pow(m_b,2) -4*m_a*m_c;
    //     solutions_size=0;
    //     if (discriminant>0){
    //         solutions_size=2;
    //     }
    //     else if (discriminant==0){
    //         solutions_size=1;
    //     }
    //     return solutions_size;
    // }
    public:
    Equation(double a, double b, double c): m_a(a), m_b(b), m_c(c){
        if (a==0){
            throw std::invalid_argument("Variable cannot be zero\n");
        }
        update_solutions();

    } 
    Equation()=default;

    ~Equation(){
        delete[] solutions;
    }

    Equation(Equation && other) noexcept { //Move constructor
        m_a=std::move(other.m_a);
        m_a=std::move(other.m_b);
        m_c=std::move(other.m_c);
        solutions=std::move(other.solutions);
        solutions_size=std::move(other.solutions_size);



    }
    Equation& operator=(Equation && other) { // move assignment
        if (this!=&other){
            m_a=std::move(other.m_a);
            m_b=std::move(other.m_b);
            m_c=std::move(other.m_c);
            solutions_size=std::move(other.solutions_size);
            solutions= new double[solutions_size];
            std::copy(other.solutions,other.solutions+other.solutions_size,solutions);
        }

        return *this;
    }

    Equation(const Equation& other) noexcept { //copy constructor
        m_a=other.m_a;
        m_b=other.m_b;
        m_c=other.m_c;
        solutions_size=other.solutions_size;
        solutions=new double[solutions_size];
        solutions=nullptr;
        if (solutions_size>=1){
            solutions[0]=other.solutions[0];
            
        }
        if (solutions_size==2){
            solutions[1]=other.solutions[1];

        }
    
        

    }
    

    
    double get_a() const {
        return m_a;
    }
    double get_b() const {
        return m_b;
    }
    double get_c() const {
        return m_c;
    }
    std::size_t get_solutions_size(){
        return solutions_size;
    }

    double const * get_solutions(){
        return solutions;
    }
    void set_a(){
        double temp_m_a;
        std::cin >> temp_m_a;
        if (temp_m_a == 0){
            throw std::invalid_argument("Variable cannot be zero\n");
            exit(0);
        }
            m_a=temp_m_a;
            update_solutions();        

    }

    void set_b(){
        std::cin >> m_b;
        update_solutions();

    }
    void set_c(){
        std::cin >> m_c;
        update_solutions();

    }

    Equation operator+(const Equation& other) const{
        double new_a=m_a+other.m_a;
        double new_b=m_b+other.m_b;
        double new_c=m_c+other.m_c;
        return Equation(new_a,new_b,new_c);
        
    }

    Equation operator+(double num){
        double new_c=m_c+num;
        return Equation(m_a,m_b,new_c);
    }
    
    friend Equation operator+(double num, const Equation& other)  { // SHOULD WORK?!
        Equation eq= Equation(other.m_a, other.m_b,num+other.m_c);
        return eq;
    }
    
  

    friend std::ostream& operator<<(std::ostream& os ,const Equation& equation) {
        os << std::fixed << std::setprecision(1);
        os << equation.m_a << "X^2 + " << equation.m_b << "X + " << equation.m_c << " =0"  <<std::endl;
        return os;
    }
};


int main() {
    
    Equation eq(10,20,30);
    std::cout << eq << std::endl;
    //should print: 10X^2 + 20X + 30 = 0
    std::cout << eq.get_solutions_size() << std::endl;
    //should print 0
    eq = -20 + eq;
    std::cout << eq << std::endl;
    //should print: 10X^2 + 20X + 10 = 0
    std::cout << eq.get_solutions_size() << std::endl;
    //should print 1
    std::cout << eq.get_solutions()[0] << std::endl;
    //should print -1
    std::cout << Equation(1,5,3) + Equation(2,6,4) << std::endl;
    //should print: 3X^2 + 11X + 7 = 0
    eq = Equation(1,3,-4);
    std::cout << eq << std::endl;
    //should print 1X^2 + 3X + -4 = 0
    std::cout << eq.get_solutions_size() << std::endl;
    //should print 2
    std::cout << "X1 = " << eq.get_solutions()[0] << std::endl;
    //should print: X1 = 1
    std::cout << "X2 = " << eq.get_solutions()[1] << std::endl;
    //should print: X2 = -4
    return 0;
}
