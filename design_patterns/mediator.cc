#include <iostream>
#include <string>
#include <list>

using namespace std;

class Mediator {
    public:
        virtual void broadcast() = 0;
};

class Colleage {
    public:
        Colleage(Mediator* m) : _m(m) { };
        virtual void tell() = 0;
        virtual void echo() = 0;

    protected:
        Mediator* _m;
};

class ConcreteColleage1 : public Colleage {
    public:
        ConcreteColleage1(Mediator* m):Colleage(m) { };

        virtual void tell() {
            cout << " i am ConcreteColleage1" << endl;
            _m->broadcast();
        };

        virtual void echo() {
            cout << "ConcreteColleage1 received message" << endl;
        };
};

class ConcreteColleage2 : public Colleage {
    public:
        ConcreteColleage2(Mediator* m):Colleage(m) { };

        virtual void tell() {
            cout << " i am ConcreteColleage2" << endl;
            _m->broadcast();
        };

        virtual void echo() {
            cout << "ConcreteColleage2 received message" << endl;
        };

};

class ConcreteColleage3 : public Colleage {
    public:
        ConcreteColleage3(Mediator* m):Colleage(m) { };

        virtual void tell() {
            cout << " i am ConcreteColleage3" << endl;
            _m->broadcast();
        };

        virtual void echo() {
            cout << "ConcreteColleage3 received message" << endl;
        };
};

class ConcreteMediator : public Mediator {
    public:
        virtual void broadcast() {
            for(list<Colleage*>::iterator it=_lc.begin();it!=_lc.end();it++) {
                (*it)->echo();
            }
        };
        void addColleage(Colleage* c) {
            _lc.push_back(c);
        };

    private:
        list<Colleage*> _lc;
};

int main(int argc, char* argv[])
{
    ConcreteMediator* m = new ConcreteMediator();

    ConcreteColleage1* c1 = new ConcreteColleage1(m);
    ConcreteColleage2* c2 = new ConcreteColleage2(m);
    ConcreteColleage3* c3 = new ConcreteColleage3(m);

    m->addColleage(c1);
    m->addColleage(c2);
    m->addColleage(c3);

    c1->tell();

    delete c1;
    delete c2;
    delete c3;
    delete m;
}

