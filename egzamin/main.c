#include "my_header.h"


int main()
{
    int  menu = 4;
    do{
        CLEAR;
        printf ("\n 1. Nowa gra");
        printf ("\n 2. Wczytaj gre");
        printf ("\n 3. Wyjdz \n");
        scanf ("%d", &menu);
        switch (menu) {
            case 1: New_game (); break;
            case 2: Load_game (); break;
        }
    } while (menu != 3);
    return 0;
}

