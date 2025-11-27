// Bibliotecas necessárias para o sistema
#include <stdio.h>      // Entrada e saída padrão
#include <string.h>     // Manipulação de strings
#include <time.h>       // Funções de data e hora
#include <stdlib.h>     // Funções gerais (system, etc)
#include <windows.h>    // Funções específicas do Windows (Sleep)
#include "biblioteca.h" // Header com definições do projeto

// Função para limpar a tela do console
void limpar_Tela(){
    #ifdef _linux_
        system("clear");  // Comando para Linux
    #else 
        system("cls");    // Comando para Windows
    #endif
}

// Função para pausar execução até o usuário pressionar Enter
void continuar(){
    printf("\nPressione enter para continuar!");
    fgetchar();  // Limpa buffer
    fgetchar();  // Aguarda Enter
}

// Função para encerrar o programa com animação
int encerrar_Codigo(){
    for (int i = 0; i < 3; i++){
        printf("Finalizando programa\n");
        limpar_Tela();
        printf("Finalizando programa.\n");
        Sleep(500);  // Pausa de 500ms
        limpar_Tela();
        printf("Finalizando programa..\n");
        Sleep(500);
        limpar_Tela();
        printf("Finalizando programa...\n");
        Sleep(500);
        limpar_Tela();

        printf("Programa Finalizado\n");
    }
    return 1;
}

// Função para validar formato do email (verifica se contém @)
void validacao_Email(){
    contagemPassagemEmail++;
    printf("Digite o email: ");
    scanf("%s", email);

    // Verifica se o email contém o símbolo @
    for (int i = 0; i < strlen(email); i++){
        if (email[i] == '@'){
            contagemPassagemEmail = -26;  // Marca como válido
        }
    }

    // Se não encontrou @, email é inválido
    if (contagemPassagemEmail != -26){
        limpar_Tela();
        printf("Email invalido!\n");
        validacao_Email();  // Chama recursivamente até email válido
    }
}

// Função para validar nome de usuário (verifica se já existe)
void validacao_Nome_Usuario(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");

    int nomeValido = 0, idPreencher, statusPreencher;  // Variáveis auxiliares para leitura
    char nomeUsuarioValidacao[100], senhaPreencher[50], emailPreencher[100];

    while (!nomeValido) {
        printf("Digite o nome de usuario(sem espacos e números): ");
        scanf("%s", nomeUsuario);

        nomeValido = 1;  // Assume que é válido inicialmente

        rewind(mestre);  // Volta ao início do arquivo

        // Verifica se o nome já existe no arquivo mestre
        while (fscanf(mestre, "%d %d %s %s %s", &statusPreencher, &idPreencher, &nomeUsuarioValidacao, & senhaPreencher, &emailPreencher) != EOF){
            if (strcmp(nomeUsuario, nomeUsuarioValidacao) == 0){
                limpar_Tela();
                printf("Esse nome de usuario ja existe! Insira outro\n");
                nomeValido = 0;  // Marca como inválido
                validacao_Nome_Usuario();  // Chama recursivamente
                break;
            }
        }
    }
    fclose(mestre);
}

// Função para criar nova conta de usuário
void criarConta() {
    FILE* contada = fopen("BD/contador.txt", "w");
    FILE* mestre = fopen("BD/arquivoMestre.txt", "a+");
    FILE *usuario;
    char nomeArquivoUsuario[20];

    validacao_Nome_Usuario();  // Valida nome único

    validacao_Email();  // Valida formato do email

    printf("Digite a senha: ");
    scanf("%s", senha);

    // Cria arquivo individual do usuário
    sprintf(nomeArquivoUsuario, "BD/usuarios/%d.txt", numeroId);
    usuario = fopen(nomeArquivoUsuario, "w");

    // Salva dados no arquivo mestre (status=0 significa ativo)
    fprintf(mestre, "\n%d %d %s %s %s", 0, numeroId, nomeUsuario, senha, email);

    numeroId++;  // Incrementa contador de IDs
    fprintf(contada, "%d", numeroId);  // Atualiza contador

    fclose(contada);
    fclose(usuario);
    fclose(mestre);
}

// Declaração antecipada da função menu_Biblioteca
void menu_Biblioteca(int id);

