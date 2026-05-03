#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float probability(int location){
    if(location==1)     //ISS
        return 0.0001f;
    if(location==2)     //Mars
        return 0.0005f;
    if(location==3)     //Deep space
        return 0.005f;
    return 0.000001f; //Earth
}

char basechanges(char original){
    char bases[4]={'A','G','C','T'};
    int flag=0,value;
    char modified;
    do{
        value=rand()%4;
        if(bases[value]!=original){
            modified=bases[value];
            flag=1;
        }
    }while (flag!=1);

    return modified;
}


int is_survived(int count,int length) {
    float percentage = ((float)count / length) * 100;
    
    if(percentage >= 30.0) {
        return 0; // DEAD
    } else {
        return 1; // SAFE
    }
}


void mutation(char *inputdna,char *outputdna,int location){
    int i,counter=0;
    float prob=probability(location);
    for(i=0;inputdna[i];i++){
        float base_prob;
        if(inputdna[i]=='G')    //WEIGHTING LOGIC
            base_prob=prob*1.5; //increase of 50%
        else if(inputdna[i]=='A')
            base_prob=prob*1.2; //increase of 20%
        else  
            base_prob=prob;
        if((((float)(rand()))/RAND_MAX)<=base_prob){          //now it changes bases
            if(((float)(rand())/RAND_MAX)<=base_prob*0.1){    //chain rupture probability
                outputdna[i]='X';
                counter+=5;             //more damage
            }
            else{
                outputdna[i]=basechanges(inputdna[i]);
                counter++;
            }
        }
        else
            outputdna[i]=inputdna[i];
    }
    outputdna[i]='\0';
    printf("\nThis DNA has in total %d mutations",counter);
    printf("\nSurvival Status: %s",is_survived(counter, strlen(inputdna)) ? "SAFE" : "DEAD");
}


//

int mutationcounter(char *dna) {
    int count=0;
    for(; *dna; dna++) {
        if(*dna == 'X') {
            count++;
        }
    }
    return count;
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
    
    char dna[] = "ATGCGATACGTTGCAATCGACTGACTAGCTAGCTAGCT";
    char dna_2[]="ATGGGCCTATTAGGCTATACGGGCTAGTAAGCCATATC";
    char modified_dna[strlen(dna) + 1];
    char modified_dna_2[strlen(dna_2) + 1];

    int location;
    printf("Insert the number of the location you want to simulate:\n1) ISS\n2) Mars\n3) Deep Space\n4) Earth");
    do{
        scanf("%d",&location);
    }while(location<1 || location >4);


    printf("FIRST ORIGINAL DNA SEQUENCE: %s\n", dna);
    printf("SECOND ORIGINAL DNA SEQUENCE: %s\n", dna_2);
    
    //OUTPUT

    printf("\nBased on the number of purines the %s dna sequence is the most susceptible to damage",comparator(dna,dna_2) ? "FIRST" : "SECOND");
    printf("\nFIRST DNA SEQUENCE:\n");
    mutation(dna, modified_dna, location);
    printf("\nMODIFIED DNA SEQUENCE: %s", modified_dna);

    printf("\n SECOND DNA SEQUENCE:\n");
    mutation(dna_2,modified_dna_2,location);
    printf("\nMODIFIED DNA SEQUENCE: %s", modified_dna_2);


    
    return 0;
}
