#include "labirintus.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <fstream>

using namespace std;


void beszur_elem(RitkaM* ritkam, int sor, int oszlop, char ertek)
{
    ritkam->lab[ritkam->meret].sor = sor;
    ritkam->lab[ritkam->meret].oszlop = oszlop;
    ritkam->lab[ritkam->meret].ertek = ertek;
    ritkam->meret++;
}

char lekerdez_elem(RitkaM* ritkam,int sor, int oszlop)
{
    for (int i = 0; i < ritkam->meret; i++)
    {
        if (ritkam->lab[i].sor == sor && ritkam->lab[i].oszlop == oszlop)
        {
            return ritkam->lab[i].ertek;
        }
    }
    return 0;
}

void Kiir(RitkaM* ritkam)
{
    system("cls");
    bool haJatekos;
    bool haCel;
    bool haCsapda;

    for (int i = 0; i < ritkam->sorok; i++)
    {
        for (int j = 0; j < ritkam->oszlopok; j++)
        {
            if (i == 0 || j == 0 || i == ritkam->sorok - 1 || j == ritkam->oszlopok - 1)
            {
                cout << ritkam->fal;
            }
            else
            {
                haJatekos = (i == ritkam->jatekosSor && j == ritkam->jatekosOszlop);
                haCel = (i == ritkam->celSor && j == ritkam->celOszlop);
                haCsapda = false;
                if (haJatekos)
                {
                    cout << ritkam->jatekos;
                }
                else if (haCel)
                {
                    cout << ritkam->cel;
                }
                else
                {

                    if (lekerdez_elem(ritkam, i, j) == ritkam->csapda)
                    {
                        haCsapda = true;

                    }
                    if (haCsapda)
                    {
                        cout << ritkam->csapda;
                    }
                    else
                    {
                        cout << ritkam->ures;
                    }
                }
            }
        }
        cout << endl;
    }
}

// Mélységi bejárás
bool dfs(int sor, int oszlop, vector<vector<bool>>& volt, vector<pair<int, int>> iranyok, RitkaM* ritkam)
{
    if (sor == ritkam->celSor && oszlop == ritkam->celOszlop)
    {
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        int ujSor = sor + iranyok[i].first;
        int ujOszlop = oszlop + iranyok[i].second;
        if (ujSor > 0 && ujSor < ritkam->sorok - 1 && ujOszlop > 0 && ujOszlop < ritkam->oszlopok - 1 && !volt[ujSor][ujOszlop])
        {
            bool csapda = false;
            for (int i = 2; i < ritkam->hossz; i++)
            {
                if (ritkam->lab[i].sor == ujSor && ritkam->lab[i].oszlop == ujOszlop)
                {
                    csapda = true;
                    break;
                }
            }
            if (!csapda)
            {
                volt[ujSor][ujOszlop] = true;
                if (dfs(ujSor, ujOszlop, volt, iranyok, ritkam))
                {
                    return true;
                }
                volt[ujSor][ujOszlop] = false;
            }
        }
    }
    return false;
}

// Ellenőrzi, hogy van-e út a kezdőpont és a cél között
bool letezikUt(RitkaM* ritkam)
{
    vector<pair<int, int>> iranyok = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // a 4 irány
    vector<vector<bool>> volt(ritkam->sorok, vector<bool>(ritkam->oszlopok, false));
    return dfs(ritkam->jatekosSor, ritkam->jatekosOszlop, volt, iranyok, ritkam);
}

