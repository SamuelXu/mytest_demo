#include <iostream>
#include <string>

using namespace std;

class Imp {
    public:
        virtual void showImp() = 0;
};

class concreteImpA : public Imp {
    public:
        virtual void showImp() {
            cout << "concreteImpA" << endl;
        };
};

class concreteImpB : public Imp {
    public:
        virtual void showImp() {
            cout << "concreteImpB" << endl;
        };
};

class Abstraction {
    public:
        virtual void product() = 0;

    protected:
        Imp* _imp;
};

class RefinedAbstractionA : public Abstraction {
    public:
        virtual void product() {
            cout << "RefinedAbstractionA bind->";
            _imp->showImp();
        };
        RefinedAbstractionA(Imp* useimp) {
            _imp = useimp;
        };
};

class RefinedAbstractionB : public Abstraction {
    public:
        virtual void product() {
            cout << "RefinedAbstractionB bind->";
            _imp->showImp();
        };
        RefinedAbstractionB(Imp* useimp) {
            _imp = useimp;
        };
};


//class RefinedAbstractionA : public Abstraction {
//    public:
//        virtual void product() {
//            cout << "RefinedAbstractionA bind->";
//            _imp->showImp();
//        };
//        RefinedAbstractionA() {
//            _imp = new concreteImpA;
//        };
//};
//
//class RefinedAbstractionB : public Abstraction {
//    public:
//        virtual void product() {
//            cout << "RefinedAbstractionB bind->";
//            _imp->showImp();
//        };
//        RefinedAbstractionB() {
//            _imp = new concreteImpB;
//        };
//};


//或者可以用工厂在具体实现中绑定，这样就可以不暴露接口部分，接口部分对客户完全隐藏
int main(int argc, char* argv[])
{
    concreteImpA impa;
    concreteImpB impb;
    RefinedAbstractionA a0(&impa);
    a0.product();
    RefinedAbstractionA a1(&impb);
    a1.product();
    RefinedAbstractionB b0(&impa);
    b0.product();
    RefinedAbstractionB b1(&impb);
    b1.product();
}

