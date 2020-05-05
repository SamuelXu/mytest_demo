#include <iostream>
#include <string>

using namespace std;

class abProto {
    public:
        virtual abProto* clone() const = 0;
        virtual void show() = 0;
};

class Prototype: public abProto {
    public:
        Prototype() : num(0) {};
        Prototype(const Prototype& that) {
            this->num = that.num + 1;
        };
        virtual abProto* clone() const {
            return new Prototype(*this);
        };
        virtual void show() {
            cout << "clone last: " << num << endl;
        };

    private:
        int num;
};

int main(int argc, char* argv[])
{
    Prototype p0;
    abProto* ap[10];
    ap[0] = p0.clone();
    ap[0]->show();
    for(int i=1;i<10;i++) {
        ap[i] = ap[i-1]->clone();
        ap[i]->show();
    }
    for(int i=0;i<10;i++) {
        delete ap[i];
    }

    return 0;
}
