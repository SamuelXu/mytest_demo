#include "iostream"
#include "string"


using namespace std;

class abProduct {
    public:
        abProduct(){};

        virtual void call() = 0;
};

class abFactory {
    public:
        abFactory(){};

        virtual abProduct* createProduct() = 0;
};


class productA : public abProduct {
    public:
        productA() {};

        virtual void call() {
            cout<< "call me productA!" << endl;
        }
};

class productB : public abProduct {
    public:
        productB() {};

        virtual void call() {
            cout<< "call me productB!" << endl;
        }
};

class factoryA : public abFactory {
    public:
        factoryA(){ };

        abProduct* createProduct() {
            return new productA();
        }
        abProduct* createProductA() {
            return new productA();
        }
        abProduct* createProductB() {
            return new productB();
        }
};

class factoryB : public abFactory {
    public:
        factoryB(){ };

        abProduct* createProduct() {
            return new productB();
        }
};

template<typename MyProduct>
class MyFactory: public abFactory {
    public:
        abProduct* createProduct() {
            return new MyProduct;
        }
};

int main(int argc, char* argv[]) {
    factoryA a;
    abProduct* aa = a.createProduct();
    aa->call();
    abProduct* a1 = a.createProductA();
    a1->call();
    abProduct* a2 = a.createProductB();
    a2->call();
    factoryB b;
    abProduct* bb = b.createProduct();
    bb->call();
    delete aa;
    delete bb;

    MyFactory<productA> c;
    abProduct* cc = c.createProduct();
    cc->call();
    delete cc;
}

