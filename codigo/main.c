#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int contagemPassagemEmail = 0, conatgemPassagemUserName = 0, idUsuarioLogado;

char nomeUsuario[100];
char email[100];
char senha[50];
int numeroId;

void limpar_Tela(){
    system("cls");
}

void continuar(){
    printf("\nPressione para continuar!");
    fgetchar();
    fgetchar();
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

    int nomeValido = 0, idPreencher, statusPreencher;//idPrencher é so pra ler no arquivo pq eu to com preguiça de dar uma volta pra ler so o nome, na vdd todos prencher no final é so pra preencher
    char nomeUsuarioValidacao[100], senhaPreencher[50], emailPreencher[100];

    while (!nomeValido) {
        printf("Digite o nome de usuario(sem espacos): ");
        scanf("%s", nomeUsuario);

        nomeValido = 1;

        rewind(mestre);

        while (fscanf(mestre, "%d %d %s %s %s", &statusPreencher, &idPreencher, &nomeUsuarioValidacao, & senhaPreencher, &emailPreencher) != EOF){
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
    char nomeArquivoUsuario[20];

    validacao_Nome_Usuario();

    validacao_Email(email);

    printf("Digite a senha: ");
    scanf("%s", senha);

    sprintf(nomeArquivoUsuario, "BD/usuarios/%d.txt", numeroId);
    usuario = fopen(nomeArquivoUsuario, "w");

    fprintf(mestre, "\n%d %d %s %s %s", 0, numeroId, nomeUsuario, senha, email);

    numeroId++;
    fprintf(contada, "%d", numeroId);

    fclose(contada);
    fclose(usuario);
    fclose(mestre);
}

void menu_Biblioteca(int id);

void fazer_Login(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");
    char nomeUsuarioInserido[100], senhaUsuario[100];
    int entrou = 0, statusUsuario;

    printf("Digite o seu userName: ");
    scanf("%s", nomeUsuarioInserido);

    printf("Digite a senha: ");
    scanf("%s", senhaUsuario);

    rewind(mestre);

    while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idUsuarioLogado, &nomeUsuario, & senha, &email) != EOF){
        if (strcmp(nomeUsuarioInserido, nomeUsuario) == 0 && strcmp(senhaUsuario, senha) == 0 && statusUsuario == 0){
            fclose(mestre);
            menu_Biblioteca(idUsuarioLogado);
            entrou++;
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
    printf("6. Sair\n");
}

void opcoes_Menu_Biblioteca_Adm(){
    opcoes_Menu_Biblioteca();
    printf("1113. Cadastrar livro\n");
    printf("1114. Apagar cadastro de livro\n");
}

int menu_Principal(){
    limpar_Tela();

    int opcao;

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
        menu_Principal();
        break;
    case 0:
        limpar_Tela();
        encerrar_Codigo();
        break;

    default:
        limpar_Tela();
        printf("Opcao inexistente!!");
        continuar();
        menu_Principal();
        break;
    }
    return 0;
}

typedef struct {
    char titulo[50];
    char autor[50];
    char genero[50];
    char data[50];
    int ano;
    int quantidade;
} Catalogo;

void emprestimo(int id)
{
    limpar_Tela();
    char lixo;
    char nomeArquivo[10];
    int sel = 0;
    int linha = 1;
    Catalogo livro;
    FILE *arq = fopen("BD/catalogo.txt","r");
    FILE *fp = fopen("BD/temp.txt","w");
    FILE *reg;

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
            while ((lixo = getchar()) != '\n' && lixo != EOF);
            getchar();
            sprintf(nomeArquivo, "BD/usuarios/%d.txt", id);
            reg = fopen(nomeArquivo,"a");
            fprintf(reg,"%s| %s| %s| %d | Data de devolução: %s", livro.titulo, livro.autor, livro.genero, livro.ano, tempofuturo);
            fclose(reg);
        }
        if(sel == contador && livro.quantidade == 0){
            printf("\nLivro indisponível");
        }

       //Reescreve o catálogo com a alteração de quantidade em um arquivo temporario
        fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
        contador++;
    }


    fclose(arq);
    fclose(fp);

    //Transforma o arquivo temporario com a alteração no novo catálogo e apaga o antigo arquivo
    remove("BD/catalogo.txt");
    rename("BD/temp.txt", "BD/catalogo.txt");

    if(sel > linha || sel <= 0){
        printf("\nOpção invalida\n\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        getchar();
        emprestimo(id);
    }

    menu_Biblioteca(id);
}

