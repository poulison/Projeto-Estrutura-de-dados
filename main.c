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
    int escolha;
    

    do {
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
        scanf("%d", &escolha);

        // Processar escolha
        switch (escolha) {
            case 1:
                printf("Cadastro: \n");
                printf("--------------\n");
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
                printf("Atendimento: \n");
                
                break;
            case 3:
                printf("Pesquisar: \n");
                
                break;
            case 4:
                printf("Desfazer: \n");
                
                break;
            case 5:
                printf("Carregar / Salvar:\n");
                break;
            case 6:
                printf("Sobre: \n");
                printf("--------------------------------------------\n");
                printf("Desenvolvedores:\n");
                printf("Nome: Paulo Andre de Oliveira Hirata\n");
                printf("Ciclo: Quarto ciclo\n");
                printf("Curso: Ciencia da computacao\n")
                printf("Disciplina: Estrutura de dados\n")
                printf("----------------\n");
                printf("Nome: Victor Merker Binda\n");
                printf("Ciclo: Quarto ciclo\n");
                printf("Curso: Ciencia da computacao\n")
                printf("Disciplina: Estrutura de dados\n")
                printf("--------------------------------------------\n");
                printf("Data: 08/11/2024")
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
