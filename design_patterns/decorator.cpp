#include <iostream>
#include <string>

using namespace std;

class Component {
    public:
        virtual void show() = 0;
};

class ConcreteComponent : public Component {
    public:
        virtual void show() {
            cout << "concrete component example" << endl;
        };
};

class Decorator: public Component {
    public:
        Decorator(Component* comp) {
            _comp = comp;
        };
        virtual void show() {
            _comp->show();
        };

    private:
        Decorator();
    private:
        Component* _comp;
};

class ConcreteDecorator : public Decorator {
    public:
        ConcreteDecorator(Component* comp) : Decorator(comp) {};
        virtual void show() {
            cout << "decorator wrapper api:";
            Decorator::show();
        };

    private:
        ConcreteDecorator();
};


int main(int argc, char* argv[])
{
    Component* com = new ConcreteComponent();
    Component* d = new ConcreteDecorator(com);
    d->show();

    delete com;
    delete d;
}
