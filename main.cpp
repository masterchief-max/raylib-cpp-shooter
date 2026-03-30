#include <iostream>
#include "raylib.h"

int const screen_height = 600;
int const screen_width = 800;

Texture2D player;
Texture2D enemy;
Texture2D bullet;
Texture2D enemy_bullet;

Vector2 pos;

int const bullet_number = 20;
int const enemy_number = 5;

struct enemy_properties{
    int posx;
    int posy;
    int speed;
    int health;
    int width;
    int height;
};
enemy_properties enemy_prop;

struct bullet_stuct{
    Vector2 bullet_pos;
    int height;
    int width;
    bool bullet_active = false;;
};
bullet_stuct Bullet[bullet_number];

float const speed = 5.0;

bool checkcollision(enemy_properties enemy_prop,bullet_stuct Bullet[bullet_number], int i)
{
    if(enemy_prop.posx < Bullet[i].bullet_pos.x + Bullet[i].width &&
    enemy_prop.posx + enemy_prop.width > Bullet[i].bullet_pos.x && 
    enemy_prop.posy < Bullet[i].bullet_pos.y + Bullet[i].height && 
    enemy_prop.posy + enemy_prop.height > Bullet[i].bullet_pos.y)
    {
        return true;
    }
    else{
        return false;
    }
}

void put_bullet(int i)
{
    Bullet[i].bullet_active = true;
    Bullet[i].bullet_pos.x = pos.x;
    Bullet[i].bullet_pos.y = pos.y + player.height / 2 - 15;
}

void reset_bullet(int i)
{
    Bullet[i].bullet_active = false;
    Bullet[i].bullet_pos.x = screen_width - player.width;
}

void reset_enemy(enemy_properties &enemy_prop)
{
    enemy_prop.posx = 0;
    enemy_prop.posy = 0;
    enemy_prop.health = 50;
}

void movement(Vector2 &pos,bullet_stuct Bullet[],enemy_properties &enemy_prop) 
{
    if(IsKeyDown(KEY_S)){pos.y += speed;}
    if(IsKeyDown(KEY_W)){pos.y -= speed;}
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

void cpu_enemy(enemy_properties &enemy_prop,Vector2 pos)
{
    if(enemy_prop.posy <  pos.y){enemy_prop.posy += enemy_prop.speed;}
    if(enemy_prop.posy >  pos.y){enemy_prop.posy -= enemy_prop.speed;}
}

int main()
{
    InitWindow(screen_width,screen_height,"Main_window");
    bullet = LoadTexture("C:/Users/archlinuxnotsohappy/Desktop/Raylib_cpp/src/bullet.png");
    enemy_bullet = LoadTexture("C:/Users/archlinuxnotsohappy/Desktop/Raylib_cpp/src/bullet1.png");
    player = LoadTexture("C:/Users/archlinuxnotsohappy/Desktop/Raylib_cpp/src/space_ship2.png");
    enemy = LoadTexture("C:/Users/archlinuxnotsohappy/Desktop/Raylib_cpp/src/enemy_ship.png");
    pos.x = screen_width - player.width;
    pos.y = 200;

    enemy_prop.posx = 0; 
    enemy_prop.posy = GetRandomValue(0,screen_height - enemy.height);
    enemy_prop.health = 50;
    enemy_prop.speed = 2;
    enemy_prop.height = enemy.height;
    enemy_prop.width = enemy.width;

    for(int i = 0; i < bullet_number; i++)
    {
        Bullet[i].height = bullet.height;
        Bullet[i].width = bullet.width;
    }

    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        movement(pos,Bullet,enemy_prop);
        boundary_check(pos);
        DrawTexture(player,pos.x,pos.y,WHITE);
        DrawTexture(enemy,enemy_prop.posx,enemy_prop.posy,WHITE);
        cpu_enemy(enemy_prop,pos);
        for(int i = 0; i < bullet_number; i++)
            {
                if(Bullet[i].bullet_active == true)
                {
                    DrawTexture(bullet,Bullet[i].bullet_pos.x,Bullet[i].bullet_pos.y,WHITE);
                    Bullet[i].bullet_pos.x -= speed;
                    if(checkcollision(enemy_prop,Bullet,i) == true)
                   {
                    enemy_prop.health -= 25;
                    reset_bullet(i);
                    if(enemy_prop.health <= 0)
                    {
                        reset_enemy(enemy_prop);
                    }
                   }
                }
            }
        for(int i = 0 ; i < bullet_number; i++)
        {
            if(Bullet[i].bullet_pos.x < 0 )
        {
            reset_bullet(i);
        }
        }
        EndDrawing();
        
    }
    UnloadTexture(player);
    UnloadTexture(bullet);
    UnloadTexture(enemy);
    UnloadTexture(enemy_bullet);
    CloseWindow();
}