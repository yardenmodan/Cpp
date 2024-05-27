#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr

class ALU{
public:
    ALU(uint8_t t_x1=0, uint8_t t_x2=0, uint8_t t_extIn=0): x1(t_x1),x2(t_x2),extIn(t_extIn) 
    {};
    virtual ~ALU();

    uint8_t get_x1() const {
        return x1;
    }
    uint8_t get_x2() const {
        return x2;
    }
    uint8_t get_extIn() const {
        return extIn;
    }
    uint8_t get_res() const {
      return res;  
    }
    uint8_t get_extOut() const {
        return extOut;
    }





    void set_x1(uint8_t t_x1) {
        x1 =t_x1;
        return;
    }
    void set_x1(uint8_t t_x2) {
        x2 =t_x2;
        return;
    }
    void set_extIn(uint8_t t_extIn) {
        extIn=t_extIn;
        return;
    }

    void displayInput(){
        std::cout<< "x1: " << x1 << std::endl;
        std::cout<< "x2: " << x2 << std::endl;
        std::cout<< "extIn: " << extIn << std::endl;

        return;
    }
    void displayOutput(){
        std::cout<< "res: "<< res << std::endl;
        std::cout<< "extOut: "<< extOut << std::endl;
        return;

        
    }

    virtual void calculate_res()  ;
    virtual void calculate_extOut()  ;
protected:
    uint8_t x1;
    uint8_t x2;
    uint8_t extIn;
    uint8_t res;
    uint8_t extOut;

};


class FA: public ALU{
    FA(uint8_t t_x1, uint8_t t_x2, uint8_t t_extIn): ALU(t_x1,t_x2,t_extIn) {};  
    void calculate_res() override {
        res = 0x01&((x1&x2)|(x1&extIn)|(x2&extIn));
    }
    void calculate_extOut() override{
        extOut = 0x01&(x1^x2^extIn);
        
    }

};

class FS: public ALU{
    FS(uint8_t t_x1, uint8_t t_x2, uint8_t t_extIn): ALU(t_x1,t_x2,t_extIn) {};  
    void calculate_res() override {
        res= 0x01&( (~(x1)&x2)|(~(x1)&extIn)|(x2&extIn));
    }
    void calculate_extOut()  override  {
        extOut=0x01&( x1^x2^extIn);
        
    }

};


class ALU_8{
public:
    ALU_8(uint8_t x1, uint8_t x2, uint8_t extIn): m_x1(x1), m_x2(x2), m_extIn(extIn) {
        for (auto i=0; i<8 ; i++){
            aluArr[i]= new ALU;

        }
        // call consturctor of all 8 bits
        // inserting each bit using methods of ALU class

    }
private:
    uint8_t m_x1;
    uint8_t m_x2;
    uint8_t m_extIn;
    uint8_t res;
    uint8_t extOut;

    std::unique_ptr<ALU> aluArr[8];

    ALU alu0();
    ALU alu1();
    

    

};
