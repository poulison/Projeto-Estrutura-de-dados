

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

typedef struct {
  Dados *dados;
  struct CFila *anterior;
  struct CFila *proximo;

} CFila;

typedef struct {
  CFila *head;
  CFila *tail;
  int qtd;
} Fila;

typedef struct Vertice {
  Dados *dados;
  struct Vertice *esq;
  struct Vertice *dir;
  struct Vertice *pai;
} Vertice;

typedef struct Arvore {
  Vertice *raiz;
  int qtde;
} Arvore;

typedef struct Celula {
  struct Celula *anterior;
  char *RG; // armazena o rg do usuario pra procura na lista dps
  struct Celula *proximo;
  int qop; // se o valor da operação for 0=usuario foi removiso da fila
           // 1=adicionado a fila
} Celula;

typedef struct {
  Celula *topo;
  int qtde;
} Stack;

Celula *cria_celula(Dados *dados) {
  Celula *celula = malloc(sizeof(Celula));
  celula->anterior = NULL;
  celula->proximo = NULL;
  celula->RG = NULL;
  celula->qop = 2;
  return celula;
}

Stack *criar_stack() {
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->topo = NULL;
  return stack;
}

void push(Stack *pilha, char *RG, int qop) {
  Celula *nova_celula = malloc(sizeof(Celula));
  nova_celula->RG = malloc(strlen(RG) + 1);
  strcpy(nova_celula->RG, RG);
  nova_celula->qop = qop; // 1 significa enfileirar
  nova_celula->proximo = pilha->topo;
  nova_celula->anterior = NULL;

  if (pilha->topo != NULL) {
    pilha->topo->anterior = nova_celula;
  }

  pilha->topo = nova_celula;
  pilha->qtde++;
}

void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

Vertice *cria_vertice(char *nome, int idade, char *RG, Data *entrada) {
  Vertice *vertice = malloc(sizeof(Vertice));
  vertice->dir = NULL;
  vertice->esq = NULL;
  vertice->pai = NULL;
  vertice->dados = malloc(sizeof(Dados));
  vertice->dados->nome = malloc(strlen(nome) + 1);
  strcpy(vertice->dados->nome, nome);
  vertice->dados->idade = idade;
  vertice->dados->RG = malloc(strlen(RG) + 1);
  strcpy(vertice->dados->RG, RG);
  vertice->dados->entrada = entrada;

  return vertice;
}

Arvore *cria_arvore() {
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;

  return arvore;
}

ListaCad *criar_listaCad() {
  ListaCad *lista = malloc(sizeof(ListaCad));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

void *criar_fila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->head = NULL;
  fila->tail = NULL;
  fila->qtd = 0;
  return fila;
}
CFila *criar_cfila(char *nome, int idade, char *RG, Data *entrada) {
  CFila *cfila = malloc(sizeof(CFila));
  cfila->anterior = NULL;
  cfila->proximo = NULL;
  cfila->dados = malloc(sizeof(Dados));
  cfila->dados->nome = malloc(strlen(nome) + 1);
  strcpy(cfila->dados->nome, nome);
  cfila->dados->idade = idade;
  cfila->dados->RG = malloc(strlen(RG) + 1);
  strcpy(cfila->dados->RG, RG);
  cfila->dados->entrada = entrada;

  return cfila;
}
void in_ordem(Vertice *raiz) {
  if (raiz != NULL) {
    in_ordem(raiz->esq);
    printf("Nome: %s, Idade: %d, RG: %s, Data de Entrada: %02d/%02d/%d\n",
           raiz->dados->nome, raiz->dados->idade, raiz->dados->RG,
           raiz->dados->entrada->dia, raiz->dados->entrada->mes,
           raiz->dados->entrada->ano);
    in_ordem(raiz->dir);
  }
}

