#include <iostream>

template <typename T>
class ArrObj {
public:
    ArrObj() {
        index = 0;
        data = 0;
    }
    ArrObj(long long unsigned int index, T data) : index(index), data(data)
    {}
    template<typename T> friend class ListList;
protected:
    long long unsigned int index;
    T data;
};

template <typename T>
class ListObj : protected ArrObj<T> {
public:
    ListObj() : ArrObj<T>()
    {
        prev = nullptr;
        next = nullptr;
    }

    ListObj(long long unsigned int index, T data) : ArrObj<T>(index, data)
    {
        prev = nullptr;
        next = nullptr;
    }
    template<typename T> friend class ListList;
    template<typename T> friend class ArrList;
protected:
    ListObj<T>* prev;
    ListObj<T>* next;
};

template <typename T>
class ListList : protected ListObj<T> {
public:
    ListList() : ListObj<T>()
    {
        start = nullptr;
        end = nullptr;
    }
protected:
    void put(long long unsigned int index, T data) {
        ListObj<T>* tmp = new ListObj<T>(index, data);
        if (start == nullptr and end == nullptr)
        {
            start = tmp;
            end = tmp;
        }
        else
        {
            end->next = tmp;
            tmp->prev = end;
            end = tmp;
        }
    }

    void remove(long long unsigned int index) {
        ListObj<T>* tmp = start;
        while (tmp->next != nullptr)
        {
            if (tmp->index == index)
            {
                break;
            }
            tmp = tmp->next;
        }
        if (tmp->index != index)
        {
            return;
        }
        if (tmp->prev != nullptr) tmp->prev->next = tmp->next;
        if (tmp->next != nullptr) tmp->next->prev = tmp->prev;
        if (tmp == start) start = tmp->next;
        if (tmp == end) end = tmp->prev;
        delete tmp;
    }

    ListObj<T>* find(long long unsigned int index) {
        ListObj<T>* tmp = start;
        if (start == nullptr) return nullptr;
        while (tmp->next != nullptr)
        {
            if (tmp->index == index)
            {
                return tmp;
            }
            tmp = tmp->next;
        }
        if (tmp->index == index)
        {
            return tmp;
        }
        return nullptr;
    }

    ~ListList() {
        while (end != nullptr)
        {
            remove(end->index);
        }
    }

    ListObj<T>* start;
    ListObj<T>* end;
};

template <typename T>
class ArrList : protected ListList<T> {
public:
    ArrList() : ListList<T>(), size(0)
    {}

    T& operator[](long long unsigned int index) {
        ListObj<T>* tmp = this->find(index);
        if (tmp != nullptr)
        {
            return tmp->data;
        }
        if (tmp == nullptr)
        {
            ListList<T>::put(index, 0);
            size++;
            return ListList<T>::find(index)->data;

        }
    }

    T const& operator[](long long unsigned int index) const {
        ListObj<T>* tmp = ListList<T>::find(index);
        if (tmp != nullptr)
        {
            return tmp->data;
        }
        if (tmp == nullptr)
        {
            return NULL;
        }
    }

private:
    long long unsigned int size;
};

int main()
{
    ArrList<int> arr;
    arr[0] = 1;
    std::cout << arr[0] << '\n';
    arr[5566666] = 995544;
    std::cout << arr[5566666];
    return 0;
}
