#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <string>

namespace EastWorld {

class EastWorldEntity {
public:
	virtual const std::string getName() = 0; //pure virtual fv: EastWorldEntity mostantol absztrakt osztaly - nem peldanyosithato!
	virtual void whatsYourName();
};

class Robot : public EastWorldEntity { // public orokles, mert Robot egyfajta Entity!!
									   // (interfeszt oroklunk, nem implementaciot hasznalunk fel ujra / rejtunk el)
public:
	Robot(const std::string name);
	const std::string getName() override;
	void recharge(int charge);
protected: // ez es szarmazo osztalyok elerik, de kivulrol nem lehet
	// ezzel szemben: public: szarmazo osztalyokbol ES kivulrol is elerheto
	// ezzel szemben: private: sem szarmazo osztalyokbol, sem kivulrol NEM elerheto
	// Stroustrup: protectedet csak fuggvenyekre hasznaljunk. Valtozoknal mindig kerdes, hogy miert protected??
	// ha protected -> ki fogja irni? Ha senki, miert protected?
	int getCharge();
	bool isDepleted();
	void recharge();
private:
	const std::string name;
	static const int maximumCharge;
	static const double depletionThreshold;
	int batteryCharge; // if zero, needs to recharge!
};


class ServantBot : public Robot {
public:
	ServantBot(std::string name);
	void whatsYourName() override;
};

class BehavesLikeHuman { // nem szarmazik EastWorldEntitybol, ld. lentebb, h miert
public:
	BehavesLikeHuman(std::string nid);
	const std::string getNationalId();
	// jo lenne, ha BehavesLikeHuman se lenne peldanyosithato. Ehhez kell egy pure virtual fv.
	// kicsit most visszafele gondolkodunk (akkor csinaljunk abstract base osztalyt, ha van ertelme)... de a pelda kedveert csinaljunk egyet direkt
	virtual void eat() = 0;
private:
	const std::string nationalid;
};

class FakeHuman : public Robot, BehavesLikeHuman {
	// megj: BehavesLikeHuman azert nem szarmazik EastWorldEntitybol, mert
	// akkor Roboton es BehavesLikeHumanen keresztul FakeHuman ket kulonbozo
	// EastWorldEntity-t is tartalmazna (hires diamond shape problem)
	// Ez tulmutat a targy keretein, de veszelyes mert akkor 2 name lenne pl.
public:
	FakeHuman(std::string name, std::string nid);
	void eat() override;
	void whatsYourName() override;
private:
	const std::string nationalid;
};

class Human : public EastWorldEntity, BehavesLikeHuman {
public:
	Human(std::string name, std::string nid);
	const std::string getName() override;
	void eat() override;
	void whatsYourName() override;
private:
	const std::string name;
	double hungerLevel; // from 0 to 1
	static const double hungerThreshold;
};

}

#endif // !EAST_WORLD_ENTITIES_HPP
