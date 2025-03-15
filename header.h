#ifndef HEADER_GUARD
#define HEADER_GUARD

#include "header.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int sorszam;
    char nev[128]; 
} Jatekos;

typedef struct {
    int tag_szam;
    char** tagok;
} Csoport;
typedef struct {
    char nev1[128];
    char nev2[128];
} Paros_csapat;

typedef struct {
    int par_szam;
    Paros_csapat* parok;
} Paros_csoport;

void print_data(Jatekos* buffer,int db);

Jatekos* input(char* filename, int db);

Jatekos* string_reset(Jatekos* buffer, int db);

void shuffle(Jatekos* buffer, int db);

Csoport* csoport_osztas(Jatekos* buffer, int n, int db, int jatekosszam);

void print_csoport(Csoport* csoportok, int db);

Paros_csapat* paros_par_osztas(Jatekos* buffer, int versenyzok_szama);

Paros_csoport* paros_csoport_osztas(Paros_csapat* buffer, int versenyzok_szama, int csoportok_szama, int csoport_parszam);

void print_paros_csoport(Paros_csoport* csoportok, int csoportok_szama);

#endif
