#include <stdio.h>
#include <omp.h>
static long num_steps = 1000000;
double step;
int main() {
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    double start_time_seq = omp_get_wtime();  
    sum = 0.0;
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    double end_time_seq = omp_get_wtime();  
    double Tseq = end_time_seq - start_time_seq;
    printf("Sequential Execution:\n");
    printf("Calculated Pi = %.15f\n", pi);
    printf("Time taken: %f seconds\n\n", Tseq);
    double start_time_par = omp_get_wtime();  
    sum = 0.0;
    #pragma omp parallel for private(x) reduction(+:sum) num_threads(4)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    double end_time_par = omp_get_wtime();  
    double Tparallel = end_time_par - start_time_par;
    printf("Parallel Execution:\n");
    printf("Calculated Pi = %.15f\n", pi);
    printf("Time taken: %f seconds\n", Tparallel);

    double speedup = Tseq / Tparallel;
    printf("\nSpeedup: %f\n", speedup);

    return 0;
}
