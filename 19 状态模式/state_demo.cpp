#include <iostream>

class IState {
public:
    IState *next;  // 关键点
    virtual void OnProcess() = 0;
};

class State1 : public IState {
public:
    virtual void OnProcess();
    static IState* getInst() {
        return inst;
    }
private:
    static IState *inst;
};
IState* State1::inst = new State1();

class State2 : public IState {
public:
    virtual void OnProcess();
    static IState* getInst() {
        return inst;
    }
private:
    static IState *inst;
};
IState* State2::inst = new State2();

void State1::OnProcess()
{
    printf("State1 Process.\n");
    next = State2::getInst();
}

void State2::OnProcess()
{
    printf("State2 Process.\n");
    next = State1::getInst();
}

class Run {
public:
    Run(IState *s) : state(s) {}
    void run() {
        state->OnProcess();
        state = state->next;  // 理解变化点在哪里
    }
private:
    IState *state;
};

int main(int argc, char *argv[]) {
    Run r(State2::getInst());
    r.run();
    r.run();
    r.run();
    r.run();

    return 0;
}
