/*
 * 享元模式主要用于"稳定不变"的对象“共享”化，以节省内存，改善程序性能
 * 如：字体对象、线型对象
 */

#include <iostream>
#include <map>

class FlyweightDemo {
public:
    static FlyweightDemo* getObj(int&& key) {
        std::map<int, FlyweightDemo*>::iterator iter = objMap.find(key);
        if (iter == objMap.end()) {
            FlyweightDemo *obj = new FlyweightDemo();
            objMap.insert(std::pair<int, FlyweightDemo*>(key, obj));
            return obj;
        } else {
            return iter->second;
        }
    }
private:
    static std::map<int, FlyweightDemo*> objMap;
};
std::map<int, FlyweightDemo*> FlyweightDemo::objMap;

int main(int argc, char *argv[]) {
    printf("Flyweight Pattern Demo.\n");

    FlyweightDemo* obj;
    obj = FlyweightDemo::getObj(1);
    std::cout << "OBJ1 Addr:" << obj << std::endl;
    obj = FlyweightDemo::getObj(2);
    std::cout << "OBJ2 Addr:" << obj << std::endl;
    obj = FlyweightDemo::getObj(3);
    std::cout << "OBJ3 Addr:" << obj << std::endl;
    obj = FlyweightDemo::getObj(2);
    std::cout << "OBJ2 Addr:" << obj << std::endl;
    obj = FlyweightDemo::getObj(1);
    std::cout << "OBJ1 Addr:" << obj << std::endl;

    return 0;
}