RitkaM* Letrehoz(int n, int m, int celSor, int celOszlop, int jatekosSor, int jatekosOszlop)
{
    srand(time(NULL));
    bool letezik_ut = false;
    bool kezdoCsapda = false;

    RitkaM* ritkam = new RitkaM;
    ritkam->sorok = n;
    ritkam->oszlopok = m;
    ritkam->celSor = celSor;
    ritkam->celOszlop = celOszlop;
    ritkam->jatekosSor = jatekosSor;
    ritkam->jatekosOszlop = jatekosOszlop;

    beszur_elem(ritkam, jatekosSor, jatekosOszlop, ritkam->jatekos);
    beszur_elem(ritkam, celSor, celOszlop, ritkam->cel);

    // csapdák véletlenszerű elhelyezése
    while (kezdoCsapda || !letezik_ut)
    {
        ritkam->meret = 2;
        int csapdaSor;
        int csapdaOszlop;
        int csapdakszama = (n * m) / 4;
        ritkam->hossz = csapdakszama + 2;
        for (int i = 2; i < csapdakszama + 2; i++)
        {
            csapdaSor = rand() % (n - 2) + 1;
            csapdaOszlop = rand() % (m - 2) + 1;
            beszur_elem(ritkam, csapdaSor, csapdaOszlop, ritkam->csapda);
        }

        // ellenőrzi, hogy került-e csapda a kezdő vagy cél pozicióra
        kezdoCsapda = false;
        for (int i = 2; i < ritkam->hossz; i++)
        {
            if (ritkam->lab[i].oszlop == jatekosOszlop && ritkam->lab[i].sor == jatekosSor)
            {
                kezdoCsapda = true;
                break;
            }
            else if (ritkam->lab[i].oszlop == celOszlop && ritkam->lab[i].sor == celSor)
            {
                kezdoCsapda = true;
                break;
            }
        }

        // maximum 100 méretű mátrixig ellenőrzi, hogy biztosan van út
        if (!kezdoCsapda)
        {
            if (n * m > 100)
            {
                letezik_ut = true;
            }
            else
            {
                letezik_ut = letezikUt(ritkam);
            }
        }
    }
    return ritkam;
}

RitkaM* LetrehozFilebol(const char* file)
{
    int sorok, oszlopok, celSor, celOszlop, jatekosSor, jatekosOszlop;
    ifstream f(file);
    f >> sorok >> oszlopok >> celSor >> celOszlop >> jatekosSor >> jatekosOszlop;
    RitkaM* ritkam = Letrehoz(sorok, oszlopok, celSor, celOszlop, jatekosSor, jatekosOszlop);
    return ritkam;
}

RitkaM* Frissit_Pozicio(RitkaM* ritkam, char lepes)
{
    switch (lepes)
    {
    case 'w':
        if (ritkam->jatekosSor < 2)
        {
            break;
        }
        ritkam->jatekosSor--;
        break;

    case 's':
        if (ritkam->jatekosSor > ritkam->sorok - 3)
        {
            break;
        }
        ritkam->jatekosSor++;
        break;

    case 'a':
        if (ritkam->jatekosOszlop < 2)
        {
            break;
        }
        ritkam->jatekosOszlop--;
        break;

    case 'd':
        if (ritkam->jatekosOszlop > ritkam->oszlopok - 3)
        {
            break;
        }
        ritkam->jatekosOszlop++;
        break;

    default:
        break;
    }
    Kiir(ritkam);
    return ritkam;
}

void Jatek(RitkaM* ritkam)
{
    int eredeti_jatekosSor = ritkam->jatekosSor, eredeti_jatekosOszlop = ritkam->jatekosOszlop;
    while (true)
    {
        Kiir(ritkam);
        if (ritkam->jatekosSor == ritkam->celSor && ritkam->jatekosOszlop == ritkam->celOszlop)
        {
            cout << "Gratulalok! Elerted a celt!";
            break;
        }
        char lepes = _getch(); // Lépés beolvasása
        Frissit_Pozicio(ritkam, lepes);
        if (lekerdez_elem(ritkam, ritkam->jatekosSor, ritkam->jatekosOszlop) == ritkam->csapda)
        {
            cout << "Vesztettel! Csapdaba leptel!" << endl;
            cout << "Nyomj le egy billentyut az ujrakezdeshez." << endl;
            _getch(); // Várakozás a billentyű lenyomására
            ritkam = Letrehoz(ritkam->sorok, ritkam->oszlopok, ritkam->celSor, ritkam->celOszlop, eredeti_jatekosSor, eredeti_jatekosOszlop);
            Jatek(ritkam);
            return;
        }

    }
}

void Felszabadit(RitkaM* ritkam)
{
    delete[] ritkam->lab;
}