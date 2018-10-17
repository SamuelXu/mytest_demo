#include <iostream>
#include <string>

using namespace std;

class State;
class Context {
    public:
        Context() { };
        virtual void Request();
        void SetState(State* s) {
            _s = s;
        };

    private:
        State* _s;
};

class State {
    public:
        virtual void Handle() = 0;
};

class StartState : public State {
    public:
        virtual void Handle() {
            cout << "handle start state" << endl;
        };
};

class StopState : public State {
    public:
        virtual void Handle() {
            cout << "handle stop state" << endl;
        };
};

void Context::Request() {
    _s->Handle();
};

int main(int argc, char* argv[])
{
    Context c;
    StartState* b = new StartState();
    StopState* e = new StopState();
    c.SetState(b);
    c.Request();
    c.SetState(e);
    c.Request();
}