void consultarCatalogo(int id)
{
    limpar_Tela();
    char lixo;
    int linha = 1;
    Catalogo livro;
    FILE *arq = fopen("BD/catalogo.txt","r");

    printf("Livros disponíveis:\n");
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        printf("%s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d | (%d)", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade, linha);
        linha++;
    }

    fclose(arq);

    printf("\n\nPressione qualquer tecla para continuar\n");
    while ((lixo = getchar()) != '\n' && lixo != EOF);
    getchar();
    limpar_Tela();
    menu_Biblioteca(id);
}

void devolução(int id)
{
    limpar_Tela();
    char save[50];
    char lixo;
    char nomeArquivo[30];
    int sel = 0;
    int linha = 1;
    int tamanho;
    Catalogo livro;
    sprintf(nomeArquivo, "BD/usuarios/%d.txt",id);
    FILE *reg = fopen(nomeArquivo,"r");
    fseek(reg, 0, SEEK_END);
    tamanho = ftell(reg);

    if(tamanho == 0){
        printf("Você não possui empréstimos\nAperte qualquer botão para continuar\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        fgetchar();
        fclose(reg);
        }
    else{
        FILE *arq = fopen("BD/catalogo.txt","r");
        FILE *fp = fopen("BD/temp.txt","w");
        FILE *temp = fopen("BD/usuarios/temp2.txt","w");

        rewind(reg);
        printf("Livro(s) Emprestado(s):\n");
        while(fscanf(reg,"%[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, livro.data) != EOF)
        {
        printf("%s| %s| %s| Ano de lançamento: %d | %s | (%d)", livro.titulo, livro.autor, livro.genero, livro.ano, livro.data, linha);
        linha++;
        }

    rewind(reg);
    int contador = 1;
    linha--;
    printf("\n\nDigite a opção do livro que você quer devolver\n");
    scanf("%d", &sel);

    while(fscanf(reg,"%[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, livro.data) != EOF)
    {
        if(sel == contador){
            sprintf(save,"%s",livro.titulo);
            printf("\nDevolução realizada com sucesso");
            }
        if(sel != contador){
            fprintf(temp,"%s| %s| %s| %d | %s", livro.titulo, livro.autor, livro.genero, livro.ano, livro.data);}

        contador++;
    }

    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        if(strcmp(save, livro.titulo) == 0){
            livro.quantidade++;}

        fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
    }

    fclose(arq);
    fclose(fp);
    fclose(reg);
    fclose(temp);

    remove("BD/catalogo.txt");
    rename("BD/temp.txt", "BD/catalogo.txt");
    remove(nomeArquivo);
    rename("BD/usuarios/temp2.txt", nomeArquivo);

    if(sel > linha || sel <= 0){
        printf("\nOpção invalida\n\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        getchar();
        devolução(id);}
    }

    menu_Biblioteca(id);
}

void apagarregistro(int id) {
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
    } else {
        char lixo;
        int sel = 0;
        int linha = 1;
        Catalogo livro;
        FILE *arq = fopen("catalogo.txt","r");
        FILE *fp = fopen("temp.txt","w");

        printf("Livros no catálogo:\n\n");
        while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
        {
            printf("%s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d | (%d)", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade, linha);
            linha++;
        }

        rewind(arq);
        int contador = 1;
        linha--;
        printf("\n\nDigite a opção do livro que você quer apagar:\n");
        scanf("%d", &sel);

        while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
        {
            if(sel != contador){
                fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
            }
            contador++;
        }

        fclose(arq);
        fclose(fp);

        //Transforma o arquivo temporario com a alteração no novo catálogo e apaga o antigo arquivo
        remove("catalogo.txt");
        rename("temp.txt", "catalogo.txt");
    }
}

void registrarLivro(int id) {
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
    } else {
        FILE *fp = fopen("BD/catalogo.txt", "a"); // Abrir o arquivo para leitura

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
}

void consultarEmprestimo(int id)
{
    limpar_Tela();
    char lixo;
    char nomeArquivo[30];
    int linha = 1;
    long tamanho;
    Catalogo livro;
    sprintf(nomeArquivo,"BD/usuarios/%d.txt",id);
    FILE *arq = fopen(nomeArquivo,"r");

    fseek(arq, 0, SEEK_END);
    tamanho = ftell(arq);

    if(tamanho == 0){
        printf("Você não possui empréstimos\nAperte qualquer botão para continuar\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        fgetchar();
        fclose(arq);
        }
    else{
    rewind(arq);
    printf("Livros emprestados:\n");
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.data) != EOF)
    {
        printf("%s| %s| %s| Ano de lançamento: %d | %s| (%d)", livro.titulo, livro.autor, livro.genero, livro.ano, livro.data, linha);
        linha++;
    }

    fclose(arq);

    printf("\n\nPressione qualquer tecla para continuar\n");
    while ((lixo = getchar()) != '\n' && lixo != EOF);
    getchar();
    limpar_Tela();
    }
    menu_Biblioteca(id);
}

void menu_Conta();

void atualizar_Dados_Cadastrais(){
    FILE *mestre = fopen("BD/arquivoMestre.txt", "r"), *mestreTemp;
    mestreTemp = fopen("BD/mestreTemp.txt", "w");

    char nomeTemp[100], senhaTemp[50], emailTemp[100], teste[21] ="BD/arquivoMestre.txt";
    int autorizacao, idTemp, statusUsuario, opcao;

    printf("O que voce deseja alterar? <nome = 0 / senha = 1 / email = 2>: ");
    opcao = Ler_Opcoes();
    switch (opcao) {
    case 0:
        validacao_Nome_Usuario();
        break;
    case 1:
        printf("Insira a nova senha: ");
        scanf("%s", senha);
        break;
    case 2:
        printf("Insira o novo email: ");
        scanf("%s", email);
        break;
    default:
        printf("Opcao inexistente!!");
        continuar();
        atualizar_Dados_Cadastrais();
        break;
    }

    printf("\nTem certeza que voce deseja alterar o usuario?<sim = 0/ nao = 1\n");
    scanf("%d", &autorizacao);

    if (autorizacao == 0){
            while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
                if(idUsuarioLogado != idTemp){
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
                } else {
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeUsuario, senha, email);
                }
            }
            
            fclose(mestre);
            fclose(mestreTemp);
            
            if (remove("BD/arquivoMestre.txt") == 0 && rename("BD/mestreTemp.txt", "BD/arquivoMestre.txt") == 0) {
                printf("O usuario foi atualizado com sucesso!");
                continuar();
                menu_Conta();
            } else {
                printf("Erro ao substituir o arquivo mestre!\n");
                continuar();
                menu_Conta();
            }
    } else{
        menu_Conta();
    }
}

void deslogar(){
    idUsuarioLogado = 0;
    strcpy(nomeUsuario, "\0");
    strcpy(senha, "\0");
    strcpy(email, "\0");
    menu_Principal();
}

void usuario_Excluir_Usuario(){
    FILE *mestre = fopen("BD/arquivoMestre.txt", "r"), *mestreTemp;
    mestreTemp = fopen("BD/mestreTemp.txt", "w");

    char nomeArquivoUsuarioExcluir[20], nomeTemp[100], senhaTemp[50], emailTemp[100], teste[21] ="BD/arquivoMestre.txt";
    int autorizacao, idTemp, statusUsuario;

    sprintf(nomeArquivoUsuarioExcluir, "BD/usuarios/%d.txt", idUsuarioLogado);

    printf("\nTem certeza que voce deseja excluir o usuario?<sim = 0/ nao = 1>: ");
    scanf("%d", &autorizacao);

    if (autorizacao == 0){
        while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
            if(idUsuarioLogado != idTemp){
                fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
            } else {
                fprintf(mestreTemp, "%d %d %s %s %s\n", 1, idTemp, nomeTemp, senhaTemp, emailTemp);
            }
        }

        fclose(mestre);
        fclose(mestreTemp);

        if (remove("BD/arquivoMestre.txt") == 0 && rename("BD/mestreTemp.txt", "BD/arquivoMestre.txt") == 0) {
            printf("O usuario foi excluido com sucesso!");
            continuar();
            menu_Principal();
        } else {
            printf("Erro ao substituir o arquivo mestre!\n");
            continuar();
            menu_Conta();
        }
    } else {
        fclose(mestre);
        fclose(mestreTemp);
        remove("BD/mestreTemp.txt");
        menu_Conta();
    }
}

