#include <iostream>
#include "raylib.h"
#include "game_config.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"

// the use of extern keyword in the .h files . extern is a keyword that tells compiler that this is variable declaration and NOT variable defination go find it in cpp or other file 

bool start_game = false;

int main()
{
    InitWindow(screen_width,screen_height,"Main_window");

    double score;
    double start_time;

    load_resources(player,enemy,bullet,enemy_bullet);

    game_reset(); 


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
        if(start_game == false)
        {
            DrawText("Press SPACE to start",0,0,20,WHITE);
            DrawText("WASD to move",0,20,20,WHITE);
            DrawText("SPACE to shoot",0,40,20,WHITE);
            if(IsKeyPressed(KEY_SPACE)){start_game = true;}

            start_time = GetTime();
            
            game_reset();

        }
        if(start_game)
        {
        if(player_prop.health > 0)
        {
        score =  GetTime() - start_time; 
        reset_enemy_state(enemy_state,enemy_prop);
        movement(player_prop.pos,Bullet,enemy_prop);
        boundary_check(player_prop.pos);
        DrawTexture(player,player_prop.pos.x,player_prop.pos.y,WHITE);
        DrawTexture(enemy,enemy_prop.posx,enemy_prop.posy,WHITE);
        cpu_enemy(enemy_prop,player_prop.pos,cool_down); 
        if(collision_objects(player_prop,enemy_prop))
        {
            DrawText("You were BUMPED into!!", 0, 0, 20, WHITE);
            player_prop.health = 0;
        }
        //bullet logic for player
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
        // bullet logic for enemy
        if(GetTime() - last_time_shot > cool_down)
        {
            for(int i = 0; i < enemy_bullet_number; i++)
            {
                    if(bullet_enemy[i].bullet_active == false)
                    {
                    put_bullet1(i);
                    last_time_shot = GetTime();
                    break;
                    }
                    
            }
        }  
        for(int i = 0; i < enemy_bullet_number;i++)
        {
            if(bullet_enemy[i].bullet_active == true)
            {
                DrawTexture(enemy_bullet,bullet_enemy[i].bullet_pos.x,bullet_enemy[i].bullet_pos.y,WHITE);
                bullet_enemy[i].bullet_pos.x += speed;
                if(collisionbullet(player_prop,bullet_enemy,i))
                {
                    player_prop.health -= 25;
                }
            }
        }     
        for(int i = 0 ; i < enemy_bullet_number; i++)
        {
            if(bullet_enemy[i].bullet_pos.x > screen_width - enemy.width)
          {
            bullet_enemy[i].bullet_active = false;
          }
        }
        }
        
        if(player_prop.health <= 0)
        {
            ClearBackground(SKYBLUE);
            DrawText(TextFormat("Score: %.1f",score),0,0,20,WHITE);
            DrawText("Press R to restart",0,20,20,WHITE);
            DrawText("Game Over",screen_width/2,screen_height/2,40,WHITE);
            start_game = true;
            if(IsKeyPressed(KEY_R)){start_game = false;}
        }
    
        }
        EndDrawing();

        
    }
    unload_resources(player,enemy,bullet,enemy_bullet);
    CloseWindow();
}