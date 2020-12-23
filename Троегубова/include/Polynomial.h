#pragma once
#include "List.h"
#include <cmath>
#include <iostream>
#include <string>

// Моном: k * x^a * y^b * z^c 
class Monom
{
	// Коэффициент монома
	double koef;
	// Степени x, y, z соответственно
	double x;
	double y;
	double z;
public:
	Monom(double koef = 0, double x = 0, double y = 0, double z = 0) : koef(koef), x(x), y(y), z(z) {}
	Monom(const Monom& m) : koef(m.koef), x(m.x), y(m.y), z(m.z) {}
	~Monom() {}

	void set_koef(double val) { koef = val; }
	double get_koef() const { return koef; }
	void set_x(double val) { x = val; }
	double get_x() const { return x; }
	void set_y(double val) { y = val; }
	double get_y() const { return y; }
	void set_z(double val) { z = val; }
	double get_z() const { return z; }

	// Существование монома (ненулевой коэффициент)
	bool exist()
	{
		return koef != 0;
	}

	Monom& operator=(const Monom& m)
	{
		koef = m.koef;
		x = m.x;
		y = m.y;
		z = m.z;
		return *this;
	}

	// Оператор сравнения степеней x, y, z
	bool equal_degrees(const Monom& m) const
	{
		if (this != &m)
		{
			if (x != m.x || y != m.y || z != m.z)
				return false;
		}
		return true;
	}

	// Операторы сравнения мономов
	bool operator==(const Monom& m) const
	{
		if (this != &m)
		{
			if (koef != m.koef || x != m.x || y != m.y || z != m.z)
				return false;
		}
		return true;
	}

	bool operator!=(const Monom& m) const
	{
		return !(*this == m);
	}

	friend Monom operator/(const Monom& m1, const Monom& m2)
	{
		return Monom(m1.koef / m2.koef, m1.x - m2.x, m1.y - m2.y, m1.z - m2.z);
	}

	friend Monom operator*(const Monom& m1, const Monom& m2)
	{
		return Monom(m1.koef * m2.koef, m1.x + m2.x, m1.y + m2.y, m1.z + m2.z);
	}

	friend std::ostream& operator<<(std::ostream& out, const Monom& m)
	{
		out << m.koef
			<< (m.x != 0 ? "*x^" + std::to_string(m.x) : "") 
			<< (m.y != 0 ? "*y^" + std::to_string(m.y) : "")
			<< (m.z != 0 ? "*z^" + std::to_string(m.z) : "");
		return out;
	}
};

// Полином 
class Polynomial
{
	List<Monom> monoms;
public:
	Polynomial() {}
	Polynomial(const List<Monom>& l) : monoms(l) {}
	Polynomial(const Polynomial& p) : monoms(p.monoms) {}
	Polynomial(const Monom& m)
	{
		monoms.push(m);
	}
	~Polynomial() {}
	List<Monom> get_monoms() const { return monoms; }
	void set_polynomial(const List<Monom>& l) { monoms = l; }

	Polynomial& operator=(const Polynomial& p)
	{
		if (this != &p)
			monoms = p.monoms;
		return *this;
	}

	double calculate_value(double x, double y, double z)
	{
		double res = 0;
		for (int i = 0; i < monoms.size(); ++i)
		{
			Monom m = monoms[i];
			res += m.get_koef() * pow(x, m.get_x()) * pow(y, m.get_y()) * pow(z, m.get_z());
		}
		return res;
	}

	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
	{
		Polynomial res(p1);
		for (int i = 0; i < p2.monoms.size(); ++i)
		{
			bool found_such_mon = false;
			Monom p2_mon = p2.monoms[i];
			for (int j = 0; j < res.monoms.size(); ++j)
			{
				Monom& res_mon = res.monoms[j];
				if (res_mon.equal_degrees(p2_mon))
				{
					found_such_mon = true;
					res_mon.set_koef(res_mon.get_koef() + p2_mon.get_koef());
					if (!res_mon.exist())
					{
						res.monoms.erase(j);
						break;
					}
				}
			}
			if (!found_such_mon)
			{
				res.monoms.push(p2_mon);
			}
		}
		return res;
	}

	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
	{
		Polynomial res(p1);
		for (int i = 0; i < p2.monoms.size(); ++i)
		{
			bool found_such_mon = false;
			Monom p2_mon = p2.monoms[i];
			for (int j = 0; j < res.monoms.size(); ++j)
			{
				Monom& res_mon = res.monoms[j];
				if (res_mon.equal_degrees(p2_mon))
				{
					found_such_mon = true;
					res_mon.set_koef(res_mon.get_koef() - p2_mon.get_koef());
					if (!res_mon.exist())
					{
						res.monoms.erase(j);
						break;
					}
				}
			}
			if (!found_such_mon)
			{
				p2_mon.set_koef(-p2_mon.get_koef());
				res.monoms.push(p2_mon);
			}
		}
		return res;
	}

	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
	{
		Polynomial res;
		for (int i = 0; i < p1.monoms.size(); ++i)
		{
			Monom p1_mon = p1.monoms[i];
			for (int j = 0; j < p2.monoms.size(); ++j)
			{
				bool found_such_mon = false;
				Monom p2_mon = p2.monoms[j];
				Monom mon = p1_mon * p2_mon;
				for (int k = 0; k < res.monoms.size(); ++k)
				{
					Monom& res_mon = res.monoms[j];
					if (res_mon.equal_degrees(mon))
					{
						found_such_mon = true;
						res_mon.set_koef(res_mon.get_koef() - p2_mon.get_koef());
						if (!res_mon.exist())
						{
							res.monoms.erase(j);
							break;
						}
					}
				}
				if (!found_such_mon)
				{
					res.monoms.push(mon);
				}
			}
		}
		return res;
	}

	friend std::ostream& operator<<(std::ostream& out, const Polynomial& p)
	{
		out << p.monoms[0];
		for (int i = 1; i < p.monoms.size(); ++i)
		{
			const Monom& m = p.monoms[i];
			out << (m.get_koef() >= 0 ? "+" : "") << m;
		}
		return out;
	}
};