#include <stdio.h>
#include <stdlib.h>

//imprime na tela o menu com as opções 
int imprimeMenu() {
    int opcao = 0; 

    printf("1 - Acessar as opções de dicionário: ");
    scanf("%d", &opcao);

    return opcao;
}

int quantidadeCaracteresArquivo(FILE *dicionario) { //retorna quantidade de caracteres do dicionario
    int count = 1;

    while(!feof(dicionario)) {
        count++;
	}

    return count;
}

void opcoesDicionario(FILE *dicionario) {
    int opcaoDicionario;
    char caracteres[100000000];


    printf("1 - Ver dicionário\n2 - Inserir nova palavra\n3 - Voltar ao menu anterior: ");
    scanf("%d", &opcaoDicionario);

    while(opcaoDicionario < 1 || opcaoDicionario > 3) { //prevenção de erros
        printf("Por favor, digite um número válido!: ");
        scanf("%d", &opcaoDicionario);
    }

    while(opcaoDicionario != 3) { //enquanto não tentar retornar ao menu continua o mesmo processo
        if(opcaoDicionario == 1) { //visualiza o dicionário
            char palavrasDicionario[quantidadeCaracteresArquivo(dicionario)]; //só cria as variáveis quando necessário

            while(!feof(dicionario)) {
                printf("%s", fgets(caracteres, 100000000, dicionario));
            }

        } else if (opcaoDicionario == 2) { //pede a palavra e seu significado, e depois insere no dicionário
            char palavra[500]; //só cria as variáveis quando necessário
            char significado[10000];

            printf("Digite a palavra desejada (caso queira sair digite 0): ");
            scanf("%s", palavra);

            while (palavra[0] != '0') {
                printf("Digite o siginificado da palavra resumida (máx: 10000 carcteres)): ");
                scanf("%s", significado);
                fputs(palavra, dicionario);
                fputs(" - ", dicionario);
                fputs(significado, dicionario);
                printf("Digite a palavra desejada (caso queira sair digite 0): ");
                scanf("%s", palavra);
            }
        }

        printf("1 - Ver dicionário\n2 - Inserir nova palavra\n3 - Voltar ao menu anterior: ");
        scanf("%d", &opcaoDicionario);
    }

    if(opcaoDicionario == 3) { //fecha o arquivo, limpa o terminal e exibe o menu
        fclose(dicionario);
        limpaTerminalEExibeMenu();
    }
}

void limpaTerminalEExibeMenu() {
    system("cls");
    imprimeMenu();
}