void adm_Excluir_Usuarios(int id){
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Conta();
    } else {
        FILE *mestre = fopen("BD/arquivoMestre.txt", "r"), *mestreTemp;
        mestreTemp = fopen("BD/mestreTemp.txt", "w");

        char nomeArquivoUsuarioExcluir[20], nomeTemp[100], senhaTemp[50], emailTemp[100];
        int autorizacao, idTemp, statusUsuario, idExcluir;
        
        printf("Digite o id do usuario em que voce deseja excluir: ");
        scanf("%d", &idExcluir);

        sprintf(nomeArquivoUsuarioExcluir, "BD/usuarios/%d.txt", idExcluir);

        printf("\nTem certeza que voce deseja excluir esse usuario?<sim = 0/ nao = 1>: ");
        scanf("%d", &autorizacao);

        if (autorizacao == 0){
            while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
                if(idExcluir != idTemp){
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
                } else {
                    fprintf(mestreTemp, "%d %d %s %s %s\n", 1, idTemp, nomeTemp, senhaTemp, emailTemp);
                }
            }

            fclose(mestre);
            fclose(mestreTemp);

            if (remove("BD/arquivoMestre.txt") == 0 && rename("BD/mestreTemp.txt", "BD/arquivoMestre.txt") == 0) {
                printf("O usuario foi excluido com sucesso!");
                continuar();
                menu_Conta();
            } else {
                printf("Erro ao substituir o arquivo mestre!\n");
                continuar();
                menu_Conta();
            }
        } else{
            fclose(mestre);
            fclose(mestreTemp);
            menu_Conta();
        }
    }
}

