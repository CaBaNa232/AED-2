#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// TRABALHO 1 DE ALGORITMOS E ESTRUTURAS DE DADOS 2
//Informacoes do estudante
// Nome: Joao Pedro Pereira
// Curso: BCC
// RA: 769714

typedef struct no No;
 
//Definicao da estrutura
struct no { 
	char nome[20];
	int telefone;
	No *pai;
	No *dir;
	No *esq;
};

//Ponteiro para Arvore
typedef No *Arvore; 

//Desaloca a Arvore
void libera_contatos (Arvore h) {
	
	if (h == NULL){
		libera_contatos (h->esq = NULL);
		libera_contatos (h->dir = NULL);
		free(h);
	}
}

//Busca um contato por nome
No *Busca_contato (Arvore h, char *nome) { 

	if (h == NULL) {
		return h;
	}
	if (strcmp(h->nome, nome) == 0) {
		return h;
	}
	if (strcmp(nome, h->nome) < 0) {
		return Busca_contato (h->esq, nome);	
	}

	return Busca_contato (h->dir, nome);
}

//Cria um novo no para um novo contato
No *Cria_contato (int tel, char *nome) {
	
	No *new_contato = (No *)malloc(sizeof(No));
	strcpy(&(new_contato->nome[0]), nome);
	new_contato->telefone = tel ;
	new_contato->esq = NULL ;
	new_contato->dir = NULL ;
	new_contato->pai = NULL ; 
	 
	return new_contato;
}

//Insere um novo contato na arvore
Arvore Insere_contato(Arvore h, No *novo){ 

	if (h == NULL) {
		return novo;	
	} 
	if (strcmp(novo->nome, h->nome) < 0) {
		h->esq = Insere_contato (h->esq, novo);
		h-> esq->pai = h; 
	}
	else {
		h->dir = Insere_contato (h->dir, novo);
		h->dir->pai = h; 
	}
		return h;
	}

No *TSmax (No *h) {
	while (h->dir != NULL) {
		h = h->dir;
	}
	return h;
}

//Remove um no da arvore
Arvore Remove_raiz (Arvore valor) { 
	No *aux, *p;
	
	if (valor->esq == NULL && valor->dir == NULL) { 
		valor->telefone = 0;
		strcpy (valor->nome, "");
		free (valor);
		return NULL;
	}

	if (valor->esq == NULL || valor->dir == NULL) { 
		if (valor->esq == NULL) {
			aux = valor->dir;
		} else {
			aux = valor->esq;
		}

		aux->pai = valor->pai; 
		valor->telefone = 0;
		strcpy (valor->nome, "");
		free (valor);
		
		return aux;
	}
	
	aux = TSmax(valor->esq);
	valor->telefone = aux->telefone;	
	strcpy(valor->nome, aux->nome);
	p = aux->pai ;
	
	if (p == valor){
		p->esq = Remove_raiz (aux);
	}
	else{
		p->dir = Remove_raiz (aux);
	}

	return valor;
}	

//Busca por um nome e remove
No *Remove_nome (Arvore h, char *nome) { 

    No *valor, *p, *aux;
    valor = Busca_contato (h, nome);
    if (valor == NULL) {
    	return h;
	}
    p = valor->pai;
    aux = Remove_raiz (valor);
    if (p == NULL) {
    	return aux;
	} 
    if (p->esq == valor) {
    	p->esq = aux;
	}
    if (p->dir == valor) {
    	p->dir = aux;
	} 
    return h;
}

int main()
{	
	
	Arvore raiz = NULL;
	//No auxiliar
	No *buscou;
	//Declaracoes locais
	char op;
	char *nome = (char *)malloc(sizeof(char) * 20);
	int tel;

	while(scanf("%c", &op) != EOF) {
		
		switch (op) {
			
			//Insere contato
			case 'I': 
			
				scanf("%s", nome);
				scanf("%d\r", &tel);

				buscou = Busca_contato (raiz, nome);
				if (buscou == NULL) {
					raiz = Insere_contato(raiz, Cria_contato(tel, nome));
				}else {
					printf("Contatinho ja inserido\n");
				}
				break;	
				
			//Pesquisa contato	
			case 'P': 
			
				scanf("%s\r", nome);
				buscou = Busca_contato (raiz, nome);
				if (buscou == NULL) {
					printf("Contatinho nao encontrado\n");
				}else {
					printf("Contatinho encontrado: telefone %d\n", buscou->telefone);
				}
				break;
			
			//Remove contato		
			case 'R': 
			
				scanf("%s\r", nome);
				buscou = Busca_contato (raiz, nome);
				if (buscou == NULL) {
					printf("Operacao invalida: contatinho nao encontrado\n");
				}else {
					raiz = Remove_nome (raiz, nome);
				}
				break;	
					
			case 'A': 
				scanf("%s", nome);
				scanf("%d\r", &tel);
				// printf("-%s %d-\n", nome, tel);

				buscou = Busca_contato (raiz, nome);
				if (buscou == NULL) {
					printf("Operacao invalida: contatinho nao encontrado\n");
				}else {
					buscou->telefone = tel;
				}
				
				break;	
		}
	}
	

    return 0;
}

