#include "header.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
    Jatekos* jatekosok;
    int versenyzok_szama = atoi(argv[2]);
    char* filename;
    filename = argv[1];
    jatekosok = input(filename, versenyzok_szama);
    string_reset(jatekosok, versenyzok_szama);

    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);

    int csoportszam = atoi(argv[3]);
    div_t result = div(versenyzok_szama, csoportszam);
    int jatekosszam_csoportonkent = (result.quot + 1);
    printf("\n");
    printf("%d \n", jatekosszam_csoportonkent);
    printf("\n");

    Csoport* csoportok;
    csoportok = csoport_osztas(jatekosok, versenyzok_szama, csoportszam, jatekosszam_csoportonkent);
    print_csoport(csoportok, csoportszam);

    free(jatekosok);
    return 0;
}