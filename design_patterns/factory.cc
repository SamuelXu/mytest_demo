#include <iostream>
#include <string>

using namespace std;

class Product {
    public:
        virtual void call() { cout << "product ok" << endl;}
};

class Factory {
    public:
        virtual Product* createProduct() = 0;
};

template<typename TheProduct>
class RealFactory: public Factory {
    public:
        virtual Product* createProduct() {
            return new TheProduct;
        }
};

class MyProduct:public Product {
    public:
        void call() { cout << "my product ok" << endl; }
};

int main(int argc, char* argv[]) {
    RealFactory<MyProduct> fac;
    Product* prod = fac.createProduct();
    prod->call();
    return 0;
}
