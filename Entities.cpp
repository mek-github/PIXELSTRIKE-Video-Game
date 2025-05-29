#include <cstdint>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "Entities.h"
#include "Images.h"
#include "MovementData.h"
#include "CollisionsAndBullets.h"
#include "../inc/ST7735.h"


void Player_Init(player_t* player, uint32_t x, uint32_t y) {
    player->x = x;
    player->y = y;
    player->xvelocity = 0;
    player->yvelocity = 0;
    player->height = PLAYER_HEIGHT;
    player->width = PLAYER_WIDTH;
    player->health = 5;
    player->player_image = PlayerEast;
}

void Player_Update(player_t* player) {
    if (isMoving(player)) {
        checkPlayerDirection(player);
        movePlayer(player);
    } 
}

void Player_Update2(player_t* player) {
    if (isMoving2(player)) {
        checkPlayerDirection2(player);
        movePlayer(player);
    } 
}

void Player_Draw(player_t* player) {
    if (player->health > 0) {
        ST7735_DrawBitmap(player->x, player->y + player->height, player->player_image, player->width, player->height);
    }
}



void Bullet_Init(bullet_t* bullet, player_t* player) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullet[i].active == false) {
            bullet[i].active = true;
            break;
        }
    }
    if (player == &Player1) {
        bullet->player = 0;
    } else if (player == &Player2){
        bullet->player = 1;
    }
    bullet->bullet_image = BulletImage;
    setBulletPosandDirection(bullet, player);
}

void Bullet_Update(bullet_t* bullet) {
    // ST7735_FillRect(bullet->x, bullet->y, bullet->width, bullet->height, ST7735_SAND);
    moveBullet(bullet);
}

void Bullet_Draw(bullet_t* bullet) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullet[i].active == true) {
            ST7735_DrawBitmap(bullet->x, bullet->y, bullet->bullet_image, bullet->width, bullet->height);
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullet[i].active == true) {
            ST7735_FillRect(bullet->x, bullet->y, bullet->width, bullet->height, ST7735_SAND);
        }
    }
}

void Box_Init(box_t* box_ptr, uint8_t x, uint8_t y) {
    box_ptr->x = x;
    box_ptr->y = y;
    box_ptr->box_image = BombImage;
    box_ptr->width = BOMB_WIDTH;
    box_ptr->height = BOMB_HEIGHT;
    box_ptr->defused = false;
}

void Box_Draw(box_t* box_ptr) {
    ST7735_DrawBitmap(box_ptr->x, box_ptr->y, BombImage, box_ptr->width, box_ptr->height);
}

// void Zombie_Init(zombie_t* zombie_ptr, uint8_t x, uint8_t y, uint8_t vy, const uint16_t* image_ptr) {
//     zombie_ptr->x = x;
//     zombie_ptr->y = y;
//     zombie_ptr->xvelocity = 0;
//     zombie_ptr->yvelocity = vy;
//     zombie_ptr->height = ZOMBIE_HEIGHT;
//     zombie_ptr->width = ZOMBIE_WIDTH;
//     zombie_ptr->health = 1;
//     zombie_ptr->zombie_image_ptr = image_ptr; 
// }

// void Zombie_Update(zombie_t* zombie_ptr) {
//     if (zombie_ptr->rendered && tick_counter % 2 == 0) {
//         zombie_ptr->y += zombie_ptr->yvelocity;
//     }

//     if (zombie_ptr->y > 160) { // went off screen
//         zombie_ptr->rendered = false;
//     }
// }

// void Zombie_Spawn() {
//     if (spawn_request && spawncount < MAX_ZOMBIES) {
//       spawn_request = false;
//       for (int i = 0; i < MAX_ZOMBIES; i++) {
//           if (!zombie_sprites_array[i].rendered) {
//               uint8_t x = Random(128 - ZOMBIE_WIDTH); // Random x position
              
//               // Increase vertical velocity slightly for later zombies to make them harder
//               uint8_t vy = 1;
//               if (spawncount > 8) vy = 2;  // Make zombies faster after the first 8
//               if (spawncount > 15) vy = 3; // Make the last few zombies even faster
              
//               Zombie_Init(&zombie_sprites_array[i], x, 10, vy, zombie_image);
//               zombie_sprites_array[i].rendered = true;
//               spawncount++;
//               break; // only spawn one per call
//           }
//       }
//     }
// }

// void Zombie_Draw(zombie_t* z) {
//     if (z->rendered)
//         ST7735_DrawBitmap(z->x, z->y + z->height, z->zombie_image_ptr, z->width, z->height);
// }

// void Zombie_Kill(zombie_t* z) {
//   // Clear the zombie sprite visually
//   ST7735_FillRect(z->x, z->y, z->width, z->height, ST7735_BLACK); // adjust y as needed
//   // Mark zombie as not rendered
//   z->rendered = false;
//   // Reset any other relevant values if needed
//   z->x = 0;
//   z->y = 0;
//   z->xvelocity = 0;
//   z->yvelocity = 0;
//   z->health = 0;
// }