/**
 *
 */

#include <iostream>

class IHouse {
public:
    void build() {
        step1();
        step2();
        step3();
        step4();
    }

protected:
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() = 0;
    virtual void step4() = 0;
};

class StoneHouse : public IHouse {
public:
    virtual void step1() {
        printf("Stone House Step1.\n");
    }
    virtual void step2() {
        printf("Stone House Step2.\n");
    }
    virtual void step3() {
        printf("Stone House Step3.\n");
    }
    virtual void step4() {
        printf("Stone House Step4.\n");
    }
};

class WoodHouse : public IHouse {
public:
    virtual void step1() {
        printf("Wood House Step1.\n");
    }
    virtual void step2() {
        printf("Wood House Step2.\n");
    }
    virtual void step3() {
        printf("Wood House Step3.\n");
    }
    virtual void step4() {
        printf("Wood House Step4.\n");
    }
};

int main(int argc, char *argv[]) {
    IHouse *house1 = new StoneHouse();  // house对象，应该避免用new，如何处理？
    house1->build();
    IHouse *house2 = new WoodHouse();
    house2->build();

    return 0;
}
