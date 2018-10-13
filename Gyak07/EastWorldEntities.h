#ifndef EAST_WORLD_ENTITIES_HPP
#define EAST_WORLD_ENTITIES_HPP

#include <string>

namespace EastWorld {

class Battery {
public:
	int getCharge();
	bool isDepleted();
	void setChargeRandom();
	void setCharge(int);
	void chargeForRandomTime();
	void tick(); // az akksi minden pillanatban hasznalodik, merul
private:
	static const int maximumCharge;
	static const double depletionThreshold;
	int batteryCharge; // if zero, needs to recharge!
};

class EastWorldEntity {
public:
	virtual const std::string getName() = 0; //pure virtual fv: EastWorldEntity mostantol absztrakt osztaly - nem peldanyosithato!
	virtual void whatsYourName();
	virtual void tick() = 0; // a robotok es emberek is oregszenek, barmit is jelentsen ez. Pure virtual mert itt nincs ertelme implementalni - nem tudjuk emberrol vagy robotrol van szo!
};

// From Scott Meyers'book :
// "Private inheritance is most likely to be a legitimate design strategy when you're dealing with two classes not related by is-a where one either needs access to the protected members of another or needs to redefine one or more its virtual functions."
// "Private inheritance means is-implemented-in-terms-of. It's usually inferior to composition"
// "If you make a class D privately inherit from a class B, you do so because you are interested in taking advantage of some of the features available in class B, not because there is any conceptual relationship between objects of types B and D."
// "Private inheritance means nothing during software design, only during software implementation."

class Robot : public EastWorldEntity, private Battery { // public orokles, mert Robot egyfajta Entity (Robot is-a entity)
														// private orokles, mert Robot has-a battery, felhasznalja az akksi implementaciojat!
public:
	Robot(const std::string name);
	const std::string getName() override;
	void tick(); // Robot Battery-bol is orokol, ezert 2 tick fv lesz! Ellenben a Battery tick() fv-e itt privat es mas scope-ban is van
	// void recharge(int charge); erre nincs is szukseg, nem is hasznaltuk...
protected: // ez es szarmazo osztalyok elerik, de kivulrol nem lehet
       // ezzel szemben: public: szarmazo osztalyokbol ES kivulrol is elerheto
       // ezzel szemben: private: sem szarmazo osztalyokbol, sem kivulrol NEM elerheto
       // Stroustrup: protectedet csak fuggvenyekre hasznaljunk. Valtozoknal mindig kerdes, hogy miert protected??
       // ha protected -> ki fogja irni? Ha senki, miert protected?
	int getBatteryLevel(); // 1 to 5
	bool isDepleted();
	void recharge();
private:
	const std::string name;
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
