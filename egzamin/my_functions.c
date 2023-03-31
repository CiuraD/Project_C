#include "my_header.h"

void New_game (){
    char tmp_name [50];
    struct character hero;
    printf ("\n Podaj imie swojej postaci (uwaga tylko 20 znakow zostanie zapisana , Lista zakazanych znakow: ',' '.' '\\' ' ' ';'): \n");
    getchar();
    scanf ("%s", tmp_name);
    Writing_name(hero.name_of_character, tmp_name);

    while (Checking_name (tmp_name)){
        CLEAR;
        printf ("\n Podaj imie swojej postaci (uwaga tylko 20 znakow zostanie zapisana , Lista zakazanych znakow: ',' '.' '\' ' ' ';'): \n");
        getchar();
        scanf ("%s", tmp_name);
        Writing_name(hero.name_of_character, tmp_name);
    }

    char path [15 + MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];

    Creating_path (path, hero.name_of_character);

    while (Checking_availability (path)) {
        CLEAR;

        printf ("\n Podaj imie swojej postaci (uwaga tylko 20 znakow zostanie zapisana , Lista zakazanych znakow: ',' '.' '\' ' ' ';'): \n");
        getchar();
        scanf ("%s", tmp_name);
        Writing_name(hero.name_of_character, tmp_name);

        Creating_path (path, hero.name_of_character);
    }

    hero.id_of_current_area = 1;
    hero.current_exp = 0;
    hero.max_hp = 20;
    hero.current_hp = hero.max_hp;
    hero.id_of_used_armor = 20;
    hero.id_of_used_potion = 0;
    hero.id_of_used_wepon = 20;
    hero.lvl_of_character = 1;
    hero.owned_gold = 0;
    hero.required_exp = 200;
    hero.current_position_X = 6;
    hero.current_position_Y = 6;

    Creating_save_file (hero, path);

    Starting_game(path);

}
void Writing_name (char string1 [], char string2 []){
     for (int i = 0; i < MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME - 1; i++){
         *string1++ = *string2++;
     }
     *string1 = '\0';
}
void Creating_save_file (struct character hero ,char path []){
    FILE *fptr;


    fptr = fopen (path, "w");



    fprintf (fptr, "%s\n", hero.name_of_character);
    fprintf (fptr, "%hd\n", hero.id_of_current_area);
    fprintf (fptr, "%d\n", hero.current_position_X);
    fprintf (fptr, "%d\n", hero.current_position_Y);
    fprintf (fptr, "%d\n", hero.lvl_of_character);
    fprintf (fptr, "%d\n", hero.current_exp);
    fprintf (fptr, "%d\n", hero.required_exp);
    fprintf (fptr, "%d\n", hero.current_hp);
    fprintf (fptr, "%d\n", hero.max_hp);
    fprintf (fptr, "%d\n", hero.id_of_used_wepon);
    fprintf (fptr, "%d\n", hero.id_of_used_armor);
    fprintf (fptr, "%d\n", hero.id_of_used_potion);
    fprintf (fptr, "%d\n", hero.owned_gold);

    fclose (fptr);
    fptr = NULL;

}
int Checking_availability (char path []){
    FILE *fptr;
    fptr = fopen ( path, "r" );
    if (fptr != NULL){
        return 1;
    }
    else{
        fclose (fptr);
        fptr = NULL;
        return 0;
    }
}
void Creating_path (char string1 [], char string2 []){
    char tmpstr [15 + MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME]= "..\\saves\\";
    strcat (tmpstr, string2);
    strcat (tmpstr,".txt");

    int i = 0;

    while (*string1++ = tmpstr [i++]);
}
int Checking_name (char string []){
    while (*string){
        if (*string == '.' || *string == ' ' || *string == ',' || *string == ';' || *string == '\\' ){
            return 1;
        }
        string++;
    }
    return 0;
}

