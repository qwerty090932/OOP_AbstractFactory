#include <iostream>
#include <vector>
using namespace std;
struct MyContainerNode {
    int data;
    MyContainerNode *next;
};
template<typename T>
class MyContainer {
    MyContainerNode *head= nullptr;
    MyContainerNode *tail= nullptr;
    int size = 0;
    int _n;
    T* mCont;
public:
//    void pushBack(T& value) {
//        MyContainerNode *new_tail = new MyContainerNode{value, nullptr};
//        if (tail) {
//            tail -> next = new_tail;
//        } else {
//            head = new_tail;
//        }
//        tail = new_tail;
//        size++;
//    }
    MyContainer(int n = 1) : _n(n) {
        mCont = new T[n];
        size++;
    }
    T& operator[] (const int&n) { //перегружаем оператор скобки
        if (n>0 && n < _n)
            return mCont[n];
        return mCont[0]; // Если вышли за границы массива, возвращаем первый элемент, как исключение
    }
    MyContainerNode* pop_front() {
        MyContainerNode* current = head;
        if ((head) && (head != tail)) {
            cout << "Произвели" << endl;
            head = head->next;
            return current;
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
template<bool Const, typename T>
class MyIterator {
    friend class MyContainer<T>;
    friend class MyIterator<!Const, T>;

    using nodePointer = std::conditional_t<Const, const MyContainerNode*, MyContainerNode*>;
    nodePointer ptr;
public:
    using difference_type = std::ptrdiff_t;

    using value_type = T;

    using pointer = std::conditional_t<Const, const int*, int*>;

    using reference = std::conditional_t<Const, const int&, int&>;
    using iterator_category = std::forward_iterator_tag;

    reference operator*() const { return ptr->data; }

    auto& operator++() { ptr = ptr->next; return *this; }
    auto operator++(int) { auto result = *this; ++*this; return result; }

    template<bool R>
    bool operator==(const MyIterator<R, T>& rhs) const
    { return ptr == rhs.ptr; }

    template<bool R>
    bool operator!=(const MyIterator<R, T>& rhs) const
    { return ptr != rhs.ptr; }

    operator MyIterator<true, T>() const
    { return MyIterator<true, T>{ptr}; }
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

    void releaseCar(IEngine* engine) override {
        cout << "Собрали японский автомобиль: ";
        engine->releaseEngine();
    }
};

class EuropeanCar : public ICar {
public:
    void releaseCar(IEngine* engine) override {
        cout << "Собрали европейский автомобиль: ";
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

    IFactory* eFactory = new EuropeanFactory();

    IEngine* eEngine = eFactory->createEngine();
    ICar* eCar = eFactory->createCar();

    eCar->releaseCar(jEngine);

    MyContainer<ICar*> seriesNumbers; // добавляем серийные номера в наш контейнер, что-то типо очереди
    seriesNumbers[0] = jCar;
    cout << seriesNumbers.get_size() << endl;
}
