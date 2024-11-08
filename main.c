

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma data com dia, mês e ano
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

// Estrutura que representa os dados de uma pessoa
typedef struct Dados {
  int idade;
  char *nome;
  char *RG;
  Data *entrada;
} Dados;

// Estrutura para representar um cadastro, que pode apontar para o próximo
// cadastro
typedef struct Cadastro {
  struct Cadastro *proximo;
  Dados *dados;
} Cadastro;

// Estrutura que representa uma lista de cadastros
typedef struct {
  Cadastro *primeiro;
  int qtde;
} ListaCad;

// Estrutura para representar um nó em uma fila
typedef struct {
  Dados *dados;
  struct CFila *anterior;
  struct CFila *proximo;
} CFila;

// Estrutura que representa uma fila
typedef struct {
  CFila *head;
  CFila *tail;
  int qtd;
} Fila;

// Estrutura que representa um vértice em uma árvore binária
typedef struct Vertice {
  Dados *dados;
  struct Vertice *esq;
  struct Vertice *dir;
  struct Vertice *pai;
} Vertice;

// Estrutura que representa uma árvore binária
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

// Estrutura para uma pilha
typedef struct {
  Celula *topo;
  int qtde;
} Stack;

// cria a celula
Celula *cria_celula(Dados *dados) {
  Celula *celula = malloc(sizeof(Celula));
  celula->anterior = NULL;
  celula->proximo = NULL;
  celula->RG = NULL;
  celula->qop = 2;
  return celula;
}
// Cria a pilha para a funcao desfazer
Stack *criar_stack() {
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->topo = NULL;
  return stack;
}

// funcao para inserir a celula na pilha
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

// funcao para limpar o buffer do teclado
void clearBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// funcao para criar os vertices para a arvore
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

// cria a arvore
Arvore *cria_arvore() {
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;

  return arvore;
}

// cria a lista de cadastros
ListaCad *criar_listaCad() {
  ListaCad *lista = malloc(sizeof(ListaCad));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

// cria a fila para os pacientes
void *criar_fila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->head = NULL;
  fila->tail = NULL;
  fila->qtd = 0;
  return fila;
}

// cria lista
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
// funcao para printar na ordem desejada as informacoes do usuario
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
// Função para inserir um vértice na árvore com base no dia de entrada
void inserir_arvore_dia(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo = cria_vertice(nome, idade, RG,
                               entrada); // Cria um novo vértice com os dados

  if (*raiz ==
      NULL) { // Se a árvore estiver vazia, o novo vértice se torna a raiz
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) { // Percorre a árvore para encontrar a posição correta
    antes = atual;
    if (entrada->dia < atual->dados->entrada->dia) {
      atual = atual->esq; // Vai para a subárvore esquerda se o dia for menor
    } else {
      atual =
          atual
              ->dir; // Vai para a subárvore direita se o dia for maior ou igual
    }
  }

  novo->pai = antes; // Define o pai do novo nó
  if (entrada->dia < antes->dados->entrada->dia) {
    antes->esq = novo; // Insere à esquerda se o dia for menor
  } else {
    antes->dir = novo; // Insere à direita se o dia for maior ou igual
  }
}

// Função para inserir um vértice na árvore com base no mês de entrada
void inserir_arvore_mes(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo =
      cria_vertice(nome, idade, RG, entrada); // Cria um novo vértice

  if (*raiz == NULL) { // Se a árvore estiver vazia
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) { // Busca a posição correta para o novo nó
    antes = atual;
    if (entrada->mes < atual->dados->entrada->mes) {
      atual = atual->esq; // Vai para a esquerda se o mês for menor
    } else {
      atual = atual->dir; // Vai para a direita se o mês for maior ou igual
    }
  }

  novo->pai = antes; // Define o pai do novo nó
  if (entrada->mes < antes->dados->entrada->mes) {
    antes->esq = novo;
  } else {
    antes->dir = novo;
  }
}

