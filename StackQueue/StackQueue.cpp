#include <iostream>

class DataStruct {
public:
    virtual void push(int value) = 0;
    virtual int pop() = 0;
    virtual ~DataStruct() {

    }
};

class Queue : public DataStruct {
public:
    Queue() : data(INT_MAX), next(nullptr)
    {}

    void push(int value) override {
        Queue* tmp = this;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new Queue(value);
    }

    ~Queue()
    {
        if (next != nullptr) delete next;
    }

    int pop() override {
        Queue* tmp = this->next->next;
        int ans = this->next->data;
        this->next->next = nullptr;
        delete this->next;
        this->next = tmp;
        return ans;
    }
private:
    Queue(int data) : data(data), next(nullptr)
    {}

    int data;
    Queue* next;
};

class Stack : public DataStruct {
public:
    Stack() : data(INT_MAX), next(nullptr)
    {}

    void push(int value) override {
        Stack* tmp = this;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new Stack(value);
    }

    ~Stack()
    {
        if (next != nullptr) delete next;
    }

    int pop() override {
        Stack* tmp = this->next;
        Stack* tmp1 = this;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            tmp1 = tmp1->next;
        }
        int ans = tmp->data;
        tmp->next = nullptr;
        delete tmp;
        tmp1->next = nullptr;
        return ans;
    }
private:
    Stack(int data) : data(data), next(nullptr)
    {}

    int data;
    Stack* next;
};

DataStruct* DataStructFactory(char s) {
    if (s == 's')
    {
        return new Stack;
    }
    if (s == 'q')
    {
        return new Queue;
    }
    return nullptr;
}

int main()
{
    char s;
    std::cin >> s;

    DataStruct* data = DataStructFactory(s);

    std::cout << typeid(*data).name() << '\n';

    data->push(1);
    data->push(2);
    data->push(3);
    std::cout << data->pop() << ' ';
    data->push(4);
    std::cout << data->pop() << ' ';
    std::cout << data->pop() << ' ';
    std::cout << data->pop() << ' ';
    data->push(5);
    std::cout << data->pop() << ' ';
}