void consultar_Cadastros(int id){
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Conta();
    } else {
        FILE *mestre = fopen("BD/arquivoMestre.txt", "r");

        char nomeTemp[100], senhaTemp[50], emailTemp[100];
        int idTemp, statusUsuarioTemp;

        if (mestre == NULL)
            printf("Erro ao abrir o arquivo de cadastros ");

        limpar_Tela();

        if(id < 0){
            while(fscanf(mestre, "%d %d %s %s %s ", &statusUsuarioTemp, &idTemp, nomeTemp, senhaTemp, emailTemp) != EOF){
                printf("Status: %d | ID: %d | Nome: %s | Email: %s\n", statusUsuarioTemp, idTemp, nomeTemp, emailTemp);
            }
            fclose(mestre);
            continuar();
            menu_Conta();
        }
        else {
            printf("Opcao inexistente!!");
            continuar();
            menu_Conta();
        }
    }
}

int validacao_Id(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");

    int idValido = 0, idValidacao, statusPreencher, id;//idPrencher é so pra ler no arquivo pq eu to com preguiça de dar uma volta pra ler so o nome, na vdd todos prencher no final é so pra preencher
    char nomeUsuarioValidacao[100], senhaPreencher[50], emailPreencher[100];

    while (!idValido) {
        printf("Insira o id do usuario (se for usuario adm inserir id < 0 e > -100)");
        scanf("%d", &id);

        idValido = 1;

        rewind(mestre);

        while (fscanf(mestre, "%d %d %s %s %s", &statusPreencher, &idValidacao, &nomeUsuarioValidacao, & senhaPreencher, &emailPreencher) != EOF){
            if (id == idValidacao){
                limpar_Tela();
                printf("Esse id ja existe! Insira outro\n");
                idValido = 0;
                break;
            }
        }
    }
    fclose(mestre);
    return id;
}

