#pragma once 
#include "raylib.h"
#include "game_config.h"

struct Player;

extern Texture2D enemy;

struct enemy_properties{
    int posx;
    int posy;
    int speed;
    int health;
    int width;
    int height;
};
extern enemy_properties enemy_prop;

struct enemy_mood{
    bool lazy;
    bool confident;
    bool locked_in;
};
extern enemy_mood enemy_state;

struct enemy_bullet_prop{
    Vector2 bullet_pos;
    int height;
    int width;
    bool bullet_active = false;;
};
extern enemy_bullet_prop bullet_enemy[enemy_bullet_number];

extern bool shoot_bullet;

extern double cool_down;
extern double last_time_shot;

void reset_enemy(enemy_properties &enemy_prop);

void reset_enemy_state(enemy_mood &enemy_state,enemy_properties enemy_prop);

void cpu_enemy(enemy_properties &enemy_prop,Vector2 pos,double &cool_down);

bool collisionbullet(Player &player_prop,enemy_bullet_prop bullet_enemy[enemy_bullet_number],int i);

bool collision_objects(Player &player_prop,enemy_properties &enemy_prop);

void put_bullet1(int i);
