#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Component {
    public:
        virtual ~Component() {};
        virtual void show() = 0;

        virtual void add(Component* comp) {
            cout << "leaf add error!" << endl;
        };
        virtual void remove(Component* comp) {
            cout << "leaf remove error!" << endl;
        };

    protected:
        Component(string name): m_strname(name) {};
    private:
        Component();

    protected:
        string m_strname;
};

class Leaf : public Component {
    public:
        virtual ~Leaf() {};

        Leaf(string name):Component(name) {};
        virtual void show() {
            cout << "this is leaf -> " << this->m_strname << endl;
        };

    private:
        Leaf();
};

class Composite : public Component {
    public:
        Composite(string name) : Component(name) {};
        virtual ~Composite() {
            vector<Component *>::iterator it = _comp1.begin();
            while(it!=_comp1.end()) {
                delete *it;
                it = _comp1.erase(it);
            }
//            for(vector<Component *>::iterator it=_comp1.begin();it!=_comp1.end();it++) {
//                delete *it;
//                *it = NULL;
//            }
//            _comp1.clear();
        };

        virtual void show() {
            cout << "parent: " << m_strname << endl;
            for(vector<Component *>::iterator it=_comp1.begin();it!=_comp1.end();it++) {
                (*it)->show();
            }
        };

        virtual void add(Component* comp) {
            _comp1.push_back(comp);
        };
        virtual void remove(Component* comp) {
            for(vector<Component *>::iterator it=_comp1.begin();it!=_comp1.end();it++) {
                if(*it == comp) {
                    delete comp;
                    _comp1.erase(it);
                    break;
                }
            }
        };

    private:
        vector<Component *> _comp1;
};

int main(int argc, char* argv[])
{
    Component* root = new Composite("company");
    Component* T = new Composite("technolagy");
    Component* P = new Composite("product");
    Component* m = new Leaf("se");
    root->add(T);
    root->add(P);
    T->add(m);

    root->show();
}

