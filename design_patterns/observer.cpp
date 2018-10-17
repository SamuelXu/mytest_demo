#include <iostream>
#include <string>
#include <list>

using namespace std;

class Observer;
class Subject {
    public:
        virtual ~Subject() { _obs.clear();};

        virtual void Attach(Observer* o) {
            _obs.push_back(o);
        };
        virtual void Detach(Observer* o) {
            _obs.remove(o);
        };
        virtual void Notify();

    protected:
        Subject() { };
    private:
        list<Observer*> _obs;
};

class Observer {
    public:
        virtual ~Observer() { };
        virtual void Update(Subject* changedsj) = 0;
    protected:
        Observer() { };
};

class ConcreteSubject : public Subject {
    public:
        ConcreteSubject() {};
        void run() {
            for(int i=0;i<10;i++) {
                if(i%5==0) {
                    Notify();
                }
            }
        };
};

class ConcreteObserver : public Observer {
    public:
        ConcreteObserver(Subject* s):_s(s) { };
        virtual void Update(Subject* s) {
            if(s == _s) {
                cout << "subject changed" << endl;
            }
        };

    private:
        Subject* _s;
};

void Subject::Notify() {
    for(list<Observer*>::iterator it=_obs.begin();it!=_obs.end();it++) {
        (*it)->Update(this);
    }
}

int main(int argc, char* argv[])
{
    ConcreteSubject* s = new ConcreteSubject();
    Observer* o = new ConcreteObserver(s);
    s->Attach(o);
    s->run();
    s->Detach(o);

    delete o;
    delete s;
}
