#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Obs.: as cores azul e ciano podem confundir um pouco
#define ESC "\033["
#define END "\033[0m"
#define RED 31 //1
#define GREEN 32 //2
#define YELLOW 33 //3
#define BLUE 34 //4
#define MAGENTA 35 //5
#define CIANO 36 //6

char tab[13][16]={
    "| 0 0 0 0 0 0 |",
    "| 1 2 3 4 5 6 |",
    "'-------------'",
    "               ",
    "1.      |      ",
    "2.      |      ",
    "3.      |      ",
    "4.      |      ",
    "5.      |      ",
    "6.      |      ",
    "7.      |      ",
    "8.      |      ",
    "9.      |      ",
};

int main(){
    srand(time(NULL));
    int resp[4], continuar=0;
    for(int i=0; i<4; i++){
        resp[i] = rand()%6+1;
    }

    for(int y=0; y<13; y++){
        for(int x=0; x<16; x++){
            if(x>1 && x<13 && x%2==0 && y==0){
                printf("%s%dm%c%s", ESC, (x/2)+30, tab[y][x], END);
            }
            else printf("%c", tab[y][x]);
        }
        printf("\n");
    }
    printf("\n\nInstrucoes:\n1. Digite os numeros correspondentes as cores dos seus palpites (4) separados por espaço.\n");
    printf("2. 'O': uma das cores existe e esta na posicao certa\n");
    printf("   '/': uma das cores existe mas esta na posicao errada\n");
    printf("   'X': uma das cores nao existe\n");
    printf("3. A relacao de erros e acertos nao aparece em ordem.\n4. Uma cor pode aparecer mais de uma vez.");

    for(int rodada=1; rodada<=9; rodada++){//---------------------------------------
        printf("\033[14;1H");
        int jogada[4], posic[4], p=0;
        continuar=0;
        char feedback[4];

        for(int i=0; i<4; i++){
            scanf("%d", &jogada[i]);
        }

        for(int i=0; i<4; i++){
            if(resp[i]==jogada[i]){
                feedback[i]='O';
                posic[p]=i;
                p++;
            }
            else{
                feedback[i]='X';
                continuar=1;
            }
        }
        for(int j=0; j<4; j++){
            for(int r=0; r<4; r++){
                if(jogada[j]==resp[r] && j!=r){
                    int chave=1;
                    for(int i=0; i<p; i++)if(posic[i]==r)chave=0;
                    if(chave){
                        feedback[j]='/';
                        posic[p]=r; p++;
                    }
                }
            }
        }

        printf("\033[%d;4H", rodada+4);
        for(int i=0; i<4; i++){
            printf("%s%dm0%s", ESC, jogada[i]+30, END);
        }
        printf("\033[%d;11H", rodada+4);
        for(int i=0; i<3; i++){
            for(int j=0; j<4; j++){
                if(i==0 && feedback[j]=='O')printf("%c", feedback[j]);
                if(i==1 && feedback[j]=='/')printf("%c", feedback[j]);
                if(i==2 && feedback[j]=='X')printf("%c", feedback[j]);
            }
        }

        printf("\033[14;1H");
        printf("           ");

        if(!continuar){
            printf("\nParabens! Voce acertou.\n");
            return 0;
        }
    }
    printf("\nVoce perdeu :(\nA sequencia era: ");
    for(int i=0; i<4; i++){
        printf("%s%dm0%s ", ESC, resp[i]+30, END);
    }
    printf("\n");

    return 0;
}