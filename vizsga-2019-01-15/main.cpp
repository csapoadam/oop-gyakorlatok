// main.cpp : Defines the entry point for the console application.
//

/*
Futball menedzser program
Készítsen C++ osztályokat focicsapatok és focisták adatainak tárolására, az alábbi specifikációk alapján!


Legalább 2-es érdemjegyért:
***
Készítsen egy Jatekos osztályt játékosok adatainak tárolására: név, születési év.
Az adatokat ne lehessen az osztályon kívülről módosítani, csak getter függvényekkel lekérdezni.

Készítsen egy Csapat osztályt is. Minden csapatnak van neve (std::string), továbbá STL vektorban tárolja, hogy a csapatban mely
játékosok játszanak (std::vector<Jatekos*>). (segítség: https://en.cppreference.com/w/cpp/container/vector))
Ezeket az adattagokat kívülről szintén nem lehet módosítani, csak a nevet lekérdezni.
A Csapat osztályhoz az alábbi metódusokat készítse el:
- Készítsen egy jatekosok() metódust, amely console-ra kilistázza a csapat játékosait (fejlécben a csapat nevét, minden játékos nevét egy új sorban).
A kilistázást végző for-ciklusban használjon a vector típusnak megfelelő iteratort (segítség: példa itt található http://www.cplusplus.com/reference/vector/vector/begin/ )
- Készítsen egy leigazol(Jatekos*) metódust, amely lehetővé teszi, hogy adott játékos az adott csapathoz szerződjön.
Egy játékos egyszerre csak egy csapathoz szerződhet, ezért a Jatekos osztály hivatkozást kell, hogy tartalmazzon arra a Csapat objektumra is,
amely csapatban a játékos játszik (egy privát Csapat* pointerrel és a megfelelő getter függvénnyel egészítse ki a Csapat osztályt!).
Mindig a legfrissebb igazolás számít, az aktuális Csapat* felülírja a korábbit!
- Készítsen egy elad() metódust is. Erre akkor lesz szükség, amikor egy játékos már játszik egy X csapatban, és egy másik Y
csapathoz igazol. Ekkor az Y csapat leigazol() metódusa meghívja az X csapat elad() metódusát, hogy az adott játékos az X csapat nyilvántartásából törlésre
kerüljön. Megjegyzés: Mivel elad() metódust csak a leigazol() metódus hívja meg, amely szintén a Csapat osztály scope-jában van, ezért az elad() metódust
állítsa privátra!
Az elad() metódus implementálása során haszálja az std::vector osztály erase() metódusát a szükséges hivatkozások törlésére
(segítség: https://en.cppreference.com/w/cpp/container/vector/erase). Vigyázat: ha for ciklus közepén törlünk, a további iterátorok invalidálásra kerülnek,
ezért törlés után break utasítást kell hívni!
Összefoglalóan a leigazol() fv az alábbi műveleteket hajtja végre:
... a játékos korábbi csapatára - ha van ilyen - meghívja az elad() metódust
... setterrel bejegyzi magát a játékoson, mint a játékos új csapatát
Összefoglalóan az elad() metódus az std::vector osztály erase() metódusa segítségével törli a játékost és az általa szerzett gólok számát a csapat nyilvántartásából
***

Jobb jegyért:
- A Jatekos objektum tartalmazzon egy PlayerStats objektumra való hivatkozást is, amelyben benne van, mi a játékos csapata és hány gólt lőtt a csapatban a játékos.
Ha a játékosnak még nincs csapata, legyen PlayerStats objektumra való mutató nullptr.
- PlayerStats objektum tartalmazzon opcionális hivatkozást az eggyel korábbi PlayerStats objektumra is, amennyiben a játékos átigazolt.
Ilyen módon egy láncolt listát hozhatunk létre minden játékoshoz, és a teljes történetüket nyomon követhetjük.
- Jatekos osztalyban Csapat*-t töröljük (hiszen most már van PlayerStats*), és ennek megfelelően dolgozzuk át a Csapat osztály leigazol() metódusát is.
- A Jatekos osztály részeként implementáljunk egy gol() metódust, amely 1-el növeli az adott játékos csapatában szerzett góljainak számát
- Készítsen a Jatekos osztaly reszekent egy statisztika() metodust, amely kiirja, hogy melyik csapatban hany golt szerzett a jatekos.
- Készítsen destruktort a Jatekos osztályhoz, amivel törölni lehet a játékos statisztikáját (a láncolt listát).
*/

#include "stdafx.h"
#include "jatekos.h"
#include <iostream>

int main() {
	
	// Kettes szint tesztelese... Kettes szint után kikommentelni!
	Jatekos cr = Jatekos("C. Ronaldo", 1985);
	Jatekos lm = Jatekos("L. Messi", 1987);
	Jatekos sr = Jatekos("S. Ramos", 1986);
	Jatekos km = Jatekos("K. Mbappe", 1998);
	Jatekos kb = Jatekos("K. Benzema", 1987);

	Csapat rma = Csapat("Real Madrid");
	Csapat psg = Csapat("Paris Saint Germain");
	Csapat juv = Csapat("Juventus");
	Csapat bar = Csapat("Barcelona");

	juv.leigazol(&cr);
	juv.leigazol(&kb);
	rma.leigazol(&lm);
	bar.leigazol(&lm); // megsem Real Madridban jatszik Lionel Messi
	rma.leigazol(&km); 
	psg.leigazol(&km); // megsem Real Madridban jatszik Kylian Mbappe
	rma.leigazol(&kb); // megis Real Madridban jatszik Karim Benzema
	rma.leigazol(&sr); // Sergio Ramos is madridos...

	rma.jatekosok();
	//Kiirja, hogy:
	//***
	//Real Madrid csapat jatekosai:
	//K. Benzema
	//S. Ramos
	//***
	juv.jatekosok();
	// Csak C. Ronaldo
	

	/* Tovabbi feladatok tesztelese */
	// elotte a fenti reszt kommenteljuk ki!
	/*
	Jatekos cr = Jatekos("C. Ronaldo", 1985);
	cr.gol(); // nem csinal semmit, mert nincs meg csapata
	cr.statisztika(); // kiirja, hogy CR meg egy csapathoz sem szerzodott
	Jatekos lm = Jatekos("L. Messi", 1987);
	Jatekos sr = Jatekos("S. Ramos", 1986);
	Jatekos km = Jatekos("K. Mbappe", 1998);
	Jatekos kb = Jatekos("K. Benzema", 1987);

	Csapat rma = Csapat("Real Madrid");
	Csapat psg = Csapat("Paris Saint Germain");
	Csapat juv = Csapat("Juventus");
	Csapat bar = Csapat("Barcelona");

	juv.leigazol(&cr);
	cr.gol();
	juv.leigazol(&kb);
	rma.leigazol(&lm);
	lm.gol();
	bar.leigazol(&lm); // megsem Real Madridban jatszik Lionel Messi
	lm.gol();
	rma.leigazol(&km);
	km.gol();
	km.gol();
	psg.leigazol(&km); // megsem Real Madridban jatszik Kylian Mbappe
	km.gol();
	rma.leigazol(&kb); // megis Real Madridban jatszik Karim Benzema
	kb.gol();
	rma.leigazol(&sr); // Sergio Ramos is madridos...

	rma.jatekosok();
	//Kiirja, hogy:
	//***
	//Real Madrid csapat jatekosai:
	//K. Benzema
	//S. Ramos
	//***
	juv.jatekosok();
	// Csak C. Ronaldo

	km.statisztika();
	lm.statisztika();
	*/

	char c;
	std::cin >> c;

}


