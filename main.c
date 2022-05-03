#include "funcoes.h"

int imprimeMenu();

int main(void) {
    FILE *dicionario;

    int opcaoMenu;
    
    opcaoMenu = imprimeMenu();
    
    if(opcaoMenu == 1) {
        dicionario = fopen("dicionario.txt", "a+");

        if (dicionario == NULL) { //caso não consiga abrir o dicionário, o sistema exibe uma mensagem e retorna um erro
            printf("Falha ao se relacionar com o dicionário!");
            return 1;
        }

        opcoesDicionario(dicionario);
    }

   

    return 0;
}               