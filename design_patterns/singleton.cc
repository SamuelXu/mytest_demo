#include <iostream>
#include <string>

using namespace std;

template <typename T>
class singleton {
    public:
        static T& instance() {
            static T value;
            return value;
        };

    private:
        singleton();
        ~singleton();
};

class product {
    public:
        void show() {
            cout << this << endl;
        };
        template <class T> friend class singleton;

    private:
        product() {};
        ~product() {};
};

int main(int argc, char* argv[])
{
    for(int i=0;i<10;i++) {
        product& s = singleton<product>::instance();
        cout << "address ";
        s.show();
    }
}
