#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mutation(char *inputdna,char *outputdna,const int level) {
    int i;
    for(i=0; inputdna[i]  ; i++) {
        if((rand() % 20) < level) {
            outputdna[i] = 'X';
        } else {
            outputdna[i] = inputdna[i];
        }
    }
    
    outputdna[i]= '\0'; 
}

int mutationcounter(char *dna,const int length) {
    int count=0;
    for(; *dna; dna++) {
        if(*dna == 'X') {
            count++;
        }
    }
    return count;
}

int is_survived(char *dna,const int length) {
    int count = mutationcounter(dna, length);
    float percentage = ((float)count / length) * 100;
    
    if(percentage >= 30.0) {
        return 0; // Morta
    } else {
        return 1; // Sopravvissuta
    }
}

int main() {
    srand(time(NULL)); 
    
    int radiationlevel = 0;
    char dna[] = "ATGCGATACGTTGCAATCGACTGACTAGCTAGCTAGCT";
    int len = strlen(dna);
    char modified_dna[len + 1]; 

    printf("SEQUENZA DNA ORIGINALE: %s\n", dna);
    
    printf("Inserisci il livello di radiazioni (1-10): ");
    do {
        scanf("%d", &radiationlevel);
    } while(radiationlevel < 1 || radiationlevel > 10);

    mutation(dna, modified_dna, radiationlevel);

    printf("\nSEQUENZA DNA MODIFICATA: %s", modified_dna);
    printf("\nIn totale sono avvenute: %d MUTAZIONI", mutationcounter(modified_dna, len));

    // Controllo sopravvivenza
    if(is_survived(modified_dna, len)) {
        printf("\nESITO: La cellula e' SOPRAVVISSUTA.\n");
    } else {
        printf("\nESITO: La cellula e' NON SOPRAVVISSUTA (Danno critico).\n");
    }

    return 0;
}
