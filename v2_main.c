#include "header.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    int versenyzok_szama; 
    printf("Versenyzők száma: \n");
    scanf("%d", &versenyzok_szama);

    printf("Versenyzőket tartalmazó file: \n");
    char filename[256]; 
    scanf("%s", filename);

    int csoportok_szama;
    printf("Hány csoport legyen?");
    scanf("%d", &csoportok_szama);

    Jatekos* jatekosok = input(filename, versenyzok_szama);
    string_reset(jatekosok, versenyzok_szama);


    //jatekos szam csoportonkent divvel
    div_t rendes = div(versenyzok_szama, csoportok_szama);
    int jatekosszam_csoportonkent = (rendes.quot + 1);

    div_t paros = div(versenyzok_szama / 2, csoportok_szama);
    int parszam_csoportonkent = (paros.quot + 1);

    //sorsolas
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);
    shuffle(jatekosok,versenyzok_szama);

    //paros vagy sima 
    printf("Ha a verseny egyéni 1, ha a verseny páros 2: \n");
    int verseny_fajta;
    scanf("%d", &verseny_fajta);
    if(verseny_fajta == 1){

        Csoport* csoportok;
        csoportok = csoport_osztas(jatekosok, versenyzok_szama, csoportok_szama, jatekosszam_csoportonkent);
        print_csoport(csoportok, csoportok_szama);
        free(jatekosok);
        free(csoportok);
        return 0;
    }
    if (verseny_fajta == 2){

        Paros_csapat* parok = paros_par_osztas(jatekosok, versenyzok_szama);
        
        Paros_csoport* csoportok = paros_csoport_osztas(parok,versenyzok_szama, csoportok_szama, parszam_csoportonkent);
        
        print_paros_csoport(csoportok, csoportok_szama);

        return 0;
    }
}