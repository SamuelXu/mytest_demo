#include <iostream>
#include <string>

using namespace std;

class Receiver {
    public:
        virtual void actionshow() {
            cout << "recv show command" << endl;
        };
};

class Command {
    public:
        virtual void execute() = 0;
        Command(Receiver* recv):precv(recv) { };
        Receiver* getrecv() { return precv;};

    private:
        Receiver* precv;
};

class ShowCommand : public Command {
    public:
        virtual void execute() {
            this->getrecv()->actionshow();
        };
        ShowCommand(Receiver* recv):Command(recv) { };
};

class Invoker {
    public:
        Invoker(Command* cmd):pcmd(cmd) { };
        virtual void show() {
            pcmd->execute();
        };

    private:
        Command* pcmd;
};

int main(int argc, char* argv[])
{
    Receiver* recv = new Receiver();
    Command* cmd = new ShowCommand(recv);
    Invoker* ivk = new Invoker(cmd);

    ivk->show();

    return 0;
}
