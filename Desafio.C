
#include <stdio.h>
#include <locale.h>

/*
1 - Escreva um programa que tem a estrutura de dados abaixo. O programa tem as seguintes opções:

1 – Entrada de dados do filme.

2 – Lista todos os filmes na tela.

3 – Pesquisar um filme pelo nome completo e mostra todos os dados na tela.

4 – Pesquisar data de lançamento do filme (mês/ano)

5 – Listar filmes por faixa de preço.

6 – Altera quantidade em estoque (entrada e saída).

7 - Altera preço de um filme pesquisado pelo nome completo.

8 – Altera todos os dados do filme pesquisado pelo nome completo.

9 – Exclui filme pesquisado pelo nome completo.

10 - Saída pelo usuário
*/


/* Estrutura do filme */
typedef struct {
    char nome[50];
    int quantidade;
    float preco;
    int mes;
    int ano;
} Filme;

/* Prototipos das funcoes */
void menu();
void entrada_dados(Filme *filme);
void listar_todos(Filme *filme);
void pesquisar_nome(Filme *filme);
void pesquisar_data(Filme *filme);
void listar_faixa_preco(Filme *filme);
void alterar_estoque(Filme *filme);
void alterar_preco(Filme *filme);
void alterar_dados(Filme *filme);
void excluir_filme(Filme *filme);

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    Filme filme;
    Filme *p;
    p = &filme;


    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: entrada_dados(p); break;
            case 2: listar_todos(p); break;
            case 3: pesquisar_nome(p); break;
            case 4: pesquisar_data(p); break;
            case 5: listar_faixa_preco(p); break;
            case 6: alterar_estoque(p); break;
            case 7: alterar_preco(p); break;
            case 8: alterar_dados(p); break;
            case 9: excluir_filme(p); break;
            case 10: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 10);

    return 0;
}

void menu() {
    printf("\n--- Menu ---\n");
    printf("1 - Entrada de dados do filme\n");
    printf("2 - Lista todos os filmes\n");
    printf("3 - Pesquisar um filme pelo nome\n");
    printf("4 - Pesquisar data de lançamento\n");
    printf("5 - Listar filmes por faixa de preço\n");
    printf("6 - Alterar quantidade em estoque\n");
    printf("7 - Alterar preço de um filme\n");
    printf("8 - Alterar todos os dados de um filme\n");
    printf("9 - Excluir um filme\n");
    printf("10 - Sair\n");
    printf("Escolha uma opção: ");
}

/* Função 1: Entrada de dados */
void entrada_dados(Filme *filme) {
    FILE *arquivo;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "a")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    printf("Digite o nome do filme: ");
    gets(filme->nome);

    printf("Digite a quantidade: ");
    scanf("%d", &filme->quantidade);

    printf("Digite o preço: ");
    scanf("%f", &filme->preco);

    printf("Digite o mês de lançamento: ");
    scanf("%d", &filme->mes);

    printf("Digite o ano de lançamento: ");
    scanf("%d", &filme->ano);

    fwrite(filme, sizeof(*filme), 1, arquivo);
    printf("Filme cadastrado com sucesso!\n");
    fclose(arquivo);
}

/* Função 2: Listar todos os filmes */
void listar_todos(Filme *filme) {

    FILE *arquivo;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo ou nenhum filme cadastrado.\n");
            printf("Teste! Tente adicionar um filme!.\n");
            return 1;
        }
    }

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
            if(filme->nome[0] != '*'){
                printf("\nNome: %s\n", filme->nome);
                printf("Quantidade: %d\n", filme->quantidade);
                printf("Preço: %.2f\n", filme->preco);
                printf("Data de lançamento: %02d/%04d\n", filme->mes, filme->ano);
            }

    }
    fclose(arquivo);
}

/* Função 3: Pesquisar filme pelo nome */

