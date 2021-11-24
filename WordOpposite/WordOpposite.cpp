#include <iostream>
#include <string>
#include <map>

class Word {
public:
    Word() : Word("")
    {}

    Word(std::string a) : data(a)
    {}
    
    bool operator<(Word const& rha) const {
        return data < rha.data;
    }

    void print() const {
        std::cout << data;
    }

    friend std::ostream& operator<< (std::ostream& out, const Word& word)
    {
        out << word.data;

        return out;
    }
private:
    std::string data;
};

class Opposite {
public:
    Opposite() : Opposite("")
    {}

    Opposite(std::string a) : data(a)
    {}

    void print() {
        std::cout << data;
    }

    friend std::ostream& operator<< (std::ostream& out, const Opposite& word)
    {
        out << word.data;

        return out;
    }
private:
    std::string data;
};



int main()
{
    std::map<Word, Opposite> m;
    m.emplace("black", "white");
    m.emplace("white", "black");

    m.emplace("cold", "hot");
    m.emplace("hot", "cold");
    for (auto it = m.begin(); it != m.end(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
    return 0;
}
