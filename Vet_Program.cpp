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
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Animal {
public:
    Animal(const std::string& name, double temp, double breath, double heart): m_name(name), m_temp(temp) \
    , m_breath(breath), m_heart(heart) {};
    virtual bool check_health() const = 0;    

    std::string m_name;
    double m_temp;
    double m_breath;
    double m_heart;

};

class Cow : public Animal{
public:
    Cow(const std::string& name, double temp, double breath, double heart, double liters):
    Animal(name, temp, breath, heart ), m_liters(liters) {}
    bool check_health() const override {
        return (m_temp >= 38.5 && m_temp <= 39.5) &&
               (m_breath >= 26 && m_breath <= 50) &&
               (m_heart >= 48 && m_heart <= 84) &&
               (m_liters >= 30);
    }

private:
    double m_liters;


};

class Cat : public Animal {
    public:
    Cat(const std::string& name, double temp, double breath, double heart): 
    Animal(name, temp, breath, heart) {};
    bool check_health() const override{
        return (m_temp >= 38 && m_temp <= 39.2) &&
               (m_breath >= 16 && m_breath <= 40) &&
               (m_heart >= 120 && m_heart <= 140);
    }
};


class Dog : public Animal {
public:
    Dog(const std::string& name, double temp, double breath, double heart, bool is_large) :
        Animal(name, temp, breath, heart), is_large(is_large) {}

    bool check_health() const override {
        // Check temperature, breath, and heart rate based on size
        return (m_temp >= 38 && m_temp <= 39.2) &&
                (m_breath >= 10 && m_breath <= 35) &&
                (((m_heart >= 60 && m_heart <= 100)&&is_large)||((m_heart >= 100 && m_heart <= 140)&&!(is_large)));

    }

private:
    bool is_large;
};

class Vet {
private:
    static Vet* instance;
    std::vector<std::unique_ptr<Animal>> animals;
    Vet() =default;
public:
    Vet(const Vet&) =delete;
    Vet& operator=(const Vet&)= delete;
    static Vet& get_instance() {
        if (instance==nullptr){
            instance= new Vet();
        }
        return *instance;

    }

    void add_animal(Animal* animal ){
        animals.emplace_back(std::move(animal));
    }

    void show_sick() {
        std:: cout<< "Sick animals:\n";
        for (const std::unique_ptr<Animal>& animal : animals){
            if (!animal->check_health()){
                std::cout << animal->m_name<< std::endl;
            }
        }
    }
    void show_sick_dogs(){
        std::cout << "Sick dogs:\n";
        for (const std::unique_ptr<Animal>& animal : animals){
            Dog *dog =dynamic_cast<Dog*>(animal.get()); // if cant cast dog ==nullptr
            if (dog&& !dog->check_health()){
                std::cout <<dog->m_name <<std::endl;
            }
        }
    }
    ~Vet(){
        animals.clear(); // delete memory located in vector
    }

};

    Vet* Vet::instance = nullptr;
int main() {
    
    using namespace std;
    cout << "program start" << endl;
    Vet& vet = Vet::get_instance();
    //healthy dog
    vet.add_animal(new Dog("dog1", 38.5, 20, 80, true));
    //not healthy dog (temp too high)
    vet.add_animal(new Dog("dog2", 40.0, 20, 80, true));
    //not healthy dog (heart rate too slow for a small breed)
    vet.add_animal(new Dog("dog3", 38.5, 20, 80, false));
    //healthy cat
    vet.add_animal(new Cat("cat1", 38.7, 30, 130));
    //not healthy cat (breath is too high)
    vet.add_animal(new Cat("cat2", 38.7, 42, 130));
    //healthy cow
    vet.add_animal(new Cow("cow1", 39.0, 37, 70, 32));
    //not healthy cow (milk production too low)
    vet.add_animal(new Cow("cow2", 39.0, 37, 70, 20));
    vet.show_sick(); //should print: dog2 dog3 cat2 cow2
    vet.show_sick_dogs(); //should print: dog2 dog3
}