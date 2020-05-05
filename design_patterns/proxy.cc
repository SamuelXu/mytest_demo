#include <iostream>
#include <string>
#include <map>

using namespace std;


class subject {
    public:
        virtual void show() = 0;
    protected:
        subject(){};
};

class concreteSubject : public subject {
    public:
        virtual void show() {
            cout << "show data: " << m_data << endl;
        };
        concreteSubject(string data) : m_data(data) {
        };
    private:
        string m_data;
};

class proxy : public subject {
    public:
        virtual void show() {
            if( !m_sub) {
                m_sub = new concreteSubject(m_data);
            }

            m_sub->show();
        };
        proxy(string data) : m_data(data),m_sub(NULL) {};

        ~proxy() {
            if(m_sub) {
                delete m_sub;
            };
        };
    private:
        string m_data;
        subject* m_sub;
};


int main(int argc, char* argv[])
{
    proxy* p = new proxy("virtual proxy");
    p->show();
    delete p;
}
