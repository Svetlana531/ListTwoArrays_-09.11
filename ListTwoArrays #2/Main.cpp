#include "List.h"
#include <locale>

#define PATH "C:\\out.txt"

int main()
{
	setlocale(LC_ALL, "RUS");

	List<int> l1;
	
	for (int i = 0; i < 15; i++)
	{
		l1.ins_Front(i * 5);
		l1.ins_Back(i - 2);
	}

	std::cout << "Список l1: \n";
	l1.print();
	std::cout << "\n\n";

	std::cout << "Поиск по индексу: \n";
	std::cout << "Index 0: "  << l1.GetData(0)  << "\n";
	std::cout << "Index 3: "  << l1.GetData(3)  << "\n";
	std::cout << "Index 6: "  << l1.GetData(6)  << "\n";
	std::cout << "Index 15: " << l1.GetData(15) << "\n";
	std::cout << "\n";

	std::cout << "Вставка значений по индексу: \n";
	l1.ins_Value(-100, 0);
	l1.ins_Value(-200, 3);
	l1.ins_Value(-300, 6);
	l1.ins_Value(-400, 15);
	l1.ins_Value(-500, 0);
	l1.print();
	std::cout << "\n";

	std::cout << "Функции поиска: \n";
	std::cout << "Find -33: " << "\t" << l1.search(-33) << "\n";
	std::cout << "Find -2: "  << "\t" << l1.search(2)	<< "\n";
	std::cout << "Find 5: "   << "\t" << l1.search(5)	<< "\n";
	std::cout << "Find 10: "  << "\t" << l1.search(10)	<< "\n";
	std::cout << "Find 101: " << "\t" << l1.search(101) << "\n";
	std::cout << "Find 0: "   << "\t" << l1.search(0)	<< "\n";
	std::cout << "\n";

	std::cout << "Выведем список l1 в файл: \n";
	l1.WriteFile(PATH);
	std::cout << "\n";

	std::cout << "После функций удаления: \n";
	l1.del_Back();
	l1.del_Back();
	l1.del_Back();
	l1.del_Back();
	l1.del_Back();
	l1.del_Front();
	l1.del_Front();
	l1.del_Front();
	l1.del_Front();
	l1.del_Front();
	l1.print();
	std::cout << "\n\n";

	std::cout << "Найдём элементы делящиеся на 3 на основе списка l1: \n";

	List<int> l2;
	l2 = *l1.findSpecialElements(3);
	l2.print();
	std::cout << "\n\n";

	std::cout << "Прочитаем список из файла: \n";
	List<int> l3;
	l3.ReadFile(PATH);
	l3.print();
	std::cout << "\n\n";

	std::cout << "Удалим 3 списка: \n";
	l1.del_List();
	l2.del_List();
	l3.del_List();

	system("pause");
	return 0;
}