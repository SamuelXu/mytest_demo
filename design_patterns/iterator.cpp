#include <iostream>
#include <string>
#include <list>

using namespace std;

#define DEFAULT_LIST_CAPACITY 12

template <class Item>
class Iterator {
    public:
        virtual void First() = 0;
        virtual void Next() = 0;
        virtual bool IsDone() const = 0;
        virtual Item CurrentItem() const = 0;
    protected:
        Iterator() {};
};

template <class Item>
class List {
    public:
        List(long size = DEFAULT_LIST_CAPACITY) {
            _l = new Item[size];
            _size = size;
            _index = 0;
        };
        ~List() { delete []_l;};

        long Count() const { return _index; };
        Item& Get(long index) const { return _l[index];};
        bool Append(Item item) {
            if(_index >= _size) {
                cout << "index out of bounds error" << endl;
                return false;
            }
            _l[_index] = item;
            _index++;
            return true;
        };
        Iterator<Item>* CreateIterator();

    private:
        Item* _l;
        long _index;
        long _size;
};

template <class Item>
class ListIterator : public Iterator<Item> {
    public:
        ListIterator(const List<Item>* aList):_list(aList),_current(0) { };
        virtual void First() {
            _current = 0;
        };
        virtual void Next() {
            _current++;
        };
        virtual bool IsDone() const {
            return _current >= _list->Count();
        };
        virtual Item CurrentItem() const {
            if(IsDone()) {
                cout << "iterator is done" << endl;
                return false;
            }
            return _list->Get(_current);
        };

    private:
        const List<Item>* _list;
        long _current;
};

template <class Item>
class IteratorPtr {
    public:
        IteratorPtr(Iterator<Item>* i):_i(i) { };
        ~IteratorPtr() { delete _i;};

        Iterator<Item>* operator->() { return _i; };
        Iterator<Item>& operator*() { return *_i; };

    private:
        IteratorPtr(const IteratorPtr&);
        IteratorPtr& operator=(const IteratorPtr&);

    private:
        Iterator<Item>* _i;
};

template <class Item>
Iterator<Item>* List<Item>::CreateIterator() {
    return new ListIterator<Item>(this);
};

int main(int argc, char* argv[])
{
    List<int>* plist = new List<int>(10);
    for(int i=0;i<11;i++) {
        plist->Append(i);
    }
    cout << plist->Count() << endl;
    cout << "--------list get-----------------" << endl;
    for(int i=0;i<10;i++) {
        cout << plist->Get(i) << endl;
    }

    cout << "--------ListIterator-------------" << endl;
    ListIterator<int> iter(plist);
    for(iter.First();!iter.IsDone();iter.Next()) {
        cout << iter.CurrentItem() << endl;
    }

    cout << "--------ListIteratorPtr-------------" << endl;
    Iterator<int>* piter = plist->CreateIterator();
    for(piter->First();!piter->IsDone();piter->Next()) {
        cout << piter->CurrentItem() << endl;
    }
    delete piter;
    cout << "--------IteratorPtr---use trait-----" << endl;
    IteratorPtr<int> ptr(plist->CreateIterator());
    for(ptr->First();!ptr->IsDone();ptr->Next()) {
        cout << ptr->CurrentItem() << endl;
    }

    delete plist;
}

