#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char titulo[50];
    char autor[50];
    char genero[50];
    int ano;
    int quantidade;
} Catalogo;

void emprestimo()
{
    char lixo;
    int sel = 0;
    int linha = 1;
    Catalogo livro;
    FILE *arq;
    FILE *fp = fopen("temp.txt","w");
    arq = fopen("catalogo.txt","r");
    
    //Mostra o catálogo para o usuario
    printf("Livros disponíveis:\n\n");
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        printf("%s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d | (%d)", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade, linha);
        linha++;
    }
    rewind(arq);
    int contador = 1;
    linha--;
    
    printf("\n\nDigite a opção do livro que você quer emprestar\n");
    scanf("%d", &sel);
    
    //Menu pra escolha de livro do usuario e Salva a nova quantidade de livros disponível
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        if(sel == contador && livro.quantidade > 0){
            livro.quantidade--;
            //Calcula o tempo daqui 1 semana e retorna para o usuario como data de devolução
            time_t tempo_atual = time(NULL);
            time_t tempo_futuro = tempo_atual + (7 * 24 * 60 * 60);
            struct tm *info_tempo_futuro = localtime(&tempo_futuro);
            char tempofuturo[50];
            strftime(tempofuturo, sizeof(tempofuturo), "%d/%m/%Y", info_tempo_futuro);
    
            printf("\nEmpréstimo realizado com sucesso\nData para devolução %s",tempofuturo);
        }
        if(sel == contador && livro.quantidade == 0){
            printf("\nLivro indisponível");
        }
    
        fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
        contador++;
    }
    
    if(sel > linha){
        printf("\nOpção invalida");
    }
    
    fclose(arq);
    fclose(fp);
    
    remove("catalogo.txt");
    rename("temp.txt", "catalogo.txt");
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

    printf("Informe os dados do livro para o catálogo:\n");
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
    
    fprintf(fp, "\n%s | %s | %s | %d | %d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
    
    fclose(fp);
}

int main(){
    //Eu quero eu posso https://www.youtube.com/shorts/zsjSWVcTD2Y 

    return 0;
}
