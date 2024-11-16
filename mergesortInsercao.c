#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

// Usado para calcular o tempo de execução
void tempoExecucao() {
    struct rusage uso;
    if (getrusage(RUSAGE_SELF, &uso) != 0) {
        perror("Erro ao obter informações de uso");
        exit(1);
    }
    double tempo_usuario = uso.ru_utime.tv_sec + uso.ru_utime.tv_usec / 1e6;
    double tempo_sistema = uso.ru_stime.tv_sec + uso.ru_stime.tv_usec / 1e6;
    printf("Tempo de CPU em modo usuário: %.6f segundos\n", tempo_usuario);
    printf("Tempo de CPU em modo sistema: %.6f segundos\n", tempo_sistema);
    printf("Tempo total de CPU: %.6f segundos\n", tempo_usuario + tempo_sistema);
}

// Gera valores aleatórios de 1-100
void vetorAleatorio(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 101;  // Gera um número aleatório entre 0 e 100
    }
}

// Função de Insertion Sort
void insertionSort(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

// Função Merge para juntar dois vetores
void merge(int vetor[], int esq[], int dir[], int meio, int fim) {
    int i = 0, j = 0, k = 0;
    int leftSize = meio;
    int rightSize = fim - meio;

    while (i < leftSize && j < rightSize) {
        if (esq[i] <= dir[j]) {
            vetor[k] = esq[i];
            i++;
        } else {
            vetor[k] = dir[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        vetor[k] = esq[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        vetor[k] = dir[j];
        j++;
        k++;
    }
}

// Função Merge Sort com Insertion Sort para partições menores ou iguais a m
void mergeSort(int vetor[], int tamanho, int m) {
    if (tamanho <= m) {
        insertionSort(vetor, tamanho);
        return;
    }

    int meio = tamanho / 2;
    int* esq = (int*)malloc(meio * sizeof(int));
    int* dir = (int*)malloc((tamanho - meio) * sizeof(int));

    memcpy(esq, vetor, meio * sizeof(int));  // Copia a parte esquerda
    memcpy(dir, &vetor[meio], (tamanho - meio) * sizeof(int));  // Copia a parte direita

    mergeSort(esq, meio, m);
    mergeSort(dir, tamanho - meio, m);
    merge(vetor, esq, dir, meio, tamanho);

    free(esq); // Libera memória alocada
    free(dir); // Libera memória alocada
}

// Função para imprimir o vetor
void printArray(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}


// Função principal
int main(int argc, char *argv[]) {
    int m = atoi(argv[1]); // Converte o argumento para um inteiro (m)
    int tamanho = atoi(argv[2]); // Converte o argumento para o tamanho do vetor
    int vetor[tamanho]; // Cria o vetor com o tamanho especificado
    vetorAleatorio(vetor, tamanho); // Gera números aleatórios no vetor
    mergeSort(vetor, tamanho, m); // Chama o MergeSort modificado com limite m
    tempoExecucao();  // Exibe o tempo de execução
    return 0;
}