#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
//usado apra calcualr o tempo de execução
void tempoExecucao() {
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
void vetorAleatorio(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 101;  // Gera um número aleatório entre 0 e 100
    }
}
//mergesort interativo baseada em artigos
void merge(int vetor[], int inicio, int meio, int fim) {
    // calcula o tamanho das duas metades do vetor a ser mesclado
    int valor1 = meio - inicio + 1;
    int valor2 = fim - (meio + 1) + 1;

    // cria vetores temporarios
    int* vault1 = (int*)malloc(valor1 * sizeof(int));
    int* vault2 = (int*)malloc(valor2 * sizeof(int));

    // verifica se a alocação funcionou
    if (vault1 == NULL || vault2 == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os vetores temporários.\n");
        exit(1);
    }

    // copia a primeira metadeda dovetor
    memcpy(vault1, &vetor[inicio], valor1 * sizeof(int));

    // copaia a segunda metade do vetor
    memcpy(vault2, &vetor[meio + 1], valor2 * sizeof(int));

    // inicializa os indices
    int i = 0, j = 0, k = inicio;

    //mesclas o vetores e salva no vetor original seguindo a ordem de crescente
    while (i < valor1 && j < valor2) {
        //se vt1 for menor q vt2 entao é salva no vetor original
        if (vault1[i] <= vault2[j]) {
            vetor[k] = vault1[i];
            i++;
        } 
        else {
            vetor[k] = vault2[j];
            j++;
        }
        k++;
    }

    // Se ainda houver elementos em vt2 coloca noo vetor original
    while (j < valor2) {
        vetor[k] = vault2[j];
        j++;
        k++;
    }
    // Se ainda houver elementos em vt1 coloca no vetor original
    while (i < valor1) {
        vetor[k] = vault1[i];
        i++;
        k++;
    }
    // lebra a memria alocada para os vetores temporários
    free(vault1);
    free(vault2);
}

// merge sort, mescla os valores
void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
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
    vetorAleatorio(vetor, n);
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
    tempoExecucao();
    return 0;
}