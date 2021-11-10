#include <iostream>
#include <vector>
#include <algorithm>

class Solver {
public:
    virtual void solve() = 0;
    //virtual void print() = 0;
    ~Solver() {}
};

class TVD : public Solver {
public:
    TVD(double ksi = 0.5, double t = 1) : ksi(ksi), h(h), t(t) {
        h = 2 * ksi * t;
        cur = t * ksi / h;
        int num = (b - a);
        for (size_t i = 0; i < t_end / t; i++)
        {
            data.push_back(std::vector<double> (num, 0));
        }
        // first func
        /*for (size_t i = 0; i < data[0].size(); i++)
        {
            data[0][i] = (i * h + a < -3) or (i * h + a > 3) ? 0 : 1;
        }*/

        // second func
        for (size_t i = 0; i < data.front().size(); i++)
        {
            double x = i * h + a;
            data[0][i] = (x < -3) or (x > 3) ? 0 : exp((-x * x) / 2) - exp(- 9 / 2);
        }

    }

    void solve() {
        for (size_t j = 1; j < t_end; j++)
        {
            for (size_t i = 2; i < data[j].size() - 2; i++)
            {
                data[j][i] = data[j - 1][i] - t * ksi / h * (wave(j - 1, i) - wave(j - 1, i - 1));
            }
        }
    }

    void print() {
        for (size_t i = 0; i < data.back().size(); i++)
        {
            std::cout << i * h + a << " " << data.back()[i] << '\n';
        }
    }

private:
    double wave(int j, int i) {
        double res = 0;
        if (ksi > 0)
        {
            res = data[j][i] + (1 - cur) / 2 * (this->*limPtr)(j, i);
        }
        else
        {
            res = data[j][i + 1] - (1 - cur) / 2 * (this->*limPtr)(j, i + 1);
        }
        return res;
    }

    double lim(int j, int i) {
        double res = 0;
        res = std::min(abs(data[j][i + 1] - data[j][i]), abs(data[j][i - 1] - data[j][i]));
        res *= ((data[j][i + 1] - data[j][i]) < 0) ? -1 : 1;
        return res;
    }

    double mc_lim(int j, int i) {
        double res = 0;
        res = std::min(abs(data[j][i + 1] - data[i][j - 1]) / 2, std::min(2 * abs(data[j][i + 1] - data[j][i]),
            2 * abs(data[j][i] - data[j][i - 1])));
        res *= ((data[j][i + 1] - data[j][i]) < 0) ? -1 : 1;
        return res;
    }

    double superbee_lim(int j, int i) {
        double res = 0;
        res = std::max(std::min(2 * abs(data[j][i + 1] - data[j][i]), abs(data[j][i] - data[j][i - 1])),
            std::min(2 * abs(data[j][i + 1] - data[j][i]), 2 * abs(data[j][i] - data[j][i - 1])));
        return res;
    }

    double vanLeer_lim(int j, int i) {
        double res = 0;
        if (abs(data[j][i + 1] - data[j][i - 1]) <= 1e-6)
        {
            return 0;
        }
        res = 2 * (data[j][i + 1] - data[j][i]) * (data[j][i] - data[j][i - 1]) / (data[j][i + 1] - data[j][i - 1]);
        return res;
    }

    double t_end = 10;
    double a = -20;
    double b = 20;
    double (TVD::*limPtr)(int, int) = &TVD::lim;
    double ksi;
    double h;
    double t;
    double cur;
    std::vector<std::vector<double>> data;
};

int main()
{
    TVD f;
    f.solve();
    f.print();
}