2. Koordináta transzformációk (2D)
==================================

Feladatok
---------

Szakaszok rajzolása
~~~~~~~~~~~~~~~~~~~

* Definiáljunk egy szakasz (``Line``) nevű struktúrát, amelyik tartalmazza a szakasz végpontjait és a kirajzoláshoz használt színt! (A szín lehet index vagy karakter szerint megadott, vagy RGB komponensekkel is. Utóbbi esetben célszerű definiálni egy külön ``Color`` struktúrát.)
* Nézzünk utána, hogy hogyan kezelhető SDL-ben az egéresemény! Kérdezzük le az egérkurzor pozícióját és írassuk ki a szabványos kimenetre!
* Készítsünk egy szakasz rajzoló programot, amellyel egérkattintással lehet megadni a szakaszok végpontjait! (Feltételezzük, hogy legfeljebb ``MAX_LINE_COUNT`` számú szakasz tárolható és jeleníthető meg egyszerre.)
* Készítsünk egy palettát, ahonnan kattintással kiválasztható az adott szakasz megjelenítéséhez használt színt!
* Készítsünk egy olyan változatot, melyben a szakaszok helyett beszínezett téglalapok vannak!


Kör közelítése
~~~~~~~~~~~~~~

* Az ``examples/circle`` példában szereplő ``Circle`` struktúrát egészítsük ki egy szín attribútummal!
* A szakasz kirajzolásához használt függvény segítségével készítsünk egy olyan programot, amely a körvonalat szakaszokkal közelíti!
* Vizsgáljuk meg azon eseteket, amikor a közelítést a felosztáshoz használt lépések számával, a lépések szögével illetve a kirajzolt szakaszok maximális hosszával adhatjuk meg!
* Készítsünk egy programot, amellyel különböző színű köröket lehet megjeleníteni!
* Oldjuk meg, hogy az egér segítségével új köröket is meg lehessen adni! (A számukat itt is maximalizálhatjuk, például egy ``MAX_CIRCLE_COUNT`` értékkel.)
* Az egéresemények kezelésével rajzoljunk be egy + vagy x jelet azon körökbe, amely felett van éppen a kurzor. (Egyidejűleg több felett is lehet.)
* Oldjuk meg, hogy a kirajzolt köröket az egér segítségével lehessen mozgatni!


Mátrixok, transzformációk
~~~~~~~~~~~~~~~~~~~~~~~~~

* Nézzük át a `Számítógépi grafika jegyzet <http://abrpc09.abrg.uni-miskolc.hu/segedlet/dokumentumok/TISZK/Szamitogepi_grafika.pdf>`_ 28. oldalától a koordináta transzformációkat!
* Nézzük át a ``matrices`` példát az ``me-courses`` repository-ban!

Végezzük el a kódban az alábbi bővítéseket!

* Definiáljunk egy ``init_identity_matrix`` függvényt, amelyik az egységmátrixot inicializálja!
* Definiáljunk függvényt a mátrix skalárral való szorzásához!
* A ``multiply_matrices`` függvényben implementáljunk a mátrix szorzást!
* Definiáljuk a ``transform_point`` függvényt, amelyik egy síkbeli, homogén koordinátákkal adott pontra végzi el a paraméterben kapott mátrix által leírt transzformációt!
* Írjunk 3 függvényt a transzformációkhoz, amelyik módosítja az első paraméterében kapott transzformációs mátrixot! A függvények neve legyen ``scale``, ``shift``, ``rotate``! A skálázás és a forgatás origó középpontú legyen!
* Készítsünk példát minden elkészített függvény használatára vonatkozóan!


Kiegészítő feladatok
--------------------

* Készítsünk egy verem struktúrát, amelynek az elemei transzformációs mátrixok!
* Valósítsuk meg a ``push_matrix`` és ``pop_matrix`` műveleteket!
* Készítsünk példát, amelyben ennek a segítségével "visszavonhatóak" lesznek a műveletek!


Kérdések
--------

* Hogyan lehet átírni egy Descartes koordinátarendszerbeli pont koordinátáit homogén koordinátarendszerbe?
* Hogyan írható át egy homogén koordinátarendszerbeli pont Descartes koordinátarendszerbe?
* Hogyan írható fel egy adott :math:`\varphi` szög esetében az origó körüli elforgatás mátrixa?
* Hogyan néznek ki az eltolás, elforgatás és skálázás mátrixoknak az inverzei?
* Hogyan számíthatjuk ki két egyenes metszéspontját homogén koordinátarendszerben?
* Hogyan számíthatjuk ki két homogén koordinátarendszerbeli pont alapján a rajtuk áthaladó egyenest?
* Miből tudhatjuk, hogy egy homogén koordinátarendszerbeli pontnak nincs Descartes koordinátarendszerbeli megfelelője?
* Hogyan számíthatjuk ki egy összetett transzformáció transzformációs mátrixát az elemi transzformációs mátrixok ismeretében?
* Adjunk példát olyan esetre, amikor számít a transzformációk sorrendje!
* Adjunk példát olyan esetre, amikor nem számít a transzformációk sorrendje!
* Írjuk fel annak a térbeli transzformációnak a transzformációs mátrixát, amelyik a tér pontjait az X-Z síkra képzi le!
