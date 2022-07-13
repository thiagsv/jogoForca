#include "funcoes.h"

int main(void) {
    FILE *dicionario;

    int opcaoMenu;
    int parar = 0;

    opcaoMenu = imprimeMenu();

    while (!parar) {
        if (opcaoMenu == 1) {
            dicionario = fopen("dicionario.txt", "a+");

            if (dicionario == NULL) { // caso não consiga abrir o dicionário, o sistema exibe uma mensagem e retorna um erro
                printf("Falha ao se relacionar com o dicionário!");
            }

            opcoesDicionario(dicionario);
            limpaTerminal();
            opcaoMenu = imprimeMenu();
        } else if (opcaoMenu == 2) {
            dicionario = fopen("dicionario.txt", "r");  

            if (dicionario == NULL) { // caso não consiga abrir o dicionário, o sistema exibe uma mensagem e retorna um erro
              printf("Falha ao se relacionar com o dicionário!");
            }

            jogo(dicionario);
            setbuf(stdin, NULL);
            opcaoMenu = imprimeMenu();
        } else if (opcaoMenu == 3) {
            parar = 1;
        }
    }
    return 0;
}