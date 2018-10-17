#include <iostream>
#include <string>

using namespace std;

class Handler {
    public:
        virtual void processor(int req) {
            if(m_successor) {
                m_successor->processor(req);
            } else {
                cout << "no handler req:" << req << endl;
            }
        };
        virtual bool myreq(int req) {
            return m_req == req;
        };
    protected:
        Handler(int req, Handler* succ): m_req(req), m_successor(succ) {};

    private:
        int m_req;
        Handler* m_successor;
};

class ConcreteHandler1 : public Handler {
    public:
        ConcreteHandler1(int req, Handler* next=NULL) : Handler::Handler(req, next) {};
        virtual void processor(int req) {
            if(myreq(req)) {
                cout << "ConcreteHandler1 process req:" << req << endl;
            } else {
                Handler::processor(req);
            }
        };
};

class ConcreteHandler2 : public Handler {
    public:
        ConcreteHandler2(int req, Handler* next=NULL) : Handler::Handler(req, next) {};
        virtual void processor(int req) {
            if(myreq(req)) {
                cout << "ConcreteHandler2 process req:" << req << endl;
            } else {
                Handler::processor(req);
            }
        };
};

class ConcreteHandler3 : public Handler {
    public:
        ConcreteHandler3(int req, Handler* next=NULL) : Handler::Handler(req, next) {};
        virtual void processor(int req) {
            if(myreq(req)) {
                cout << "ConcreteHandler3 process req:" << req << endl;
            } else {
                Handler::processor(req);
            }
        };
};

int main(int agrc, char* argv[])
{
    Handler* q3 = new ConcreteHandler3(3);
    Handler* q2 = new ConcreteHandler2(2, q3);
    Handler* q1 = new ConcreteHandler1(1, q2);

    q1->processor(1);
    q1->processor(2);
    q1->processor(3);
    q1->processor(4);
}

