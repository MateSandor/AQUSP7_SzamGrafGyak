1. Fejlesztőkörnyezet beüzemelése
=================================

A fejlesztőkörnyezet összeállítása
----------------------------------

Windows esetében a fejlesztéshez szükséges dolgok a `c_sdk_220203.zip <https://www.uni-miskolc.hu/~matip/_downloads/c_sdk_220203.zip>`_ formájában letölthetőek.
Telepíteni nem szükséges, mindössze ki kell tömöríteni egy tetszőleges helyre. A csomag tartalmazza

* a Git parancssori változatát,
* a GNU C/C++ fordítóját,
* a szükséges OpenGL és SDL2 fejléceket és binárisokat,
* a Notepad++ szövegszerkesztőt.

GNU/Linux és más UNIX-szerű rendszerben a ``gcc``, ``make`` programokra és az SDL2 függvénykönyvtár telepítésére van szükség.


Repository-k szervezése
-----------------------

* A D meghajtón létre kell hozni egy saját jegyzéket.
* Ki kell tömöríteni bele a C fejlesztéshez használt SDK-t (akár közvetlenül ide másolva a fájlokat).
* Az SDK-ban lévő programok eléréséhez el kell indítani a ``shell.bat`` fájlt.
* A gyakorlatokhoz tartozó anyagok a `www.gitlab.com/imre-piller/me-courses <https://www.gitlab.com/imre-piller/me-courses>`_ címről érhetők el. A repository-t le kell klónozni a kitömörített SDK-ba. (Nem muszáj ide, de így praktikus.)
* A branch-et át kell váltani a ``grafika`` nevűre:

.. code::

  git checkout -b grafika origin/grafika

A repository-t időszakosan ``pull`` paranccsal érdemes frissíteni.
* Szintén a kitömörített SDK jegyzékébe klónozni kell a hallgató saját repository-ját.
* A példák megoldása során az ``me-courses``-ból célszerű egyből átmásolni a fájlokat, hogy a módosításoka vissza lehessen tölteni.


Példa programok fordítása és futtatása
--------------------------------------

* A példa programokról célszerű másolatot készíteni a saját repository-ba (azon belül is a ``gyakorlatok`` nevű jegyzékbe).
* El kell indítani a ``shell.bat`` fájlt.
* Be kell lépni a parancssorban a megfelelő mappába.
* Ki kell adni egy ``make`` parancsot.
* Le kell ellenőrízni, hogy létrejött-e a futtatható állomány.
* Meg kell próbálni elindítani. Dupla kattintás esetén hiányzó DLL-el kapcsolatos hibaüzenetet kaphatunk. Ezt vissza lehet keresni a ``MinGW/bin`` jegyzékben. Parancssorból futtatva a problémának nem szabad fennállnia.


Programozási feladat
--------------------

A ``circle`` példához hasonlóan készítendő el.

* Készítsünk egy programot, amellyel téglatestek adatait lehet kezelni!
* Definiáljunk egy struktúrát (például ``Cuboid`` vagy ``Brick`` néven), amely tartalmazza a téglatest 3 élének a hosszát!
* Definiáljunk egy függvényt, amellyel ellenőrzött módon be lehet állítani egyszerre a 3 él hosszát (például ``set_size`` néven)!
* Definiáljunk egy függvényt, amelyik kiszámítja a téglatest térfogatát (például ``calc_volume``), és egy másikat amelyik a felszínét (például ``calc_surface``)!
* Definiáljunk egy függvényt, amelyik a téglalapot megvizsgálja, hogy van-e négyzet alakú lapja!


Kérdések
--------

* Milyen fő lépéseken keresztül lesz a forrásfájlokból futtatható állomány?
* Mire szolgálnak a statikus függvénykönyvtárak (*static library*)?
* Miért és hogyan használjuk a ``make`` programot?
* Mi a különbség a statikus és a dinamikus linkelés között?
* Mit csinál az SDK-ban a ``shell.bat``?
* Célszerűen mi kerül a forrás és a fejléc (*header*) állományokba?