void adm_Criar_Comta(int id){
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Conta();
    } else {
        FILE* contada = fopen("BD/contador.txt", "w");
        FILE* mestre = fopen("BD/arquivoMestre.txt", "a+");
        FILE *usuario;
        char nomeArquivoUsuario[20];
        int idCriar;

        idCriar = validacao_Id();

        validacao_Nome_Usuario();

        validacao_Email(email);

        printf("Digite a senha: ");
        scanf("%s", senha);

        sprintf(nomeArquivoUsuario, "BD/usuarios/%d.txt", idCriar);
        usuario = fopen(nomeArquivoUsuario, "w");

        fprintf(mestre, "%d %d %s %s %s\n", 0, numeroId, nomeUsuario, senha, email);

        if (numeroId > 0){
            numeroId++;
        }
        
        fprintf(contada, "%d", numeroId);

        fclose(contada);
        fclose(usuario);
        fclose(mestre);
        menu_Conta();
    }
}

void opcoes_Menu_Conta(){
    printf("===Menu Contas===\n");
    printf("1. Atualizar dados cadastrais\n");
    printf("2. Sair da conta\n");
    printf("3. Excluir meu usuario\n");
    printf("4. Voltar\n");
}

void opcoes_Menu_Conta_Adm(){
    opcoes_Menu_Conta();
    printf("6822. Excluir usuarios\n");
    printf("6823. Consultar cadastros\n");
    printf("6824. Criar conta\n");
}

void menu_Conta(){
    limpar_Tela();
    int opcao;
    
    if (idUsuarioLogado < 0) {
        opcoes_Menu_Conta_Adm();
        opcao = Ler_Opcoes();
    } else {
        opcoes_Menu_Conta();
        opcao = Ler_Opcoes();
    }
    
    switch (opcao){
    case 1:
        atualizar_Dados_Cadastrais();
        break;
    case 2:
        deslogar();
        break;
    case 3:
        usuario_Excluir_Usuario();
        break;
    case 4:
        menu_Biblioteca(idUsuarioLogado);
        break;
    case 6822:
        adm_Excluir_Usuarios(idUsuarioLogado);
        break;
    case 6823:
        consultar_Cadastros(idUsuarioLogado);
        break;
    case 6824:
        adm_Criar_Comta(idUsuarioLogado);
        break;
    
    default:
        printf("Opcao inexistente!!");
        continuar();
        menu_Conta();
        break;
    }
}

void menu_Biblioteca(int id){
    limpar_Tela();

    int opcao;
    if (id < 0) {
        opcoes_Menu_Biblioteca_Adm();
        opcao = Ler_Opcoes();
    } else {
        opcoes_Menu_Biblioteca();
        opcao = Ler_Opcoes();
    }

    switch (opcao) {
    case 1:
        consultarCatalogo(id);
        break;
    case 2:
        emprestimo(id);
        break;
    case 3:
        devolução(id);
        break;
    case 4:
        consultarEmprestimo(id);
        break;
    case 5:
        menu_Conta(id);
        break;
    case 6:
        limpar_Tela();
        encerrar_Codigo();
        break;
    case 1113:
        registrarLivro(id);
        break;
    case 1114:
        apagarregistro(id);
        break;

    default:
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
        break;
    }
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

        menu_Principal();
    }
    return 0;
}