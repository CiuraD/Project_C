#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAX_NUMBER_OF_ENEMIES 10
#define MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME 21

#define CLEAR system("cls")

struct enemy{
    int id_of_enemy;
    char name_of_enemy [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    int lvl_of_enemy;
    int max_hp_of_enemy;
    int current_hp;
    int giving_exp;
    int giving_gold;
    int id_of_used_wepon;
    int id_of_used_armor;
};
struct area{
    char name_of_area [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    unsigned char id_of_area;
    int heigh_of_area;
    int width_of_area;
    int hostility_of_area; // 0 - non hostile; 1 - hostile
    int list_of_enemies [MAX_NUMBER_OF_ENEMIES];
    int position_X_of_teleporter;
    int position_Y_of_teleporter;
};
struct character{
    char name_of_character [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    unsigned short id_of_current_area;
    int current_position_X;
    int current_position_Y;
    int lvl_of_character;
    int current_exp;
    int required_exp;
    int current_hp;
    int max_hp;
    int id_of_used_wepon;
    int id_of_used_armor;
    int id_of_used_potion;
    int owned_gold;
};
struct weapon{
    int id_of_weapon;
    char name_of_weapon [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    int minimal_dmg;
    int maximal_dmg;
    int value;
};
struct armor{
    int id_of_armor;
    char name_of_armor [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    int protection;
    int value;
};
struct potion{
    int id_of_potion;
    char name_of_potion [MAX_NUMBER_OF_CHARACTERS_IN_THE_NAME];
    int recovered_health;
    int value;
};

void New_game ();
void Writing_name (char *, char *);
void Creating_save_file (struct character, char *);
void Creating_path (char *, char *);
void Load_game ();
int Listing_saves ();

int Checking_availability (char *);
int Checking_name (char []);

void Starting_game (char *);
void The_game (struct character *, char*);
void Taking_map (int, struct area *);
void Drawing_map (int, int, int, int, int, int);
void Save_game (struct character *, char *, int *);
void Use_of_potion (struct character *);

void Interact (struct character *,  int, int, int *);
void Tp_healing (int *, int);
void Teleportation (unsigned short *, int *, int *, int *);
void Changing_path_ar (char *, int);
void Changing_path_we (char *, int);
void Changing_path_am (char *, int);
void Changing_path_pt (char *, int);
void Show_stats (struct character *);
void Making_space (char *);
void Shop (int *, int *, int *, int *);
void Buy_weapon (int *, int *);
void Buy_armor (int *, int *);
void Buy_potion (int *, int *);

void Move (struct character *, struct area *, int *);
void Fight (struct character *, int, int *);
void Attack (struct weapon, int *, int, int);
void Taking_exp (struct character *, int);
#endif // MY_HEADER_H