// Função para autenticar usuário no sistema
void fazer_Login(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");
    char nomeUsuarioInserido[100], senhaUsuario[100];
    int entrou = 0, statusUsuario;

    printf("Digite o seu userName: ");
    scanf("%s", nomeUsuarioInserido);

    printf("Digite a senha: ");
    scanf("%s", senhaUsuario);

    rewind(mestre);

    // Procura usuário no arquivo mestre
    while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idUsuarioLogado, &nomeUsuario, & senha, &email) != EOF){
        // Verifica credenciais e se usuário está ativo (status=0)
        if (strcmp(nomeUsuarioInserido, nomeUsuario) == 0 && strcmp(senhaUsuario, senha) == 0 && statusUsuario == 0){
            fclose(mestre);
            menu_Biblioteca(idUsuarioLogado);  // Redireciona para menu principal
            entrou++;
        }
    }
    // Se não encontrou usuário válido
    if (entrou == 0){
        limpar_Tela();
        printf("Usuario ou senhas incoretos!\n");
        fclose(mestre);
        fazer_Login();  // Tenta novamente
    }
}

// Função auxiliar para ler opções do menu
int Ler_Opcoes(){
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

// Exibe opções do menu principal da biblioteca para usuários comuns
void opcoes_Menu_Biblioteca(){
    printf("====Biblioteca Virtual====\n");
    printf("1. Visualizar catalogo\n");
    printf("2. Realizar emprestimo\n");
    printf("3. Realizar devolucao\n");
    printf("4. Consultar emprestimos\n");
    printf("5. Conta\n");
    printf("6. Sair\n");
}

// Exibe opções do menu da biblioteca para administradores (inclui opções extras)
void opcoes_Menu_Biblioteca_Adm(){
    opcoes_Menu_Biblioteca();  // Mostra opções básicas
    printf("1113. Cadastrar livro\n");      // Opções exclusivas do admin
    printf("1114. Apagar cadastro de livro\n");
}

// Menu principal do sistema (login/cadastro)
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
        menu_Principal();  // Retorna ao menu após cadastro
        break;
    case 0:
        limpar_Tela();
        encerrar_Codigo();
        break;

    default:
        limpar_Tela();
        printf("Opcao inexistente!!");
        continuar();
        menu_Principal();  // Retorna ao menu se opção inválida
        break;
    }
    return 0;
}

// Função para realizar empréstimo de livros
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

    // Mostra o catálogo para o usuário
    printf("Livros disponíveis:\n\n");
    while(fscanf(arq," %[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        printf("%d. %s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d\n", linha, livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
        linha++;
    }
    rewind(arq);
    int contador = 1;
    linha--;

    printf("\nDigite a opção do livro que você quer emprestar\n");
    scanf("%d", &sel);

    // Processa escolha do usuário e atualiza quantidade disponível
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        if(sel == contador && livro.quantidade == 0){
            printf("\nLivro indisponível");
            continuar();
        }

        if(sel == contador && livro.quantidade > 0){
            livro.quantidade--;  // Diminui quantidade disponível
            // Calcula data de devolução (7 dias a partir de hoje)
            time_t tempo_atual = time(NULL);
            time_t tempo_futuro = tempo_atual + (7 * 24 * 60 * 60);  // +7 dias
            struct tm *info_tempo_futuro = localtime(&tempo_futuro);
            char tempofuturo[50];
            strftime(tempofuturo, sizeof(tempofuturo), "%d/%m/%Y", info_tempo_futuro);

            printf("\nEmpréstimo realizado com sucesso\nData para devolução %s",tempofuturo);
            while ((lixo = getchar()) != '\n' && lixo != EOF);  // Limpa buffer
                getchar();
            // Registra empréstimo no arquivo do usuário
            sprintf(nomeArquivo, "BD/usuarios/%d.txt", id);
            reg = fopen(nomeArquivo,"a");
            fprintf(reg,"%s| %s| %s| %d | Data de devolução: %s", livro.titulo, livro.autor, livro.genero, livro.ano, tempofuturo);
            fclose(reg);
        }

       // Reescreve o catálogo com a nova quantidade em arquivo temporário
        fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
        contador++;
    }


    fclose(arq);
    fclose(fp);

    // Substitui arquivo original pelo temporário atualizado
    remove("BD/catalogo.txt");
    rename("BD/temp.txt", "BD/catalogo.txt");

    // Valida opção escolhida
    if(sel > linha || sel <= 0){
        printf("\nOpção invalida\n\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        getchar();
        emprestimo(id);  // Tenta novamente
    }

    continuar();
    menu_Biblioteca(id);
}

