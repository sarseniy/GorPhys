#include <iostream>
#include <vector>

double f(double x, double y)
{
    return x * x - 2 * y;;
}

class Solver {
public:
    virtual void solve() = 0;
    virtual void print() = 0;
    ~Solver() {}
};

class Euler : public Solver {
public:
    Euler(double (*fcnPtr)(double, double), double h=0.1, double start=0, double end=1, double y_0=1) :
        fcnPtr(fcnPtr),h(h), start(start), end(end), y_0(y_0)
    {
        steps = (end - start) / h;
        for (size_t i = 0; i < 2; i++)
        {
            std::vector<double> tmp;
            solution.push_back(tmp);
            for (size_t j = 0; j < steps + 1; j++)
            {
                if (!i)
                {
                    solution[i].push_back((double)j / 10);
                }
                else
                {
                    solution[i].push_back(y_0);
                }
            }
        }
    }

    void solve() override {
        for (size_t x = 1; x < steps + 1; x += 1)
        {
            solution[1][x] = solution[1][x - 1] + h * fcnPtr(solution[0][x - 1], solution[1][x - 1]);
        }
    }

    void print() override {
        for (size_t i = 0; i < steps + 1; i++)
        {
            std::cout << solution[0][i] << ' ' << solution[1][i] << '\n';
        }
        std::cout << '\n';
    }

private:
    double (*fcnPtr)(double, double);
    double h;
    double start;
    double end;
    double y_0;
    size_t steps;
    std::vector<std::vector<double>> solution;
};

class Euler_2 : public Solver
{
public:
    Euler_2(double (*fcnPtr)(double, double), double h = 0.1, double start = 0, double end = 1, double y_0 = 1) :
        fcnPtr(fcnPtr), h(h), start(start), end(end), y_0(y_0)
    {
        steps = (end - start) / h * 2;
        for (size_t i = 0; i < 2; i++)
        {
            std::vector<double> tmp;
            solution.push_back(tmp);
            for (size_t j = 0; j < steps + 1; j++)
            {
                if (!i)
                {
                    solution[i].push_back((double)j / (2 * 10));
                }
                else
                {
                    solution[i].push_back(y_0);
                }
            }
        }
    }
    void solve() {
        for (size_t n = 1; n < steps + 1; n += 1)
        {
            if (n % 2 == 1) {
                solution[1][n] = solution[1][n - 1] + h / 2 * fcnPtr(solution[0][n - 1], solution[1][n - 1]);
            }
            else
            {
                solution[1][n] = solution[1][n - 2] + h * fcnPtr(solution[0][n - 1] + h / 2, solution[1][n - 1]);
            }
        }
    }

    void print() override {
        for (size_t i = 0; i < steps + 1; i++)
        {
            std::cout << solution[0][i] << ' ' << solution[1][i] << '\n';
        }
        std::cout << '\n';
    }

private:
    double (*fcnPtr)(double, double);
    double h;
    double start;
    double end;
    double y_0;
    size_t steps;
    std::vector<std::vector<double>> solution;
};

class RK : public Solver {
public:
    RK(double (*fcnPtr)(double, double), double h = 0.1, double start = 0, double end = 1, double y_0 = 1) :
        fcnPtr(fcnPtr), h(h), start(start), end(end), y_0(y_0)
    {
        steps = (end - start) / h;
        for (size_t i = 0; i < 2; i++)
        {
            std::vector<double> tmp;
            solution.push_back(tmp);
            for (size_t j = 0; j < steps + 1; j++)
            {
                if (!i)
                {
                    solution[i].push_back((double)j / 10);
                }
                else
                {
                    solution[i].push_back(y_0);
                }
            }
        }
    }

    void solve() {
        for (size_t n = 1; n < steps + 1; n += 1)
        {
            double k1 = fcnPtr(solution[0][n - 1], solution[1][n - 1]);
            double k2 = fcnPtr(solution[0][n - 1] + h / 2, solution[1][n - 1] + h * k1 / 2);
            double k3 = fcnPtr(solution[0][n - 1] + h / 2, solution[1][n - 1] + h * k2 / 2);
            double k4 = fcnPtr(solution[0][n - 1] + h, solution[1][n - 1] + h * k3);

            solution[1][n] = solution[1][n - 1] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        }
    }

    void print() override {
        for (size_t i = 0; i < steps + 1; i++)
        {
            std::cout << solution[0][i] << ' ' << solution[1][i] << '\n';
        }
        std::cout << '\n';
    }

private:
    double (*fcnPtr)(double, double);
    double h;
    double start;
    double end;
    double y_0;
    size_t steps;
    std::vector<std::vector<double>> solution;
};

int main()
{
    Euler eul(f);
    eul.solve();
    eul.print();

    Euler_2 eul_2(f);
    eul_2.solve();
    eul_2.print();

    RK rk_s(f);
    rk_s.solve();
    rk_s.print();
}