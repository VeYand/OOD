#include "lib/Duck/DecoyDuck.h"
#include "lib/Duck/MallardDuck.h"
#include "lib/Duck/ModelDuck.h"
#include "lib/Duck/RedheadDuck.h"
#include "lib/Duck/RubberDuck.h"
#include "lib/DuckFunctions.h"
#include <cstdlib>

int main()
{
	const MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	const RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	const RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	const DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}