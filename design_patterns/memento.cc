#include <iostream>
#include <string>


using namespace std;

class Memento;
class Originator {
    public:
        Memento* CreateMemento();
        void SetMemento(const Memento*);
        void SetState(int s) {
            _state = s;
        };
        int GetState() {
            return _state;
        };

    private:
        int _state;
};

class Memento {
    public:
        virtual ~Memento() { };

    private:
        friend class Originator;
        Memento() { };

        void SetState(int s) { _state = s;};
        int  GetState() const { return _state;};

    private:
        int _state;
};

Memento* Originator::CreateMemento() {
    Memento* m = new Memento();
    m->SetState(_state);

    return m;
}
void Originator::SetMemento(const Memento* m) {
    int s = m->GetState();
    _state = s;
}

int main(int argc, char* argv[])
{
    Originator* o = new Originator();
    o->SetState(1);
    Memento* m = o->CreateMemento();
    cout << o->GetState() << endl;
    o->SetState(2);
    cout << o->GetState() << endl;
    o->SetMemento(m);
    cout << o->GetState() << endl;
}

