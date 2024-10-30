#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Dados {
  int idade;
  char *nome;
  char *RG;
  Data *entrada;
} Dados;

typedef struct Cadastro {
  struct Cadastro *proximo;
  Dados *dados;
} Cadastro;

typedef struct {
  Cadastro *primeiro;
  int qtde;
} ListaCad;

void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

ListaCad *criar_listaCad() {
  ListaCad *lista = malloc(sizeof(ListaCad));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

Cadastro *criar_cadastro(char *nome, int idade, char *RG, Data *entrada) {
  Cadastro *cadastro = malloc(sizeof(Cadastro));
  cadastro->proximo = NULL;
  cadastro->dados = malloc(sizeof(Dados));
  cadastro->dados->nome = malloc(strlen(nome) + 1);
  strcpy(cadastro->dados->nome, nome);
  cadastro->dados->idade = idade;
  cadastro->dados->RG = malloc(strlen(RG) + 1);
  strcpy(cadastro->dados->RG, RG);
  cadastro->dados->entrada = entrada;

  return cadastro;
}

void mostrar(ListaCad *lista) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    printf("Nome: %s", atual->dados->nome);
    printf("Data de Entrada: %02d/%02d/%d\n", 
           atual->dados->entrada->dia, 
           atual->dados->entrada->mes, 
           atual->dados->entrada->ano);
    printf("RG: %s", atual->dados->RG);
    printf("Idade: %d\n", atual->dados->idade);
    printf("-----------------------\n");
    atual = atual->proximo;
  }
  printf("\n");
}

