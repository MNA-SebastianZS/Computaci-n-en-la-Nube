#include <stdio.h>    /
#include <stdlib.h>   
#include <time.h>    
#include <omp.h>      // OpenMP: omp_get_thread_num, omp_get_num_threads

int main(void)
{
    // Cantidad de elementos (se usaran mil para aprovechar el paralelismo de operaciones)
    int N = 1000;
    int* A = NULL, * B = NULL, * R = NULL;

    // 1) Reservar memoria dinámica para los arreglos
    A = (int*)malloc(N * sizeof(int));
    B = (int*)malloc(N * sizeof(int));
    R = (int*)malloc(N * sizeof(int));

    if (A == NULL || B == NULL || R == NULL) {
        printf("Error: no se pudo reservar memoria.\n");
        return 1;
    }

    // 2) Inicializar semilla para números aleatorios usando la función srand
    srand((unsigned)time(NULL));

    // 3) Llenar A y B con valores aleatorios (0 a 99) para que no haga sumas muy grandes 
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // 4) Suma paralela: cada hilo toma una parte del arreglo
    //    'parallel for' divide automáticamente el rango del for entre hilos

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        R[i] = A[i] + B[i];
    }

    // 5) Mostrar parte del resultado para comprobar (primeros 20)
    printf("Mostrando primeros 20 elementos:\n");
    printf(" i |  A  |  B  |  R=A+B\n");
    printf("------------------------\n");
    for (int i = 0; i < 20; i++) {
        printf("%2d | %3d | %3d | %3d\n", i, A[i], B[i], R[i]);
    }

    // 6) Liberar memoria
    free(A);
    free(B);
    free(R);

    return 0;
}
