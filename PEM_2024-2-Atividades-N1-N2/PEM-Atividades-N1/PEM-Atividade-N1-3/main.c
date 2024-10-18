/*--------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular           *
*          Prof. Carlos Veríssimo                         *
*-------------------------------------------------------- *
* Objetivo do Programa: Criar um tabuleiro de xadrez em C *
* Data - 17/10/2024                                       * 
* Autores: Matheus Arthur;                                *
*-------------------------------------------------------- */
#include <stdio.h>
#define SIZE 8

void imprimirTabuleiro(char tabuleiro[SIZE][SIZE][4]){
    int i,j;
	printf("    A   B   C   D   E   F   G   H\n");
    for(i = 0; i < SIZE; i++) {
        printf("%i  ", 8 - i);
        for(j = 0; j < SIZE; j++) {
            printf("%s ", tabuleiro[i][j]);
        }
        printf("\n");
        
    }
    printf("\n");
}

int main(){
    char tabuleiro[SIZE][SIZE][4] = {
        {"PT1", "PC1", "PB1", "PR ", "PD ", "PB2", "PC2", "PT2"}, 
        {"PP1", "PP2", "PP3", "PP4", "PP5", "PP6", "PP7", "PP8"},
        {" x ", " x ", " x ", " x ", " x ", " x ", " x ", " x "},
        {" x ", " x ", " x ", " x ", " x ", " x ", " x ", " x "},
        {" x ", " x ", " x ", " x ", " x ", " x ", " x ", " x "},
        {" x ", " x ", " x ", " x ", " x ", " x ", " x ", " x "},
        {"BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8"},
        {"BT1", "BC1", "BB1", "BR ", "BD ", "BB2", "BC2", "BT2"},
    };
    imprimirTabuleiro(tabuleiro);
    
    return 0;
}



