#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
//usado apra calcualr o tempo de execução
void calcula_tempo_execucao() {
    //armazena estatistica de recursos consumidos pelos processos
    struct rusage uso;
    // obtem informaçoes sobre o processo atual e armazena na variavel uso 
    if (getrusage(RUSAGE_SELF, &uso) != 0) {
        // imprimi mensagem de erro descrevendo o problema
        perror("Erro ao obter informações de uso");
        exit(1);
    }
    //calcula o tempo gasto no modo usuario, soma todo o tempo gasto e returna em microssegundos
    double tempo_usuario = uso.ru_utime.tv_sec + uso.ru_utime.tv_usec / 1e6;
    //calcula o tempo no modo sistema 
    double tempo_sistema = uso.ru_stime.tv_sec + uso.ru_stime.tv_usec / 1e6;
    // mostra os resultados separados e totais com 6 casas de precisão
    printf("Tempo de CPU em modo usuário: %.6f segundos\n", tempo_usuario);
    printf("Tempo de CPU em modo sistema: %.6f segundos\n", tempo_sistema);
    printf("Tempo total de CPU: %.6f segundos\n", tempo_usuario + tempo_sistema);
}
// gera valores aleatorios de 1-100
void gerar_vetor_aleatorio(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 101;  // Gera um número aleatório entre 0 e 100
    }
}
//função padrao do merge
void merge(int vetor[], int inicio, int meio, int fim) {

    int tamanho = fim - inicio + 1;
    //cria um vetor temporario
    int *temp = (int*) malloc(tamanho * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(1);
    }
    // mescla os valores
    int p1 = inicio, p2 = meio + 1;
    int fim1 = 0, fim2 = 0;
    for (int i = 0; i < tamanho; i++) {
        if (!fim1 && !fim2) {
            if (vetor[p1] < vetor[p2]) {
                temp[i] = vetor[p1++];
            } else {
                temp[i] = vetor[p2++];
            }
            if (p1 > meio) fim1 = 1;
            if (p2 > fim) fim2 = 1;
        } else {
            if (!fim1) {
                temp[i] = vetor[p1++];
            } else {
                temp[i] = vetor[p2++];
            }
        }
    }
    // Copia de volta para o vetor original
    memcpy(vetor + inicio, temp, tamanho * sizeof(int));  
    //libera o valor
    free(temp);
}
//mergesort, particiona o vetor
void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int main(int argc, char *argv[]) {
    // Verifica se o argumento foi passado
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <tamanho do vetor>\n", argv[0]);
        return 1;
    }

    // Converte o argumento para inteiro
    int n = atoi(argv[1]);

    // Verifica se o tamanho do vetor é válido
    if (n <= 0) {
        fprintf(stderr, "O tamanho do vetor deve ser maior que zero.\n");
        return 1;
    }

    // cria um vetor com o tamanho alocado
    int *vetor = (int*) malloc(n * sizeof(int));
    // verifica se a alocação não funcionou
    if (vetor == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return 1;
    }

    // gera os números aleatoriamente
    srand(time(NULL));
    gerar_vetor_aleatorio(vetor, n);

    // chama o merge sort 
    mergeSort(vetor, 0, n - 1);

    // (opcional) imprime o vetor ordenado
    /*
    printf("Vetor ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    */

    // libera a memória alocada
    free(vetor);
    calcula_tempo_execucao();
    return 0;
}
