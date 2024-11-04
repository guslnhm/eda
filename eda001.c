#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct node no;
struct node{
    Item info;
    no *prox;
};
typedef struct head cabeca;
struct head{
    int qtd_itens;
    no *prox;
    no *ultimo;
}; //Lembrar que a cabeça representa a lista! Então no *prox é o primeiro elemento

void contar_num_cels_lista(cabeca *lista);
void concatenar_listas(cabeca *lista1, cabeca *lista2);
void insere_x_apos_k_esima_celula(cabeca *lista, int x, int index);
void swap_cells(cabeca *lista, no *a, no *b);

int main(){
    printf("teste");
    return 0;
}

void contar_num_cels_lista(cabeca *lista){
    printf("Número de células na lista: %d\n",lista->qtd_itens);
}

void concatenar_listas(cabeca *lista1, cabeca *lista2){
    /*
    linkar lista1->ultimo->prox à lista2->prox
    excluir lista2, liberar espaço da memória
    e fazer lista1->ultimo = lista2->ultimo
    */
   /*if(lista2->prox){ //verificação pra ver se lista2 está vazia
    lista1->qtd_itens += lista2->qtd_itens; //atualizei!!
    lista1->ultimo->prox = lista2->prox;
    lista1->ultimo = lista2->ultimo;
    free(lista2);
   }
   else return;*///se lista2 estiver vazia, n faço nada
   /*
   e se lista1 estiver vazia?
   atualizar quantidade total de itens!
   e se lista2 estiver vazia?
   */
  
  //VERIFICAÇÃO MAIS ELEGANTE ABAIXO:
  
    if(lista2->prox==NULL || lista2->qtd_itens==0) return;
    //e a verificação se lista1 está vazia?
    if(lista1->prox==NULL || lista1->qtd_itens==0){
        lista1->qtd_itens = lista2->qtd_itens;
        lista1->prox = lista2->prox;
        lista1->ultimo = lista2->ultimo;
        free(lista2);
        return; //!!!!
    }
    lista1->qtd_itens += lista2->qtd_itens; //atualizei!!
    lista1->ultimo->prox = lista2->prox;
    lista1->ultimo = lista2->ultimo;
    free(lista2);
}

void insere_x_apos_k_esima_celula(cabeca *lista, int x, int index){
    no *a;
    no *new = malloc(sizeof(no)); //ALOCAR MEMÓRIA PARA O NOVO NÓ!! IMPORTANTE
    int i=0;
    new->info = x;
    /*for(a=lista->prox; a!=index && a!=NULL; a=a->prox);
    if(a==NULL) return;
    new->prox = a->prox;
    a->prox = new;*/
    //se index for 0
    if(lista->prox==NULL && lista->qtd_itens==0){
        lista->qtd_itens++;
        lista->prox = new;
        new->prox = NULL;
        lista->ultimo = new; //ÚLTIMO NÓ VAI SER O ÚNICO NÓ!!
        return;
    }
    for(a=lista->prox; i!=index && a!=NULL; a=a->prox, i++);
    if(a==NULL){
        free(new); //SE NÃO HOUVER O INDEX ESPECIFICADO, LIBERA A MEMÓRIA RESERVADA!!
        return;
    } //rodou a lista toda e não tem a tal k-ésima celula
    //e se k for o último item?
    if(lista->ultimo==a){
        a->prox=new;
        new->prox=NULL;
        lista->ultimo=new;
        lista->qtd_itens++;
        return;
    }
    //e se k for o primeiro item? índice 0? no caso então lista vazia - COLOCAR VERIFICAÇÃO LÁ PRA CIMA
    new->prox = a->prox;
    a->prox = new;
    lista->qtd_itens++;
}

void swap_cells(cabeca *lista, no *a, no *b){
    // a_anterior->prox = b
    // b_anterior->prox = a
    // a->prox = b->prox
    // b-> prox = a->prox
    /*no *ant_a, *ant_b;
    for(ant_a=lista->prox; a!=NULL && ant_a->prox!=a; ant_a=ant_a->prox);
    for(ant_b=lista->prox; b!=NULL && ant_b->prox!=b; ant_b=ant_b->prox);
    a->prox = b->prox;
    b->prox = ant_a->prox->prox;*/
    no *t, *ant_a, *ant_b;
    for(ant_a=lista->prox; a!=NULL && ant_a->prox!=a; ant_a=ant_a->prox);
    for(ant_b=lista->prox; b!=NULL && ant_b->prox!=b; ant_b=ant_b->prox);
}