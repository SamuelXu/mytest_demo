#include <iostream>
#include <string>

using namespace std;

class Strategy {
    public:
        virtual void alg() = 0;
};

class ConcreteStrategyA : public Strategy {
    public:
        virtual void alg() {
            cout << "use algorithm A" << endl;
        };
};

class ConcreteStrategyB : public Strategy {
    public:
        virtual void alg() {
            cout << "use algorithm B" << endl;
        };
};

class Context {
    public:
        virtual void run() {
            _alg->alg();
        };
        virtual void use(Strategy* alg) {
            _alg = alg;
        };

    private:
        Strategy* _alg;
};

int main(int argc, char* argv[])
{
    Context* c = new Context();
    Strategy* s = new ConcreteStrategyA();

    c->use(s);
    c->run();

    delete c;
    delete s;
}

