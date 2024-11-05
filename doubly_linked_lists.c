#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct node no;

struct node{
    Item info;
    no *prox;
    no *ant;
};

typedef struct head cabeca;

struct head{
    int qtd_itens;
    no *prox;
    no *ultimo;
};

cabeca *criar(){
    cabeca *lista = malloc(sizeof(cabeca));
    lista->prox = NULL;
    lista->ultimo = NULL;
    lista->qtd_itens = 0;
    
    return lista; //lembra pelo tipo tenho que retornar algo
}

no *criar_no(Item x){
    no *novo = malloc(sizeof(no));
    novo->ant = NULL; //??????
    novo->prox = NULL;
    novo->info = x;
    
    return novo; //tenho que retornar algo
}

//em relação a esses retornos, como ficariam na main? a chamada dessas funções, no caso

int vazia(cabeca *lista){
    return(lista->prox==NULL);//1 se vazia, 0 se não
                              //é tipo o boolean
}

no *buscar(cabeca *lista, Item x){
    no *a;
    for(a=lista->prox; a && a->info!=x; a=a->prox);
    return a;
    //busca uma informação na lista, começando do começo (lista->prox)
    //e enquanto a info não for x, ou enquanto "a" - o que é essa segunda condição?
    //retorna a, mas e aí? e se não achar? retorna NULL pq chegou no final?
    //exatamente isso que eu pensava. retorna NULL se não encontrar, pq chegou no fim da
    //lista e a->prox = NULL
}

void inserir_inicio(cabeca *lista, no *elem){
    elem->ant = NULL;
    elem->prox = lista->prox;
    lista->prox = elem;
    if(elem->prox!=NULL) elem->prox->ant = elem;
    else lista->ultimo = elem;
    lista->qtd_itens++;
    //entendi tudo, faz muito sentido
}

void inserir_depois(cabeca *lista, no *ref, no *elem){
    elem->ant = ref; //CERTO, primeiro também
    elem->prox = ref->prox; //CERTO, segundo também
    /*
    ref->prox->ant=elem;
    ref->prox = elem;
    ela inverteu a ordem desses 2:
    */
    ref->prox = elem;
    //AH SIM, AÍ SÓ BASTA USAR elem->prox->ant, ao invés de ref->prox->ant
    //colocou num if também, pq?
    if(elem->prox!=NULL) elem->prox->ant = elem;
    //se elem->prox não for o último elemento
    //então o anterior desse próximo elemento é o próprio elemento
    //existe algo que mexe com o elem->prox? sim, a segunda linha
    //mas se for NULL não dá nada ali, só aponta pra NULL, o que não existe é NULL->ant
    else lista->ultimo = elem;
    lista->qtd_itens++;
}

void inserir_antes(cabeca *lista, no *ref, no *elem){
    elem->prox = ref;
    elem->ant = ref->ant;
    //MEXA SEMPRE PRIMEIRO NO ELEMENTO, PORQUE ESTOU SÓ CONECTANDO MESMO
    //NÃO ESTOU DESFAZENDO NADA
    //elem->prox->ant = elem; ?? posso simplificar como:
    ref->ant = elem;
    //elem->ant->prox = elem; COLOCO NUM IF - POR QUÊ?
    if(elem->ant!=NULL) //se o elemento anterior não for NULL;
                        //único caso em que isso acontece é no primeiro elemento
                        //então tá vendo se não tô inserindo antes do primeiro elemento
                        elem->ant->prox = elem; //TÁ CERTA A MINHA SINTAXE
    else lista->prox = elem; //caso contrário, estamos falando do primeiro elemento
    lista->qtd_itens++;
    //certinho
}

void insere_antes2(cabeca *lista, no *ref, no *elem){
    if(lista->prox == ref) //se a ref for o primeiro elemento
                           //ou seja, se estamos tentando inserir no início da lista
        return inserir_inicio(lista,elem);
    inserir_depois(lista, ref->ant, elem); //caso contrário, insere o elemento depois de ref->ant
    //ou seja (depois do elemento anterior à ref, no caso então, antes da ref)
}

void insere_fim(cabeca *lista, no *elem){
    /*    MEU RACIOCÍNIO:
    lista->ultimo->prox = elem;
    elem->prox = NULL; //2
    elem->ant = lista->ultimo; //1
    lista->ultimo = elem; //3
    lista->qtd_itens++;
    */
    elem->ant = lista->ultimo;
    elem->prox = NULL;
    lista->ultimo = elem;
    if(elem->ant) //se há um elemento antes de elem, isto é, se ele não é o primeiro
                  elem->ant->prox = elem; //o elemento depois do anterior ao elemento que estou inserindo
                                          //é o próprio elemento, intuitivo isso né. mas não veio pra mim
                                          //no caso, fiz lista->ultimo->prox = elem; não funciona isso?
                                          //FUNCIONA SIM! então posso usar "lista->ultimo->prox=elem"
                                          //mas preciso checar que não é o primeiro elemento
                                          //de praxe: checar casos das extremidades
    else //se essa inserção no final na verdade insere no começo
        lista->prox = elem; //intuitivo
    lista->qtd_itens++;
}

void insere_fim2(cabeca *lista, no *elem){
    if(vazia(lista))
        return inserir_inicio(lista,elem); //se a lista estiver vazia, inserção no final na vdd é no início
    inserir_depois(lista, lista->ultimo, elem); //ultimately é isso mesmo, insere dps do último
}

void remover_no(cabeca *lista, no *lixo){
    /*
    lixo->prox->ant = lixo->ant;
    lixo->ant->prox = lixo->prox;
    free(lixo);
    */
    if(lista->prox == lixo) //se quiser remover o primeiro nó
        lista->prox = lixo->prox; //segundo nó torna-se o primeiro nó, apontamos pela cabeça
    else lixo->ant->prox = lixo->prox; //caso contrário, o elemento anterior ao lixo tem como prox o elemento que vem depois do elemento lixo (lixo->prox)
    //essa verificação é importante, porque se for o primeiro elemento, lembra, seu ant aponta para NULL
    if(lista->ultimo == lixo) lista->ultimo = lixo->ant; //intuitivo
    //se o último elemento for o elemento a ser removido, então o último passa a ser o anterior ao último atual
    //e se não for o último?
    else lista->prox->ant = lixo->ant; //CORRETO, EXATAMENTE
    //o elemento anterior ao elemento seguinte ao que vai ser excluído tem que ser igual ao elemento anterior ao que vai ser excluído
    lista->qtd_itens--;
    //bastante intuitivo, desenhar e pensar nos casos extremos
}

//EXERCÍCIOS

int main()
{
    printf("Hello World");

    return 0;
}
