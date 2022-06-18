#include<stdio.h>
#include<stdlib.h>
#define int_max 10000


// TRABALHO 3 DE ALGORITMOS E ESTRUTURAS DE DADOS 2
//Informacoes do estudante
// Nome: Joao Pedro Pereira
// Curso: BCC
// RA: 769714

//Recebe como entrada dois inteiros x e y, decide qual o maior e retorna m
int minimo(int x, int y) {

	int m;

	if(x < y) {
		m = x;
	}else{
		m = y;
	}
	return m;
}

void menor_distancia(int **ma, int v) {

	int i, j, k; 

	  for(k = 0; k < v; k++) {
		for(i = 0; i < v; i++) {
			for(j = 0; j < v; j++) {
				if(ma[i][j] > ma[i][k] + ma[k][j]) {
					ma[i][j] = ma[i][k] + ma[k][j];
				} 
			}             
		}   
	}
}

int main()
{
	int vets, ares, **grafo;
	int in_vet, out_vet, peso_are; 
	int i, j;

	//Recebe o número de vértice e arestas 
	scanf("%d %d", &vets, &ares);
   
	//Aloca o grafo
	grafo = (int **) malloc(vets * sizeof(int *));

	//Aloca os vértices do grafo
	for(i = 0; i < vets; i++){
		grafo[i] = (int *) malloc(vets* sizeof(int));
	}
		
	//Inicializa os vértices do grafo com 0
	for(i = 0; i < vets; i++) {
		for(j = 0; j < vets; j++) {
			grafo[i][j] = int_max;
		}
	}

	for(i = 0; i < vets; i++) {
		grafo[i][i] = 0;
	}

	//Inicia os vértices com os vértices de entrada, vértices de saída e o peso da aresta      
	for(i = 0; i < ares; i++) {
		scanf("%d %d %d", &in_vet, &out_vet, &peso_are);
		grafo[in_vet][out_vet] = minimo(grafo[in_vet][out_vet], peso_are);
	}

	menor_distancia(grafo, vets);

	printf("%d", grafo[0][vets - 1]);

	return 0;
}

