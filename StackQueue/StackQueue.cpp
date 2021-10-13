#include <iostream>

class DataStruct {
public:
    virtual void push(int value) = 0;
    virtual int pop() = 0;
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

    int pop() override {
        Queue* tmp = this->next->next;
        int ans = this->next->data;
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

    int pop() override {
        Stack* tmp = this->next;
        Stack* tmp1 = this;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            tmp1 = tmp1->next;
        }
        int ans = tmp->data;
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

    std::cout << typeid(*data).name();

    /*Queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    std::cout << queue.pop() << ' ';
    queue.push(4);
    std::cout << queue.pop() << ' ';
    std::cout << queue.pop() << ' ';
    std::cout << queue.pop() << ' ';
    queue.push(5);
    std::cout << queue.pop() << ' ';

    std::cout << '\n';

    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << stack.pop() << ' ';
    stack.push(4);
    std::cout << stack.pop() << ' ';
    std::cout << stack.pop() << ' ';
    std::cout << stack.pop() << ' ';
    stack.push(5);
    std::cout << stack.pop() << ' ';*/
}
