#include <iostream>
#include <string>

using namespace std;

class AbsTemplate {
    public:
        void doShow() {
            this->preprocess();
            cout << "show process" << endl;
        };
        virtual void preprocess() = 0;
};

class ConcreteTemplateA : public AbsTemplate {
    public:
        virtual void preprocess() {
            cout << "use concrete template A" << endl;
        };
};

int main(int argc, char* argv[])
{
    AbsTemplate* t = new ConcreteTemplateA();

    t->doShow();
}

