# Projekt bemutatása
Ez a projekt egy egyszerű 2D-s "raycasting" alapú játék motor, amelyet C programozási nyelven írtunk. 
Az alapötlet az volt, hogy egy egyszerű, top-down nézetű, térbeli világot hozzunk létre, amelyben a játékos navigálhat.
A játékos nézete a térben a körülötte lévő falakat és tárgyakat képes megjeleníteni a raycasting technikával, ami valósághűbb látványt eredményez, mint egy egyszerű térképes megjelenítés.

A projekt célja a játékos mozgásának szimulálása egy 2D-s világban, ahol a különböző falak, padlók és mennyezetek textúrái is megjelennek. A raycasting segítségével a játékos látómezejét számítjuk ki, és ennek megfelelően rendereljük a világot.

## Funkciók
Játékos irányítása: A játékos a W, A, S, D billentyűkkel tudja mozgatni a karaktert.

Raycasting algoritmus: A világ megjelenítése valósághűen, a távolságok figyelembevételével történik.

Térkép és textúrák: A játék térképe egy egyszerű 2D mátrix segítségével van reprezentálva, amelyen falak, padlók és mennyezetek helyezkednek el. A falakat és a padlókat megfelelő textúrákkal jelenítjük meg.

Nézet frissítés: A játékos irányától függően a képernyőn az adott irányba tartó falak és textúrák jelennek meg.

## Program követelmények
A program fejlesztéséhez és futtatásához az alábbi eszközökre van szükség:

Operációs rendszer: Linux, Windows, vagy macOS

## Követelmények:

C nyelv

GLUT könyvtár: A grafikai felület és eseménykezelés biztosítására.

OpenGL: A 3D grafikai megjelenítéshez és rendereléshez.

Matematikai függvények: A raycasting algoritmushoz szükséges számításokhoz.

A program a GLUT és OpenGL használatával készül, és a grafikai megjelenítés egyszerűsített 2D raycasting eljárásra épül.

## Jelenlegi állapot
Jelenleg a program képes megjeleníteni a térképet, és alapvető irányítási funkciókat biztosít a játékos számára. Az irányítás a W, A, S, D billentyűkkel működik. Az alap raycasting algoritmus működik, és a falak textúrázása is elkezdődött, de finomhangolásra és további funkciók hozzáadására van szükség.

### Jelenleg nincs:

További játékelemek (például NPC-k vagy tárgyak).

Különböző típusú padló és mennyezet textúrák.

Játékmenet logika (pontozás, célok stb.).

## Szükséges assetek
A következő assetek szükségesek a program futtatásához:

ALL_texture.ppm fájl: Ez a fájl tartalmazza a szükséges textúrákat, amelyek a falak, a padló és a mennyezet megjelenítéséhez szükségesek. Az assetek valószínűleg .ppm formátumban vannak, és a program ezt az egyes textúrák kódolására használja.

## Felhasználói felület
A program felhasználói felülete nagyon egyszerű, és teljes egészében egy ablakban történik. Az ablakban megjelenik:

A játékos karaktere: A játékos a képernyő közepén található egy sárga pont formájában, és az irányt az előtte megjelenő vonal jelzi.

A térkép: Az egész világ 2D-s térképe jelenik meg, a falak fehér színnel, az üres területek pedig feketével.

A látótér: A raycasting algoritmus segítségével a játékos körül lévő világot látja, ahol a falak, padlók és mennyezetek textúrákkal vannak megjelenítve.

## Irányítási útmutató
W: A játékos előre mozog.

A: A játékos balra fordul.

S: A játékos hátra mozog.

D: A játékos jobbra fordul.

E: A játékos interakcíóba lép.

A játékos a W és S billentyűk segítségével mozgathatja a karaktert, míg az A és D billentyűkkel fordulhat. A játék irányításához az egyes billentyűk lenyomásával és felengedésével módosíthatjuk a játékos helyzetét.

## További funkciók fejlesztése:
Játékos továábi interakciói: például tárgyak felvétele, vagy NPC-k kommunikációja jöhetne.

Játékmenet: Különböző szintek, célok és pontozási rendszer.

Továbbfejlesztett AI: Társak, ellenségek, illetve egyéb interakciók a játékos környezetében.

Ez a projekt a raycasting alapú 2D játékok fejlesztésének alapjait mutatja be, és lehetőséget ad a játékos világának és funkcióinak bővítésére.
