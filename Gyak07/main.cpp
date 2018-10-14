// EastWorldProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EastWorldEntities.h"
#include <iostream>
#include <vector>
#include <ctime>

// altalaban nem szeretjuk, mert ha tobb namespace-t hasznalunk akkor megintcsak name collisionok lehetnek
// using namespace EastWorld;
namespace EW = EastWorld; //namespace alias OK

int main() {
	// absztrakt osztaly nem peldanyosithato!!
	//EW::EastWorldEntity ewe1("Who Am I"); // igy nem kell mindehol kiirni, hogy EastWorld::valami
	// std::cout << ewe1.name << std::endl; name private, vagyis nem hozzaferheto kivulrol
	EW::Robot rob1("Robi");
	EW::ServantBot sb1("Hello Bello");
	// sb1.getCharge(); protected, ezert inaccessible kivulrol
	EW::FakeHuman fh("Tisztara Ember", "062255AB");
	EW::Human hum("Igazi Ember", "252525PK");
	EW::Human hum2("Igazi Ember 2", "252525PS");

	rob1.whatsYourName();
	sb1.whatsYourName();
	fh.whatsYourName();
	hum.whatsYourName();
	hum2.whatsYourName();

	rob1.tick();
	rob1.whatsYourName();

	// std::vector<EW::EastWorldEntity*> EastWorldEntityCollection;
	// char probachar = '5';
	// EW::EastWorldSociety<char> soc(probachar); // nem fordul le, mivel char tipusnak nincs push_back, iterator stb. tagja!
	// De mi tortenik, ha olyan tipust hasznalunk, aminek vanak ilyen dolgai, de teljesen mast csinal? akar segfaultot is okozhat...
	//std::vector<char*> EastWorldEntityCollection;
	//EW::EastWorldSociety<std::vector<char*> > soc(EastWorldEntityCollection); //nem, ezzel nem sikerult demonstralni.
	//a fordito ezt is elkapja, mert eszreveszi, hogy EastWorldEntity pointereket probalunk belepakolaszni egy char pointereket tartalmazo vektorba.
	//maradjunk annyiban, hogy a statikus tipusossag sokat segit, de elmeletileg ki lehet talalni olyan osztaly part, ahol:
	//az egyiknek van push_back metodusa, begin() es end() metodusa es megfelelo iterator tagja stb.
	//es raadasul push_back EastWorldEntity pointert var...
	//Egyszeru pelda: nem ragaszkodunk csak a push_back()-hez, a size()-hoz es az operator[]-hoz (ezek megvannak a Vector osztalynak is!)
	//mivel getName()-et is hasznaljuk, azt is implementaljuk.

	class DemoFail {
	public:
		DemoFail() {}
		void push_back(EW::EastWorldEntity* ewep) {
			//do something
		}
		const std::string getName() { return "blabla"; }
		int size() { return 2; }
		EW::EastWorldEntity* operator[](int i) { return myewe + i; } // ez lesz a hiba: van, nullptrt-t adunk vissza, ha myewe nincs inicializalva!
	private:
		EW::EastWorldEntity* myewe;
	};

	DemoFail mydemofail;
	EW::EastWorldSociety<DemoFail> soc(mydemofail); // latszolag minden rendben!

	// meg egyszer: igy minden OK lenne
	// std::vector<EW::EastWorldEntity*> eastWorldEntityCollection;
	// EW::EastWorldSociety<std::vector<EW::EastWorldEntity*> > soc(eastWorldEntityCollection);

	soc.addEntity(&rob1);
	soc.addEntity(&sb1);
	soc.addEntity(&fh);
	soc.addEntity(&hum);
	soc.addEntity(&hum2);

	char c;
	for (int i = 0; i < 100; i++) {
		soc.alternativeTickEntities();
		std::cin >> c;
	}

	// huh, nehez volt demonstralni
	// de amugy: az is a gond, hogy valakinek a kodja "nem tudja nekunk megmondani", hogy csak vektorra mukodik es milyen egyeb feltetelezesek vannak a kod mogott
	// mivel van tipusellenorzes, egy ido utan nehez olyan kodot irni, ami teljesen mast csinal es veletlenul atmegy a rostan
	// de a template-ekkel kapcsolatosan igy is sok meglepetesunk lehet
	// osszefoglaloan: akkor hasznaljunk template-et, ha olyan oztalyokat akarunk "egyutt" hasznalni, amiknek nincs szarmazasi kozuk egymashoz, tul azon, hogy
	// mindegyik hasznalatat lehetove akarjuk tenni
	// Itt az EastWorldSocietynek ugy mindegy, milyen adastrukturaban tartjuk az egyedeket.

	std::cin >> c;
	return 0;
}
