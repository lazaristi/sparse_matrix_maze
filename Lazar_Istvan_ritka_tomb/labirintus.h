#ifndef LABIRINTUS
#define LABIRINTUS

typedef struct RitkaM
{
    // a játékban levő karakterek jelzése
    const char fal = '#';
    const char ures = ' ';
    const char cel = 'X';
    const char csapda = '*';
    const char jatekos = 254;

    int sorok;
    int oszlopok;
    int celSor;
    int celOszlop;
    int jatekosSor;
    int jatekosOszlop;
    int hossz;
    int meret = 0;

    struct Cella
    {
        int sor;
        int oszlop;
        char ertek;
    };
    Cella* lab = new Cella[1000]; // a labirintusban levő elemek eltárolása

} RitkaM;

// Labirintus létrehozása, a kezdő és cél pozició, illetve a csapdák elhelyezése
RitkaM* Letrehoz(int, int, int, int, int, int);

// Labirintus létrehozása file-ból
RitkaM* LetrehozFilebol(const char*);

// Elem beszúrása a tömbbe
void beszur_elem(RitkaM*, int, int, char);

// Elem lekérdezése a tömbből
char lekerdez_elem(RitkaM*, int, int);

// Labirintus kiírása
void Kiir(RitkaM*);

// A játékos pozició frissítése lépés után
RitkaM* Frissit_Pozicio(RitkaM*, char);

// A teljes játékmenet
void Jatek(RitkaM*);

// Lefoglalt memória felszabadítása
void Felszabadit(RitkaM*);

#endif 

