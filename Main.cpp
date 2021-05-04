#include "List.h"
#include <locale>

#define PATH "C:\\out.txt"

int main()
{
	setlocale(LC_ALL, "RUS");

	List l1;

	l1.InsFirst(1);
	l1.InsFirst(2);
	l1.InsFirst(3);
	l1.InsFirst(4);
	l1.InsFirst(5);
	l1.InsFirst(6);
	l1.InsFirst(7);
	l1.InsFirst(8);

	l1.InsLast(101);
	l1.InsLast(-1);
	l1.InsLast(-2);
	l1.InsLast(-3);
	l1.InsLast(-4);
	l1.print();

	l1.InsValue(-33, 0);
	l1.InsValue(-66, 3);
	l1.InsValue(-99, 6);
	l1.print();

	l1.InsValue(339, 14);
	l1.print();

	l1.WriteFile(PATH);

	std::cout << "\n";

	std::cout << l1.search(-33) << "\n";
	std::cout << l1.search(-66) << "\n";
	std::cout << l1.search(-99) << "\n";
	std::cout << l1.search(339) << "\n";
	std::cout << l1.search(101) << "\n";
	std::cout << l1.search(55555) << "\n";

	std::cout << "\n";

	std::cout << l1.get(0) << "\n";
	std::cout << l1.get(3) << "\n";
	std::cout << l1.get(6) << "\n";
	std::cout << l1.get(14) << "\n";
	std::cout << l1.get(17) << "\n";

	std::cout << "\n";

	std::cout << l1.IsSort() << "\n";

	List l2;
	
	l2.InsFirst(8);
	l2.InsFirst(7);
	l2.InsFirst(6);
	l2.InsFirst(5);
	l2.InsFirst(4);

	std::cout << l2.IsSort() << "\n";

	List l3;
	l3 = *l1.findSpecialElements(3);
	l3.print();

	List l4;
	l4.ReadFile(PATH);
	l4.print();

	l4.DelList();
	l4.InsFirst(1);
	l4.InsFirst(5);
	l4.InsFirst(10);
	l4.InsFirst(15);
	l4.InsFirst(20);

	l4.InsLast(55);
	l4.InsLast(65);
	l4.InsLast(75);
	l4.InsLast(85);

	l4.print(); 
	l4.DelFirst();
	l4.DelFirst();
	l4.DelFirst();

	l4.DelLast();
	l4.DelLast();
	l4.DelLast();

	l4.print();

	l4.InsFirst(30);
	l4.InsFirst(33);
	l4.InsFirst(36);
	l4.InsFirst(39);
	l4.print();

	l4.DelValue(0);
	l4.DelValue(6);
	l4.print();
	l4.DelValue(4);
	l4.print();
	l4.InsLast(5);
	l4.InsLast(55);
	l4.InsLast(555);
	l4.InsLast(5555);
	l4.InsLast(55555);
	l4.print();
	l4.DelValue(6);
	l4.print();

	system("pause");
	return 0;
}