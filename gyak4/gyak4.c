#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MERET 3

void szekvencialis(double* tomb);
void openmp_parhuzamos_for(double* tomb);
void openmp_redukcios_for(double* tomb);

int main(){
    double tomb[MERET];
    srand(time(NULL));

    for (int i = 0; i < MERET; i++) {
        tomb[i] = (float)rand()/(float)(1000);
    }

    for (int i = 0; i < MERET; i++)
    {
        printf("%lf ",tomb[i]);
    }
    printf("\n");
    
    szekvencialis(tomb);
    openmp_parhuzamos_for(tomb);
    openmp_redukcios_for(tomb);
    
    return 0;
}

void szekvencialis(double* tomb){
    double osszeg = 1;
    for (int i = 0; i < MERET; i++)
    {
       osszeg *= tomb[i];
    }
    printf("Szekvencialis eredmeny: %lf\n",osszeg);
    
}
void openmp_parhuzamos_for(double* tomb){
    double osszeg = 1;
    #pragma omp parallel for
    for (int i = 0; i < MERET; i++) {
        osszeg *= tomb[i];
    }
    printf("OpenMP parhuzamos eredmeny: %lf\n", osszeg);
}
void openmp_redukcios_for(double* tomb) {
    double osszeg = 1;
    #pragma omp parallel for reduction(*:osszeg)
    for (int i = 0; i < MERET; i++) {
        osszeg *= tomb[i];
    }
    printf("OpenMP redukcios for eredmeny: %f\n", tomb);
}