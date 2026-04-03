// define necessary files
#include "enemy.h"
#include "game_config.h"
#include "player.h"
#include "enemy.h"
// define variables
Texture2D enemy;

enemy_properties enemy_prop;

enemy_mood enemy_state;

enemy_bullet_prop bullet_enemy[enemy_bullet_number];

bool shoot_bullet = false;

double cool_down = 1.0;
double last_time_shot = 0;
//define functions
void reset_enemy(enemy_properties &enemy_prop)
{
    enemy_prop.posx = 0;
    enemy_prop.posy = GetRandomValue(0,screen_height);
    enemy_prop.health = 100;
}
// resets enemy
void reset_enemy_state(enemy_mood &enemy_state,enemy_properties enemy_prop)
{
    if(enemy_prop.health > 75)
        {
            enemy_state.lazy = true;
            enemy_state.confident = false;
            enemy_state.locked_in = false;
        }
    if(enemy_prop.health <= 50)
        {
            enemy_state.lazy = false;
            enemy_state.confident = true;
            enemy_state.locked_in = false;
        } 
    if(enemy_prop.health <= 25)
        {
            enemy_state.lazy = false;
            enemy_state.confident = false;
            enemy_state.locked_in = true;
        }
}
// enemy AI
void cpu_enemy(enemy_properties &enemy_prop,Vector2 pos,double &cool_down)
{
    if(enemy_state.lazy)
    {
        if(enemy_prop.posy <  pos.y){enemy_prop.posy += enemy_prop.speed;}
        if(enemy_prop.posy >  pos.y){enemy_prop.posy -= enemy_prop.speed;}
        shoot_bullet = false;
        cool_down = 2.0;
    }
    else if(enemy_state.confident)
    {
        if(enemy_prop.posy <  pos.y){enemy_prop.posy += enemy_prop.speed;}
        if(enemy_prop.posy >  pos.y){enemy_prop.posy -= enemy_prop.speed;}
        if(enemy_prop.posx < pos.x){enemy_prop.posx += enemy_prop.speed;}
        if(enemy_prop.posx > pos.x){enemy_prop.posx -= enemy_prop.speed;}
        shoot_bullet = false;
        cool_down = 1.0;
    }
    else if (enemy_state.locked_in)
    {
        if(enemy_prop.posy <  pos.y){enemy_prop.posy += enemy_prop.speed;}
        if(enemy_prop.posy >  pos.y){enemy_prop.posy -= enemy_prop.speed;}
        if(enemy_prop.posx < pos.x){enemy_prop.posx += enemy_prop.speed;}
        if(enemy_prop.posx > pos.x){enemy_prop.posx -= enemy_prop.speed;}
        cool_down = 0.2;
    }
}
// for collision bullets 
bool collisionbullet(Player &player_prop,enemy_bullet_prop bullet_enemy[enemy_bullet_number],int i)
{
    if(player_prop.pos.x < bullet_enemy[i].bullet_pos.x + bullet_enemy[i].width &&
    player_prop.pos.x + player_prop.width > bullet_enemy[i].bullet_pos.x && 
    player_prop.pos.y < bullet_enemy[i].bullet_pos.y + bullet_enemy[i].height && 
    player_prop.pos.y + player_prop.height > bullet_enemy[i].bullet_pos.y)
    {
        return true;
    }
    else{
        return false;
    }
}
// for collision between player and enemy
bool collision_objects(Player &player_prop,enemy_properties &enemy_prop)
{
    if(player_prop.pos.x < enemy_prop.posx + enemy_prop.width &&
    player_prop.pos.x + player_prop.width > enemy_prop.posx &&
    player_prop.pos.y < enemy_prop.posy + enemy_prop.height && 
    player_prop.pos.y + player_prop.height > enemy_prop.posy)
    {
        return true;
    }
    else{
        return false;
    }
}

void put_bullet1(int i)
{
    bullet_enemy[i].bullet_active = true;
    bullet_enemy[i].bullet_pos.x = enemy_prop.posx;
    bullet_enemy[i].bullet_pos.y = enemy_prop.posy + player.height / 2 - 15;
}