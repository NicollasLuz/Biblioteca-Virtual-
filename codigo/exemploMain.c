#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/*
    numeroId:
    serve pro RF006 para que o adm vizualize a quantidade 
    e os usuários castrados e pra gerenciar qual o proximo 
    número de id que vai ser cadastrado;
*/
int contagemPassagemEmail = 0, conatgemPassagemUserName = 0, idUsuarioLogado; 

char nomeUsuario[100];
char email[100];
char senha[50];
int numeroId;

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

void validacao_Nome_Usuario(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");

    int nomeValido = 0, idPreencher;//idPrencher é so pra ler no arquivo pq eu to com preguiça de dar uma volta pra ler so o nome, na vdd todos prencher no final é so pra preencher
    char nomeUsuarioValidacao[100], senhaPreencher[50], emailPreencher[100];
    
    while (!nomeValido) {
        printf("Digite o nome de usuario: ");
        scanf("%s", nomeUsuario);
        
        nomeValido = 1; 

        rewind(mestre);
        
        while (fscanf(mestre, "%d %s %s %s", &idPreencher, &nomeUsuarioValidacao, & senhaPreencher, &emailPreencher) != EOF){
            if (strcmp(nomeUsuario, nomeUsuarioValidacao) == 0){
                limpar_Tela();
                printf("Esse nome de usuario ja existe! Insira outro\n");
                nomeValido = 0; 
                break;
            }
        }
    }
    fclose(mestre);
}

void criarConta() {
    FILE* contada = fopen("BD/contador.txt", "w");
    FILE* mestre = fopen("BD/arquivoMestre.txt", "a+");
    FILE *usuario;
    char nomeArquivoUsuario[10];

    validacao_Nome_Usuario(nomeUsuario);
    
    validacao_Email(email);
    
    printf("Digite a senha: ");
    scanf("%s", senha);

    sprintf(nomeArquivoUsuario, "BD/usuarios/%d.txt", numeroId);
    usuario = fopen(nomeArquivoUsuario, "w");

    fprintf(mestre, "\n%d %s %s %s", numeroId, nomeUsuario, senha, email);
    fprintf(usuario, "ID: %d \nNome de usuario: %s\nEmail: %s\nSenha: %s", numeroId, nomeUsuario, email, senha);
    
    numeroId++;
    fprintf(contada, "%d", numeroId);
    
    fclose(contada);
    fclose(usuario);
    fclose(mestre);
}

void menu_Biblioteca(int id);

void fazer_Login(){
    char nomeusuario[100], senhaUsuario[100];
    int entrou = 0;

    printf("Digite o seu userName: ");
    scanf("%s", nomeusuario);

    printf("Digite a senha: ");
    scanf("%s", senhaUsuario);

    for (int i = 0; i < numeroId + 1; i++){
        if (strcmp(nomeusuario, nomeUsuario) == 0){//mexer nessa prr aqui pra analisar no arquivo mestre quais que são os usuarios batem 
            if (strcmp(senhaUsuario, senha) == 0){//mexer nessa prr aqui pra analisar no arquivo mestre se o email com a senha bate   
                //puxar tela Biblioteca
                printf("funcionou essa merda vai pro menu agr");
                menu_Biblioteca(idUsuarioLogado);
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
        limpar_Tela();
        fazer_Login();
        break;
    case 2:
        limpar_Tela();
        criarConta();
        limpar_Tela();
        printf("O usuario foi criado com sucesso!");
        menu_Principal();
        break;
    case 0:
        limpar_Tela();
        encerrar_Codigo();
        break;
    
    default:
        limpar_Tela();
        printf("Opcao invalida");
        menu_Principal();
        break;
    }
    return 0;
} 

int main(){
    FILE* contagem = fopen("BD/contador.txt", "r");
    int ultimoId;

    if (contagem == NULL) {
        printf("Erro ao abrir arquivo!");
        printf("\nPressione enter para encerrar o programa!");
        getchar(); 
        encerrar_Codigo();
    } else {
        fscanf(contagem, "%d", &numeroId);
        fclose(contagem);
        
        strcpy(nomeUsuario, "nike");
        strcpy(senha, "123");

        
        menu_Principal();
    }
    return 0;
}