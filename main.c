#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[20];
    int habilidade;
    int energia;
} Criatura;

typedef struct {
    char texto[1000];
    int concluido; /* Se esse desafio foi concluido 1, caso contrário 0 */
    Criatura criatura;
    int resposta;
    int tipo; /* se for desafio 1, se for batalha 2*/
} Desafio;

void salvar_desafio(Desafio desafio)
{
    FILE *desafios = fopen("desafios.bin", "ab");

    if (!desafios) {
        printf("Erro ao tentar ler o arquivo desafios.bin");
        exit(1);
    }

    fwrite(&desafio, sizeof(Desafio), 1, desafios);

    fclose(desafios);

    printf("Desafio salvo!\n");
}
void imprime_desafio(Desafio desafio)
{
    int opcao;
    system("cls");
    printf("TEXTO: \n");
    printf("%s\n\n", desafio.texto);

    if (desafio.tipo == 1) {
        printf("Resposta: %d\n", desafio.resposta);
    } else {
        printf("NOME CRIATURA: %s\n", desafio.criatura.nome);
        printf("ENERGIA CRIATURA: %d\n", desafio.criatura.energia);
        printf("HABILIDADE CRIATURA: %d\n", desafio.criatura.habilidade);
    }

    do {
        printf("SALVAR DESAFIO?\n1 - SIM\n2 - NÃO\nOPÇÃO: ");
        scanf("%d", &opcao);
        if (opcao == 1) salvar_desafio(desafio);
    } while (opcao != 1 && opcao != 2);
}
void interface()
{
    system("cls");
    Desafio desafio;
    char msg[1000];
    char nome_arquivo[20];
    int opcao;

    printf("Informe o nome do arquivo (Ex: desafio1.txt): ");
    fflush(stdin);
    gets(nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (!arquivo) {
        printf("Erro ao tentar ler o arquivo!\n");
        exit(1);
    }

    strcpy(desafio.texto, "");
    while (fgets(msg, 1000, arquivo) != NULL) {
        strcat(desafio.texto, msg);
    }

    desafio.concluido = 0;

    do {
        printf("É um desafio ou uma batalha?\n1 - DESAFIO\n2 - BATALHA\nOPÇÃO: ");
        scanf("%d", &opcao);
        if (opcao == 1) {
            desafio.tipo = 1;
            printf("Qual a resposta para a pergunta do desafio (tipo int)?: ");
            scanf("%d", &desafio.resposta);
        } else if (opcao == 2) {
            desafio.tipo = 2;
            printf("Qual o nome da criatura? ");
            fflush(stdin);
            gets(desafio.criatura.nome);
            printf("ENERGIA da criatura: ");
            scanf("%d", &desafio.criatura.energia);
            printf("HABILIDADE da criatura: ");
            scanf("%d", &desafio.criatura.habilidade);
        } else {
            printf("Opção inválida!\n");
            system("cls");
        }
    } while (opcao != 1 && opcao != 2);

    imprime_desafio(desafio);
}
int main()
{
    int opcao = 1;
    setlocale(LC_ALL, "Portuguese");

    printf("Deseja adicionar um desafio?\n1 - SIM\n2 - NÃO\nOPÇÃO: ");
    scanf("%d", &opcao);

    while (opcao == 1) {
        interface();
        system("cls");
        printf("Deseja adicionar outro desafio?\n1 - SIM\n2 - NÃO\nOPÇÃO: ");
        scanf("%d", &opcao);
    }

    return 0;
}
