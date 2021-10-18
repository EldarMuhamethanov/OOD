#include <cassert>
#include <iostream>
#include <memory>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"
#include "Duck.h"

using namespace std;

void PlayWithDuck(Duck& duck)
{
	duck.Display();
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	modelDuck.SetFlyBehavior(FlyBehavior::FlyWithWingsDecorator());
	modelDuck.Fly();
	modelDuck.Fly();
	PlayWithDuck(modelDuck);
}
