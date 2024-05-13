/* PROJETO 2 - PROJETO DE ANÁLISE DE ALGORITMOS II
    INTEGRANTES: 

        - Gustavo Garabetti Munhoz      |   10409258

    LINK PARA VÍDEO DO YT: https://www.youtube.com/watch?v=_iqIGdFhdPg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 200     // Comprimento máximo do nome dos centros

int CENTRO_INICIAL = 1;

int min(int a, int b){
    if(a < b) return a;
    return b;
}

int main() {
    // Rotas até os arquivos de entrada e saída
    FILE *input = fopen("./entrada.txt", "r"), *output = fopen("./saida.txt", "w");

    int n, k;
    fscanf(input, "%d %d\n", &n, &k);

    char **predio = (char**)calloc(n+1, sizeof(char *));
    for (int i = 1; i <= n; i++) *(predio + i) = (char *)calloc(MAX_LEN, sizeof(char));

    for (int i = 1; i <= n; i++) {
        fgets(*(predio + i), MAX_LEN * sizeof(char), input);
        *(*(predio + i)+(int)strlen(*(predio + i)) - 1) = '\0';
    }

    // Matriz de adjascência do grafo ponderado que contém as distâncias entre os prédios
    int **grafo = (int**)calloc(n+1, sizeof(int*));
    for (int i = 1; i <= n; i++) *(grafo+i) = (int*)calloc(n+1, sizeof(int));

    int m;
    fscanf(input, "%d\n", &m);

    // Lendo cada aresta
    for(int i = 0; i < m; i++){
        int u, v, d;
        fscanf(input, "%d %d %d\n", &u, &v, &d);
        grafo[u][v] = d;    // O grafo é simples e bidirecionado
        grafo[v][u] = d;
    }

    // Comente as duas linhas abaixo pra obter o resultado esperado no exemplo do descritivo
    srand(time(NULL));
    CENTRO_INICIAL = rand() % n + 1;

    // Vetor que guarda se cada prédio é centro (0 se não, 1 se sim)
    int *predio_eh_centro = (int*)calloc(n+1, sizeof(int));
    predio_eh_centro[CENTRO_INICIAL] = 1;
    int *centro = (int*)calloc(k, sizeof(int));
    centro[0] = CENTRO_INICIAL;

    for(int i = 1; i < k; i++){
        int max_dist = 0, centro_atual = 1;
        for(int j = 1; j <= n; j++){
            if(predio_eh_centro[j]) continue;   // Se o prédio atual já for centro, não faz sentido revisitá-lo
            int min_dist_local = grafo[j][centro[0]];
            // Para cada prédio restante, buscamos o centro mais próximo
            for(int l = 1; l < i; l++) min_dist_local = min(min_dist_local, grafo[j][centro[l]]);
            if(min_dist_local > max_dist){  // Se a menor distância for maior que as distâncias anteriores, o prédio que a originou será um novo centro
                max_dist = min_dist_local;
                centro_atual = j;
            }
        }
        centro[i] = centro_atual;   // Guardo ele como novo centro
        predio_eh_centro[centro_atual] = 1; // Vetor de índices é marcado também
    }

    for(int i = 0; i < k; i++) fprintf(output, "%s\n", predio[centro[i]]);  // Os k-centros vão pro arquivo de saída

    return 0;
}