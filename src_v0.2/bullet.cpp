// import neseccary files
#include "bullet.h"
#include "player.h"
#include "game_config.h"
// define 
Texture2D bullet;
Texture2D enemy_bullet;

bullet_stuct Bullet[bullet_number];

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
    Bullet[i].bullet_pos.x = player_prop.pos.x;
    Bullet[i].bullet_pos.y = player_prop.pos.y + player.height / 2 - 15; // magic numbers here are used to center the bullet
}

void reset_bullet(int i)
{
    Bullet[i].bullet_active = false;
    Bullet[i].bullet_pos.x = screen_width - player.width;
}
