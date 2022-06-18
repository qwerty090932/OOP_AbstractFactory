#include <iostream>
#include <vector>
using namespace std;

class Car
{
public:
	virtual void info() = 0;
	virtual ~Car(){}
};
class Engine 
{
public:
	virtual void info() = 0;
	virtual ~Engine() {}
};
class Corpus
{
public:
	virtual void info() = 0;
	virtual ~Corpus() {}
};


// Японские автомобили
class JapaneseCar : public Car
{
public:
	void info() {
		cout << "JapaneseCars " << endl;
	}
};
class JapaneseEngine : public Engine
{
public:
	void info() {
		cout << "JapaneseEngine " << endl;
	}
};
class JapaneseCorpus : public Corpus
{
public:
	void info() {
		cout << "JapaneseCorpus " << endl;
	}
};

// Европейские автомобили
class EuropeCar : public Car
{
public: 
	void info() {
		cout << "EuropeCars " << endl;
	}
};
class EuropeEngine : public Engine
{
public:
	void info() {
		cout << "EuropeEngine " << endl;
	}
};
class EuropeCorpus : public Corpus
{
public:
	void info() {
		cout << "EuropeCorpus " << endl;
	}
};


// Создание фабрики
class CarFactory
{
public:
	virtual Car* createCar() = 0;
	virtual Engine* createEngine() = 0;
	virtual Corpus* createCorpus() = 0;
	virtual ~CarFactory() {}
};

// Фабрика по производству Японских автомобилей
class JapaneseCarFactory: public CarFactory
{
public:
	Car* createCar() {
		return new JapaneseCar;
	}
	Engine* createEngine() {
		return new JapaneseEngine;
	}
	Corpus* createCorpus() {
		return new JapaneseCorpus;
	}
};

// Фабрика по производству Европейских автомобилей
class EuropeCarFactory : public CarFactory
{
public:
	Car* createCar() {
		return new EuropeCar;
	}
	Engine* createEngine() {
		return new EuropeEngine;
	}
	Corpus* createCorpus() {
		return new EuropeCorpus;
	}
};

// Все машины из той или иной фабрики
class AllCars
{
public:
	~AllCars() {
		int i;
		for (i = 0; i < vCar.size(); ++i)  delete vCar[i];
		for (i = 0; i < vEngine.size(); ++i)  delete vEngine[i];
		for (i = 0; i < vCorpus.size(); ++i)  delete vCorpus[i];
	}
	void info() {
		int i;
		for (i = 0; i < vCar.size(); ++i)  vCar[i]->info();
		for (i = 0; i < vEngine.size(); ++i)  vEngine[i]->info();
		for (i = 0; i < vCorpus.size(); ++i)  vCorpus[i]->info();
	}
	vector <Car*> vCar;
	vector <Engine*> vEngine;
	vector <Corpus*> vCorpus;
};

class СreateCar
{
public:
	AllCars* createAllCars(CarFactory& factory) {
		AllCars* p = new AllCars;
		p->vCar.push_back(factory.createCar());
		p->vEngine.push_back(factory.createEngine());
		p->vCorpus.push_back(factory.createCorpus());
		return p;
	}
};
int main()
{
	СreateCar car;
	JapaneseCarFactory JC_factory;
	EuropeCarFactory EC_factory;

	AllCars* JapanCars = car.createAllCars(JC_factory);
	AllCars* EuropeCars = car.createAllCars(EC_factory);
	cout << "Japanese Cars:" << endl;
	JapanCars->info();
	cout << " Europe Cars : " << endl;
	EuropeCars->info();
	// ...
}