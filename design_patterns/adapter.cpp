#include <iostream>
#include <string>

using namespace std;

class Target {
    public:
        virtual void show() =0;
};

class Adaptee {
    public:
        virtual int oldshow() {
            cout << "maybe old interface" << endl;
        };
};

class Adapter1 :public Target, private Adaptee {
    public:
        virtual void show() override {
            cout << "wrapper as new interface1: ";
            this->oldshow();
        };
};

class Adapter2 :public Target {
    public:
        virtual void show() {
            cout << "wrapper as new interface2: ";
            _old.oldshow();
        };

    private:
        Adaptee _old;
};

int main(int argc, char* argv[])
{
    Target* t1 = new Adapter1;
    t1->show();
    Target* t2 = new Adapter2;
    t2->show();

    delete t1;
    delete t2;
}
