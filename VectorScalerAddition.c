#include <stdio.h>
#include <omp.h>
#include <stdlib.h> 
#include <time.h>

int main() {
    int n = 200000;  
    float scalar = 5.5;  
    float *vector;
    vector = (float *)malloc(n * sizeof(float));
    if (vector == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    clock_t start_time_seq = clock();
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }
    clock_t end_time_seq = clock();
     
    double Tseq = (double)(end_time_seq - start_time_seq) / CLOCKS_PER_SEC;
    
    printf("Sequential Execution Time: %f seconds\n", Tseq);

    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }
    double start_time_par = omp_get_wtime();  
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }
    double end_time_par = omp_get_wtime();  
    double Tparallel = end_time_par - start_time_par;
    printf("Parallel Execution Time: %f seconds\n", Tparallel);
    double speedup = Tseq / Tparallel;
    printf("Speedup: %f\n", speedup);
    printf("First 20 Elements of the vector after addition:\n");
    for (int i = 0; i < 20; i++) {
        printf("%f ", vector[i]);
    }
    printf("\n");

    free(vector);
    return 0;
}
