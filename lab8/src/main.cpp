#include "gumball_machine/CGumballMachine.h"

using namespace std;

template<typename GumballMachineType>
void TestGumballMachine(GumballMachineType &m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.EjectQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
}

void TestGumballMachineWithState()
{
	gumball_machine::CGumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{
	cout << "\n-----------------\n";
	TestGumballMachineWithState();
	cout << "\n-----------------\n";

	return 0;
}
