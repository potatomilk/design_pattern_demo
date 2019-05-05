/*
 * 命令模式是将行为封装为对象，在C++中，与函数指针/函数对象类似，因此，在效率与性能上，
 * 使用函数指针/函数对象+模板，可实现命令模式
 */

#include <iostream>
#include <vector>

struct Context {  // 上下文参数
};

class ICommand {
public:
    virtual void execute() = 0;
private:
    Context* context;
};

class OpenCommand : public ICommand {
public:
    OpenCommand() : ICommand() {}
    virtual void execute() override {
        printf("Open Command Execute.\n");
    }
};

class CloseCommand : public ICommand {
public:
    CloseCommand() : ICommand() {}
    virtual void execute() override {
        printf("Close Command Execute.\n");
    }
};

class SaveCommand : public ICommand {
public:
    SaveCommand() : ICommand() {}
    virtual void execute() override {
        printf("Save Command Execute.\n");
    }
};

class MarcoCommand : public ICommand {
public:
    void AddCommand(ICommand* c) {
        cmd.push_back(c);
    }
    void DeleteCommand(ICommand* c) {
        // 可以删除
    }
    virtual void execute() override {
        printf("Macro Command Execute.\n");
        for (std::vector<ICommand*>::iterator iter = cmd.begin(); iter != cmd.end(); ++iter) {
            (*iter)->execute();
        }
    }
private:
    std::vector<ICommand*> cmd;
};

int main(int argc, char *argv[]) {
    printf("Command Pattern Demo.\n");

    ICommand *open = new OpenCommand();
    open->execute();
    ICommand *save = new SaveCommand();
    save->execute();
    ICommand *close = new CloseCommand();
    close->execute();

    MarcoCommand *com = new MarcoCommand();
    com->AddCommand(open);
    com->AddCommand(save);
    com->AddCommand(close);
    com->execute();

    return 0;
}