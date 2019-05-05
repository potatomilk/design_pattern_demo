#include <iostream>

class IStrategy {
public:
    virtual void algo() = 0;
};

class Algo1 : public IStrategy {
public:
    virtual void algo() {
        printf("Algo1 calculate.\n");
    }
};

class Algo2 : public IStrategy {
public:
    virtual void algo() {
        printf("Algo2 calculate.\n");
    }
};

class App {
public:
    App(IStrategy *algo) : algo(algo) {}
    void run() {
        algo->algo();
    }
private:
    IStrategy *algo;
};

int main() {
    App app1(new Algo1());
    app1.run();

    App app2(new Algo2());
    app2.run();

    return 0;
}
