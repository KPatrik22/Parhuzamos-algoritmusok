#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

void padding();
void sleepTest();
int Random();
int randomintervallum(int min, int max);
void szamolas();


int main()
{
    srand(time(NULL));
    padding();
    sleep();
    printf("Sorsolt szam 500 es 1000 kozott:\n");
        printf("%d\n", Random());
    int min = 231;
    int max = 782;
    printf("Sorsolt szam %d es %d kozott:\n", min, max);
        printf("%d\n", randomintervallum(min, max));
    szamolas();
    return 0;
}

void padding()
{
    printf("%*d\n", 8, 123);
    printf("%*d\n", 8, 12);
    printf("%*d\n", 8, 13456);
    printf("%*d\n", 8, 12345678);
}

void sleep()
{
    printf("1 sec delay\n");
    Sleep(1000);
}

int Random()
{
        int num = (rand() % (1000 - 500 + 1)) + 500;
        return num;
}

int randomintervallum(int min, int max)
{
    if (min >= max)
    {
        printf("Intervallumon kivul (min >= max)!\n");
        return -1;
    }
    else
    {
        int num = (rand() % (max - min + 1)) + min;

        return num;
    }
}

void szamolas()
{
    int x = randomintervallum(1,50);
    int y = randomintervallum(1,50);
    int guess;
    printf("%d + %d = ?\n", x, y);
    clock_t time = clock();
    do
    {
        scanf("%d", &guess);
        if (guess != x+y)
            printf("Nem jo\n");
    }while(guess != x+y);
    time = clock()-time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC;
    printf("Szamolas ideje %f mp\n", time_taken);
}