// Função para consultar e exibir todo o catálogo de livros
void consultarCatalogo(int id)
{
    limpar_Tela();
    char lixo;
    int linha = 1;
    Catalogo livro;
    FILE *arq = fopen("BD/catalogo.txt","r");

    printf("Livros disponíveis:\n\n");
    // Lê e exibe todos os livros do catálogo
    while(fscanf(arq," %[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        printf("%d. %s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d\n", linha, livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
        linha++;
    }

    fclose(arq);

    printf("\nPressione qualquer tecla para continuar\n");
    while ((lixo = getchar()) != '\n' && lixo != EOF);  // Limpa buffer
    getchar();
    limpar_Tela();
    menu_Biblioteca(id);
}

// Função para realizar devolução de livros emprestados
void devolução(int id)
{
    limpar_Tela();
    char save[50];  // Armazena título do livro devolvido
    char lixo;
    char nomeArquivo[30];
    int sel = 0;
    int linha = 1;
    int tamanho;
    Catalogo livro;
    sprintf(nomeArquivo, "BD/usuarios/%d.txt",id);
    FILE *reg = fopen(nomeArquivo,"r");
    fseek(reg, 0, SEEK_END);
    tamanho = ftell(reg);  // Verifica se arquivo está vazio

    // Se usuário não tem empréstimos
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
        printf("Livro(s) Emprestado(s):\n\n");
        // Exibe livros emprestados pelo usuário
        while(fscanf(reg," %[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, livro.data) != EOF)
        {
        printf("%d. %s| %s| %s| Ano de lançamento: %d | %s\n", linha, livro.titulo, livro.autor, livro.genero, livro.ano, livro.data);
        linha++;
        }

    rewind(reg);
    int contador = 1;
    linha--;
    printf("\nDigite a opção do livro que você quer devolver\n");
    scanf("%d", &sel);

    // Remove livro selecionado da lista de empréstimos do usuário
    while(fscanf(reg,"%[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, livro.data) != EOF)
    {
        if(sel == contador){
            sprintf(save,"%s",livro.titulo);  // Salva título para atualizar estoque
            printf("\nDevolução realizada com sucesso");
            continuar();
            }
        if(sel != contador){  // Mantém outros empréstimos
            fprintf(temp,"%s| %s| %s| %d | %s", livro.titulo, livro.autor, livro.genero, livro.ano, livro.data);}

        contador++;
    }

    // Atualiza quantidade disponível no catálogo
    while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
    {
        if(strcmp(save, livro.titulo) == 0){
            livro.quantidade++;  // Incrementa quantidade disponível
        }

        fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
    }

    fclose(arq);
    fclose(fp);
    fclose(reg);
    fclose(temp);

    // Substitui arquivos originais pelos atualizados
    remove("BD/catalogo.txt");
    rename("BD/temp.txt", "BD/catalogo.txt");
    remove(nomeArquivo);
    rename("BD/usuarios/temp2.txt", nomeArquivo);

    // Valida opção escolhida
    if(sel > linha || sel <= 0){
        printf("\nOpção invalida\n\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        getchar();
        devolução(id);  // Tenta novamente
    }
    }

    menu_Biblioteca(id);
}

// Função para apagar registro de livro do catálogo (apenas administradores)
void apagarregistro(int id) {
    limpar_Tela();

    // Verifica se é administrador (ID negativo)
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
    } else {
        char lixo;
        int sel = 0;
        int linha = 1;
        Catalogo livro;
        FILE *arq = fopen("BD/catalogo.txt","r");
        FILE *fp = fopen("BD/temp.txt","w");

        printf("Livros no catálogo:\n\n");
        // Exibe todos os livros para seleção
        while(fscanf(arq," %[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
        {
            printf("%d. %s| %s| %s| Ano de lançamento: %d | Quantidade Disponível: %d\n", linha, livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
            linha++;
        }

        rewind(arq);
        int contador = 1;
        linha--;
        printf("\nDigite a opção do livro que você quer apagar:\n");
        scanf("%d", &sel);

        // Copia todos os livros exceto o selecionado para arquivo temporário
        while(fscanf(arq,"%[^|] %c %[^|] %c %[^|] %c %d %c %d", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, &livro.quantidade) != EOF)
        {
            if(sel != contador){  // Não copia o livro selecionado (efetivamente o apaga)
                fprintf(fp,"%s|%s|%s|%d|%d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);
            }
            contador++;
        }

        fclose(arq);
        fclose(fp);

        // Substitui catálogo original pelo atualizado
        remove("BD/catalogo.txt");
        rename("BD/temp.txt", "BD/catalogo.txt");

        menu_Biblioteca(id);
    }
}

// Função para registrar novo livro no catálogo (apenas administradores)
void registrarLivro(int id) {
    limpar_Tela();

    // Verifica se é administrador (ID negativo)
    if (id >= 0) {
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
    } else {
        FILE *fp = fopen("BD/catalogo.txt", "a"); // Abre arquivo para anexar

        // Estrutura local para o livro
        typedef struct
        {
            char titulo[100], autor[100], genero[100];
            int ano, quantidade;
        } catalogo;
        catalogo livro;

        // Coleta dados do novo livro
        printf("Informe os dados do livro para o catálogo:\n");
        printf("Título: ");
        scanf(" %[^\n]", livro.titulo);  // Lê linha completa incluindo espaços
        printf("Autor: ");
        scanf(" %[^\n]", livro.autor);
        printf("Gênero: ");
        scanf(" %[^\n]", livro.genero);
        printf("Ano de lançamento: ");
        scanf("%d", &livro.ano);
        printf("Quantidade disponível: ");
        scanf("%d", &livro.quantidade);

        // Adiciona livro ao catálogo
        fprintf(fp, "\n%s | %s | %s | %d | %d", livro.titulo, livro.autor, livro.genero, livro.ano, livro.quantidade);

        fclose(fp);

        menu_Biblioteca(id);
    }
}

// Função para consultar histórico de empréstimos do usuário
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
    tamanho = ftell(arq);  // Verifica se arquivo está vazio

    // Se não há empréstimos
    if(tamanho == 0){
        printf("Você não possui empréstimos\nAperte qualquer botão para continuar\n");
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        fgetchar();
        fclose(arq);
        }
    else{
    rewind(arq);
    printf("Livros emprestados:\n\n");
    // Exibe todos os empréstimos ativos do usuário
    while(fscanf(arq," %[^|] %c %[^|] %c %[^|] %c %d %c %[^\n]", livro.titulo, &lixo, livro.autor, &lixo, livro.genero, &lixo, &livro.ano, &lixo, livro.data) != EOF)
    {
        printf("%d. %s| %s| %s| Ano de lançamento: %d | %s\n", linha, livro.titulo, livro.autor, livro.genero, livro.ano, livro.data);
        linha++;
    }

    fclose(arq);

    printf("\nPressione qualquer tecla para continuar\n");
    while ((lixo = getchar()) != '\n' && lixo != EOF);
    getchar();
    limpar_Tela();
    }
    menu_Biblioteca(id);
}

// Declaração antecipada da função menu_Conta
void menu_Conta();

// Função para atualizar dados cadastrais do usuário logado
void atualizar_Dados_Cadastrais(){
    FILE *mestre = fopen("BD/arquivoMestre.txt", "r"), *mestreTemp;
    mestreTemp = fopen("BD/mestreTemp.txt", "w");

    char nomeTemp[100], senhaTemp[50], emailTemp[100], teste[21] ="BD/arquivoMestre.txt";
    int autorizacao, idTemp, statusUsuario, opcao;

    // Menu para escolher qual dado alterar
    printf("O que voce deseja alterar? <nome = 0 / senha = 1 / email = 2>: ");
    opcao = Ler_Opcoes();
    switch (opcao) {
    case 0:
        validacao_Nome_Usuario();  // Valida novo nome
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
        atualizar_Dados_Cadastrais();  // Tenta novamente
        break;
    }

    // Confirmação da alteração
    printf("\nTem certeza que voce deseja alterar o usuario?<sim = 0/ nao = 1\n");
    scanf("%d", &autorizacao);

    if (autorizacao == 0){
            // Atualiza arquivo mestre com novos dados
            while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
                if(idUsuarioLogado != idTemp){
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
                } else {
                    // Substitui dados do usuário logado pelos novos
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeUsuario, senha, email);
                }
            }

            fclose(mestre);
            fclose(mestreTemp);

            // Substitui arquivo original pelo atualizado
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
        menu_Conta();  // Cancela operação
    }
}

// Função para deslogar usuário (limpa dados da sessão)
void deslogar(){
    idUsuarioLogado = 0;  // Reseta ID
    strcpy(nomeUsuario, "\0");  // Limpa nome
    strcpy(senha, "\0");        // Limpa senha
    strcpy(email, "\0");        // Limpa email
    menu_Principal();  // Retorna ao menu principal
}

// Função para o usuário excluir sua própria conta
void usuario_Excluir_Usuario(){
    FILE *mestre = fopen("BD/arquivoMestre.txt", "r"), *mestreTemp;
    mestreTemp = fopen("BD/mestreTemp.txt", "w");

    char nomeArquivoUsuarioExcluir[20], nomeTemp[100], senhaTemp[50], emailTemp[100], teste[21] ="BD/arquivoMestre.txt";
    int autorizacao, idTemp, statusUsuario;

    sprintf(nomeArquivoUsuarioExcluir, "BD/usuarios/%d.txt", idUsuarioLogado);

    // Confirmação de exclusão
    printf("\nTem certeza que voce deseja excluir o usuario?<sim = 0/ nao = 1>: ");
    scanf("%d", &autorizacao);

    if (autorizacao == 0){
        // Marca usuário como inativo (status = 1) em vez de deletar
        while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
            if(idUsuarioLogado != idTemp){
                fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
            } else {
                fprintf(mestreTemp, "%d %d %s %s %s\n", 1, idTemp, nomeTemp, senhaTemp, emailTemp);  // Status 1 = inativo
            }
        }

        fclose(mestre);
        fclose(mestreTemp);

        // Substitui arquivo original
        if (remove("BD/arquivoMestre.txt") == 0 && rename("BD/mestreTemp.txt", "BD/arquivoMestre.txt") == 0) {
            printf("O usuario foi excluido com sucesso!");
            continuar();
            menu_Principal();  // Retorna ao menu principal
        } else {
            printf("Erro ao substituir o arquivo mestre!\n");
            continuar();
            menu_Conta();
        }
    } else {
        // Cancela operação
        fclose(mestre);
        fclose(mestreTemp);
        remove("BD/mestreTemp.txt");
        menu_Conta();
    }
}

// Função para administrador excluir outros usuários
void adm_Excluir_Usuarios(int id){
    // Verifica se é administrador
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

        // Confirmação de exclusão
        printf("\nTem certeza que voce deseja excluir esse usuario?<sim = 0/ nao = 1>: ");
        scanf("%d", &autorizacao);

        if (autorizacao == 0){
            // Marca usuário especificado como inativo
            while (fscanf(mestre, "%d %d %s %s %s", &statusUsuario, &idTemp, &nomeTemp, &senhaTemp, &emailTemp) != EOF){
                if(idExcluir != idTemp){
                    fprintf(mestreTemp, "%d %d %s %s %s\n", statusUsuario, idTemp, nomeTemp, senhaTemp, emailTemp);
                } else {
                    fprintf(mestreTemp, "%d %d %s %s %s\n", 1, idTemp, nomeTemp, senhaTemp, emailTemp);  // Status 1 = inativo
                }
            }

            fclose(mestre);
            fclose(mestreTemp);

            // Substitui arquivo original
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
            // Cancela operação
            fclose(mestre);
            fclose(mestreTemp);
            menu_Conta();
        }
    }
}

// Função para administrador consultar todos os cadastros de usuários
void consultar_Cadastros(int id){
    // Verifica se é administrador
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
            // Lista todos os usuários cadastrados (ativos e inativos)
            while(fscanf(mestre, "%d %d %s %s %s ", &statusUsuarioTemp, &idTemp, nomeTemp, senhaTemp, emailTemp) != EOF){
                printf("\nStatus: %d | ID: %d | Nome: %s | Email: %s", statusUsuarioTemp, idTemp, nomeTemp, emailTemp);
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

// Função para validar ID único ao criar conta (verifica se já existe)
int validacao_Id(){
    FILE* mestre = fopen("BD/arquivoMestre.txt", "r");

    int idValido = 0, idValidacao, statusPreencher, id;  // Variáveis auxiliares para leitura
    char nomeUsuarioValidacao[100], senhaPreencher[50], emailPreencher[100];

    while (!idValido) {
        printf("Insira o id do usuario (se for usuario adm inserir id < 0 e > -100)");
        scanf("%d", &id);

        idValido = 1;  // Assume que é válido inicialmente

        rewind(mestre);

        // Verifica se ID já existe no arquivo mestre
        while (fscanf(mestre, "%d %d %s %s %s", &statusPreencher, &idValidacao, &nomeUsuarioValidacao, & senhaPreencher, &emailPreencher) != EOF){
            if (id == idValidacao){
                limpar_Tela();
                printf("Esse id ja existe! Insira outro\n");
                idValido = 0;  // Marca como inválido
                break;
            }
        }
    }
    fclose(mestre);
    return id;  // Retorna ID válido
}

// Função para administrador criar conta de outros usuários
void adm_Criar_Comta(int id){
    // Verifica se é administrador
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

        idCriar = validacao_Id();  // Valida ID único

        validacao_Nome_Usuario();  // Valida nome único

        validacao_Email(email);  // Valida formato do email

        printf("Digite a senha: ");
        scanf("%s", senha);

        // Cria arquivo individual do usuário
        sprintf(nomeArquivoUsuario, "BD/usuarios/%d.txt", idCriar);
        usuario = fopen(nomeArquivoUsuario, "w");

        // Adiciona usuário ao arquivo mestre
        fprintf(mestre, "%d %d %s %s %s\n", 0, numeroId, nomeUsuario, senha, email);

        if (numeroId > 0){
            idCriar++;
        }

        fprintf(contada, "%d", idCriar);  // Atualiza contador

        fclose(contada);
        fclose(usuario);
        fclose(mestre);
        menu_Conta();
    }
}

// Exibe opções do menu de conta para usuários comuns
void opcoes_Menu_Conta(){
    printf("===Menu Contas===\n");
    printf("1. Atualizar dados cadastrais\n");
    printf("2. Sair da conta\n");
    printf("3. Excluir meu usuario\n");
    printf("4. Voltar\n");
}

// Exibe opções do menu de conta para administradores (inclui opções extras)
void opcoes_Menu_Conta_Adm(){
    opcoes_Menu_Conta();  // Mostra opções básicas
    printf("6822. Excluir usuarios\n");      // Opções exclusivas do admin
    printf("6823. Consultar cadastros\n");
    printf("6824. Criar conta\n");
}

// Menu de gerenciamento de conta (diferente para admin e usuário comum)
void menu_Conta(){
    limpar_Tela();
    int opcao;

    // Verifica se é administrador (ID negativo) para mostrar opções apropriadas
    if (idUsuarioLogado < 0) {
        opcoes_Menu_Conta_Adm();  // Menu com opções administrativas
        opcao = Ler_Opcoes();
    } else {
        opcoes_Menu_Conta();  // Menu básico
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
    // Opções exclusivas do administrador
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

// Menu principal da biblioteca (diferente para admin e usuário comum)
void menu_Biblioteca(int id){
    limpar_Tela();

    int opcao;
    // Verifica se é administrador para mostrar opções apropriadas
    if (id < 0) {
        opcoes_Menu_Biblioteca_Adm();  // Menu com opções administrativas
        opcao = Ler_Opcoes();
    } else {
        opcoes_Menu_Biblioteca();  // Menu básico
        opcao = Ler_Opcoes();
    }

    switch (opcao) {
    case 1:
        consultarCatalogo(id);  // Visualizar catálogo
        break;
    case 2:
        emprestimo(id);  // Realizar empréstimo
        break;
    case 3:
        devolução(id);  // Realizar devolução
        break;
    case 4:
        consultarEmprestimo(id);  // Consultar empréstimos
        break;
    case 5:
        menu_Conta(id);  // Gerenciar conta
        break;
    case 6:
        limpar_Tela();
        encerrar_Codigo();  // Sair do programa
        break;
    // Opções exclusivas do administrador
    case 1113:
        registrarLivro(id);  // Cadastrar livro
        break;
    case 1114:
        apagarregistro(id);  // Apagar livro
        break;

    default:
        printf("Opcao inexistente!!");
        continuar();
        menu_Biblioteca(id);
        break;
    }
}

// Função de inicialização do sistema
void start()
{
    FILE* contagem = fopen("BD/contador.txt", "r");
    int ultimoId;

    // Verifica se consegue abrir arquivo contador (necessário para IDs)
    if (contagem == NULL) {
        printf("Erro ao abrir arquivo!");
        printf("\nPressione enter para encerrar o programa!");
        getchar();
        encerrar_Codigo();
    } else {
        fscanf(contagem, "%d", &numeroId);  // Lê próximo ID disponível
        fclose(contagem);

        // Inicializa variáveis globais com valores padrão
        strcpy(nomeUsuario, "nike");
        strcpy(senha, "123");

        menu_Principal();  // Inicia o programa
    }
}