void procurar(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    if (strcmp(atual->dados->RG, RG) == 0) {
      printf("-----------------------\n");
      printf("Nome: %s", atual->dados->nome);
      printf("Data de Entrada: %02d/%02d/%d\n", 
             atual->dados->entrada->dia, 
             atual->dados->entrada->mes, 
             atual->dados->entrada->ano);
      printf("RG: %s", atual->dados->RG);
      printf("Idade: %d\n", atual->dados->idade);
      printf("-----------------------\n");
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente não encontrado.\n");
}

void atualizar(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    if (strcmp(atual->dados->RG, RG) == 0) {
      printf("-----------------------\n");
      printf("Escolha qual campo você deseja mudar\n");
      printf("1. Nome\n");
      printf("2. RG\n");
      printf("3. Data de Entrada\n");
      printf("4. Idade\n");
      int escolha;
      scanf("%d", &escolha);
      clearBuffer();
      switch (escolha) {
        case 1: {
          char novoNome[100];
          printf("Digite o novo nome: ");
          fgets(novoNome, sizeof(novoNome), stdin);
          novoNome[strcspn(novoNome, "\n")] = 0;
          free(atual->dados->nome);
          atual->dados->nome = malloc(strlen(novoNome) + 1);
          strcpy(atual->dados->nome, novoNome);
          printf("Nome atualizado com sucesso!\n");
          break;
        }
        case 2: {
          char novoRG[20];
          printf("Digite o novo RG: ");
          fgets(novoRG, sizeof(novoRG), stdin);
          novoRG[strcspn(novoRG, "\n")] = 0;
          free(atual->dados->RG);
          atual->dados->RG = malloc(strlen(novoRG) + 1);
          strcpy(atual->dados->RG, novoRG);
          printf("RG atualizado com sucesso!\n");
          break;
        }
        case 3: {
          int novodia, novomes, novoano;
          printf("Digite a nova data de entrada (dd/mm/aaaa): ");
          scanf("%d/%d/%d", &novodia, &novomes, &novoano);
          free(atual->dados->entrada);
          atual->dados->entrada = malloc(sizeof(Data));
          atual->dados->entrada->dia = novodia;
          atual->dados->entrada->mes = novomes;
          atual->dados->entrada->ano = novoano;
          printf("Data de entrada atualizada com sucesso!\n");
          break;
        }
        case 4: {
          int novaIdade;
          printf("Digite a nova idade: ");
          scanf("%d", &novaIdade);
          atual->dados->idade = novaIdade;
          printf("Idade atualizada com sucesso!\n");
          break;
        }
        default:
          printf("Opção inválida!\n");
      }
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente não encontrado para atualização.\n");
}

void remover(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  Cadastro *anterior = NULL;

  while (atual != NULL && strcmp(atual->dados->RG, RG) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }

  if (atual != NULL) {
    if (anterior == NULL) {
      lista->primeiro = atual->proximo;
    } else {
      anterior->proximo = atual->proximo;
    }
    free(atual->dados->nome);
    free(atual->dados->RG);
    free(atual->dados->entrada);
    free(atual->dados);
    free(atual);
    lista->qtde--;
  } else {
    printf("Paciente não encontrado para remoção.\n");
  }
}

void inserir(ListaCad *lista, char *nome, int idade, char *RG, Data *entrada) {
  Cadastro *novo = criar_cadastro(nome, idade, RG, entrada);
  Cadastro *atual = lista->primeiro;
  Cadastro *anterior = NULL;

  if (lista->primeiro == NULL) {
    lista->primeiro = novo;
    lista->qtde++;
  } else {
    while (atual != NULL && novo->dados->idade >= atual->dados->idade) {
      anterior = atual;
      atual = atual->proximo;
    }
    if (anterior == NULL) {
      novo->proximo = lista->primeiro;
      lista->primeiro = novo;
    } else {
      anterior->proximo = novo;
      novo->proximo = atual;
    }
    lista->qtde++;
  }
}

int main() {
  ListaCad *lista = criar_listaCad();
  int escolha;
  char nome[50], RG[20];
  int idade, dia, mes, ano;

  do {
    printf("-----------------------\n");
    printf("Escolha uma opção:\n");
    printf("1. Cadastrar\n");
    printf("2. Atendimento\n");
    printf("3. Pesquisar\n");
    printf("4. Desfazer\n");
    printf("5. Carregar / Salvar\n");
    printf("6. Sobre\n");
    printf("0. Sair\n");
    printf("-----------------------\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1: {
      int subEscolha;
      do {
        printf("-----------------------\n");
        printf("Menu de Cadastro:\n");
        printf("1. Cadastrar novo paciente\n");
        printf("2. Consultar paciente\n");
        printf("3. Mostrar lista completa\n");
        printf("4. Atualizar dados de paciente\n");
        printf("5. Remover paciente\n");
        printf("0. Voltar\n");
        printf("-----------------------\n");
        printf("Digite sua escolha: ");
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1: {
          printf("Nome: ");
          clearBuffer();
          fgets(nome, sizeof(nome), stdin);

          printf("Idade: ");
          scanf("%d", &idade);
          clearBuffer();
          printf("RG: ");
          fgets(RG, sizeof(RG), stdin);

          printf("Dia de entrada: ");
          scanf("%d", &dia);
          printf("Mês de entrada: ");
          scanf("%d", &mes);
          printf("Ano de entrada: ");
          scanf("%d", &ano);

          Data *entrada = malloc(sizeof(Data));
          entrada->dia = dia;
          entrada->mes = mes;
          entrada->ano = ano;

          inserir(lista, nome, idade, RG, entrada);
          printf("Paciente cadastrado com sucesso!\n");
          break;
        }
        case 2: {
          printf("Digite o RG do paciente: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          procurar(lista, RG);
          break;
        }
        case 3:
          mostrar(lista);
          break;
        case 4: {
          printf("Digite o RG do paciente para atualizar: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          atualizar(lista, RG);

          break;
        }
        case 5: {
          printf("Digite o RG do paciente para remover: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          remover(lista, RG);

          break;
        }
        case 0:
          break;
        default:
          printf("Opção inválida!\n");
          break;
        }
      } while (subEscolha != 0);
      break;
    }
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
      printf("Curso: Ciencia da computacao\n");
      printf("Disciplina: Estrutura de dados\n");
      printf("----------------\n");
      printf("Nome: Victor Merker Binda\n");
      printf("Ciclo: Quarto ciclo\n");
      printf("Curso: Ciencia da computacao\n");
      printf("Disciplina: Estrutura de dados\n");
      printf("--------------------------------------------\n");
      printf("Data: 08/11/2024\n");
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida! Tente novamente.\n");
    }
    printf("\n");
  } while (escolha != 0);

  return 0;
}
