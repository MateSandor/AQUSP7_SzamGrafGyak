Gyakorlatok
===========

Gépes gyakorlattal kapcsolatos tudnivalók
-----------------------------------------

* A számítógépeken a D meghajtóra lehet elhelyezni azokat a dolgokat, amelyekre egész félévben szükség lehet. (Az asztalon lévő dolgok időszakosan törlésre kerülnek.)
* Mindenkinek létre kellene hoznia egy saját névre szóló jegyzéket.

Git-tel kapcsolatos tudnivalók
------------------------------

* Az elkészített kódokat (beleértve a gyakorlatokat és a féléves feladatot is) egy *git* repozitóriumba kell elhelyezni.
* Ez lehet például `GitHub <https://github.com/>`_-on, `GitLab <https://about.gitlab.com/>`_-on vagy `BitBucket <https://bitbucket.org/>`_-on. (Mindenki használhatja azt, amelyik szimpatikusabb.)
* A repozitóriumot publikussá kell tenni, hogy egyszerűen elérhető legyen.

Kliens program
~~~~~~~~~~~~~~

A ``git`` használatához valamilyen kliens program szükséges.

* Az egyik egyszerű megoldás a parancssoros git kliens.
* Grafikus alkalmazást is lehet használni, hogy ha valakinek az szimpatikusabb.
* A szövegszerkesztőkbe, IDE-kbe integráltan, jellemzően bővítmény formájában rendelkezésre állnak ilyenek.

Alapvető parancsok
~~~~~~~~~~~~~~~~~~

.. code::

  git init
  git clone
  git status
  git add
  git rm
  git commit
  git log
  git push
  git pull

.. note::

  Érdemes a parancsokat egy lokálisan létrehozott repozitóriumon próbálgatni.


A repozitórium felépítése
-------------------------

.. code::

  /feladat
  /gyakorlatok
  README.md

* A ``feladat`` jegyzékbe kerül majd a féléves feladat.
* A ``gyakorlatok`` jegyzékbe kell a gyakorlatokon megoldott kódokat feltölteni.
* A ``README.md`` állományba kerül majd a repository bemutatása, benne részletezve a féléves feladat specifikációját.


Asset-ek kezelése
-----------------

Az alkalmazásokhoz (a grafikusokhoz különösképpen) szoktak tartozni különböző adatfájlok. Ilyenek például a képek, 3D-s modellek adatait tartalmazó fájlok. Ezek a program futásához szükségesek ugyan, a forráskódnak viszont nem képezik a részét, a fordításhoz nem szükségesek.

Jellemzően ezen fájlok nagyobb méretűek. Érdemes őket külön kezelni. Ez aktuálisan egy példán keresztül bemutatva a következő formában történne.

.. code::

  /assets/models/house.obj
  /assets/models/tree.obj
  /assets/textures/house.png
  /assets/texture/tree.png
  /assets/config.csv

* A textúrák és a modellek külön jegyzékekbe kerülnek.
* Az ``assets`` jegyzéket és tartalmát ZIP formátumban tömörítve kell feltölteni egy tárhelyre.
