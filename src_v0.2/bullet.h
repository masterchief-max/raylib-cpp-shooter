#pragma once
// include files

#include "raylib.h"
#include "game_config.h"
#include "enemy.h"
// declare varibles
extern Texture2D bullet;
extern Texture2D enemy_bullet;

struct bullet_stuct{
    Vector2 bullet_pos;
    int height;
    int width;
    bool bullet_active = false;;
};
extern bullet_stuct Bullet[bullet_number];
// define fuctions
bool checkcollision(enemy_properties enemy_prop,bullet_stuct Bullet[bullet_number], int i);

void put_bullet(int i); 

void reset_bullet(int i);