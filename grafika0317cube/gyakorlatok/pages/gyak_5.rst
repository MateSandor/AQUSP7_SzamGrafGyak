5. Modellek betöltése, OBJ formátum
===================================

OBJ loader statikus library használata
--------------------------------------

* Keressük meg az ``me-courses`` repository-ban a ``utils`` nevű mappát!
* A statikus library a ``utils/obj`` jegyzékben van.
* Lépjünk be a jegyzékbe, és adjuk ki a ``make`` parancsot.
* Létre fog jönni egy ``libobj.a`` fájl. Ezt másoljuk be a fordító ``lib`` jegyzékébe.
* A ``utils/obj/include`` jegyzékben lévő header fájlokat másoljuk be a fordító ``include/obj`` nevű jegyzékébe. (Az ``obj`` nevű jegyzék nem létezik, azt létre kell hozni.)


Blender
-------

* A modellek szerkesztéséhez Blender-t értdemes használni: https://www.blender.org/
* A modell exportálásánál figyelni kell arra, hogy
    * a modell csak háromszögeket tartalmazzon (*Triangle faces* kapcsoló),
    * a felfele irány megfelelően legyen megadva (általában Z szokott lenni),
    * a modell a normálvektorokat és a textúrakoordinátákat is tartalmazza (ez alapértelmezés szerint jól van),
    * csak a kijelölt vagy az összes objektumot el kell-e menteni (részemről inkább a kijelöltre hagyatkozom).
* A modellek előkészítéséről és használatáról itt található egy videó: https://www.uni-miskolc.hu/~matip/downloads/grafika/animals.ogv


Feladatok
---------

* A tigrises demo-ban próbáljuk kicserélni a modellt!
* Jelenítsünk meg egy kockát OBJ fájlból beolvasva!
* Rajzoljuk ki ugyanazt a modellt egy 4x4-es rácsba!
* Töltsünk be egyszerre két modellt, és az egyiket forgassuk!
* Töltsünk be egyszerre két modellt, és az egyiket lehessen mozgatni egér és/vagy billentyűk segítségével!
* Fordítsuk és futtassuk le a `flat_model.zip <https://www.uni-miskolc.hu/~matip/downloads/grafika/flat_model.zip>`_ fájlban lévő programot!
* Cseréljük ki a házat a ``kocka.obj``-ben lévő modellre!
* Nézzük meg, hogy a modell adatai hogyan kerülnek tárolásra az OBJ fájlokban!
* Módosítsuk a megjelenített modell színét és pozícióját!
* Töltsük be és jelenítsük meg egyszerre a kocka és a ház modelljét!


Kérdések
--------

* Milyen előnyei és hátrányai vannak az adatok bináris és a szöveges fájlokban történő tárolásának?
* A modellekhez milyen adatok tartoznak, amelyeket az OBJ fájlokban tárolunk?
* Milyen módon tárolja az WaveFront OBJ szabványa a modellekhez tartozó adatokat?
* Egy betöltött modellt meg tudunk-e jeleníteni több különböző helyen a virtuális terünkben?
* Hogyan néz ki egy tetraéder adatait tartalmazó OBJ fájl?
* Mennyi számértéket fog tartalmazni egy szabályos oktaéder adatait tartalmazó OBJ fájl?
* Hogyan tárolja az OBJ fájl magukat a textúrákat?
* Miért előnyös, hogy ha a normálvektorok le vannak tárolva a modellfájlban?
