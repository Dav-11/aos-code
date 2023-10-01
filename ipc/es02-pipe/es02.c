#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include <unistd.h>
#include <fcntl.h>


#define MAX 12
#define MIN 1
#define COMPUTE_PER_PRC 4

double base_compute(int n) {

    double res = 0.0;
    res = pow(1.5, (double) n );

    return res;
}

void prc_compute(int min, int max, int *file_descriptor) {

    // close reading end
    close(file_descriptor[0]);

    for (int n = min; n <= max; n++) {
        
        double res = base_compute(n);

        printf("[child] (1.5)^%d = %f\n", n, res);
        
        // send to pipe
        write(file_descriptor[1], &res, sizeof(res));
    }

    // close writing end
    close(file_descriptor[1]);
    exit(0);
}

int main() {

    int prc_number = ceil(MAX/COMPUTE_PER_PRC);
    double sum = 0.0;

    // create pipe
    int file_descriptor[2];
    pipe(file_descriptor);

    // spawn children
    for (int prc = 0; prc < prc_number; prc++) {
        
        // compute range
        int min = MIN + prc * COMPUTE_PER_PRC;
        int max = (min + COMPUTE_PER_PRC) - 1;

        int res = fork();
        
        // if child exec computation
        if (res == 0) {

            prc_compute(min, max, file_descriptor);
        }
    }

    // close writing end
    close(file_descriptor[1]);

    sleep(2);
    
    // read results from children
    double from_child = -1;
    int counter = MAX;
    do {

        // read from pipe
        read(file_descriptor[0], &from_child, sizeof(double));

        // add to sum
        printf("[master] retrieved: %f \n", from_child);
        sum += from_child;
        from_child = -1;

        // decrement counter
        counter--;
    } while (counter > 0);

    printf("[master] Total: %f\n", sum);
}