void pesquisar_nome(Filme *filme) {
    FILE *arquivo;
    int i;

    if ((arquivo = fopen("filmes.bin", "r")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    char nome[50];
    printf("Digite o nome do filme: ");
    gets(nome);


    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
        for(i = 0; nome[i] != '\0'; i++){
            if (nome[i] != filme->nome[i]){
                break;
            }
        }
        if (filme->nome[i] == '\0' && nome[i] == '\0') {
            printf("\nNome: %s\n", filme->nome);
            printf("Quantidade: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
            printf("Data de lançamento: %02d/%04d\n", filme->mes, filme->ano);
            return;
        }
    }
    printf("Filme não encontrado.\n");
    fclose(arquivo);
}
/* Função 4: Pesquisar data de lançamento */
void pesquisar_data(Filme *filme) {
    FILE *arquivo;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    int mes, ano;
    printf("Digite o mês e ano de lançamento (mês/ano): ");
    scanf("%d/%d", &mes, &ano);


    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
        if (filme->mes == mes && filme->ano == ano) {
            printf("\nNome: %s\n", filme->nome);
            printf("Quantidade: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
        }
    }
    fclose(arquivo);
}

/* Função 5: Listar filmes por faixa de preço */
void listar_faixa_preco(Filme *filme) {
    FILE *arquivo;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    float min, max;
    printf("Digite a faixa de preço (mínimo e máximo): ");
    scanf("%f %f", &min, &max);

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
        if (filme->preco >= min && filme->preco <= max) {

            if(filme->nome[0] != '*'){
                printf("\nNome: %s\n", filme->nome);
                printf("Quantidade: %d\n", filme->quantidade);
                printf("Preço: %.2f\n", filme->preco);
            }
        }
    }


    fclose(arquivo);
}

/* Função 6: Alterar quantidade em estoque */
void alterar_estoque(Filme *filme) {
    FILE *arquivo;
     int i;

    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }


    char nome[50];
    int nova_quantidade;
    printf("Digite o nome do filme: ");
    gets(nome);

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
            for(i = 0; nome[i] != '\0'; i++){
            if (nome[i] != filme->nome[i]){
                break;
            }
        }
        if (filme->nome[i] == '\0' && nome[i] == '\0') {
            printf("Some ou subtraia a quantidade atual: ");
            scanf("%d", &nova_quantidade);
            filme->quantidade = filme->quantidade + nova_quantidade;
            fseek(arquivo, -sizeof(*filme), SEEK_CUR);
            fwrite(filme, sizeof(*filme), 1, arquivo);
            printf("Quantidade alterada com sucesso.\n");
            fclose(arquivo);
            return;
        }
    }
    printf("Filme não encontrado.\n");
   fclose(arquivo);
}

/* Função 7: Alterar preço de um filme */
void alterar_preco(Filme *filme) {
    FILE *arquivo;
    int i;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    char nome[50];
    float novo_preco;
    printf("Digite o nome do filme: ");
    gets(nome);

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
            for(i = 0; nome[i] != '\0'; i++){
                if (nome[i] != filme->nome[i]){
                    break;
                }
            }

            if (filme->nome[i] == '\0' && nome[i] == '\0') {
                printf("Digite o novo preço: ");
                scanf("%f", &novo_preco);
                filme->preco =  novo_preco;
                fseek(arquivo, -sizeof(*filme), SEEK_CUR);
                fwrite(filme, sizeof(*filme), 1, arquivo);
                printf("Preço alterado com sucesso.\n");
                fclose(arquivo);
                return;
        }
    }
    printf("Filme não encontrado.\n");
    fclose(arquivo);
}


/* Função 8: Alterar todos os dados de um filme */
void alterar_dados(Filme *filme) {
    FILE *arquivo;
     int i;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }
    char nome[50];
    printf("Digite o nome do filme: ");
    gets(nome);

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
            for(i = 0; nome[i] != '\0'; i++){
                if (nome[i] != filme->nome[i]){
                    break;
                }
            }

        if (filme->nome[i] == '\0' && nome[i] == '\0') {
            printf("Digite o novo nome: ");
            gets(filme->nome);
            printf("Digite a nova quantidade: ");
            scanf("%d", &filme->quantidade);
            printf("Digite o novo preço: ");
            scanf("%f", &filme->preco);
            printf("Digite o novo mês de lançamento: ");
            scanf("%d", &filme->mes);
            printf("Digite o novo ano de lançamento: ");
            scanf("%d", &filme->ano);

            fseek(arquivo, -sizeof(*filme), SEEK_CUR);
            fwrite(filme, sizeof(*filme), 1, arquivo);
            printf("Dados alterados com sucesso.\n");

            fclose(arquivo);
            return;
        }
    }
    printf("Filme não encontrado.\n");
    fclose(arquivo);
}

/* Função 9: Excluir filme */
void excluir_filme(Filme *filme) {
    FILE *arquivo;
    int i;
    /* Abrir arquivo no modo leitura e escrita. Criar se nao existir */
    if ((arquivo = fopen("filmes.bin", "r+")) == NULL) {
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
    }

    char nome[50];

    printf("Digite o nome do filme para excluir: ");
    gets(nome);

    while (fread(filme, sizeof(*filme), 1, arquivo) == 1) {
             for(i = 0; nome[i] != '\0'; i++){
                if (nome[i] != filme->nome[i]){
                    break;
                }
            }
        if (filme->nome[i] == '\0' && nome[i] == '\0') {
            filme->nome[0] = '*';
            fseek(arquivo, -sizeof(*filme), SEEK_CUR);
            fwrite(filme, sizeof(*filme), 1, arquivo);
            break;
        }
    }

    fclose(arquivo);

    printf("Filme excluído com sucesso.\n");
}