void Load_game (){
    char name [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    char path [15 + MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    printf("\n Istniejace postacie:\n");
    if(Listing_saves()){

        getchar();

        printf ("\n Podaj nazwe postaci:\n");
        scanf ("%[^\n]s", name);

        Creating_path (path, name);

        while (!Checking_availability (path)) {
            CLEAR;
            printf("\n Istniejace postacie:\n");
            Listing_saves();
            printf ("\n Podaj ponownie nazwe postaci \n");
            getchar();
            scanf ("%[^\n]s", name);
            Creating_path (path, name);
        }
        Starting_game (path);
    }
    else{
        printf ("\nNacisnij dowolny klawisz aby kontynuowac\n");
        getchar();
        getchar();
    }
}
int Listing_saves (){
    struct dirent *de;
    int working = 1;

        DIR *dr = opendir("..\\saves");

        if (dr == NULL)
        {
            printf("Nie mozna otworzyc folderu z zapisanymi stanami gry" );
            working = 0;
            return working;
        }


        while ((de = readdir(dr)) != NULL){
            if(strcmp( de->d_name, ".") && strcmp( de->d_name, "..")){
                for(int i = 0; de->d_name[i] != '.'; i++)
                    printf ("%c", de->d_name[i]);
            }
            printf ("\n");
        }
        closedir(dr);
        de = NULL;
        dr = NULL;
        return working;
}

void Starting_game (char path []){
    struct character character;

    FILE *fptr = NULL;
    if ( (fptr = fopen(path, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf(fptr, "%s %hd %d %d %d %d %d %d %d %d %d %d %d", character.name_of_character, &character.id_of_current_area, &character.current_position_X, &character.current_position_Y, &character.lvl_of_character, &character.current_exp, &character.required_exp, &character.current_hp, &character.max_hp, &character.id_of_used_wepon, &character.id_of_used_armor, &character.id_of_used_potion, &character.owned_gold);
        fclose (fptr);
        fptr = NULL;
        The_game (&character, path);

    }
}
void The_game (struct character *hero, char *path){
    struct area area;
    int option, chane_of_area = 1;
    do{
        getchar();
        CLEAR;
        if(chane_of_area){
            Taking_map (hero->id_of_current_area, &area);
            chane_of_area = 0;
        }
        Drawing_map (hero->current_position_X, hero->current_position_Y, area.position_X_of_teleporter, area.position_Y_of_teleporter, area.heigh_of_area, area.width_of_area);
        printf ("\n Wybierz co chcesz zrobic\n 1 - Poruszyc sie\n 2 - Uzyc mikstury\n 3 - Wejsc w interakcje\n 4 - Zapisac gre\n 5 - Pokaz statystyki postaci\n 0 - Wyjsc z do menu glownego\n");
        scanf ("%d", &option);
        switch (option) {
        case 1: Move (hero, &area, &option); break;
        case 2: Use_of_potion (hero); break;
        case 3: Interact (hero, area.position_X_of_teleporter, area.position_Y_of_teleporter, &chane_of_area); break;
        case 4: Save_game (hero, path, &option); break;
        case 5: Show_stats (hero); break;
        default: printf ("Prosze wybrac inna opcje"); break;
        }
    }while(option);
}
void Taking_map (int area_of_hero, struct area *area){

    FILE *fptr = NULL;
    char tmp [10];
    char path [30] = "..\\resources\\maps\\";

    itoa(area_of_hero, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

    if ( (fptr = fopen(path, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf(fptr, "%s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", area->name_of_area, &area->id_of_area, &area->heigh_of_area, &area->width_of_area, &area->hostility_of_area, &area->list_of_enemies[0], &area->list_of_enemies[1], &area->list_of_enemies[2], &area->list_of_enemies[3], &area->list_of_enemies[4], &area->list_of_enemies[5], &area->list_of_enemies[6], &area->list_of_enemies[7], &area->list_of_enemies[8], &area->list_of_enemies[9], &area->position_X_of_teleporter, &area->position_Y_of_teleporter);
        fclose (fptr);
        fptr = NULL;
    }

}
void Drawing_map (int hero_X, int hero_Y, int teleporter_X, int teleporter_Y, int heigh, int width){
    for (int i = 0; i < (width + 4); i++){
        printf ("=");
    }
    printf ("\n");
    for (int i = 0; i < heigh; i++){
        printf ("||");
        for (int j = 0; j < width; j++){
            if (i == hero_Y && j == hero_X){
                printf ("X");
            }
            else if (i == teleporter_Y && j == teleporter_X){
                printf ("Y");
            }
            else{
                printf (" ");
            }
        }
        printf ("||\n");
    }
    for (int i = 0; i < (width + 4); i++){
        printf ("=");
    }
}
void Save_game (struct character *hero, char path[], int *option){
    int yes_no = 1;

    FILE *fptr;

    fptr = fopen (path, "w");

    fprintf (fptr, "%s\n", hero->name_of_character);
    fprintf (fptr, "%hd\n", hero->id_of_current_area);
    fprintf (fptr, "%d\n", hero->current_position_X);
    fprintf (fptr, "%d\n", hero->current_position_Y);
    fprintf (fptr, "%d\n", hero->lvl_of_character);
    fprintf (fptr, "%d\n", hero->current_exp);
    fprintf (fptr, "%d\n", hero->required_exp);
    fprintf (fptr, "%d\n", hero->current_hp);
    fprintf (fptr, "%d\n", hero->max_hp);
    fprintf (fptr, "%d\n", hero->id_of_used_wepon);
    fprintf (fptr, "%d\n", hero->id_of_used_armor);
    fprintf (fptr, "%d\n", hero->id_of_used_potion);
    fprintf (fptr, "%d\n", hero->owned_gold);

    fclose (fptr);
    fptr = NULL;

    printf ("Czy chcesz wrocic do menu glownego? (0 - nie, kazda inna liczba - tak)\n");
    scanf ("%d", &yes_no);
    if (yes_no){
        *option = 0;
    }
    else{
        *option = 6;
    }
}
void Use_of_potion (struct character *hero){
    FILE *fptr = NULL;
    char tmp [10];
    char path [35] = "..\\resources\\potions\\";
    struct potion pots;
    int healed_hp = 0;

    itoa(hero->id_of_used_potion, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

    if ( (fptr = fopen(path, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf (fptr, "%d %s %d %d", &pots.id_of_potion, pots.name_of_potion, &pots.recovered_health, &pots.value);
        fclose (fptr);
        fptr = NULL;
        healed_hp = pots.recovered_health;
        if ( (hero->current_hp + healed_hp) < hero->max_hp){
            hero->current_hp += healed_hp;
        }
        else {
            hero->current_hp = hero->max_hp;
        }
    }
}
void Interact (struct character *hero, int tp_X, int tp_Y, int *change_of_area){
    int option;
    if( hero->current_position_X == tp_X && hero->current_position_Y == tp_Y){
        do{
            printf ("Prosze wybrac co chcesz zrobic (0 - wyjscie z menu interakcji, 1 - uleczenie postaci, 2 - kupno wyposazenia, 3 - zmiana strefy)");
            scanf ("%d", &option);
            switch (option) {
                case 0: break;
                case 1: Tp_healing (&hero->current_hp, hero->max_hp); break;
                case 2: Shop (&hero->id_of_used_armor, &hero->id_of_used_wepon, &hero->id_of_used_potion, &hero->owned_gold); break;
                case 3: Teleportation (&hero->id_of_current_area, &hero->current_position_X, &hero->current_position_Y, change_of_area); break;
                default: printf("Wybierz poprawna opcje \n");
            }
        } while (option);
    }
    else{
        printf ("Nie mozna wejsc w interakcje z czymkolwiek w tym miejscu");
        getchar();
    }
}
void Tp_healing (int *current_hp, int max_hp){
    *current_hp = max_hp;
}
void Teleportation (unsigned short *id_current_area, int *hero_X, int *hero_Y, int *change_area){
    FILE *fptr = NULL;
    struct area area;
    int i = 1, tmp_id;
    char tmp [10];
    char path [30] = "..\\resources\\maps\\";

    itoa(i, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

   while ((fptr = fopen(path, "r")) != NULL){
            fscanf(fptr, "%s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", area.name_of_area, &area.id_of_area, &area.heigh_of_area, &area.width_of_area, &area.hostility_of_area, &area.list_of_enemies[0], &area.list_of_enemies[1], &area.list_of_enemies[2], &area.list_of_enemies[3], &area.list_of_enemies[4], &area.list_of_enemies[5], &area.list_of_enemies[6], &area.list_of_enemies[7], &area.list_of_enemies[8], &area.list_of_enemies[9], &area.position_X_of_teleporter, &area.position_Y_of_teleporter);
            printf ("%d -  %s\n", i, area.name_of_area);
            i++;
            Changing_path_ar (path,i);
    }
   do{
       printf ("\n Podaj numer strefy do ktorej chcesz sie przeniesc\n");
       scanf ("%d", &tmp_id);
   }while (tmp_id <= 0 && tmp_id > i-1);

   if (tmp_id != *id_current_area){
       *id_current_area = tmp_id;
       *change_area = 1;
       Changing_path_ar (path, tmp_id);
       fptr = fopen(path, "r");
       fscanf(fptr, "%s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", area.name_of_area, &area.id_of_area, &area.heigh_of_area, &area.width_of_area, &area.hostility_of_area, &area.list_of_enemies[0], &area.list_of_enemies[1], &area.list_of_enemies[2], &area.list_of_enemies[3], &area.list_of_enemies[4], &area.list_of_enemies[5], &area.list_of_enemies[6], &area.list_of_enemies[7], &area.list_of_enemies[8], &area.list_of_enemies[9], &area.position_X_of_teleporter, &area.position_Y_of_teleporter);
       *hero_X = area.position_X_of_teleporter;
       *hero_Y = area.position_Y_of_teleporter;
   }
   fclose (fptr);
   fptr = NULL;
}
void Changing_path_ar (char path [], int i){
    char tmp [10];
    char path_tmp [30] = "..\\resources\\maps\\";
    int j = 0;

    itoa(i, tmp, 10);
    strcat(path_tmp, tmp);
    strcat(path_tmp, ".txt");

    while (*path++ = path_tmp[j++]);
}
void Show_stats (struct character *hero){
    FILE *fptr = NULL;
    char tmp [10];
    char path_w [35] = "..\\resources\\weapons\\";
    char path_a [35] = "..\\resources\\armor\\";
    char path_p [35] = "..\\resources\\potions\\";

    struct weapon used_weapon;
    struct armor used_armor;
    struct potion used_potion;

    itoa(hero->id_of_used_wepon, tmp, 10);
    strcat(path_w, tmp);
    strcat(path_w, ".txt");

    if ( (fptr = fopen(path_w, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf (fptr, "%d %s %d %d %d", &used_weapon.id_of_weapon, used_weapon.name_of_weapon, &used_weapon.minimal_dmg, &used_weapon.maximal_dmg, &used_weapon.value);
        fclose (fptr);
        fptr = NULL;
    }

    itoa(hero->id_of_used_armor, tmp, 10);
    strcat(path_a, tmp);
    strcat(path_a, ".txt");

    if ( (fptr = fopen(path_a, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf (fptr, "%d %s %d %d", &used_armor.id_of_armor, used_armor.name_of_armor, &used_armor.protection, &used_armor.value);
        fclose (fptr);
        fptr = NULL;
    }

    itoa(hero->id_of_used_potion, tmp, 10);
    strcat(path_p, tmp);
    strcat(path_p, ".txt");

    if ( (fptr = fopen(path_p, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf (fptr, "%d %s %d %d", &used_potion.id_of_potion, used_potion.name_of_potion, &used_potion.recovered_health, &used_potion.value);
        fclose (fptr);
        fptr = NULL;
    }

    Making_space (used_armor.name_of_armor);
    Making_space (used_weapon.name_of_weapon);
    Making_space (used_potion.name_of_potion);

    CLEAR;
    printf ("Imie: %s\n", hero->name_of_character);
    printf ("Lvl: %d\n", hero->lvl_of_character);
    printf ("HP: %d\\%d\n", hero->current_hp, hero->max_hp);
    printf ("EXP: %d\\%d\n", hero->current_exp, hero->required_exp);
    printf ("Bron: %s\n", used_weapon.name_of_weapon);
    printf ("Obrazenia: %d - %d\n", used_weapon.minimal_dmg, used_weapon.maximal_dmg);
    printf ("Pancerz: %s\n", used_armor.name_of_armor);
    printf ("Obrona: %d\n", used_armor.protection);
    printf ("Mikstura: %s\n",used_potion.name_of_potion);
    printf ("Przywracane HP: %d\n", used_potion.recovered_health);
    printf ("Posiadane zloto: %d\n", hero->owned_gold);
    printf ("\n Aby kontynuowac nacisnij dowolny przycisk \n");
    getchar();
    getchar();
}
void Making_space (char name []){
    while (*name != '\0'){
        if (*name == '_'){
            *name = ' ';
        }
        name++;
    }
}
void Shop (int *current_armor, int *current_weapon, int *current_potion, int *gold){
    int option;
    do{
        printf ("Prosze wybrac co chcesz zrobic (0 - wyjscie z menu interakcji, 1 - kupno broni, 2 - pancerza, 3 - kupno mikstury)");
        scanf ("%d", &option);
        switch (option) {
            case 1: Buy_weapon (current_weapon, gold); break;
            case 2: Buy_armor (current_armor, gold); break;
            case 3: Buy_potion (current_potion, gold); break;
            case 0: break;
            default: printf("Wybierz poprawna opcje \n");
        }
    }while (option);
}
void Buy_weapon (int *current_weapon, int *gold){
    CLEAR;
    FILE *fptr = NULL;
    struct weapon weapon;
    int i = 20, tmp_id;
    char tmp [10];
    char path [35] = "..\\resources\\weapons\\";

    itoa(i, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

    printf ("\n Posiadane zloto: %d\n", *gold);
    printf ("\n    id                  bron  min-obrazenia  max-obrazenia  wartosc\n");
    while ((fptr = fopen(path, "r")) != NULL){
        fscanf (fptr, "%d %s %d %d %d", &weapon.id_of_weapon, weapon.name_of_weapon, &weapon.minimal_dmg, &weapon.maximal_dmg, &weapon.value);
        Making_space (weapon.name_of_weapon);
        printf ("%3d   %20s %8d %16d %10d", weapon.id_of_weapon, weapon.name_of_weapon, weapon.minimal_dmg, weapon.maximal_dmg, weapon.value);
        if (i == *current_weapon){
            printf("     OBECNA");
        }
        printf ("\n");
        i++;
        Changing_path_we (path,i);
    }
    do{
        printf("\n Podaj numer broni ktora chcesz kupic (0 - jesli chcesz anulowac zakupy)\n");
        scanf ("%d", &tmp_id);
        Changing_path_we (path,tmp_id);
        while( (fptr = fopen(path, "r")) == NULL){
            printf("\n Podaj numer broni ktora chcesz kupic (0 - jesli chcesz anulowac zakupy)\n");
            scanf ("%d", &tmp_id);
            Changing_path_we (path,tmp_id);
        }
        fscanf (fptr, "%d %s %d %d %d", &weapon.id_of_weapon, weapon.name_of_weapon, &weapon.minimal_dmg, &weapon.maximal_dmg, &weapon.value);
    }while (tmp_id == *current_weapon && *gold < weapon.value && tmp_id < 20 && tmp_id >= i && tmp_id != 0);
    CLEAR;
    *gold -= weapon.value;
    if (weapon.id_of_weapon){
        *current_weapon = weapon.id_of_weapon;
    }
    fclose (fptr);
    fptr = NULL;
}
void Buy_armor (int *current_armor, int *gold){
    CLEAR;
    FILE *fptr = NULL;
    struct armor armor;
    int i = 20, tmp_id;
    char tmp [10];
    char path [35] = "..\\resources\\armor\\";

    itoa(i, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

    printf ("\n Posiadane zloto: %d\n", *gold);
    printf ("\n  id            pancerz    obrona   wartosc\n");
    while ((fptr = fopen(path, "r")) != NULL){
        fscanf (fptr, "%d %s %d %d", &armor.id_of_armor, armor.name_of_armor, &armor.protection, &armor.value);
        Making_space(armor.name_of_armor);
        printf ("%3d   %20s %8d %6d", armor.id_of_armor, armor.name_of_armor, armor.protection, armor.value);
        if (i == *current_armor){
            printf("     OBECNY");
        }
        printf ("\n");
        i++;
        Changing_path_am (path,i);
    }
    do{
        printf("\n Podaj numer pancerza ktory chcesz kupic (0 - jesli chcesz anulowac zakupy)\n");
        scanf ("%d", &tmp_id);
        Changing_path_am (path,tmp_id);
        while( (fptr = fopen(path, "r")) == NULL){
            printf("\n Podaj numer pancerza ktory chcesz kupic (0 - jesli chcesz anulowac zakupy)\n");
            scanf ("%d", &tmp_id);
            Changing_path_am (path,tmp_id);
        }
        fscanf (fptr, "%d %s %d %d", &armor.id_of_armor, armor.name_of_armor, &armor.protection, &armor.value);
    }while (tmp_id == *current_armor && *gold < armor.value && tmp_id < 20 && tmp_id >= i && tmp_id != 0);
    CLEAR;
    *gold -= armor.value;
    if (armor.id_of_armor){
        *current_armor = armor.id_of_armor;
    }
    fclose (fptr);
    fptr = NULL;
}
void Buy_potion (int *current_potion, int *gold){
    CLEAR;
    FILE *fptr = NULL;
    struct potion potion;
    int i = 0, tmp_id;
    char tmp [10];
    char path [35] = "..\\resources\\potions\\";

    itoa(i, tmp, 10);
    strcat(path, tmp);
    strcat(path, ".txt");

    printf ("\n Posiadane zloto: %d\n", *gold);
    printf ("\n    id            mikstura  leczenie  wartosc\n");
    while ((fptr = fopen(path, "r")) != NULL){
        fscanf (fptr, "%d %s %d %d", &potion.id_of_potion, potion.name_of_potion, &potion.recovered_health, &potion.value);
        printf ("%3d   %20s %8d %16d", potion.id_of_potion, potion.name_of_potion, potion.recovered_health, potion.value);
        if (i == *current_potion){
            printf("     OBECNA");
        }
        printf ("\n");
        i++;
        Changing_path_pt (path,i);
    }
    do{
        printf("\n Podaj numer mikstury ktora chcesz kupic (OBECNY - jesli chcesz anulowac zakupy)\n");
        scanf ("%d", &tmp_id);
        Changing_path_pt (path,tmp_id);
        while( (fptr = fopen(path, "r")) == NULL){
            printf("\n Podaj numer mikstury ktora chcesz kupic (OBECNY - jesli chcesz anulowac zakupy)\n");
            scanf ("%d", &tmp_id);
            Changing_path_pt (path,tmp_id);
        }
        fscanf (fptr, "%d %s %d %d", &potion.id_of_potion, potion.name_of_potion, &potion.recovered_health, &potion.value);
    }while (tmp_id == *current_potion && *gold < potion.value && tmp_id < 0 && tmp_id >= i);
    CLEAR;
    if (tmp_id == *current_potion){
        potion.value = 0;
    }
    *gold -= potion.value;
    if (potion.id_of_potion){
        *current_potion = potion.id_of_potion;
    }
    fclose (fptr);
    fptr = NULL;
}
void Changing_path_we (char path [], int i){
    char tmp [10];
    char path_tmp [35] = "..\\resources\\weapons\\";
    int j = 0;

    itoa(i, tmp, 10);
    strcat(path_tmp, tmp);
    strcat(path_tmp, ".txt");

    while (*path++ = path_tmp[j++]);
}
void Changing_path_am (char path [], int i){
    char tmp [10];
    char path_tmp [35] = "..\\resources\\armor\\";
    int j = 0;

    itoa(i, tmp, 10);
    strcat(path_tmp, tmp);
    strcat(path_tmp, ".txt");

    while (*path++ = path_tmp[j++]);
}
void Changing_path_pt (char path [], int i){
    char tmp [10];
    char path_tmp [35] = "..\\resources\\potions\\";
    int j = 0;

    itoa(i, tmp, 10);
    strcat(path_tmp, tmp);
    strcat(path_tmp, ".txt");

    while (*path++ = path_tmp[j++]);
}

void Move (struct character *hero, struct area *miejsce, int *contiuation){
    srand(time(NULL));
    char m;
    int encounter;
    getchar();
    do{
        printf ("Podaj gdzie chcesz isc (n/N - 1 w gore, e/E - 1 w prawo, s/S - 1 w dol, w/W - 1 w lewo) \n");
        scanf ("%c", &m);
        switch (m) {
        case 'n': if ( (hero->current_position_Y - 1) >= 0 ){
                hero->current_position_Y--;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'N': if ( (hero->current_position_Y - 1) >= 0 ){
                hero->current_position_Y--;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'e': if ( (hero->current_position_X + 1) < miejsce->width_of_area ){
                hero->current_position_X++;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'E': if ( (hero->current_position_X + 1) < miejsce->width_of_area ){
                hero->current_position_X++;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 's': if ( (hero->current_position_Y + 1) < miejsce->heigh_of_area ){
                hero->current_position_Y++;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'S': if ( (hero->current_position_Y + 1) < miejsce->heigh_of_area ){
                hero->current_position_Y++;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'w': if ( (hero->current_position_X - 1) >= 0 ){
                hero->current_position_X--;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        case 'W': if ( (hero->current_position_X - 1) >= 0 ){
                hero->current_position_X--;
            }
            else {
                printf ("Nie mozna sie tam ruszyc");
                printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                getchar();
            }
            break;
        }
    }while ( m != 'n' && m != 'N' && m != 'e' && m != 'E' && m != 's' && m != 'S' && m != 'w' && m != 'W');



    if (miejsce->hostility_of_area == 1){
        encounter = rand()%4;
        if (encounter == 1){
            encounter = rand()%10;
            Fight (hero, miejsce->list_of_enemies[encounter], contiuation);
        }
    }
}
void Fight (struct character *hero, int id_of_enemy ,int *contiuation){
    CLEAR;
    FILE *fptr = NULL;
    char tmp [10];
    char path_e [35] = "..\\resources\\enemies\\";
    char path_e_a [35] = "..\\resources\\armor\\";
    char path_e_w [35] = "..\\resources\\weapons\\";
    char path_h_a [35] = "..\\resources\\armor\\";
    char path_h_w [35] = "..\\resources\\weapons\\";

    struct enemy enemy;
    struct weapon heros_weapon;
    struct weapon enemy_weapon;
    struct armor heros_armor;
    struct armor enemy_armor;
    int option, player = 0;

    itoa(id_of_enemy, tmp, 10);
    strcat(path_e, tmp);
    strcat(path_e, ".txt");

    if ( (fptr = fopen(path_e, "r")) == NULL ){
        printf ("Nie udalo sie otworzyc pliku");
    }
    else{
        fscanf (fptr, "%d %s %d %d %d", &enemy.id_of_enemy, enemy.name_of_enemy, &enemy.lvl_of_enemy, &enemy.id_of_used_wepon, &enemy.id_of_used_armor);
        fclose (fptr);
        fptr = NULL;

        enemy.max_hp_of_enemy = enemy.lvl_of_enemy * 20;
        enemy.current_hp = enemy.max_hp_of_enemy;
        enemy.giving_gold = enemy.lvl_of_enemy * 15;
        enemy.giving_exp = enemy.lvl_of_enemy * 25;

        itoa(enemy.id_of_used_armor, tmp, 10);
        strcat(path_e_a, tmp);
        strcat(path_e_a, ".txt");

        if ( (fptr = fopen(path_e_a, "r")) == NULL ){
            printf ("Nie udalo sie otworzyc pliku");
        }
        else{
            fscanf (fptr, "%d %s %d %d", &enemy_armor.id_of_armor, enemy_armor.name_of_armor, &enemy_armor.protection, &enemy_armor.value);
            fclose (fptr);
            fptr = NULL;

            itoa(enemy.id_of_used_wepon, tmp, 10);
            strcat(path_e_w, tmp);
            strcat(path_e_w, ".txt");

            if ( (fptr = fopen(path_e_w, "r")) == NULL ){
                printf ("Nie udalo sie otworzyc pliku");
            }
            else{
                fscanf (fptr, "%d %s %d %d %d", &enemy_weapon.id_of_weapon, enemy_weapon.name_of_weapon, &enemy_weapon.minimal_dmg, &enemy_weapon.maximal_dmg, &enemy_weapon.value);
                fclose (fptr);
                fptr = NULL;

                itoa(hero->id_of_used_armor, tmp, 10);
                strcat(path_h_a, tmp);
                strcat(path_h_a, ".txt");

                if ( (fptr = fopen(path_h_a, "r")) == NULL ){
                    printf ("Nie udalo sie otworzyc pliku");
                }
                else{
                    fscanf (fptr, "%d %s %d %d", &heros_armor.id_of_armor, heros_armor.name_of_armor, &heros_armor.protection, &heros_armor.value);
                    fclose (fptr);
                    fptr = NULL;

                    itoa(hero->id_of_used_wepon, tmp, 10);
                    strcat(path_h_w, tmp);
                    strcat(path_h_w, ".txt");

                    if ( (fptr = fopen(path_h_w, "r")) == NULL ){
                        printf ("Nie udalo sie otworzyc pliku");
                    }
                    else{
                        fscanf (fptr, "%d %s %d %d %d", &heros_weapon.id_of_weapon, heros_weapon.name_of_weapon, &heros_weapon.minimal_dmg, &heros_weapon.maximal_dmg, &heros_weapon.value);
                        fclose (fptr);
                        fptr = NULL;
                        Making_space(enemy.name_of_enemy);
                        do{
                            getchar();
                            CLEAR;
                            printf ("\n %s \n", enemy.name_of_enemy);
                            printf ("     %d\\%d", enemy.current_hp, enemy.max_hp_of_enemy);
                            printf ("\n\n\n\n");
                            printf ("\n %s \n", hero->name_of_character);
                            printf ("     %d\\%d", hero->current_hp, hero->max_hp);
                            printf ("\n Obrazenia: %d - %d\n", heros_weapon.minimal_dmg, heros_weapon.maximal_dmg);
                            if (player){
                                    Attack (enemy_weapon, &hero->current_hp, heros_armor.protection, enemy.lvl_of_enemy); player ++;
                            }
                            else {
                                do{
                                    printf ("Wybierz co chcesz zrobic (1 - zaatakuj, 2 - uzyj mikstury):\n");
                                    scanf("%d", &option);
                                    switch (option) {
                                        case 1: Attack (heros_weapon, &enemy.current_hp, enemy_armor.protection, hero->lvl_of_character); player ++; break;
                                        case 2: Use_of_potion (hero); player ++; break;
                                        default : printf ("Wybierz poprawna opcje"); printf("\n Nacisnij dowolny klawisz aby kontynuowac \n"); getchar(); break;
                                    }
                                }while (player == 0);
                            }
                            player %= 2;
                        }while (hero->current_hp > 0 && enemy.current_hp > 0);
                        if (hero->current_hp <= 0){
                            printf ("\n Przegrales, wczytaj gre jesli chcesz kontynuowac \n");
                            printf("\n Nacisnij dowolny klawisz aby kontynuowac \n");
                            getchar();
                            *contiuation = 0;
                        }
                        else {
                            Taking_exp (hero, enemy.giving_exp);
                        }
                    }
                }
            }
        }
    }

}
void Attack (struct weapon weapon, int *health, int protection, int bonus){
    srand(time(NULL));
    int dmg;
    dmg = rand() % (weapon.maximal_dmg + 1 - weapon.minimal_dmg) + weapon.minimal_dmg;
    dmg += bonus;
    dmg = dmg - protection;
    *health -= dmg;
}
void Taking_exp (struct character *hero, int taken_exp){
    if( (taken_exp + hero->current_exp) >= hero->required_exp){
        hero->current_exp = ( (hero->current_exp + taken_exp) - hero->required_exp);
        hero->lvl_of_character++;
        hero->required_exp = hero->lvl_of_character * 200;
        hero->max_hp = (hero->max_hp + (hero->lvl_of_character * 20));
        hero->current_hp = hero->max_hp;
    }
    else{
        hero->current_exp += taken_exp;
    }
}
