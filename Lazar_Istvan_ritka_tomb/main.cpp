#include "labirintus.h"

using namespace std;

int main()
{
    RitkaM* ritkam = LetrehozFilebol("be1.txt");
    Jatek(ritkam);
    Felszabadit(ritkam);
    
    return 0;
}