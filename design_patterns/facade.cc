#include <iostream>
#include <string>

using namespace std;

class Book {
    public:
        virtual void open() {
            cout << "open and read book " << endl;
        };
        virtual void close() {
            cout << "close the book " << endl;
        };
};

class Code {
    public:
        virtual void start() {
            cout << "start coding" << endl;
        };
        virtual void stop() {
            cout << "stop coding" << endl;
        }
};

class Tv {
    public:
        virtual void watch() {
            cout << "start watch TV" << endl;
        };
        virtual void close() {
            cout << "close TV" << endl;
        };
};

class Facade {
    public:
        virtual void work() {
            cout << "---work day---" << endl;
            t.close();
            b.close();
            c.start();
        };
        virtual void sleep() {
            cout << "---sleep day---" << endl;
            c.stop();
            t.watch();
        };

    private:
        Book b;
        Code c;
        Tv   t;
};

int main(int argc, char* argv[])
{
    Facade* f = new Facade();
    f->work();
    f->sleep();

    delete f;
}

