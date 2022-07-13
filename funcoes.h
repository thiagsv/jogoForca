#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// imprime na tela o menu com as opções
int imprimeMenu() {
  int opcao = 0;

  printf("1 - Acessar as opções de dicionário\n2 - Jogar forca\n3 - Sair: ");
  scanf("%d", &opcao);

  return opcao;
}

void limpaTerminal() {
  system("clear");
}

void opcoesDicionario(FILE *dicionario) {
    int opcaoEscolhidaDicionario;
    char caracteres[400];
    int sair = 0;

    limpaTerminal();

    printf("1 - Buscar significado\n2 - Inserir nova palavra\n3 - Voltar ao menu anterior: ");
    scanf("%d", &opcaoEscolhidaDicionario);

    while (opcaoEscolhidaDicionario < 1 || opcaoEscolhidaDicionario > 3) { // prevenção de erros
        printf("Por favor, digite um número válido!: ");
    }
    while (!sair) {
        if (opcaoEscolhidaDicionario == 1) {  // visualiza o dicionário
            char palavraBuscar[23];
            char palavraLida[100];
            int terminouVer = 0; //flag
            int encontrou = 0; //flag
            int linha = 1;
            printf("Digita a palavra que deseja buscar: ");
            scanf("%s", palavraBuscar);
          
            int k = strlen(palavraBuscar);
            for(int l = 0; l <= k; l++) {
              palavraBuscar[l] = toupper(palavraBuscar[l]);
            }
            
            while (!feof(dicionario)) {
                fgets(palavraLida, 99, dicionario);
                palavraLida[strcspn(palavraLida, "\n")] = 0;
                if(linha % 2 != 0 && (strcmp(palavraBuscar, palavraLida)) == 0) {//verifica apenas as linhas ímpares, que são as que possuem palavras
                    encontrou = 1; //encontra a palavra
                    break;
                  }
                linha++;//armazena na variável a linha da palavra
            }
            if(!encontrou) {
              printf("Palavra não encontrada ou dicionário vazio!\n");
            } else {
              int cont = 0;
              char significado[100];
              rewind(dicionario);
              while(cont <= linha) { 
                fgets(significado, 99, dicionario); //linhas impares, impar+1 siginificado
                if(cont == linha) {   
                  printf("\nPalavra: %s", palavraBuscar);
                  printf("\n\nSignificado: %s", significado);
                }
                cont++;
              }
            }
            if(terminouVer == 0) {
              printf("\n\nDigite 1 para sair: ");
              scanf("%d", &terminouVer);
            }
        } else if (opcaoEscolhidaDicionario == 2) { //pede a palavra e seu significado, e depois insere no dicionário
            char palavra[20]; // só cria as variáveis quando necessário
            char significado[100];

            printf("Digite a palavra desejada (caso queira sair digite 0): ");
            scanf("%s", palavra);

            int k = strlen(palavra);
            for(int l = 0; l <= k; l++) {
              palavra[l] = toupper(palavra[l]);
            }
            while (palavra[0] != '0') {
              setbuf(stdin, NULL);
              printf("Digite o siginificado da palavra resumida (máx: 100 carcteres)): ");
              fgets(significado, 99, stdin);
              fputs(palavra, dicionario);
              fputs("\n", dicionario);
              fputs(significado, dicionario);
              printf("Digite a palavra desejada (caso queira sair digite 0): ");
              scanf("%s", palavra);
              int k = strlen(palavra);
              for(int l = 0; l <= k; l++) {
                palavra[l] = toupper(palavra[l]);
              }
            }
            fclose(dicionario);
        } else if (opcaoEscolhidaDicionario ==  3) { // fecha o arquivo, limpa o terminal e exibe o menu
            fclose(dicionario);
            sair = 1;
            limpaTerminal();
            imprimeMenu();
        }
        sair = 1;
    }
}

void parteCorpoForca(int erros) {
  char erro = erros + '0'; //transformar o inteiro para char
  switch(erro) {
    case '0':
      printf("\nX==:==\nX  :  \nX\nX\nX\nX\n=======");
      break;   
    case '1':
      printf("\nX==:==\nX  :  \nX  O  \nX\nX\nX\n=======");
      break;
    case '2':
      printf("\nX==:==\nX  :  \nX  O  \nX  |  \nX\nX\n=======");
      break;
    case '3':
      printf("\nX==:==\nX  :  \nX  O  \nX \\|  \nX\nX\n=======");
      break;
    case '4':
      printf("\nX==:==\nX  :  \nX  O  \nX \\|/ \nX\nX\n=======");
      break;
    case '5':
      printf("\nX==:==\nX  :  \nX  O  \nX \\|/  \nX /\nX\n=======");
      break;
    case '6':
      printf("\nX==:==\nX  :  \nX  O  \nX \\|/  \nX / \\ \nX\n=======");
      break;
  }
}

