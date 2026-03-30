#include "player.h"
#include "game_config.h"
#include "bullet.h"
#include "raylib.h"
#include "enemy.h"

Texture2D player;
Vector2 pos;
Player player_prop;


void movement(Vector2 &pos,bullet_stuct Bullet[],enemy_properties &enemy_prop) 
{
    if(IsKeyDown(KEY_S)){pos.y += speed;}
    if(IsKeyDown(KEY_W)){pos.y -= speed;}
    if(IsKeyDown(KEY_D)){pos.x += speed;}
    if(IsKeyDown(KEY_A)){pos.x -= speed;}
    if(IsKeyPressed(KEY_SPACE))
    {
        for(int i = 0; i < bullet_number; i++)
        {
            if(Bullet[i].bullet_active == false)
            {
                put_bullet(i);
                break;
            }
        }
    }
}

void boundary_check(Vector2 &pos)
{
    if(pos.x  > screen_width - player.width){pos.x = screen_width - player.width;}
    if(pos.x  < 0){pos.x = 0;}
    if(pos.y  > screen_height - player.height){pos.y = screen_height - player.height;}
    if(pos.y  < 0){pos.y = 0;}
}

void game_reset()
{
    player_prop.height = player.height;
    player_prop.width = player.width;

    player_prop.pos.x = screen_width - player.width;
    player_prop.pos.y = player.width;

    player_prop.health = 50;

    enemy_prop.posx = 0; 
    enemy_prop.posy = GetRandomValue(0,screen_height - enemy.height);
    enemy_prop.health = 200;
    if(enemy_state.lazy){enemy_prop.speed = 3;}
    if(enemy_state.confident){enemy_prop.speed = 4;}
    if(enemy_state.locked_in){enemy_prop.speed = 5;}
    else{enemy_prop.speed = 3;}
    enemy_prop.height = enemy.height;
    enemy_prop.width = enemy.width;
}

void load_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet)
{
    bullet = LoadTexture("resources/bullet.png");
    enemy_bullet = LoadTexture("resources/bullet1.png");
    player = LoadTexture("resources/space_ship2.png");
    enemy = LoadTexture("resources/enemy_ship.png");
}

void unload_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet)
{
    UnloadTexture(player);
    UnloadTexture(bullet);
    UnloadTexture(enemy);
    UnloadTexture(enemy_bullet);
}