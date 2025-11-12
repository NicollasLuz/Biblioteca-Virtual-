#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

extern int contagemPassagemEmail;
extern int conatgemPassagemUserName;
extern int idUsuarioLogado;
extern char nomeUsuario[100];
extern char email[100];
extern char senha[50];
extern int numeroId;

typedef struct {
    char titulo[50];
    char autor[50];
    char genero[50];
    char data[50];
    int ano;
    int quantidade;
} Catalogo;

void limpar_Tela();
void continuar();
int encerrar_Codigo();
int encerrar_Codigo();
void validacao_Nome_Usuario();
void criarConta();
void fazer_Login();
int Ler_Opcoes();
void opcoes_Menu_Biblioteca();
void opcoes_Menu_Biblioteca_Adm();
int menu_Principal();
void emprestimo(int id);
void consultarCatalogo(int id);
void apagarRegistro();
void registrarLivro();
void consultarEmprestimo(int id);
void atualizar_Dados_Cadastrais();
void deslogar();
void usuario_Excluir_Usuario();
void adm_Excluir_Usuarios(int id);
void consultar_Cadastros(int id);
int validacao_Id();
void adm_Criar_Comta(int id);
void opcoes_Menu_Conta();
void opcoes_Menu_Conta_Adm();
void menu_Conta();
void menu_Biblioteca(int id);
void start();

#endif // BIBLIOTECA_H_INCLUDED
