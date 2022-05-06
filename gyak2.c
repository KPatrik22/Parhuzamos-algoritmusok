#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define DEBUG 1
int osszeg(int * tomb, int meret);
int min(int * tomb, int meret);
int max(int * tomb, int meret);
void minR(int *tomb, int meret, int min);
void maxR(int *tomb, int meret, int max);
int find_max(int *a,int n);
int find_min(int *a,int n);

int main() //1. feladat
{
    clock_t t;
    double Rmax = 0;
    double Rmin = 0;
    double Mmax = 0;
    double Mmin = 0;

    FILE * f_rek_max;
    FILE * f_rek_min;
    FILE * f_man_max;
    FILE * f_man_min;

    f_rek_max = fopen("Rmax.txt", "w+");
    f_rek_min = fopen("Rmin.txt", "w+");
    f_man_max = fopen("Mmax.txt", "w+");
    f_man_min = fopen("Mmin.txt", "w+");

    fprintf(f_rek_max, "Rmax = [");
    fprintf(f_rek_min, "Rmin = [");
    fprintf(f_man_max, "Mmax = [");
    fprintf(f_man_min, "Mmin = [");

    int const N = 20000;
    srand(time(0));
    int tomb[N];
    for (int i=0; i<N; i++){
        tomb[i] = rand() % (1000 - 1 + 1) + 1;
    }
    printf("\n");
    printf("Merete: %d\n", N);
    printf("Elemeinek osszege: %d\n", osszeg(tomb, N));
    for (int j = 5000; j <= 50000; j = j + 5000)
        {
          for (int i = 0; i < j; i++)
            {
                //Rekurziv max
                t = clock();
                find_max(tomb, N);
                t = clock() - t;
                Rmax = ((double) t / CLOCKS_PER_SEC) + Rmax;
                //Rekurziv min
                t = clock();
                find_min(tomb, N);
                t = clock() - t;
                Rmin = ((double) t / CLOCKS_PER_SEC) + Rmin;
                //Manual max
                t = clock();
                max(tomb, N);
                t = clock() - t;
                Mmax = ((double) t / CLOCKS_PER_SEC) + Mmax;
                //Manual min
                t = clock();
                min(tomb, N);
                t = clock() - t;
                Mmin = ((double) t / CLOCKS_PER_SEC) + Mmin;
            }
            printf("Maximum Rekurziv Meres: %f mp %d eseten\n", Rmax/j, j);
            printf("Minimum Rekurziv Meres: %f mp %d eseten\n", Rmin/j, j);
            printf("Maximum Manualis Meres: %f mp %d eseten\n", Mmax/j, j);
            printf("Minimum Manualis Meres: %f mp %d eseten\n", Mmin/j, j);

            fprintf(f_rek_max, "%f ", Rmax/j);
            fprintf(f_rek_min, "%f ", Rmin/j);
            fprintf(f_man_max, "%f ", Mmax/j);
            fprintf(f_man_min, "%f ", Mmin/j);
        }
        fprintf(f_rek_max, "]");
        fprintf(f_rek_min, "]");
        fprintf(f_man_max, "]");
        fprintf(f_man_min, "]");
    return 0;
}

void meresMaxMan(int * tomb, int meret)
{
    clock_t start = clock();
    #ifdef DEBUG
    printf("Maximum elem: %d\n", max(tomb, meret));
    #endif
    clock_t end = clock();
    double ido = (double) (end - start) / CLOCKS_PER_SEC;
    printf("CPU ido (Maximum - manualis): %f\n", ido);
}



int osszeg(int * tomb, int meret)
{
    int sum = 0;
    for (int i=0; i<meret; i++)
        sum += tomb[i];
    return sum;
}

int min(int * tomb, int meret)
{
    int min = tomb[0];
    for (int i=0; i<meret; i++)
        if (min > tomb[i])
            min = tomb[i];
    return min;
}

int max(int * tomb, int meret)
{
    int max = tomb[0];
    for (int i=0; i<meret; i++)
        if (max < tomb[i])
            max = tomb[i];
    return max;
}

int find_min(int *a,int n)
{
    int m_min;
    if(n==1){
        return a[0];
    }
    m_min=find_min(a,n-1);
    if(a[n-1]<m_min)
        m_min = a[n-1];
    return m_min;
}

int find_max(int *a,int n)
{
    int m_max;
    if(n==1){
        return a[0];
    }
    m_max=find_max(a,n-1);
    if(a[n-1]>m_max)
        m_max=a[n-1];
    return m_max;
}
