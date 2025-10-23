#include <stdio.h>

int senhaAdministrador = 123;
typedef struct{
        char nomeCadastrado[30];
        char emailCadastrado[60];
    } cadastro;

void consultar_cadastros(){
    
    int senhaDigitada;
    cadastro usuario;
    FILE *arquivo;
    arquivo = fopen("cadastros.txt", "r");
    if (arquivo == NULL)
        printf("Erro ao abrir o arquivo de cadastros ");
        
    printf("Digite a senha de Administrador para ter acesso aos cadastros: ");
    scanf("%d", &senhaDigitada);
    
    if(senhaDigitada == senhaAdministrador){
        while(fscanf(arquivo, "%s %s", usuario.nomeCadastrado, usuario.emailCadastrado) != EOF){
            printf("Nome: %s  Email: %s\n", usuario.nomeCadastrado, usuario.emailCadastrado);
        }
        fclose(arquivo);
    }
    else
        printf("Senha Incorreta");
}

int main()
{
    consultar_cadastros();
    return 0;
}
