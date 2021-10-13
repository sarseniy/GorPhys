#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Error
{
public:
	void virtual perr() = 0;
	virtual ~Error() {

	}
};

class CurErr : public Error 
{
public:
	CurErr(double c, double t, double h) : c(c), t(t), h(h)
	{}

	bool test() {
		return (c * t / h < 1);
	}

	void perr() override {
		cout << "CurErr occured";
	}
private:
	double c;
	double t;
	double h;
};

void print(const vector<double>& vec) {
	cout.setf(ios::fixed);
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << fixed << setprecision(3) << vec[i] << ' ';
	}
	cout << endl;
}

class Scheme
{
protected:
	double h;
	double N;
	double L;

	double t;
	double T;

	double c;
};

class LW : public Scheme
{
public:
	LW(double c0, double T0, double L0 = 1, double N0 = 1000)
	{
		c = c0;
		T = T0;
		L = L0;
		N = N0;
		h = L / N;
//		t = h / c / 2; нормальный код
		t = 2 * h / c;   // для тестирования ошибки

		CurErr cur(c, t, h);
		if (!cur.test())
		{
			throw cur;
		}

		for (double i = 0; i <= L; i += h)
		{
			if (i < 0.2 or i > 0.4)
			{
				U0.push_back(0);
			}
			else
			{
				U0.push_back(1);
			}
		}
	}

	void save(int n, vector<double>& a)
	{
		ofstream f;
		f.open(to_string(n) + ".txt");
		for (size_t i = 0; i < a.size(); i++)
		{
			f << a[i] << ' ';
		}
		f << endl;
		f.close();
	}

	void Solve() {
		vector<vector<double>> tmp(2);
		tmp[0] = U0;
		tmp[1] = U0;

		int t_count = 0;
		for (int t1 = 1; t1 < T / t; t1++)
		{
			for (double x = 0; x < L / h; x++)
			{
				tmp[t1 % 2][x] = tmp[(t1 - 1) % 2][x] - (c * t / (2 * h)) *
					(((x + 1 >= L / h) ? 0 : tmp[(t1 - 1) % 2][x + 1]) - ((x == 0) ? 0 : tmp[(t1 - 1) % 2][x - 1])) +
					(c * c * t * t / (2 * h * h)) *
					(((x + 1 >= L / h) ? 0 : tmp[(t1 - 1) % 2][x + 1]) - 2 * tmp[(t1 - 1) % 2][x] + ((x == 0) ? 0 : tmp[(t1 - 1) % 2][x - 1]));
			}
			t_count++;
			if (t1 % 10 == 0)
			{
				save(t1, tmp[t1 % 2]);
			}
		}
		result = tmp[(t_count - 1) % 2];
	}

	vector<double> GetResult() {
		return result;
	}


private:
	vector<double> U0;
	vector<double> result = {};
};

class CIR : public Scheme
{
public:
	CIR(double c0, double T0, double L0 = 1, double N0 = 1000)
	{
		c = c0;
		T = T0;
		L = L0;
		N = N0;
		h = L / N;
		t = h / c / 2;

		CurErr cur(c, t, h);
		if (!cur.test())
		{
			throw cur;
		}

		for (double i = 0; i <= L; i += h)
		{
			if (i < 0.2 or i > 0.4)
			{
				U0.push_back(0);
			}
			else
			{
				U0.push_back(1);
			}
		}
	}

	void save(int n, vector<double>& a)
	{
		ofstream f;
		f.open(to_string(n) + ".txt");
		for (size_t i = 0; i < a.size(); i++)
		{
			f << a[i] << ' ';
		}
		f << endl;
		f.close();
	}

	void Solve() {
		vector<vector<double>> tmp(2);
		tmp[0] = U0;
		tmp[1] = U0;

		int t_count = 0;
		for (int t1 = 1; t1 < T / t; t1++)
		{
			for (double x = 0; x < L / h; x++)
			{
				tmp[t1 % 2][x] = tmp[(t1 - 1) % 2][x] - (c * t / h) *
					(tmp[(t1 - 1) % 2][x] - ((x == 0) ? 0 : tmp[(t1 - 1) % 2][x - 1]));
			}
			t_count++;
			if (t1 % 10 == 0)
			{
				save(t1, tmp[t1 % 2]);
			}
		}
		result = tmp[(t_count - 1) % 2];
	}

	vector<double> GetResult() {
		return result;
	}

private:
	vector<double> U0;
	vector<double> result = {};

};

int main() {
	try
	{
		CIR CIR_solver(0.1, 5);
		CIR_solver.Solve();

		LW LW_solver(0.1, 5);
		LW_solver.Solve();

		vector<double> a;
		a = LW_solver.GetResult();

		for (size_t i = 0; i < a.size(); i++)
		{
			cout << a[i] << ' ';
		}

		vector<double> b;
		b = LW_solver.GetResult();
	}
	catch (CurErr err)
	{
		err.perr();
	}
	catch (...)
	{
		std::cout << "Something else went wrong!" << '\n';
	}



	return 0;
}
