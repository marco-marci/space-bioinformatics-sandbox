#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mutation(char *inputdna,char *outputdna,const int level) {
    int i;
    for(i=0; inputdna[i]  ; i++) {
        if(inputdna[i]=='A' || inputdna[i]=='G'){
            if((rand() % 15) < level) {
                outputdna[i] = 'X';
            }
            else {
                outputdna[i] = inputdna[i];
            }
        }
        else{
            if((rand() % 20) < level) {
                outputdna[i] = 'X';
            }
            else {
                outputdna[i] = inputdna[i];
            }
        }
    }
    
    outputdna[i]= '\0'; 
}

int mutationcounter(char *dna) {
    int count=0;
    for(; *dna; dna++) {
        if(*dna == 'X') {
            count++;
        }
    }
    return count;
}

int is_survived(char *dna,const int length) {
    int count = mutationcounter(dna);
    float percentage = ((float)count / length) * 100;
    
    if(percentage >= 30.0) {
        return 0; // Morta
    } else {
        return 1; // Sopravvissuta
    }
}

int purines_counter (char *dna){ //purines are more exposed to damages by radiations
    int c=0;
    while(*dna){
        if(*dna=='A' || *dna=='G')
            c++;
        dna++;
    }
    return c;
}

int comparator (char *dna_1,char *dna_2){
    if(purines_counter(dna_1)>purines_counter(dna_2))
        return 1;
    else
        return 0;
}

int main() {
    srand(time(NULL)); 
    
    int radiationlevel = 0;
    char dna[] = "ATGCGATACGTTGCAATCGACTGACTAGCTAGCTAGCT";
    char dna_2[]="ATGGGCCTATTAGGCTATACGGGCTAGTAAGCCATATC";
    int len = strlen(dna);
    int len_2=strlen(dna_2);
    char modified_dna[len + 1];
    char modified_dna_2[len_2 + 1];


    printf("FIRST ORIGINAL DNA SEQUENCE: %s\n", dna);
    printf("SECOND ORIGINAL DNA SEQUENCE: %s\n", dna_2);
    
    printf("Insert the radiation level (1-10): ");
    do {
        scanf("%d", &radiationlevel);
    } while(radiationlevel < 1 || radiationlevel > 10);

    printf("Based on the number of purines the %s dna sequence is the most susceptible to damage",comparator(dna,dna_2) ? "FIRST" : "SECOND");

    mutation(dna, modified_dna, radiationlevel);
    mutation(dna_2,modified_dna_2,radiationlevel);

    //output 

    printf("\nFIRST MODIFIED DNA SEQUENCE: %s", modified_dna);
    printf("\nIn total there are: %d MUTATIONS", mutationcounter(modified_dna, len));

    printf("\nSECOND MODIFIED DNA SEQUENCE: %s", modified_dna_2);
    printf("\nIn total there are: %d MUTATIONS", mutationcounter(modified_dna_2, len_2));

    // Check survival rate
    if(is_survived(modified_dna, len)) {
        printf("\nCONCLUSION: The cell n°1 survived.\n");
    } else {
        printf("\nCONCLUSION: The cell n°1 died (critical damage).\n");
    }

    if(is_survived(modified_dna_2, len_2)) {
        printf("\nCONCLUSION: The cell n°2 survived.\n");
    } else {
        printf("\nCONCLUSION: The cell n°2 died (critical damage).\n");
    }

    return 0;
}
