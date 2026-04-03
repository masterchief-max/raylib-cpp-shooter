// including nessecary files and header files
#include "player.h"
#include "game_config.h"
#include "bullet.h"
#include "raylib.h"
#include "enemy.h"
#include <iostream>
// define variables
Texture2D player;
Vector2 pos;
Player player_prop;

int player_health_width;
int enemy_health_width;

//movment function for player
void movement(Vector2 &pos,bullet_stuct Bullet[],enemy_properties &enemy_prop) 
{
    if(IsKeyDown(KEY_S)){pos.y += speed;}
    if(IsKeyDown(KEY_W)){pos.y -= speed;}
    if(IsKeyDown(KEY_D)){pos.x += speed;}
    if(IsKeyDown(KEY_A)){pos.x -= speed;}
    if(IsKeyPressed(KEY_SPACE))
    {
        // for bullet (player)
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
// boundary check function for player
void boundary_check(Vector2 &pos)
{
    if(pos.x  > screen_width - player.width){pos.x = screen_width - player.width;}
    if(pos.x  < 0){pos.x = 0;}
    if(pos.y  > screen_height - player.height){pos.y = screen_height - player.height;}
    if(pos.y  < 0){pos.y = 0;}
}
// fuction to reset game
void game_reset()
{
    player_prop.height = player.height;
    player_prop.width = player.width;

    player_prop.pos.x = screen_width - player.width;
    player_prop.pos.y = player.width;

    player_prop.health = 50;
    player_prop.maxhealth = 50;

    enemy_prop.posx = 0; 
    enemy_prop.posy = GetRandomValue(0,screen_height - enemy.height);
    enemy_prop.health = 200;
    enemy_prop.maxhealth = 200;
    if(enemy_state.lazy){enemy_prop.speed = 3;}
    if(enemy_state.confident){enemy_prop.speed = 4;}
    if(enemy_state.locked_in){enemy_prop.speed = 5;}
    else{enemy_prop.speed = 3;}
    enemy_prop.height = enemy.height;
    enemy_prop.width = enemy.width;
}
// function to load resources
void load_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet)
{
    bullet = LoadTexture("resources/bullet.png");
    enemy_bullet = LoadTexture("resources/bullet1.png");
    player = LoadTexture("resources/space_ship2.png");
    enemy = LoadTexture("resources/enemy_ship.png");
}
// funtion to unload resources
void unload_resources(Texture2D &player,Texture2D &enemy,Texture2D &bullet,Texture2D &enemy_bullet)
{
    UnloadTexture(player);
    UnloadTexture(bullet);
    UnloadTexture(enemy);
    UnloadTexture(enemy_bullet);
}

void draw_health(Player &player_prop,enemy_properties &enemy_prop,int player_health_width,int enemy_health_width)
{
    // this was converted into float becuase the interger devision result is a float and the decimal part is truncated and returns a 0 which makes health bar disapper in to oblivion
    enemy_health_width = ((float)enemy_prop.health / enemy_prop.maxhealth) * enemy_prop.width;
    player_health_width = ((float)player_prop.health / player_prop.maxhealth) * player_prop.width; 

    // these were put here for debugging 
    //std::cout << enemy_health_width << " enemy "<< "\n";
    //std::cout << player_health_width << " player " << "\n";


    DrawRectangle(player_prop.pos.x,player_prop.pos.y - 10,player_health_width,5,RED);
    DrawRectangle(enemy_prop.posx,enemy_prop.posy - 10,enemy_health_width,5,GREEN);
}