void inserir_arvore_dia(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo = cria_vertice(nome, idade, RG, entrada);

  if (*raiz == NULL) {
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) {
    antes = atual;
    if (entrada->dia < atual->dados->entrada->dia) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  novo->pai = antes;
  if (entrada->dia < antes->dados->entrada->dia) {
    antes->esq = novo;
  } else {
    antes->dir = novo;
  }
}
void inserir_arvore_mes(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo = cria_vertice(nome, idade, RG, entrada);

  if (*raiz == NULL) {
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) {
    antes = atual;
    if (entrada->mes < atual->dados->entrada->mes) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  novo->pai = antes;
  if (entrada->mes < antes->dados->entrada->mes) {
    antes->esq = novo;
  } else {
    antes->dir = novo;
  }
}
void inserir_arvore_ano(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo = cria_vertice(nome, idade, RG, entrada);

  if (*raiz == NULL) {
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) {
    antes = atual;
    if (entrada->ano < atual->dados->entrada->ano) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  novo->pai = antes;
  if (entrada->ano < antes->dados->entrada->ano) {
    antes->esq = novo;
  } else {
    antes->dir = novo;
  }
}
void inserir_arvore_idade(Vertice **raiz, char *nome, int idade, char *RG,
                          Data *entrada) {
  Vertice *novo = cria_vertice(nome, idade, RG, entrada);

  if (*raiz == NULL) {
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) {
    antes = atual;
    if (idade < atual->dados->idade) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  novo->pai = antes;
  if (idade < antes->dados->idade) {
    antes->esq = novo;
  } else {
    antes->dir = novo;
  }
}

void enfileirar_no_inicio(char *nome, int idade, char *RG, Data *entrada, Fila *fila) {
  CFila *novo = criar_cfila(nome, idade, RG, entrada);
  if (fila->qtd == 0) {
    fila->head = novo;
    fila->tail = novo;
  } else {
    novo->proximo = fila->head;
    fila->head->anterior = novo;
    fila->head = novo;
  }
  fila->qtd++;
}

int desinfileirar_do_inicio(Fila *fila) {
  if (fila->qtd > 0) {
    CFila *temp = fila->head;
    fila->head = fila->head->proximo;

    if (fila->qtd == 1) {
      fila->tail = NULL;
    } else {
      fila->head->anterior = NULL;
    }

    free(temp->dados->nome);
    free(temp->dados->RG);
    free(temp->dados->entrada);
    free(temp->dados);
    free(temp);

    fila->qtd--;
    return 1; // Sucesso
  }
  return 0; // Falha: fila vazia
}

void liberar_arvore(Vertice *vertice) {
  if (vertice != NULL) {
    liberar_arvore(vertice->esq);
    liberar_arvore(vertice->dir);
    free(vertice);
  }
}
void inserir_todos_na_arvore(ListaCad *lista, Arvore *arvore,
                             void tipo_arvore()) {
  Cadastro *atual = lista->primeiro;

  liberar_arvore(arvore->raiz);
  arvore->raiz = NULL;

  while (atual != NULL) {

    tipo_arvore(&(arvore->raiz), atual->dados->nome, atual->dados->idade,
                atual->dados->RG, atual->dados->entrada);
    atual = atual->proximo;
  }
  arvore->qtde = lista->qtde;
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

void *enfileirar(Stack *stack,char *nome, int idade, char *RG, Data *entrada, Fila *fila) {
  CFila *novo = criar_cfila(nome, idade, RG, entrada);
  if (fila->qtd == 0) {
    fila->head = novo;
  } else {
    fila->tail->proximo = novo;
    novo->anterior = fila->tail;
  }
  push(stack,RG,1);
  fila->tail = novo;
  fila->qtd++;

}

void mostrar_fila(Fila *fila) {
  CFila *atual = fila->head;
  while (atual != NULL) {
    printf("Nome: %s, Idade: %d, RG: %s\n", atual->dados->nome,
           atual->dados->idade, atual->dados->RG);
    atual = atual->proximo;
  }
  printf("Total na fila: %d\n", fila->qtd);
}
int desinfeirar(Stack *stack,Fila *fila) {

  if (fila->qtd > 0) {
    CFila *temp = fila->head;
    char *rg=fila->head->dados->RG;
    fila->head = fila->head->proximo;

    if (fila->qtd == 1) {
      fila->tail = NULL;
    } else {
      fila->head->anterior = NULL;
    }

    push(stack,rg,0);
    fila->qtd--;
    free(temp);
    return 1; // Sucesso
  }
  return 0; // Falha: fila vazia
}

void mostrar(ListaCad *lista) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    printf("Nome: %s\n", atual->dados->nome);
    printf("Data de Entrada: %02d/%02d/%d \n", atual->dados->entrada->dia,
           atual->dados->entrada->mes, atual->dados->entrada->ano);
    printf("RG: %s \n", atual->dados->RG);
    printf("Idade: %d \n", atual->dados->idade);
    printf("-----------------------\n");
    atual = atual->proximo;
  }
  printf("\n");
}

char pop(Stack *pilha) {
  char *rg = pilha->topo->RG;
  Celula *temp = pilha->topo;
  pilha->topo = pilha->topo->anterior;
  free(temp);
  pilha->qtde--;

  // Garantir que 'topo' não seja acessado se a pilha estiver vazia
  if (pilha->topo != NULL) {
    pilha->topo->proximo = NULL;
  }

  return *rg;
}
void procurar(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    if (strcmp(atual->dados->RG, RG) == 0) {
      printf("-----------------------\n");
      printf("Nome: %s", atual->dados->nome);
      printf("Data de Entrada: %02d/%02d/%d\n", atual->dados->entrada->dia,
             atual->dados->entrada->mes, atual->dados->entrada->ano);
      printf("RG: %s", atual->dados->RG);
      printf("Idade: %d\n", atual->dados->idade);
      printf("-----------------------\n");
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente não encontrado.\n");
}

void desfazer(Stack *pilha, ListaCad *lista, Fila *fila) {
  if (pilha->topo == NULL) {
    printf("Não há operações para desfazer.\n");
    return;
  }


  Celula *ultimo = pilha->topo;
  Cadastro *cadastro = lista->primeiro;
  char *nome = NULL;
  int idade = 0;
  char *RG = NULL;
  Data *entrada = NULL;


  while (cadastro != NULL) {
    if (strcmp(cadastro->dados->RG, ultimo->RG) == 0) {
      nome = cadastro->dados->nome;
      idade = cadastro->dados->idade;
      RG = cadastro->dados->RG;
      entrada = cadastro->dados->entrada;
      break;
    }
    cadastro = cadastro->proximo;
  }

  if (ultimo->qop == 0) { 
    enfileirar_no_inicio(nome, idade, RG, entrada, fila);
  } else if (ultimo->qop == 1) { 
    desinfileirar_do_inicio(fila);
  }


  pop(pilha);
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

void menu() {
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
}

void print_cadatrar() {
  printf("Cadastro: \n");
  printf("------------------------\n");
  printf("Qual operacao deseja fazer ? \n");
  printf("1. Novo Paciente\n");
  printf("2. Consultar paciente cadastrado\n");
  printf("3. Mostrar lista completa\n");
  printf("4. Atualizar dados\n");
  printf("5. Remover paciente\n");
  printf("0. Sair\n");
  printf("------------------------\n");
  printf("Digite sua escolha: ");
}

void print_atendimento() {
  printf("Atendimento: \n");
  printf("----------------------------------\n");
  printf("Qual operacao deseja fazer ? \n");
  printf("1. Enfileirar paciente\n");
  printf("2. Desinfileirar paciente\n");
  printf("3. Mostrar fila\n");
  printf("0. Sair\n");
  printf("-----------------------------------\n");
  printf("Digite sua escolha: ");
}

void print_Sobre() {
  printf("Sobre: \n");
  printf("--------------------------------------------\n");
  printf("Desenvolvedores:\n");
  printf("Nome: Paulo Andre de Oliveira Hirata\n");
  printf("Ciclo: Quarto ciclo\n");
  printf("Curso: Ciencia da computacao\n");
  printf("Disciplina: Estrutura de dados\n");
  printf("---------------------------------------------\n");
  printf("Nome: Victor Merker Binda\n");
  printf("Ciclo: Quarto ciclo\n");
  printf("Curso: Ciencia da computacao\n");
  printf("Disciplina: Estrutura de dados\n");
  printf("--------------------------------------------\n");
  printf("Data: 08/11/2024");
}

void print_pesquisa() {
  printf("Pesquisar: \n");
  printf("------------------------------------------------\n");
  printf("Selecione qual operacao voce deseja realizar\n");
  printf("1. Registros ordenados por ano\n");
  printf("2. Registros ordenados por mes\n");
  printf("3. Registros ordenados por dia\n");
  printf("4. Registros ordenados por idade\n");
  printf("------------------------------------------------\n");
}
int main() {
  ListaCad *lista = criar_listaCad();
  int escolha;
  char nome[50], RG[20];
  int idade, dia, mes, ano;
  Fila *fila = criar_fila();
  Arvore *arvoredia = cria_arvore();
  Arvore *arvoremes = cria_arvore();
  Arvore *arvoreano = cria_arvore();
  Arvore *arvoreidade = cria_arvore();
  Stack *stack = criar_stack();

  do {
    menu();
    scanf("%d", &escolha);

    switch (escolha) {
      int subEscolha;

    case 1:
      do {
        print_cadatrar();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1:
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

          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(lista, arvoreidade, inserir_arvore_idade);
          break;

        case 2:
          printf("Consultar cadastro \n");
          printf("Digite o RG do paciente: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);

          procurar(lista, RG);
          break;

        case 3:
          mostrar(lista);
          break;

        case 4:
          printf("Digite o RG do paciente para atualizar: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);

          atualizar(lista, RG);
          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(lista, arvoreidade, inserir_arvore_idade);
          break;

        case 5:
          printf("Digite o RG do paciente para remover: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          remover(lista, RG);
          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(lista, arvoreidade, inserir_arvore_idade);
          break;

        case 0:
          printf("Saindo...\n");
          break;

        default:
          printf("Opção inválida\n");
          break;
        }
      } while (subEscolha != 0);
      break;

    case 2:
      do {

        print_atendimento();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1:
          printf("Digite o RG do usuario para inseri-lo na fila: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          Cadastro *inserido = lista->primeiro;
          int found = 0;

          while (inserido != NULL) {
            if (strcmp(inserido->dados->RG, RG) == 0) {

              enfileirar(stack,inserido->dados->nome, inserido->dados->idade,
                         inserido->dados->RG, inserido->dados->entrada, fila);
              printf("Paciente inserido na fila com sucesso!\n");
              found = 1;
              break;
            }
            inserido = inserido->proximo;
          }

          if (!found) {
            printf("RG não encontrado\n");
          }
          break;

        case 2:
          printf("Desinfileirar paciente \n");
          desinfeirar(stack,fila);
          
          break;

        case 3:
          printf("Mostrar fila\n");
          mostrar_fila(fila);
          break;

        case 0:
          printf("Saindo...\n");
          break;

        default:
          printf("Opção inválida\n");
        }
      } while (subEscolha != 0);
      break;

    case 3:
      do {
        print_pesquisa();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1:
          printf("Mostrar registros ordenados por ano:\n");
          in_ordem(arvoreano->raiz);
          break;

        case 2:
          printf("Mostrar registros ordenados por mes:\n");
          in_ordem(arvoremes->raiz);
          break;

        case 3:
          printf("Mostrar registros ordenados por dia:\n");
          in_ordem(arvoredia->raiz);
          break;

        case 4:
          printf("Mostrar registros ordenados por idade:\n");
          in_ordem(arvoreidade->raiz);
          break;

        case 0:
          printf("Sair \n");
          break;

        default:
          printf("Opção inválida\n");
          break;
        }
      } while (subEscolha != 0);
      break;

    case 4:
      printf("Desfazer: \n");
      desfazer(stack, lista , fila);
      printf("Ultima operação desfeita com sucesso!\n");
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
  } while (escolha != 0);

  return 0;
}
