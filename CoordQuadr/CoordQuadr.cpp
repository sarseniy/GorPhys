#include <iostream>
#include <cmath>

#define PI 3.14159265  

class Coord {
public:
	Coord(double x = 1, double y = 1) : x{ x }, y{ y }
	{}

	void set(double x, double y) {
		x = x;
		y = y;
	}

	double** get() {
		double** tmp = new double* [2];
		tmp[0] = &x;
		tmp[1] = &y;
		return tmp;
	}

	virtual void show() {
		std::cout << x << ' ' << y << '\n';
	}

private:
	double x;
	double y;
};

class AbsCoord : public Coord {
public:
	AbsCoord(int x_ = 1, int y_ = 1) : Coord(static_cast<double>(x_), static_cast<double>(y_)), 
		x_abs(x_), y_abs(y_)
	{}

	void setAbs(int x_, int y_) {
		x_abs = x_;
		y_abs = y_;
		double** tmp = this->get();
		*tmp[0] = static_cast<double>(x_);
		*tmp[1] = static_cast<double>(x_);
	}

	int** getAbs() {
		int** tmp = new int* [2];
		tmp[0] = &x_abs;
		tmp[1] = &y_abs;
		return tmp;
	}

	void showAbs() {
		std::cout << x_abs << ' ' << y_abs << '\n';
	}

private:
	int x_abs;
	int y_abs;
};

class ModCoord : public Coord {
public:
	ModCoord(double x = 1, double y = 1) : Coord(x, y)
	{
		x_mod = x * cos(PI / 4) - y * sin(PI / 4);
		y_mod = x * sin(PI / 4) + y * cos(PI / 4);
	}

	void setMod(double x_, double y_) {
		x_mod = x_;
		y_mod = y_;
		double** tmp = this->get();
		*tmp[0] = x_mod * cos(PI / 4) + y_mod * sin(PI / 4);
		*tmp[1] = -x_mod * sin(PI / 4) + y_mod * cos(PI / 4);
	}

	double** getMod() {
		double** tmp = new double* [2];
		tmp[0] = &x_mod;
		tmp[1] = &y_mod;
		return tmp;
	}

	void showMod() {
		std::cout << x_mod << ' ' << y_mod << '\n';
	}

private:
	double x_mod;
	double y_mod;
};

void Quard(Coord* p) {
	if (typeid(*p) == typeid(AbsCoord))
	{
		auto v = dynamic_cast<AbsCoord*>(p);
		int** tmp = v->getAbs();
		if (*tmp[0] > 0 and *tmp[1] > 0)
		{
			std::cout << "First quadr";
		}
	}
}

int main()
{

	return 0;
}