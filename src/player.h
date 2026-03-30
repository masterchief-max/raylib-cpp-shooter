#pragma once
#include "raylib.h"
#include "bullet.h"
#include "enemy.h"

extern Texture2D player;

struct Player
{
    Vector2 pos;
    int height;
    int width;
    int health;
};
extern Player player_prop;

extern bool start_game;

void movement(Vector2 &pos,bullet_stuct Bullet[],enemy_properties &enemy_prop);

void boundary_check(Vector2 &pos);

void game_reset();

void load_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet);

void unload_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet);