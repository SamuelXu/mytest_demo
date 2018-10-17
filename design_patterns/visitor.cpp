#include <iostream>
#include <string>
#include <list>

using namespace std;

class Visitor;
class Element {
    public:
        virtual void accept(Visitor* v) = 0;
        virtual void action() = 0;
};

class Visitor {
    public:
        virtual void visit(Element* e) = 0;
};

class ConcreteVisitor : public Visitor {
    public:
        virtual void visit(Element* e) {
            e->action();
        };
};

class ConcreteElement1 : public Element {
    public:
        virtual void accept(Visitor* v) {
            v->visit(this);
        };
        virtual void action() {
            cout << "process ConcreteElement1" << endl;
        };
};

class ConcreteElement2 : public Element {
    public:
        virtual void accept(Visitor* v) {
            v->visit(this);
        };
        virtual void action() {
            cout << "process ConcreteElement2" << endl;
        };
};

class ObjectStructure {
    public:
        list<Element *> getlist() {
            for(int i=0;i<10;i++) {
                if(i%2==0) _es.push_back(new ConcreteElement1());
                if(i%2==1) _es.push_back(new ConcreteElement2());
            }
            return _es;
        };
        ~ObjectStructure() {
            for(list<Element*>::iterator it=_es.begin();it!=_es.end();it++) {
                delete (*it);
            }
            _es.clear();
        };

    private:
        list<Element *> _es;
};

int main(int argc, char* argv[])
{
    ObjectStructure obj;
    list<Element*> l(obj.getlist());
    Visitor* v = new ConcreteVisitor();
    for(list<Element*>::iterator it=l.begin();it!=l.end();it++) {
        (*it)->accept(v);
    }
}

