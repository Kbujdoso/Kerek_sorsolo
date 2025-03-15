#include "header.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Jatekos* input(char* filename, int n){
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Error occoured while opening the file!");
        return NULL;
    }



    Jatekos* buffer;
    buffer = malloc(sizeof(Jatekos)*n);
    if (buffer == NULL){
        printf("Allocation failed!");
        return NULL; 
    }

    for (int i = 0; i < n; i++){
        buffer[i].sorszam = i + 1;
        fgets(buffer[i].nev, (sizeof(buffer[i].nev)), file);
    }
    
    fclose(file);
    printf("Successful data handling! \n");
    return buffer;
}




void print_data(Jatekos* buffer,int n){
    for (int i = 0; i < n; i++){
        printf("%d: %s", buffer[i].sorszam, buffer[i].nev);
        printf("\n");

    }
}

Jatekos* string_reset(Jatekos* buffer, int jatekosszam) {
    for (int i = 0; i < jatekosszam; i++) {
        buffer[i].nev[strcspn(buffer[i].nev, "\n")] = '\0';
    }
    return buffer;
}

void shuffle(Jatekos* buffer, int n) {
    srand((unsigned int)time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        char temp[128]; 
        strcpy(temp, buffer[i].nev);
        strcpy(buffer[i].nev, buffer[j].nev);
        strcpy(buffer[j].nev, temp);
}
}

Csoport* csoport_osztas(Jatekos* buffer, int n, int db, int jatekosszam){
    Csoport* csoportok; 
    csoportok = malloc(sizeof(Csoport)*db);
    if (csoportok == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }
    char nev[128];

    for (int i = 0; i < db; i++){
            csoportok[i].tagok = malloc(sizeof(nev)*jatekosszam);
            if (csoportok[i].tagok == NULL){
             printf("Memory allocation failed!");
            return NULL;
            }
            csoportok[i].tag_szam = 0;

    }


     int j = 0; 
    int count = 0; 
    int extra_tags = n % db; 
    int normal_size = n / db;  

 
    for (int i = 0; i < n; i++) {

        csoportok[j].tagok[count] = malloc(sizeof(char) * (strlen(buffer[i].nev) + 1));
        if (csoportok[j].tagok[count] == NULL) {
            printf("Memory allocation failed for player %s!\n", buffer[i].nev);
            return NULL;
        }
        strcpy(csoportok[j].tagok[count], buffer[i].nev); 

        csoportok[j].tag_szam++;

        count++;

        if (extra_tags > 0 && count >= normal_size + 1) {
            extra_tags--;  
            count = 0;     
            j++;           
        }
        if (j == db) {
            break;
        }

        if (count == normal_size + (extra_tags > 0 ? 1 : 0)) {
            j++;
            count = 0;
        }
    }
    return csoportok;
}


void print_csoport(Csoport* csoportok, int db){
    for (int i = 0; i < db; i++){
        printf("%d. csoport: \n", i + 1);
        for (int j = 0; j < csoportok[i].tag_szam; j++){
            printf("%s \n", csoportok[i].tagok[j]);
        }
        printf("\n");
    }
}


Paros_csapat* paros_par_osztas(Jatekos* buffer, int versenyzok_szama){
    int parok_szama = versenyzok_szama / 2;  
    Paros_csapat* result = malloc(sizeof(Paros_csapat)* parok_szama);
    for (int i = 0; i < parok_szama; i++){
        strcpy(result[i].nev1, buffer[i].nev);
        strcpy(result[i].nev2, buffer[i+parok_szama].nev);      
    } 
    return result;
}


Paros_csoport* paros_csoport_osztas(Paros_csapat* buffer, int versenyzok_szama, int csoportok_szama, int csoport_parszam) {
    
    int parok_szama = versenyzok_szama / 2;
    
    Paros_csoport* csoportok = malloc(sizeof(Paros_csoport) * csoportok_szama);
    if (csoportok == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < csoportok_szama; i++) {
        int aktualis_meret = parok_szama / csoportok_szama + (i < parok_szama % csoportok_szama ? 1 : 0);
        csoportok[i].parok = malloc(sizeof(Paros_csapat) * aktualis_meret);
        if (csoportok[i].parok == NULL) {
            printf("Memory allocation failed!\n");
            // Már lefoglalt memóriák felszabadítása
            for (int k = 0; k < i; k++) {
                free(csoportok[k].parok);
            }
            free(csoportok);
            return NULL;
        }
        csoportok[i].par_szam = 0;
    }

    int j = 0; 
    int count = 0; 
    int extra_tags = parok_szama % csoportok_szama; 
    int normal_size = parok_szama / csoportok_szama; 

    for (int i = 0; i < parok_szama; i++) {
        csoportok[j].parok[csoportok[j].par_szam] = buffer[i];
        csoportok[j].par_szam++;

        count++;

        if (count >= normal_size + (extra_tags > 0 ? 1 : 0)) {
            extra_tags--;  
            count = 0;     
            j++;           
        }
    }

    return csoportok;
}




void print_paros_csoport(Paros_csoport* csoportok, int csoportok_szama){
    for (int i = 0; i < csoportok_szama; i++){
        printf("%d. csoport: \n", i + 1);
        for (int j = 0; j < csoportok[i].par_szam; j++){
            printf("%s - ", csoportok[i].parok[j].nev1);
            printf("%s ", csoportok[i].parok[j].nev2);
            printf("\n");
        }
        printf("\n");
    }
}