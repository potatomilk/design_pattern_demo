#include <iostream>
#include <set>

namespace Interface {
    class INotification {
    public:
        void Notify(int p) {
            printf("Notify.\n");
            printf("%d.\n", s.size());
            for (auto i = s.begin(); i != s.end(); ++i) {
                (*i)->OnNotify(p);
            }
        }
        void Add(INotification* n) {
            s.insert(n);
        }
        void Delete(INotification* n) {
            s.erase(n);
        }
        virtual void OnNotify(int) = 0;
    private:
        static std::set<INotification*> s;
    };

    std::set<INotification*> INotification::s;
}

namespace MO {
    class AlgoModel : public Interface::INotification {
    public:
        int Progress() {
            Notify(1);
            return 1;
        }
        virtual void OnNotify(int) {}
    };
}

namespace VIEW {
    class ProgressBar : public Interface::INotification {
    public:
        ProgressBar() {
            Add(this);
        }
        ~ProgressBar() {
            Delete(this);
        }
        void Update() {
            printf("Update Progress Bar.\n");
        }
        virtual void OnNotify(int) {
            Update();
        }
    };

    class MainWindow : public Interface::INotification {
    public:
        MainWindow() {
            Add(this);
            bar = new ProgressBar();
        }
        ~MainWindow() {
            Delete(this);
            delete bar;
        }
        void Click() {
            // 一开始，只需要更新一处，但随着业务发展，需要多处通知处理的进展，如何处理？
            // MO::AlgoModel algo;
            // int prog = algo.Progress();

            // bar->Update(prog);
            // cmd->Update(prog);  // 可能控制台需要输出
            // textBox->Update(prog); // 文本框需要显式输出

            MO::AlgoModel algo;
            algo.Progress();
        }
        virtual void OnNotify(int p) {
            printf("Main Window Update.\n");
        }
    private:
        ProgressBar *bar;
    };

    class ChartWindow : public Interface::INotification {
    public:
        ChartWindow() {
            Add(this);
        }
        ~ChartWindow() {
            Delete(this);
        }
        void View() {
            // 这里的显式也需要根据MO::AlgoModel的处理进度进行更新显式，如何处理这种？
            printf("Chart Window Update.\n");
        }
        virtual void OnNotify(int) {
            View();
        }
    };
}


int main(int argc, char **argv) {
    VIEW::MainWindow mainWindow;
    VIEW::ChartWindow chartWindow;
    mainWindow.Click();

    return 0;
}