#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    long num_points = 10000000;
    long points_in_circle = 0;
    double x, y;
    double pi;
    srand(time(NULL));
    #pragma omp parallel private(x, y) reduction(+:points_in_circle)
    {
        #pragma omp for
        for (long i = 0; i < num_points; i++) {
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            if (x*x + y*y <= 1.0) {
                points_in_circle++;
            }
        }
    }
    pi = 4.0 * points_in_circle / num_points;

    printf("Estimated value of Pi: %f\n", pi);

    return 0;
}
