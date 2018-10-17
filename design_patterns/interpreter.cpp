#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <stdlib.h>

using namespace std;

class VariableExp;
class Context {
    public:
        bool Lookup(const char* name) const;
        void Assign(VariableExp* exp, bool c);

    private:
        map<const char*, bool> LinkArr;
};

class BooleanExp {
    public:
        BooleanExp() { };
        virtual ~BooleanExp() { };

        virtual bool Evaluate(Context&) = 0;
        virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
        virtual BooleanExp* Copy() const = 0;
};

class VariableExp : public BooleanExp {
    public:
        VariableExp(const char* name) { _name = strdup(name); };
        virtual ~VariableExp() { free(_name);};

        virtual bool Evaluate(Context& aContext) { return aContext.Lookup(_name); };
        virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
            if( strcmp(name, _name) == 0) {
                return exp.Copy();
            } else {
                return new VariableExp(_name);
            }
        };
        virtual BooleanExp* Copy() const { return new VariableExp(_name); };
        const char* myname() { return _name; };

    private:
        char* _name;
};

class AndExp : public BooleanExp {
    public:
        AndExp(BooleanExp* op1, BooleanExp* op2) {
            _op1 = op1;
            _op2 = op2;
        };
        virtual ~AndExp() { };

        virtual bool Evaluate(Context& aContext) { return _op1->Evaluate(aContext) && _op2->Evaluate(aContext); };
        virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
            return new AndExp(_op1->Replace(name, exp), _op2->Replace(name, exp));
        };
        virtual BooleanExp* Copy() const {
            return new AndExp(_op1->Copy(), _op2->Copy() );
        };

    private:
        BooleanExp* _op1;
        BooleanExp* _op2;
};

class OrExp : public BooleanExp {
    public:
        OrExp(BooleanExp* op1, BooleanExp* op2) {
            _op1 = op1;
            _op2 = op2;
        };
        virtual ~OrExp() { };

        virtual bool Evaluate(Context& aContext) { return _op1->Evaluate(aContext) || _op2->Evaluate(aContext); };
        virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
            return new OrExp(_op1->Replace(name, exp), _op2->Replace(name, exp));
        };
        virtual BooleanExp* Copy() const {
            return new OrExp(_op1->Copy(), _op2->Copy() );
        };

    private:
        BooleanExp* _op1;
        BooleanExp* _op2;
};

class NotExp : public BooleanExp {
    public:
        NotExp(BooleanExp* op) {
            _op = op;
        };
        virtual ~NotExp() { };

        virtual bool Evaluate(Context& aContext) { return ! _op->Evaluate(aContext); };
        virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
            return new NotExp(_op->Replace(name, exp));
        };
        virtual BooleanExp* Copy() const {
            return new NotExp(_op->Copy());
        };

    private:
        BooleanExp* _op;
};

bool Context::Lookup(const char* name) const { return LinkArr.find(name)->second; };
void Context::Assign(VariableExp* exp, bool c) { LinkArr[exp->myname()]=c; };

// compute (z and x) or (y and (not x))
int main(int argc, char* argv[])
{
    BooleanExp* expression;
    Context context;

    VariableExp* x = new VariableExp("X");
    VariableExp* y = new VariableExp("Y");
    VariableExp* z = new VariableExp("Z");

    expression = new OrExp(
            new AndExp(z, x),
            new AndExp(y, new NotExp(x))
            );
    context.Assign(x, false);
    context.Assign(y, true);
    context.Assign(z, true);

    bool ret = expression->Evaluate(context);

    cout << ret << endl;
}

