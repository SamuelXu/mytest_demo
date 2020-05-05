#include <iostream>
#include <string>
#include <map>

using namespace std;

class Flyweight {
    public:
        virtual void show() = 0;
        virtual void setid(int id) {
            m_id = id;
            return ;
        };
        virtual int getid() {
            return m_id;
        };
    protected:
        Flyweight() {};
        int m_id;
};

class ConcreteFlyweight: public Flyweight {
    public:
        ConcreteFlyweight(string s):u_string(s){};
        virtual void show() {
            cout << "id:" << Flyweight::m_id << " shared:" << u_string << endl;
        };
    private:
        string u_string;
};

class UnsharedConcreteFlyweight: public Flyweight {
    public:
        UnsharedConcreteFlyweight(string s):un_str(s){};
        virtual void show() {
            cout << "id:" << Flyweight::m_id << " unshared:" << un_str << endl;
        };
    private:
        string un_str;
};

class FlyweightFactory {
    public:
        virtual Flyweight* create(string m_s) {
            map<string, Flyweight*>::iterator it = _fw.find(m_s);
            if(it != _fw.end()) {
                cout << "use exist obj:" << _fw.size() << " ";
                return it->second;
            } else {
                Flyweight* nfw = new ConcreteFlyweight(m_s);
                _fw[m_s] = nfw;
                return nfw;
            }
        };

        virtual Flyweight* createUnshared(string m_s) {
            return new UnsharedConcreteFlyweight(m_s);
        };
        virtual ~FlyweightFactory() {
            map<string, Flyweight*>::iterator it=_fw.begin();
            while(it!=_fw.end()) {
                delete it->second;
                it++;
            }
            _fw.clear();
        };
    private:
        map<string, Flyweight*> _fw;
};

int main(int argc, char* argv[]) 
{
    FlyweightFactory* ff = new FlyweightFactory();
    for(int i=0;i<10;i++) {
        Flyweight* fw = ff->create("shared");
        fw->setid(i);
        fw->show();
    }
    for(int i=0;i<10;i++) {
        Flyweight* fw1 = ff->createUnshared("shared");
        fw1->setid(i);
        fw1->show();
        delete fw1;
    }

    delete ff;
}

