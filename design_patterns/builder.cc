#include "iostream"
#include "string"

using namespace std;

class product {
    public:
        void setPartA(string a) {this->a = a;};
        void setPartB(string b) {this->b = b;};

        void show() { cout << "complete product:(" << a << "," << b << ")" << endl;};

    private:
        string a;
        string b;
};

class builder {
    public:
        virtual void buildPart(string a, string b) = 0;
        virtual product* getProduct() = 0;
};

class builderA: public builder {
    public:
        builderA() {this->p1 = 0;};

        virtual void buildPart(string a, string b) {
            this->p1 = new product();
            this->p1->setPartA(a);
            this->p1->setPartB(b);
        };
        product* getProduct() {
            return this->p1;
        };

    private:
        product *p1;
};

class director {
    public:
        product* makep1() {
            builderA* b1 = new builderA();
            b1->buildPart("baoma", "X5");
            return b1->getProduct();
        };
        product* makep2() {
            builderA* b2 = new builderA();
            b2->buildPart("aodi", "Q7");
            return b2->getProduct();
        };

};

int main(int argc, char* argv[])
{
    director* d1 = new director();
    product* p1 = d1->makep1();
    p1->show();
    product* p2 = d1->makep2();
    p2->show();
}

