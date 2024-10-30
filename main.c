#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia;
    int mes;
    int ano;

} Data;

typedef struct Cadastro {
  struct Cadastro *proximo;
  int idade;
  string nome;
  string RG;
  struct Data *entrada;

} Cadastro;

typedef struct{
  Cadastro *primeiro;
  int qtde;
} ListaCad;

int escolha;
int subescolha;

void clearBuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}


ListaCad *criar_listaCad(){
  ListaCad *lista = malloc(sizeof(ListaCad));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

Cadastro *criar_cadastro(string nome, int idade, string RG, Data *entrada){
  Cadastro *cadastro = malloc(sizeof(Cadastro));
  cadastro->proximo = NULL;
  cadastro-> nome = nome;
  cadastro-> idade = idade;
  cadastro-> RG = RG;
  cadastro->entrada-> dia = dia;
  cadastro->entrada-> mes = dia;
  cadastro->entrada-> ano = dia;

  return cadastro;
}

void menu(int escolha){
    printf("-----------------------\n")
    printf("Escolha uma opção:\n");
    printf("1. Cadastrar\n");
    printf("2. Atendimento\n");
    printf("3. Pesquisar\n");
    printf("4. Desfazer\n");
    printf("5. Carregar / Salvar\n");
    printf("6. Sobre\n");
    printf("0. Sair\n")
    printf("-----------------------\n")
    printf("Digite sua escolha: ");
}

void print_cadatrar(int subescolha){
    printf("Cadastro: \n");
    printf("------------------------\n");
    printf("Qual operacao deseja fazer ? \n");
    printf("1. Novo Paciente\n");
    printf("2. Consultar paciente cadastrado\n");
    printf("3. Mostrar lista completa\n");
    printf("4. Atualizar dados\n");
    printf("5. Remover paciente\n");
    printf("------------------------\n")
    printf("Digite sua escolha: ");
}

void print_atendimento(int subescolha){
    printf("Atendimento: \n");
    printf("----------------------------------\n");
    printf("Qual operacao deseja fazer ? \n");
    printf("1. Enfileirar paciente\n");
    printf("2. Desinfileirar paciente\n");
    printf("3. Mostrar fila\n");
    printf("-----------------------------------\n")
    printf("Digite sua escolha: ");
}

void print_Sobre(){
    printf("Sobre: \n");
    printf("--------------------------------------------\n");
    printf("Desenvolvedores:\n");
    printf("Nome: Paulo Andre de Oliveira Hirata\n");
    printf("Ciclo: Quarto ciclo\n");
    printf("Curso: Ciencia da computacao\n");
    printf("Disciplina: Estrutura de dados\n");
    printf("----------------\n");
    printf("Nome: Victor Merker Binda\n");
    printf("Ciclo: Quarto ciclo\n");
    printf("Curso: Ciencia da computacao\n");
    printf("Disciplina: Estrutura de dados\n");
    printf("--------------------------------------------\n");
    printf("Data: 08/11/2024");
}

void print_pesquisa(int subescolha){
    printf("Pesquisar: \n");
    printf("------------------------------------------------\n");
    printf("Selecione qual operacao voce deseja realizar\n");
    printf("1. Registros ordenados por ano\n");
    printf("2. Registros ordenados por mes\n");
    printf("3. Registros ordenados por dia\n");
    printf("4. Registros ordenados por idade\n");
    printf("------------------------------------------------\n");
}

void inserir(ListaCad *lista, string nome, int idade, string RG, Data *entrada){
  Cadastro *novo = criar_cadastro(nome, idade, RG, entrada);
  Cadastro *atual = lista -> primeiro;
  Cadastro *anterior = NULL;
  if(lista->primeiro == NULL){
    lista -> primeiro = novo;
    lista -> qtde++;
  } else{
    while(atual != NULL && novo -> idade >= atual -> idade){
      anterior = atual;
      atual = atual -> proximo;
    }
    if(anterior == NULL){
      novo -> proximo = lista -> primeiro;
      lista -> primeiro = novo;
      lista->qtde++;
    }else{
      if(atual == NULL){
        anterior -> proximo = novo;
        lista -> qtde++;
      }else{
        anterior -> proximo = novo;
        novo -> proximo = atual;
        lista -> qtde++;
      }
    }
  }
}

int main() {
    
    
    do {
        menu(escolha);
        scanf("%d", &escolha);

        // Processar escolha
        switch (escolha) {
            
            case 1:
                print_cadatrar(subescolha);
                scanf("%d", &subescolha);
                
                switch(subescolha){
                  case 1 :
                      printf("cadastro de um novo paciente:\n")
                      printf("--------------------------------\n");
                      printf("Por favor insira os dados: \n");
                      printf("Nome: \n");
                      scanf("%s", nome);
                      printf("Idade: \n");
                      scanf("%d", idade);
                      clearBuffer();
                      printf("RG: \n");
                      scanf("%s", RG);
                      printf("Dia: \n");
                      scanf("%d", dia);
                      printf("Mes: \n");
                      scanf("%d", mes);
                      printf("Ano: \n");
                      scanf("%d", ano);
                      clearBuffer();
                      inserir(ListaCad *lista, nome, idade, RG, *entrada);
                
                  break;

                  case 2:
                      printf("Consultar cadastro \n");

                  break;

                  case 3:
                      printf("Mostrar lista completa\n");

                  break;

                  case 4:
                      printf("Atualizar dados de paciente\n");

                  break;

                  case 5:
                      printf("Remover paciente\n");

                  break;
                }

                break;  
            
            case 2:
                print_atendimento(subescolha);
                scanf("%d", &subescolha);
                
                switch(subescolha){
                  case 1 :
                      printf("Enfileirar paciente:\n")
                     
                  break;

                  case 2:
                      printf("Desinfileirar paciente \n");

                  break;

                  case 3:
                      printf("Mostrar fila\n");

                  break;
                 }
                
                break;
            case 3:
                print_pesquisa(subescolha);
                scanf("%d", &subescolha);
                
                switch(subescolha){
                  case 1 :
                      printf("Mostrar registros ordenados por ano:\n")
                     
                  break;

                  case 2:
                      printf("Mostrar registros ordenados por mes:\n")

                  break;

                  case 3:
                      printf("Mostrar registros ordenados por dia:\n")

                  break;

                  case 4:
                      printf("Mostrar registros ordenados por idade:\n")

                  break;
                 }

                break;

            case 4:
                printf("Desfazer: \n");
                
                break;
            case 5:
                printf("Carregar / Salvar:\n");
                
                break;
            case 6:
                print_Sobre();
      
                break;
            case 0:
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while (escolha != 6);

    return 0;
}