// Função para inserir um vértice na árvore com base no ano de entrada
void inserir_arvore_ano(Vertice **raiz, char *nome, int idade, char *RG,
                        Data *entrada) {
  Vertice *novo =
      cria_vertice(nome, idade, RG, entrada); // Cria um novo vértice

  if (*raiz == NULL) { // Se a árvore estiver vazia
    *raiz = novo;
    return;
  }

  Vertice *atual = *raiz;
  Vertice *antes = NULL;

  while (atual != NULL) { // Busca a posição correta para o novo nó
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
// Função para inserir um vértice na árvore com base na idade
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

// Função para enfileirar um elemento no início da fila
void enfileirar_no_inicio(char *nome, int idade, char *RG, Data *entrada,
                          Fila *fila) {
  CFila *novo = criar_cfila(nome, idade, RG, entrada);
  if (fila->qtd == 0) { // Se a fila estiver vazia
    fila->head = novo;
    fila->tail = novo;
  } else {
    novo->proximo = fila->head;
    fila->head->anterior = novo;
    fila->head = novo;
  }
  fila->qtd++;
}

// Função para desenfileirar do início da fila
int desinfileirar_do_fim(Fila *fila) {
  if (fila->qtd > 0) {
    CFila *temp = fila->tail;

    if (fila->qtd == 1) {
      // Se houver apenas um elemento na fila
      fila->head = NULL;
      fila->tail = NULL;
    } else {
      // Atualiza o tail para o penúltimo elemento
      fila->tail = fila->tail->anterior;
      fila->tail->proximo = NULL;
    }

    // Libera a memória do nó removido
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

// Função para liberar a memória de todos os vértices da árvore
void liberar_arvore(Vertice *vertice) {
  if (vertice != NULL) {
    liberar_arvore(vertice->esq); // Libera a subárvore esquerda
    liberar_arvore(vertice->dir); // Libera a subárvore direita
    free(vertice);                // libera o vertice atual
  }
}
// Função para inserir todos os cadastros da lista na árvore
void inserir_todos_na_arvore(ListaCad *lista, Arvore *arvore,
                             void tipo_arvore()) {
  Cadastro *atual = lista->primeiro;

  liberar_arvore(
      arvore->raiz); // Libera a árvore antes de inserir os novos elementos
  arvore->raiz = NULL;

  while (atual != NULL) {

    tipo_arvore(&(arvore->raiz), atual->dados->nome, atual->dados->idade,
                atual->dados->RG, atual->dados->entrada);
    atual = atual->proximo;
  }
  arvore->qtde = lista->qtde; // Atualiza a quantidade de elementos na árvore
}

// Função para criar um novo cadastro com os dados fornecidos
Cadastro *criar_cadastro(char *nome, int idade, char *RG, Data *entrada) {
  Cadastro *cadastro =
      malloc(sizeof(Cadastro)); // Aloca memória para o cadastro
  cadastro->proximo = NULL; // Define o próximo como NULL para o final da lista
  cadastro->dados =
      malloc(sizeof(Dados)); // Aloca memória para os dados do cadastro
  cadastro->dados->nome = malloc(
      strlen(nome) + 1); // Aloca memória para o nome e copia o valor fornecido
  strcpy(cadastro->dados->nome, nome);
  cadastro->dados->idade = idade;
  cadastro->dados->RG = malloc(strlen(RG) + 1);
  strcpy(cadastro->dados->RG, RG);
  cadastro->dados->entrada = entrada;

  return cadastro;
}

// Função para enfileirar um novo elemento na fila
void *enfileirar(Stack *stack, char *nome, int idade, char *RG, Data *entrada,
                 Fila *fila) { // Cria um novo nó de fila
  CFila *novo = criar_cfila(nome, idade, RG, entrada);
  if (fila->qtd == 0) { // Se a fila está vazia, define o novo nó como a cabeça
    fila->head = novo;
  } else {
    fila->tail->proximo = novo;
    novo->anterior = fila->tail;
  }
  push(stack, RG,
       1); // Empilha o RG com um código de ação (1) na pilha auxiliar
  fila->tail = novo;
  fila->qtd++;
}

// Função para exibir todos os elementos da fila
void mostrar_fila(Fila *fila) {
  CFila *atual = fila->head;
  while (atual !=
         NULL) { // Percorre a fila do início ao fim, imprimindo os dados
    printf("Nome: %s, Idade: %d, RG: %s\n", atual->dados->nome,
           atual->dados->idade, atual->dados->RG);
    atual = atual->proximo;
  }
  printf("Total na fila: %d\n", fila->qtd);
}

// Função para remover um elemento do início da fila
int desinfeirar(Stack *stack, Fila *fila) {

  if (fila->qtd > 0) {
    CFila *temp = fila->head;
    char *rg = fila->head->dados->RG; // Captura o RG do elemento removido
    fila->head = fila->head->proximo;

    if (fila->qtd == 1) { // Se era o único elemento, define o final como NULL
      fila->tail = NULL;
    } else {
      fila->head->anterior =
          NULL; // Ajusta o ponteiro anterior do novo primeiro nó
    }

    push(stack, rg, 0); // Empilha o RG na pilha com código de remoção (0)
    fila->qtd--;
    free(temp);
    return 1; // Sucesso
  }
  return 0; // Falha: fila vazia
}

// Função para exibir todos os cadastros em uma lista
void mostrar(ListaCad *lista) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {
    printf("\n"); // Percorre a lista e imprime os dados de cada cadastro
    printf("Nome: %s\n", atual->dados->nome);
    printf("Data de Entrada: %02d/%02d/%d\n", atual->dados->entrada->dia,
           atual->dados->entrada->mes, atual->dados->entrada->ano);
    printf("\n");
    printf("RG: %s\n", atual->dados->RG);
    printf("Idade: %d\n", atual->dados->idade);
    printf("-----------------------\n");
    atual = atual->proximo;
  }
  printf("\n");
}

// Função para remover o topo da pilha e retornar o RG do elemento removido
char pop(Stack *pilha) {
  char *rg = pilha->topo->RG;
  Celula *temp = pilha->topo;          // Guarda o elemento do topo para liberar
  pilha->topo = pilha->topo->anterior; // Move o topo para o próximo elemento
  free(temp);                          // Libera a memória do elemento removido
  pilha->qtde--; // Decrementa a quantidade de elementos na pilha

  // Garantir que 'topo' não seja acessado se a pilha estiver vazia
  if (pilha->topo != NULL) {
    pilha->topo->proximo = NULL;
  }

  return *rg;
}

// Função para procurar um cadastro pelo RG na lista
void procurar(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) {                    // Percorre a lista de cadastros
    if (strcmp(atual->dados->RG, RG) == 0) { // Verifica se o RG corresponde
      printf("-----------------------\n");
      printf("Nome: %s\n", atual->dados->nome);
      printf("Data de Entrada: %02d/%02d/%d\n", atual->dados->entrada->dia,
             atual->dados->entrada->mes, atual->dados->entrada->ano);
      printf("RG: %s\n", atual->dados->RG);
      printf("Idade: %d\n", atual->dados->idade);
      printf("-----------------------\n");
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente não encontrado.\n");
}

// Função para desfazer a última operação, com base no conteúdo da pilha
void desfazer(Stack *pilha, ListaCad *lista, Fila *fila) {
  if (pilha->topo == NULL) { // Verifica se há operações na pilha para desfazer
    printf("Não há operações para desfazer.\n");
    return;
  } // Verificar se a pilha está vazia

  Celula *ultimo = pilha->topo; // Obtém o topo da pilha
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

  // Realiza a operação de desfazer baseada no tipo de operação armazenado (qop)
  if (ultimo->qop ==
      0) { // qop == 0 indica um desenfileiramento, então enfileira
    enfileirar_no_inicio(nome, idade, RG, entrada, fila);
  } else if (ultimo->qop ==
             1) { // qop == 1 indica um enfileiramento, então desenfileira
    desinfileirar_do_fim(fila);
  }

  pop(pilha); // Remove o topo da pilha após desfazer a operação
}

// Função para atualizar informações de um cadastro específico pelo RG
void atualizar(ListaCad *lista, char *RG) {
  Cadastro *atual = lista->primeiro;
  while (atual != NULL) { // Percorre a lista de cadastros
    if (strcmp(atual->dados->RG, RG) == 0) {
      printf("-----------------------\n");
      printf("Escolha qual campo você deseja mudar\n");
      printf("1. Nome\n");
      printf("2. RG\n");
      printf("3. Data de Entrada\n");
      printf("4. Idade\n");
      int escolha;
      scanf("%d", &escolha); // Recebe a escolha do campo a ser atualizado
      clearBuffer();
      // Switch para modificar o campo escolhido pelo usuário
      switch (escolha) {
      case 1: { // Atualiza o nome
        char novoNome[100];
        printf("Digite o novo nome: ");
        fgets(novoNome, sizeof(novoNome), stdin);

        free(atual->dados->nome);
        atual->dados->nome = malloc(strlen(novoNome) + 1);
        strcpy(atual->dados->nome, novoNome);
        printf("Nome atualizado com sucesso!\n");
        break;
      }
      case 2: { // Atualiza o RG
        char novoRG[20];
        printf("Digite o novo RG: ");
        fgets(novoRG, sizeof(novoRG), stdin);

        free(atual->dados->RG);
        atual->dados->RG = malloc(strlen(novoRG) + 1);
        strcpy(atual->dados->RG, novoRG);
        printf("RG atualizado com sucesso!\n");
        break;
      }
      case 3: { // Atualiza a data de entrada
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
      case 4: { // Atualiza a idade
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

// funcao para remover o cadastro de algum paciente
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
    free(atual); // da free nas variaveis
    lista->qtde--;
  } else {
    printf("Paciente não encontrado para remoção.\n");
  }
}

// funcao para inserir na lista
void inserir(ListaCad *lista, char *nome, int idade, char *RG, Data *entrada) {
  Cadastro *novo =
      criar_cadastro(nome, idade, RG, entrada); // cria um novo cadastro
  Cadastro *atual = lista->primeiro; // cria um ponteiro atual para o primeiro
                                     // cadastro da lista
  Cadastro *anterior = NULL;         // declara que o ponteiro anterior e nulo

  if (lista->primeiro == NULL) { // se o primeiro for null
    lista->primeiro = novo;      // o novo cadastro sera o primeiro
    lista->qtde++;
  } else {
    while (atual != NULL && novo->dados->idade >= atual->dados->idade) {
      anterior = atual; // enquanto o atual nao for nulo e o novo for maior que
                        // o atual, o atual sera o anterior
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

// print do menu principal
void menu() {
  printf("-----------------------\n");
  printf("Escolha uma opção:\n");
  printf("1. Cadastrar\n");
  printf("2. Atendimento\n");
  printf("3. Pesquisar\n");
  printf("4. Desfazer\n");
  printf("5. Salvar\n");
  printf("6. Sobre\n");
  printf("0. Sair\n");
  printf("-----------------------\n");
  printf("\n");
  printf("Digite sua escolha: ");
}

// print do menu de cadastro
void print_cadatrar() {
  printf("Cadastro: \n");
  printf("\n");
  printf("------------------------\n");
  printf("Qual operacao deseja fazer ? \n");
  printf("1. Novo Paciente\n");
  printf("2. Consultar paciente cadastrado\n");
  printf("3. Mostrar lista completa\n");
  printf("4. Atualizar dados\n");
  printf("5. Remover paciente\n");
  printf("0. Sair\n");
  printf("------------------------\n");
  printf("\n");
  printf("Digite sua escolha: ");
}

// print do menu de atendimento
void print_atendimento() {
  printf("Atendimento: \n");
  printf("\n");
  printf("----------------------------------\n");
  printf("Qual operacao deseja fazer ? \n");
  printf("1. Enfileirar paciente\n");
  printf("2. Desinfileirar paciente\n");
  printf("3. Mostrar fila\n");
  printf("0. Sair\n");
  printf("-----------------------------------\n");
  printf("\n");
  printf("Digite sua escolha: ");
}

// print da funcao sobre
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

// print do menu pesquisa
void print_pesquisa() {
  printf("Pesquisar: \n");
  printf("------------------------------------------------\n");
  printf("Selecione qual operacao voce deseja realizar\n");
  printf("1. Registros ordenados por ano\n");
  printf("2. Registros ordenados por mes\n");
  printf("3. Registros ordenados por dia\n");
  printf("4. Registros ordenados por idade\n");
  printf("0. Sair\n");
  printf("------------------------------------------------\n");
}

// Função para salvar os cadastros em um arquivo
void salvarLista(ListaCad *lista) {
  FILE *arquivo =
      fopen("lista_cadastros.txt", "w"); // abre o arquivo para escrita
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para salvar.\n");
    return; // se o arquivo não abrir, retorna
  }
  Cadastro *atual = lista->primeiro; // inicializa o ponteiro atual com o
                                     // primeiro elemento da lista
  while (atual != NULL) {
    // Salvar os dados do cadastro no arquivo
    fprintf(arquivo, "%s;%d;%s;%d/%d/%d\n", atual->dados->nome,
            atual->dados->idade, atual->dados->RG, atual->dados->entrada->dia,
            atual->dados->entrada->mes, atual->dados->entrada->ano);
    atual = atual->proximo;
  }

  fclose(arquivo);
  printf("Lista salva com sucesso!\n");
  // finaliza o processo de salvamento
}

// Função para carregar os cadastros de um arquivo para o codigo
void carregarLista(ListaCad *lista) {
  FILE *arquivo = fopen("lista_cadastros.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para carregar.\n");
    return; // se o arquivo nao existir retorna
  }
  char nome[100], rg[20];
  int idade, dia, mes, ano; // variaveis para armazenar os dados lidos do
                            // arquivo
  while (fscanf(arquivo, "%99[^;];%d;%19[^;];%d/%d/%d\n", nome, &idade, rg,
                &dia, &mes, &ano) == 6) {
    // Alocar memória para os novos dados e cadastro
    Dados *dados = (Dados *)malloc(sizeof(Dados));
    Cadastro *novoCadastro = (Cadastro *)malloc(sizeof(Cadastro));

    if (dados == NULL || novoCadastro == NULL) {
      printf("Erro ao alocar memória.\n");
      fclose(arquivo);
      return;
    }

    dados->idade = idade;
    dados->nome = strdup(nome); // Usamos strdup para copiar a string
    dados->RG = strdup(rg);     // Usamos strdup para copiar a string
    dados->entrada = (Data *)malloc(sizeof(Data));
    if (dados->entrada == NULL) {
      printf("Erro ao alocar memória para a data.\n");
      fclose(arquivo);
      return;
    }
    dados->entrada->dia = dia;
    dados->entrada->mes = mes;
    dados->entrada->ano = ano;

    novoCadastro->dados = dados;
    novoCadastro->proximo = lista->primeiro;
    lista->primeiro = novoCadastro; // Inserção no início da lista
    lista->qtde++;                  // Aumenta a quantidade de cadastros
  }

  fclose(arquivo);
  printf("Lista carregada com sucesso!\n");
}

int main() {
  ListaCad *lista = criar_listaCad(); // declarando as variaveis e chama funcoes
                                      // necessarias nessa parte inicial da main
  int escolha;
  char nome[50], RG[20];
  int idade, dia, mes, ano;
  Fila *fila = criar_fila();
  Arvore *arvoredia = cria_arvore();
  Arvore *arvoremes = cria_arvore();
  Arvore *arvoreano = cria_arvore();
  Arvore *arvoreidade = cria_arvore();
  Stack *stack = criar_stack();
  carregarLista(lista);
  inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
  inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
  inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
  inserir_todos_na_arvore(
      lista, arvoreidade,
      inserir_arvore_idade); // para inserir os dados do arquivo
  // na arvore

  do {
    menu();
    scanf("%d", &escolha); // inicializa o switch case com o menu principal

    switch (escolha) {
      int subEscolha;

    case 1: // Menu e Submenu de cadastro
      do {
        print_cadatrar();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1: // Cadastro de um novo paciente
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
          scanf("%d", &ano); // Resgatou os dados necessarios para o cadastro,
                             // informados pelo usuario

          Data *entrada =
              malloc(sizeof(Data)); // aloca as datas inseridas pelo usuario
          entrada->dia = dia;
          entrada->mes = mes;
          entrada->ano = ano;

          inserir(lista, nome, idade, RG, entrada); // insere os dados na lista
          printf("Paciente cadastrado com sucesso!\n");
          printf("\n");

          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(
              lista, arvoreidade,
              inserir_arvore_idade); // insere os dados na arvore
          break;

        case 2: // caso de consultar um cadastro
          printf("Consultar cadastro \n");
          printf("Digite o RG do paciente: ");
          clearBuffer();
          fgets(RG, sizeof(RG),
                stdin); // pega o RG do paciente que deve ser buscado

          procurar(lista, RG); // procura o paciente
          break;

        case 3:
          mostrar(lista); // mostra todos os cadastros
          break;

        case 4: // caso para atualizar os dados de um cadastro
          printf("Digite o RG do paciente para atualizar: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);

          atualizar(lista, RG);
          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(lista, arvoreidade, inserir_arvore_idade);
          break; // insere e atualiza os dados na arvore

        case 5: // caso para remover um cadastro
          printf("Digite o RG do paciente para remover: ");
          clearBuffer();
          fgets(RG, sizeof(RG),
                stdin); // recebe o RG do paciente que deve ser removido
          remover(lista, RG);
          inserir_todos_na_arvore(lista, arvoredia, inserir_arvore_dia);
          inserir_todos_na_arvore(lista, arvoremes, inserir_arvore_mes);
          inserir_todos_na_arvore(lista, arvoreano, inserir_arvore_ano);
          inserir_todos_na_arvore(lista, arvoreidade, inserir_arvore_idade);
          break; // remove o paciente e atualiza a arvore

        case 0:
          printf("Saindo...\n");
          break;

        default:
          printf("Opção inválida\n");
          break;
        }
      } while (subEscolha != 0);
      break;

    case 2: // Menu de atendimento  e enfileiramento
      do {

        print_atendimento();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1: // enfileirar um paciente
          printf("Digite o RG do usuario para inseri-lo na fila: ");
          clearBuffer();
          fgets(RG, sizeof(RG), stdin);
          Cadastro *inserido = lista->primeiro;
          int found = 0;

          while (inserido != NULL) {
            if (strcmp(inserido->dados->RG, RG) == 0) {

              enfileirar(stack, inserido->dados->nome, inserido->dados->idade,
                         inserido->dados->RG, inserido->dados->entrada,
                         fila); // insere o paciente na fila
              printf("Paciente inserido na fila com sucesso!\n");
              found = 1;
              break;
            }
            inserido = inserido->proximo;
          }

          if (!found) {
            printf("RG não encontrado\n"); // caso nao encontre o RG retorna
          }
          break;

        case 2: // tira um paciente da fila
          printf("Desinfileirar paciente \n");
          desinfeirar(stack, fila);
          printf("Paciente desinfileirado com sucesso!\n");

          break;

        case 3: // mostra a fila na situacao atual
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
      do { // menu de pesquisa
        print_pesquisa();
        scanf("%d", &subEscolha);

        switch (subEscolha) {
        case 1:
          printf(
              "Mostrar registros ordenados por ano:\n"); // mostra os registros
                                                         // ordenados por ano
          in_ordem(arvoreano->raiz);

          break;

        case 2:
          printf(
              "Mostrar registros ordenados por mes:\n"); // mostra os registros
                                                         // ordenados por mes
          in_ordem(arvoremes->raiz);
          break;

        case 3:
          printf(
              "Mostrar registros ordenados por dia:\n"); // mostra os registros
                                                         // ordenados por dia
          in_ordem(arvoredia->raiz);
          break;

        case 4:
          printf("Mostrar registros ordenados por idade:\n"); // mostra os
                                                              // registros
                                                              // ordenados por
                                                              // idade
          in_ordem(arvoreidade->raiz);
          break;

        case 0:
          break;

        default:
          printf("Opção inválida\n");
          break;
        }
      } while (subEscolha != 0);
      break;

    case 4:
      printf("Desfazer: \n"); // desfaz a ultima operacao relacionada a filas
      desfazer(stack, lista, fila);

      break;

    case 5:
      printf("Salvar:\n"); // caso para salvar os cadastros num arquivo
      salvarLista(lista);
      break;

    case 6:
      print_Sobre(); // caso que mostra sobre os desenvolvedores do projeto
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