void jogo(FILE *dicionario) {
  char letraDigitada[23]; //quantidade de letras do alfabeto
  char palavraEscolhida[50];
  int erros = 0;
  int cont = 1;
  int teste = 2;
  char c;
  int linha = 1;
  int continua = 1;
  memset(letraDigitada, 0, 22); //limpa o array para evitar erros
  do { //pega a quantidade de linhas do arquivo
    c = fgetc(dicionario);
    if(c=='\n'){
      linha++;
    }
  } while(c != EOF);

  if(linha < 2) { //verfica se ta vazio para continuar o jogo ou não
    printf("Dicionário vazio!\n");
    continua = 0;
  }
  
  fclose(dicionario);
  if(continua) {
    dicionario = fopen("dicionario.txt", "r");
  
    srand(time(NULL));
    int n = rand() % (linha - 1);
  
    if(n % 2 == 0) { //com base na linha randomica, garante que ela seja impar
      n--;
    }
    
    while(cont <= n) { //vai até a palavra
      fgets(palavraEscolhida, 49, dicionario);
      cont++;
    }
  
    int caracteresPalavra = strlen(palavraEscolhida);
  
    cont = 0;
    char formacaoPalavra[caracteresPalavra];
    for(int a = 0; a < caracteresPalavra - 1; a++) { //monta o array que vai ser usado no jogo
      formacaoPalavra[a] = '_';
    }

    limpaTerminal();
    parteCorpoForca(0); //inicia a forca
    while(cont < 23) {
      char letraAux;
      int push = 1; //flag
      int tem = 0; //flag
  
      printf("\n");
      for(int k = 0; k < strlen(formacaoPalavra); k++) {
        printf("%c ", formacaoPalavra[k]);
      }
      printf("\n");
      if(cont > 0) {
        printf("Letras já digitadas: ");
        if(cont == 1) {
          printf("%c", toupper(letraDigitada[0])); //imprime as letras que já foram digitadas
        } else {
          printf("%c", toupper(letraDigitada[0]));
          for(int i = 1; i <= cont - 1; i++) {
            printf(", %c", toupper(letraDigitada[i]));
          }
        }
      }
  
      setbuf(stdin, NULL);
      printf("\nDigite uma letra:\n");
      scanf(" %c", &letraAux);
      for(int k = 0; k < 23; k++) {
        if(toupper(letraDigitada[k]) == toupper(letraAux)) { //verifica se a letra já foi digitada antes de adicionar no array
          printf("Letra já digitada!\n");
          push = 0; //pede para digitar a letra novamente caso já tenha sido digitada
        }
      }
  
      setbuf(stdin, NULL);
      if(push) { //após garantir que a letra não foi digitada antes
        limpaTerminal();
        letraDigitada[cont] = letraAux;
        for(int b = 0; b < caracteresPalavra; b++) { //verifica se a letra digitada anteriormente faz parte da palavra
          if(toupper(letraDigitada[cont]) == toupper(palavraEscolhida[b])) {//se sim, adiciona
            formacaoPalavra[b] = toupper(letraDigitada[cont]);
            tem = 1;
          }
        }
        if(tem == 0) {//se não, então tem erro, atualiza a forca
          erros++;
          printf("\nVocê errou!");
          parteCorpoForca(erros);
          tem = 1;
        } else {
          printf("\nVocê acertou!");
          parteCorpoForca(erros);
        }
        cont++;
      }
  
      if(erros == 6) { //verifica quantidade de erros
        printf("\n\nVocê perdeu! A palavra era: %s\n\n", palavraEscolhida);
        cont = 23;
      }
  
      int acabou = 0;
      for(int t = 0; t < caracteresPalavra; t++) { //verifica se já acabou
        if(formacaoPalavra[t] == '_') {
          acabou = 1;
        }
      }
  
      if(acabou == 0) {
        printf("\n\nVocê ganhou! A palavra era: %s\n\n", formacaoPalavra);
        cont = 23;
      }
    }
  }
}