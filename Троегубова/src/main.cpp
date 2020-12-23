#include "List.h"
#include "Polynomial.h"
#include <iostream>

int main(void)
{
	/*List<int> list;
	for (int i = 0; i < 10; ++i)
		list.append(i, i);
	for (int i = 0; i < list.size(); ++i)
		std::cout << list[i];
	List<int> list2(list);
	std::cout << std::endl;
	std::cout << (list == list2);
	std::cout << std::endl;
	while (list.size() != 0)
		std::cout << list.erase(0);
	std::cout << std::endl;
	for (int i = 0; i < list.size(); ++i)
		std::cout << list[i];
	std::cout << std::endl;
	std::cout << (list == list2);
	std::cout << std::endl;*/
	Monom m(1, 1), m2(1, 0, 1), m3;
	m3 = m * m2;
	std::cout << m3.get_koef() << " " << m3.get_x() << " " << m3.get_y() << " " << m3.get_z() << std::endl;
	Polynomial p = Polynomial(m) + Polynomial(m2);
	List<Monom> list = p.get_monoms();
	std::cout << p;
	std::cout << p.calculate_value(2, 3, 0); // x = 2, y = 3, z = 0
	system("pause");
	return 0;
}