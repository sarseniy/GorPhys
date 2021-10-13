#include <iostream>

class Shape {
public:
    virtual void show() = 0;
};

class Line : public Shape {
public:
    void show() override {
        std::cout << "It's Line\n";
    }
};

class Square : public Shape {
public:
    void show() override {
        std::cout << "It's Square\n";
    }
};

class Rectangle : public Shape {
public:
    void show() override {
        std::cout << "It's Rectangle\n";
    }
};

class NullShape : public Shape {
public:
    void show() override {
        std::cout << "It's NullShape\n";
    }
};

Shape* generator() {
    int i = rand() % 4;
    if (i == 0)
    {
        return new Line;
    }
    if (i == 1)
    {
        return new Square;
    }
    if (i == 2)
    {
        return new Rectangle;
    }
    if (i == 3)
    {
        return new NullShape;
    }
}

int main()
{    
    for (size_t i = 0; i < 20; i++)
    {
        Shape* x = generator();
        if (typeid(*x) != typeid(NullShape))
        {
            x->show(); 
        }
        else
        {
            std::cout << "Oops!\n";
        }
    }
}

