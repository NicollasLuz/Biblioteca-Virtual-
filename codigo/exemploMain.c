#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int contagemUsuario = 0; 
/*
    serve pro RF006 para que o adm vizualize a quantidade 
    e os usuários castrados e pra gerenciar qual posição do 
    vetor a conta vai ficar armazenada
    struct Conta contas[50];
*/
int contagemPassagemEmail = 0, conatgemPassagemUserName = 0; 
char usuarioLogado[100];

typedef struct {
    char nomeUsuario[100];
    char email[100];
    char senha[50];
    int numeroId;
} Conta;

Conta contas[50];

void limpar_Tela(){
    system("cls");
}

int encerrar_Codigo(){
    for (int i = 0; i < 3; i++){
        printf("Finalizando programa\n");
        limpar_Tela();
        printf("Finalizando programa.\n");
        Sleep(500);
        limpar_Tela();
        printf("Finalizando programa..\n");
        Sleep(500);
        limpar_Tela();
        printf("Finalizando programa...\n");
        Sleep(500);
        limpar_Tela();
    }
    return 1;
}

void validacao_Email(char email[100]){
    contagemPassagemEmail++;
    printf("Digite o email: ");
    scanf("%s", email);

    for (int i = 0; i < strlen(email); i++){
        if (email[i] == '@'){
            contagemPassagemEmail = -26;
        } 
    }

    if (contagemPassagemEmail != -26){
        limpar_Tela();
        printf("Email invalido!\n");
        validacao_Email(email);
    }
}

void validacao_Nome_Usuario(char nomeUsuario[100]){
    int nomeValido = 0;
    
    while (!nomeValido) {
        printf("Digite o nome de usuario: ");
        scanf("%s", nomeUsuario);
        
        nomeValido = 1; 
        
        for (int i = 0; i < contagemUsuario + 1; i++){
            if (strcmp(nomeUsuario, contas[i].nomeUsuario) == 0){
                limpar_Tela();
                printf("Esse nome de usuario ja existe! Insira outro\n");
                nomeValido = 0; 
                break;
            }
        }
    }
}

void criarConta(Conta *conta) {
    validacao_Nome_Usuario(conta ->nomeUsuario);
    
    validacao_Email(conta->email);
    
    printf("Digite a senha: ");
    scanf("%s", conta->senha);
    contagemUsuario++;
    conta->numeroId = contagemUsuario;
}

int menu_Principal();
void menu_Biblioteca();

void fazer_Login(){
    char nomeusuario[100], senhaUsuario[100];
    int entrou = 0;

    printf("Digite o seu userName: ");
    scanf("%s", nomeusuario);

    printf("Digite a senha: ");
    scanf("%s", senhaUsuario);

    for (int i = 0; i < contagemUsuario + 1; i++){
        if (strcmp(nomeusuario, contas[i].nomeUsuario) == 0){
            if (strcmp(senhaUsuario, contas[i].senha) == 0){
                strcpy(usuarioLogado, nomeusuario);
                //puxar tela Biblioteca
                printf("funcionou essa merda vai pro menu agr");
                menu_Biblioteca(contas[i].numeroId);
                entrou++;
            } 
        }
    }
    if (entrou == 0){
        limpar_Tela();
        printf("Usuario ou senhas incoretos!\n");
        fazer_Login(); 
    }
}

int Ler_Opcoes(){
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

void opcoes_Menu_Biblioteca(){
    printf("====Biblioteca Virtual====\n");
    printf("1. Visualizar catalogo\n");
    printf("2. Realizar emprestimo\n");
    printf("3. Realizar devolucao\n");
    printf("4. Consultar emprestimos\n");
    printf("5. Conta\n");
}

void opcoes_Menu_Biblioteca_Adm(){
    opcoes_Menu_Biblioteca();
    printf("1113. Cadastrar livro\n");

}

void menu_Biblioteca(int id){
    limpar_Tela();

    int opcao;
    if (id == -99) {
        opcoes_Menu_Biblioteca_Adm();
        opcao = Ler_Opcoes();
    } else {
        opcoes_Menu_Biblioteca();
        opcao = Ler_Opcoes();
    }

    switch (opcao) {
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    case 1113:
        /* code */
        break;
    
    default:
        break;
    }
}

int menu_Principal(){
    int opcao;
    limpar_Tela();
    printf("====Biblioteca Virtual====\n");
    printf("1. Fazer login\n");
    printf("2. Fazer cadastro\n");
    printf("0. Sair\n");
    opcao = Ler_Opcoes();
    switch (opcao) {
    case 1:
        fazer_Login();
        break;
    case 2:
        limpar_Tela();
        criarConta(&contas[contagemUsuario + 1]);
        break;
    case 0:
        limpar_Tela();
        encerrar_Codigo();
        break;
    
    default:
        printf("Opcao invalida");
        menu_Principal();
        break;
    }
    return 0;
} 

int main(){
    strcpy(contas[0].nomeUsuario, "nike");
    strcpy(contas[0].senha, "123");
    contas[0].numeroId = -99;

    menu_Principal();
    return 0;
}