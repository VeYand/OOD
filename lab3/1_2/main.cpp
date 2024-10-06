#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	explicit MakeLemon(const unsigned quantity)
		: m_quantity(quantity)
	{
	}

	auto operator()(IBeveragePtr &&beverage) const
	{
		return make_unique<CLemon>(std::move(beverage), m_quantity);
	}

private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [](IBeveragePtr &&b) {
		return make_unique<CCinnamon>(std::move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template<typename Condiment, typename... Args>
auto MakeCondiment(const Args &... args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=]<typename T>(T &&b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(std::forward<T>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage =
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage =
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template<typename Component, typename Decorator>
auto operator <<(Component &&component, const Decorator &decorate)
{
	return decorate(forward<Component>(component));
}

bool CompleteBeverageChoice(unique_ptr<IBeverage> &beverage, const int beverageChoice)
{
	int portionChoice;
	TeaType teaType;
	switch (beverageChoice)
	{
		case 1:
			beverage = make_unique<CCoffee>();
			return true;
		case 2:
			cout << "1 - Standard portion, 2 - Double portion" << endl;
			cin >> portionChoice;

			if (portionChoice < 1 || portionChoice > 2)
			{
				cout << "Invalid Cappuccino portion choice";
				return false;
			}

			beverage = make_unique<CCappuccino>(portionChoice == 2);
			return true;
		case 3:
			cout << "1 - Standard portion, 2 - Double portion" << endl;
			cin >> portionChoice;

			if (portionChoice < 1 || portionChoice > 2)
			{
				cout << "Invalid Cappuccino portion choice";
				return false;
			}

			beverage = make_unique<CLatte>(portionChoice == 2);
			return true;
		case 4:
			int teaChoice;

			cout << "1 - Black, 2 - Oolong, 3 - White, 4 - Yellow" << endl;
			cin >> teaChoice;

			if (teaChoice < 1 || teaChoice > 4)
			{
				cout << "Invalid choice";
				return false;
			}

			teaType = static_cast<TeaType>(teaChoice);
			beverage = make_unique<CTea>(teaType);
			return true;
		case 5:
			int sizeChoice;

			cout << "1 - Small, 2 - Medium, 3 - Large" << endl;
			cin >> sizeChoice;

			if (sizeChoice < 1 || sizeChoice > 3)
			{
				cout << "Invalid choice";
				return false;
			}

			beverage = make_unique<CMilkshake>(static_cast<MilkshakeSize>(sizeChoice));
			return true;
		default:
			cout << "Invalid choice" << endl;
			return false;
	}
}

bool CompleteCondimentChoice(unique_ptr<IBeverage> &beverage, const int condimentChoice)
{
	switch (condimentChoice)
	{
		case 1:
			beverage = std::move(beverage) << MakeCondiment<CLemon>(2);
			return true;
		case 2:
			beverage = std::move(beverage) << MakeCondiment<CCinnamon>();
			return true;
		case 3:
			int cubeChoice;
			cout << "1 - Water ice cubes, 2 - Dry ice cubes" << endl;
			cin >> cubeChoice;
			if (cubeChoice > 2 or cubeChoice < 1)
			{
				cout << "Invalid choice";
				return false;
			}
			beverage = std::move(beverage) << MakeCondiment<CIceCubes>(
				           2,
				           cubeChoice == 1
					           ? IceCubeType::Water
					           : IceCubeType::Dry
			           );
			return true;
		case 4:
			beverage = std::move(beverage) << MakeCondiment<CChocolateCrumbs>(5);
			return true;
		case 5:
			beverage = std::move(beverage) << MakeCondiment<CCoconutFlakes>(5);
			return true;
		case 6:
			cout << "1 - Maple syrup, 2 - Chocolate syrup" << endl;
			int syrupChoice;

			cin >> syrupChoice;
			if (syrupChoice < 1 || syrupChoice > 2)
			{
				cout << "Invalid  choice";
				return false;
			}

			beverage = std::move(beverage) << MakeCondiment<CSyrup>(
				           syrupChoice == 1
					           ? SyrupType::Maple
					           : SyrupType::Chocolate
			           );
			return true;
		case 7:
			beverage = std::move(beverage) << MakeCondiment<CCream>();
			return true;
		case 8:
			int liquorChoice;
			cout << "1 - Chocolate liquor, 2 - Nutty liquor" << endl;
			cin >> liquorChoice;
			if (liquorChoice < 1 || liquorChoice > 2)
			{
				cout << "Invalid choice";
				return false;
			}

			beverage = std::move(beverage) << MakeCondiment<CLiquor>(
				           liquorChoice == 1
					           ? LiquorType::CHOCOLATE
					           : LiquorType::NUTTY
			           );
			return true;
		case 9:
			cout << "Choose chocolate slices count (max 5)" << endl;
			int slicesCount;

			cin >> slicesCount;
			try
			{
				beverage = std::move(beverage) << MakeCondiment<CChocolate>(slicesCount);
			}
			catch (const std::invalid_argument &e)
			{
				cout << e.what() << std::endl;
				return false;
			}

			return true;
		case 0:
			cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
			return false;
		default:
			cout << "Invalid choice" << endl;
			return true;
	}
}

void DialogWithUser()
{
	unique_ptr<IBeverage> beverage;

	cout << "Choose beverage:" << endl;
	cout << "1 - Coffee" << endl;
	cout << "2 - Cappuccino" << endl;
	cout << "3 - Latte" << endl;
	cout << "4 - Tea" << endl;
	cout << "5 - Milkshake" << endl;

	int beverageChoice;
	cin >> beverageChoice;

	if (CompleteBeverageChoice(beverage, beverageChoice))
	{
		while (true)
		{
			cout << "Choose condiment:" << endl;
			cout << "1 - Lemon" << endl;
			cout << "2 - Cinnamon" << endl;
			cout << "3 - Ice Cubes" << endl;
			cout << "4 - Chocolate Crumbs" << endl;
			cout << "5 - Coconut Flakes" << endl;
			cout << "6 - Syrup" << endl;
			cout << "7 - Cream" << endl;
			cout << "8 - Liquor" << endl;
			cout << "9 - Chocolate" << endl;
			cout << "0 - Checkout" << endl;

			int condimentChoice;
			cin >> condimentChoice;

			if (!CompleteCondimentChoice(beverage, condimentChoice))
			{
				break;
			}
		}
	}
}

int main()
{
	DialogWithUser();
	cout << endl;
	// {
	// 	// Наливаем чашечку латте
	// 	auto latte = make_unique<CLatte>();
	// 	// добавляем корицы
	// 	auto cinnamon = make_unique<CCinnamon>(move(latte));
	// 	// добавляем пару долек лимона
	// 	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	// 	// добавляем пару кубиков льда
	// 	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	// 	// добавляем 2 грамма шоколадной крошки
	// 	auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);
	//
	// 	// Выписываем счет покупателю
	// 	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	// } {
	// 	auto beverage =
	// 			make_unique<CChocolateCrumbs>( // Внешний слой: шоколадная крошка
	// 				make_unique<CIceCubes>( // | под нею - кубики льда
	// 					make_unique<CLemon>( // | | еще ниже лимон
	// 						make_unique<CCinnamon>( // | | | слоем ниже - корица
	// 							make_unique<CLatte>()), // | | |   в самом сердце - Латте
	// 						2), // | | 2 дольки лимона
	// 					2, IceCubeType::Dry), // | 2 кубика сухого льда
	// 				2); // 2 грамма шоколадной крошки
	//
	// 	// Выписываем счет покупателю
	// 	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	// }
	//
	// // Подробнее рассмотрим работу MakeCondiment и оператора <<
	// {
	// 	// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
	// 	auto lemon2 = MakeCondiment<CLemon>(2);
	// 	// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
	// 	auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);
	//
	// 	auto tea = make_unique<CTea>();
	//
	// 	// декорируем чай двумя дольками лимона и тремя кусочками льда
	// 	auto lemonIceTea = iceCubes3(lemon2(move(tea)));
	// 	/* Предыдущая строка выполняет те же действия, что и следующий код:
	// 	auto lemonIceTea =
	// 		make_unique<CIceCubes>(
	// 			make_unique<CLemon>(
	// 				move(tea),
	// 				2),
	// 			2, IceCubeType::Water);
	// 	*/
	//
	// 	auto oneMoreLemonIceTea =
	// 			make_unique<CTea>() // Берем чай
	// 			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
	// 			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
	// 	/*
	// 	Предыдущая конструкция делает то же самое, что и следующая:
	// 	auto oneMoreLemonIceTea =
	// 		MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
	// 			MakeCondiment<CLemon>(2)(make_unique<CTea>())
	// 			);
	// 	*/
	// }
	//
	// // Аналог предыдущего решения с добавкой синтаксического сахара
	// // обеспечиваемого операторами << и функцией MakeCondiment
	// {
	// 	auto beverage =
	// 			make_unique<CLatte>() // Наливаем чашечку латте,
	// 			<< MakeCondiment<CCinnamon>() // оборачиваем корицей,
	// 			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
	// 			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry) // брасаем пару кубиков сухого льда
	// 			<< MakeCondiment<CChocolateCrumbs>(2); // посыпаем шоколадной крошкой
	//
	// 	// Выписываем счет покупателю
	// 	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	// } {
	// 	auto beverage =
	// 			make_unique<CMilkshake>() // Наливаем молочный коктейль
	// 			<< MakeCondiment<CSyrup>(SyrupType::Maple) // заливаем кленовым сиропом
	// 			<< MakeCondiment<CCoconutFlakes>(8); // посыпаем кокосовой стружкой
	//
	// 	// Выписываем счет покупателю
	// 	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	// }
}
