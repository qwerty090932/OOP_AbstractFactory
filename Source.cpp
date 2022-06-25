#include <iostream>
#include <vector>
using namespace std;
struct MyContainerNode {
    int data;
    MyContainerNode *next;
};
class MyContainer {
    MyContainerNode *head= nullptr;
    MyContainerNode *tail= nullptr;
    int size = 0;
public:
    void pushBack(int value) {
        MyContainerNode *new_tail = new MyContainerNode{value, nullptr};
        if (tail) {
            tail -> next = new_tail;
        } else {
            head = new_tail;
        }
        tail = new_tail;
        size++;
    }

    MyContainerNode* pop_front() {
        MyContainerNode* current = head;
        if ((head) && (head != tail)) {
            cout << "Произвели" << endl;
            head = head->next;
        } else if(head == tail) {
            cout << "Произвели" << endl;
            head = nullptr;
            tail = nullptr;
            return current;
        }
        else {
            cout << "Очередь пуста" << endl;
            return nullptr;
        }
    }

    int get_size() { return size; }

    ~MyContainer() {
        for(MyContainerNode *next, *el = head; el != nullptr; el = next) {
            next = el -> next;
            delete el;
        }
    }
};
template<bool Const>
class MyIterator {
    friend class MyContainer;
    friend class MyIterator<!Const>;

    using nodePointer = std::conditional_t<Const, const MyContainerNode*, MyContainerNode*>;
    nodePointer ptr;
public:
    using difference_type = std::ptrdiff_t;

    using value_type = int;

    using pointer = std::conditional_t<Const, const int*, int*>;

    using reference = std::conditional_t<Const, const int&, int&>;
    using iterator_category = std::forward_iterator_tag;

    reference operator*() const { return ptr->data; }

    auto& operator++() { ptr = ptr->next; return *this; }
    auto operator++(int) { auto result = *this; ++*this; return result; }

    template<bool R>
    bool operator==(const MyIterator<R>& rhs) const
    { return ptr == rhs.ptr; }

    template<bool R>
    bool operator!=(const MyIterator<R>& rhs) const
    { return ptr != rhs.ptr; }

    operator MyIterator<true>() const
    { return MyIterator<true>{ptr}; }
};
class IEngine {
public:
    virtual void releaseEngine() = 0;
};
class JapaneseEngine : public IEngine {
public:
    void releaseEngine() override {
        cout << "Japanese engine" << endl;
    }
};

class EuropeanEngine : public IEngine {
public:
    void releaseEngine() override {
        cout << "European engine" << endl;
    }
};

class ICar {
    int seriesNumber = rand() % 10000 + 10000; // создавая автомобиль присваиваем ему серийный номер
public:
    int getNumber() {
        return seriesNumber;
    }
    virtual void releaseCar(IEngine* engine) = 0;
};

class JapaneseCar : public ICar {
public:
//    JapaneseCar() {
//        int seriesNumber = rand() % 10000 + 10000;
//    }
    void releaseCar(IEngine* engine) override {
        cout << "Japanese Car ";
        engine->releaseEngine();
    }
};

class EuropeanCar : public ICar {
public:
    void releaseCar(IEngine* engine) override {
        cout << "European Car ";
        engine->releaseEngine();
    }
};

class IFactory {
public:
    virtual IEngine* createEngine() = 0;
    virtual ICar* createCar() = 0;
};

class JapaneseFactory : public IFactory {
public:
    IEngine* createEngine() override {
        return new JapaneseEngine();
    }
    ICar* createCar() override {
        return new JapaneseCar();
    }
};

class EuropeanFactory : public IFactory {
public:
    IEngine* createEngine() override {
        return new EuropeanEngine();
    }
    ICar* createCar() override {
        return new EuropeanCar();
    }
};

int main()
{

    IFactory* jFactory = new JapaneseFactory();

    IEngine* jEngine = jFactory->createEngine();
    ICar* jCar = jFactory->createCar();

    jCar->releaseCar(jEngine);
    MyContainer seriesNumbers; // добавляем серийные номера в наш контейнер, что-то типо очереди
    seriesNumbers.pushBack(jCar->getNumber());
    seriesNumbers.pop_front();
}

