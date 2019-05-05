#include <iostream>

namespace Lib {
    class ISplitter {
    public:
        virtual void Split() = 0;
        virtual ~ISplitter() {}
    };

    class IFactoryMethod {
    public:
        virtual ISplitter* Create() = 0;
        virtual ~IFactoryMethod() {}
    };
};

namespace App {
    // 文本分割
    // class TextSplitter // 应用模式之前
    class TextSplitter : public Lib::ISplitter {
    public:
        void Split() {
            printf("Text Split.\n");
        }
    };

    // 图片分割
    // class PictureSplitter // 应用模式之前
    class PictureSplitter : public Lib::ISplitter {
    public:
        void Split() {
            printf("Picture Split.\n");
        }
    };

    // 还有别的内容分割器

    // 创建具体工厂
    class TextSplitterFactory : public Lib::IFactoryMethod {
    public:
        virtual Lib::ISplitter* Create() {  // 具体工厂可以是单一的
            return new TextSplitter();
        }
    };

    class PictureSplitterFactory : public Lib::IFactoryMethod {
    public:
        virtual Lib::ISplitter* Create() {  // 具体工厂可以是单一的
            return new PictureSplitter();
        }
    };
};

namespace Window {
    class MainWindow {  // 该业务逻辑趋于稳定
    public:
        MainWindow() : m_factory(nullptr) {}
        // 以入参的方式对工厂实例化
        MainWindow(Lib::IFactoryMethod *factory) : m_factory(factory) {}
        void Button1_Click() {
            // TextSplitter spliter;
            // spliter.Split();       // 引入设计之前，或许只需要实现文本分割，
                                      // 但需求变更，需要增加对图片等内容的分割

            // ISplitter *splitter =
            //     new App::TextSplitter();  // 明显依赖具体实现

            // 工厂方法的目的是消除new引入的依赖，通过工厂消除这种依赖，而工厂通过入参来赋
            // 值，即：实例化交给子类实现
            Lib::ISplitter *splitter = m_factory->Create();
            splitter->Split();
        }
    private:
        Lib::IFactoryMethod *m_factory;
    };
}

int main(int argc, char **argv) {
    // 这里的工厂可以再采用生成实例的设计模式，如单例模式，进行进一步提升可维护性与架构稳定性
    Window::MainWindow *mainWindow1 =
        new Window::MainWindow(new App::PictureSplitterFactory());
    mainWindow1->Button1_Click();

    Window::MainWindow *mainWindow2 =
        new Window::MainWindow(new App::TextSplitterFactory());
    mainWindow2->Button1_Click();

    // 这里的细分是必不可少的，而设计模式的应用则是实现将变化的点收紧到一处，使稳定与变化进行
    // 分离，减少不必要的耦合性

    delete mainWindow1;
    delete mainWindow2;

    return 0;
}