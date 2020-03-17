#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ERROR "Erro ao alocar memoria !" 
#define ID_NOT_FOUNDED "Elemento nao encontrado !"

typedef struct lista {   
    int id;
    struct lista* prox;
} Lista;

/**
 * Função de inicialização.
 * @param Lista* l, referência para lista.
 * @return void.
*/
void inicializa (Lista** l){ (*l) = NULL; }

/**
 * Função para informar tamanho de lista.
 * @param Lista* l, referência para lista.
 * @return inteiro contendo tamanho da lista.
*/
int listaEncadeadaTamanho(Lista* l) {
    if(l != NULL) {
		
		int tam = 0;
		Lista* i = l;

		while(i->prox != NULL) {
			tam++;
			i = i->prox;
		}
		
		return tam;
    }
    return 0;
}

/**
 * Função de inserção, insere no início da lista.
 * @param Lista** l, referência para lista.
 * @param id valor a ser inserido.
 * @return inteiro informando se a operação foi realizada com sucesso.
*/
int insereInicio (Lista** l, int id){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if(novo != NULL) {
        novo->id = id;
        novo->prox = *l;
        *l = novo;
        return 1;
    } else {
        return 0;
    }
}

/**
 * Função de inserção, insere entre após um número informado da lista.
 * @param Lista** l, referência para lista.
 * @param n_pos número como referência para inserção.
 * @return inteiro informando se a operação foi realizada com sucesso.
*/
int insereApos(Lista **l, int pos_id, int id) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if(novo != NULL) {
        novo->id = id;
        novo->prox = NULL;
        
        // se lista estiver vazia
        if(listaEncadeadaTamanho((*l)) == 0 ) {
            (*l) = novo;
        } else {
            // recebendo 1º elemento
            Lista* i = (*l);
            // percorrendo array ate achar última posição
            while (1)
            {
                if(i->id == pos_id) {
                    Lista* aux = i->prox;
                    i->prox = novo;
                    novo->prox = aux;
                    return 1;
                } else if(i->prox == NULL) {
                    return 2;
                } else {
                    i = i->prox;
                }
            }
            i->prox = novo;
            return 1;
        }
    }
    return 0;
}

/**
 * Função de inserção, insere no fim da lista.
 * @param Lista** l, referência para lista.
 * @param id valor a ser inserido.
 * @return inteiro informando se a operação foi realizada com sucesso.
*/
int insereFinal (Lista** l, int id){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if(novo != NULL) {
        novo->id = id;
        novo->prox = NULL;
        
        // se lista estiver vazia
        if(listaEncadeadaTamanho((*l)) == 0 ) {
            (*l) = novo;
        } else {
            // recebendo 1 elemento
            Lista* i = (*l);
            // percorrendo array ate achar utlima posicao
            while (i->prox != NULL) { i = i->prox; }
            i->prox = novo;
        }
        return 1;
    } else {
        return 0;
    }    
}

/**
 * Função de impressão, imprime toda a lista.
 * @param Lista* l, referência para lista.
 * @return void;
*/
void imprime (Lista* l){
    while(l != NULL) {
		if(l->prox != NULL)	{
			printf("%d, ", l->id);
		} else {
			printf("%d. ", l->id);
		}
		l = l->prox;
	}
	printf("\n");
}

/**
 * Função de impressão, imprime toda a lista recursivamente.
 * @param Lista* l, referência para lista.
 * @return void;
*/
void imprimeRecursivo (Lista* l){
    if (l == NULL) printf("\n");
    else {
		if(l->prox != NULL)	{
			printf("%d, ", l->id);
		} else {
			printf("%d. ", l->id);
		}
        return imprimeRecursivo(l->prox);
    }
}

/**
 * Função de busca, busca um elemento da lista.
 * @param Lista* l, referência para lista.
 * @param id id a ser pesquisado.
 * @return Lista* l.
*/
Lista* busca (Lista* l, int id){   
    Lista* i;   
    while(i != NULL) {
		if ( i->id == id ) {
			i = NULL;
			return i;
		}
		i = i->prox;
	}
    return l;
}

/**
 * Função de busca, busca um elemento da lista recursivamente.
 * @param Lista* l, referência para lista.
 * @param id id a ser pesquisado.
 * @return Lista* l.
*/
Lista* buscaRecursiva(Lista* l, int id) {
    return (l->id == id) ? (
        l
    ) : (l == NULL) ? (
        l
    ) : ( buscaRecursiva(l->prox, id) );
}

/**
 * Função de remoção, remove um determinado elemento da lista.
 * @param Lista** l, referência para lista.
 * @param id id a ser pesquisado.
 * @return 0, 1.
*/
int retira (Lista** l, int id) {   
    Lista* ant = NULL; /* ponteiro para elemento anterior */
    Lista* i = (*l);   /* ponteiro para percorrer a lista*/   
    
    while (i != NULL && i->id != id) {      
        ant = i;      
        i = i->prox;   
    }   
    
    if (i == NULL) return 0;
       
    if (ant == NULL) {      
        (*l) = i->prox;   
    } else {
        ant->prox = i->prox;   
    }   
    free(i);   
    return 1;
}


/**
 * Função libera, libera lista encadeada da memória.
 * @param Lista** l, referência para lista.
 * @return void.
*/
void libera (Lista** l) {
    if((*l) != NULL) {
		while ((*l) != NULL) {
			free((*l));
			(*l) = (*l)->prox;
		}
    }
}

int main (void) {   
    Lista* l;

    inicializa(&l);  
    printf("Tamanho lista: %d\n", listaEncadeadaTamanho(l));
    printf("%s", insereInicio(&l, 24) == 1 ? ("") : (MEMORY_ERROR));
    printf("%s", insereInicio(&l, 23) == 1 ? ("") : (MEMORY_ERROR));
    printf("%s", insereFinal(&l, 26) == 1 ? ("") : (MEMORY_ERROR));

    int insert = insereApos(&l, 30, 25);
    if( insert == 0) {
        printf("%s \n", MEMORY_ERROR);
    }
    if( insert == 2) {
        printf("%s \n", ID_NOT_FOUNDED);
        insereApos(&l, 24, 25);
    }

    printf("Imprime: ");
    imprime(l);
    printf("Imprime recursivo: ");
    imprimeRecursivo(l);
    printf("Tamanho lista: %d\n", listaEncadeadaTamanho(l));
    
    if( busca(l, 24) == NULL) printf("Elemento não encontrado");
    else printf("Busca: %d \n", busca(l, 24)->id);

    if( buscaRecursiva(l, 24) == NULL ) printf("Elemento não encontrado");
    else printf("Busca recursiva: %d \n", buscaRecursiva(l, 24)->id);

    retira(&l, 24);
    
    printf("Imprime recursivo: ");
    imprimeRecursivo(l);
    
    libera(&l);
    printf("Tamanho lista: %d\n", listaEncadeadaTamanho(l));
    
    return 0;
}
