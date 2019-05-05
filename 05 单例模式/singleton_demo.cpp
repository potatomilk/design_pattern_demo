#include <iostream>

class SingletonDemo {
public:
    static SingletonDemo* getInstance(){
        return inst;
    }
private:
    static SingletonDemo *inst;
    SingletonDemo() {
        printf("Constructor\n");
    }
    ~SingletonDemo() {
        printf("Destructor\n");
        delete inst;
    }
};

SingletonDemo* SingletonDemo::inst = new SingletonDemo();

void Test() {
    SingletonDemo *inst = SingletonDemo::getInstance();
    std::cout << inst << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Enter Main Func.\n");
    SingletonDemo *inst = SingletonDemo::getInstance();
    std::cout << inst << std::endl;
    SingletonDemo *inst2 = SingletonDemo::getInstance();
    std::cout << inst << std::endl;

    Test();

    return 0;
}

