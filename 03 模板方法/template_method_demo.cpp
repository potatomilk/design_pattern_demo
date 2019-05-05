#include <iostream>

class Library {
public:
    void run() {
        printf("Exec Algorithm Logic.\n");
        step1();
        step2();
        step3();
        step4();
        step5();
    }

    virtual ~Library() {

    }
protected:
    virtual void step2() = 0;
    virtual void step4() = 0;

private:
    void step1() {
        printf("Statble Step 1.\n");
    }
    
    void step3() {
        printf("Statble Step 3.\n");
    }
    
    void step5() {
        printf("Statble Step 5.\n");
    }
};

class App : public Library {  // Library 是早于App 开发的，因此，又称晚绑定
private:
    virtual void step2() {
        printf("User Define Step 2.\n");
    }

    virtual void step4() {
        printf("User Define Step 4.\n");
    }
};

int main(int argc, char *argv[]) {
    printf("Template Method Demo.\n");

    Library *app = new App();
    app->run();  // 模板方法：由类库开发人员编写算法逻辑框架，应用开发人员只需关注自定义部分
    // 属于后绑定操作，应用多态特性
    // 依赖倒置，又称好莱坞原则
    // ——“你别不要调用我，让我来调用你”——  好莱坞原则
    delete app;

    return 0;
}