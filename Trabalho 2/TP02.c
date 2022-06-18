#include<stdio.h>
#include<stdlib.h>
#define MAX 100

// TRABALHO 2 DE ALGORITMOS E ESTRUTURAS DE DADOS 2
//Informacoes do estudante
// Nome: Joao Pedro Pereira
// Curso: BCC
// RA: 769714


double sepera_vetor (int ini, int end, double*vet) { //Separa o veotr em sub-vetores
	double a, b;
    int i, j;
	a = vet[end];
	j = ini;
	for (i = ini; i < end; i++) {
		if (vet[i] <= a) {
			b = vet[j];
			vet[j] = vet[i];
			vet[i] = b;
			j++;
		}
	}
	vet[end] = vet[j];
	vet[j] = a;
	return j;
}

void Quicksort (int k, int ini, int end, double *vet) { //Ordena o vetor em ordem crescente
    int i;
    if(ini < end) {
        i = sepera_vetor (ini, end, vet);
        if (k < i) {
            Quicksort (k, ini, i - 1, vet);
        }else {
            Quicksort (k, i + 1, end, vet);
        }
          
    }
}

int main(int argc, char *argv[])
{
    char file_name[MAX];

    double **v, limiar;
    int n, k, i, j;
    int outlier = 0;
    FILE *entrada;

    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(entrada, "%d %d %lf", &n, &k, &limiar);
    v = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        v[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++)
            fscanf(entrada, "%lf", &v[i][j]);
    }
    fclose(entrada);

    for(i = 0; i < n; i++) {
        Quicksort (k, 0, n - 1, v[i]);
        if (v[i][k + 1] > limiar) {
        	outlier++;
		}
        
    }
	
	printf("%d", outlier);
    free(v);
    
    return 0;
}

