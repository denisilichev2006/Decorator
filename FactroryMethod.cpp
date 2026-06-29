#include <iostream>
#include <string>

class Coffee {
public:
	virtual ~Coffee() = default;
	virtual double Cost() const = 0;
	virtual std::string Description() const = 0;
};

class SimpleCoffee : public Coffee {
public:
	double Cost() const override { return 100; }
	std::string Description() const override { return "Кофе"; }
};

class CoffeeDecorator : public Coffee {
protected:
	Coffee* coffee_;
public:
	CoffeeDecorator(Coffee* coffee) : coffee_(coffee) {}
	virtual ~CoffeeDecorator() { delete coffee_; }
};

class MilkDecorator : public CoffeeDecorator {
public:
	MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
	double Cost() const override { return coffee_->Cost() + 50; }
	std::string Description() const override { return coffee_->Description() + " + молоко"; }
};

class SugarDecorator : public CoffeeDecorator {
public:
	SugarDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
	double Cost() const override { return coffee_->Cost() + 20; }
	std::string Description() const override { return coffee_->Description() + " + сахар"; }
};

class CinnamonDecorator : public CoffeeDecorator {
public:
	CinnamonDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
	double Cost() const override { return coffee_->Cost() + 30; }
	std::string Description() const override { return coffee_->Description() + " + корица"; }
};

int main() {
	Coffee* coffee = new SimpleCoffee();
	std::cout << coffee->Description() << " - " << coffee->Cost() << " руб\n";
	delete coffee;

	coffee = new MilkDecorator(new SimpleCoffee());
	std::cout << coffee->Description() << " - " << coffee->Cost() << " руб\n";
	delete coffee;

	coffee = new CinnamonDecorator(new SugarDecorator(new MilkDecorator(new SimpleCoffee())));
	std::cout << coffee->Description() << " - " << coffee->Cost() << " руб\n";
	delete coffee;

	return 0;
}