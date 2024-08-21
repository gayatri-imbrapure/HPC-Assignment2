#include <stdio.h>
#include <omp.h>
#include <stdlib.h> 

int main() {
    int n = 1000000;  
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

    
    double start_time = omp_get_wtime();  // 

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }

    double end_time = omp_get_wtime();  
    printf("Execution Time: %f seconds\n", end_time - start_time);


    printf("First 20 Elements of the vector after addition:\n");
    for (int i = 0; i < 20; i++) {
        printf("%f ", vector[i]);
    }
    printf("\n");


    free(vector);

    return 0;
}
