#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[100];
    char autor[50];
    char genero[50];
    int ano;
    int quantidade;
} Catalogo;

void emprestimo()
{
    int linha = 1;
    Catalogo livro;
    char inf[100];
    FILE *arq;
    arq = fopen("catalogo.txt","r");
    
    while(fscanf(arq,"%[^0-9] %d %d", inf, &livro.ano, &livro.quantidade) != EOF)
    {
        printf("%s| Ano de lançamento: %d | Quantidade Disponível: %d | (%d)", inf, livro.ano, livro.quantidade, linha);
        linha++;
    }
    
    fclose(arq);
}

void registrarlivro()
{
    FILE *fp = fopen("catalogo.txt", "a"); // Abrir o arquivo para leitura

    typedef struct
    {
        char titulo[100], autor[100], genero[100];
        int ano, quantidade;
    } catalogo;
    catalogo livro;

    printf("Informe as informações para o catálogo do livro:\n");
    printf("Título: ");
    scanf(" %[^\n]", livro.titulo);
    printf("Autor: ");
    scanf(" %[^\n]", livro.autor);
    printf("Gênero: ");
    scanf(" %[^\n]", livro.genero);
    printf("Ano de lançamento: ");
    scanf("%d", &livro.ano);
    printf("Quantidade disponível: ");
    scanf("%d", &livro.quantidade);
    
    fprintf(fp, "\n%s %s %s %d %d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
    
    fclose(fp);
}

int main(){
    //Eu quero eu posso https://www.youtube.com/shorts/zsjSWVcTD2Y 

    return 0;
}
