#include <cstdint>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#ifndef ENTITIES_H
#define ENTITIES_H

#define MAX_BULLETS 5

typedef enum Direction {
    North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest
} direction_t;

typedef struct Player {
    uint8_t x;
    uint8_t y;
    uint8_t xvelocity;
    uint8_t yvelocity;
    uint8_t height;
    uint8_t width;
    int8_t health;
    uint8_t tick_counter;
    direction_t direction;
    const uint16_t* player_image;
} player_t;

typedef struct Bullet {
    uint8_t x;
    uint8_t y;
    uint8_t height = 4;
    uint8_t width = 4;
    uint8_t player;
    direction_t direction;
    bool active = false;
    const uint16_t* bullet_image;
} bullet_t;

typedef struct Box {
    uint8_t x;
    uint8_t y;
    uint8_t height;
    uint8_t width;
    bool defused;
    const uint16_t* box_image;
} box_t;

extern bullet_t BulletArray[MAX_BULLETS];

void Box_Init(box_t* box_ptr, uint8_t x, uint8_t y);
void Box_Draw(box_t* box_ptr);

void Bullet_Init(bullet_t* bullet, player_t* player);
void Bullet_Update(bullet_t* bullet);
void Bullet_Draw(bullet_t* bullet);

void Player_Init(player_t* player, uint32_t x, uint32_t y);
void Player_Update(player_t* player);
void Player_Update2(player_t* player);
void Player_Draw(player_t* player);

// typedef struct Zombie {
//     uint8_t x;
//     uint8_t y;
//     uint8_t xvelocity;
//     uint8_t yvelocity;
//     uint8_t height;
//     uint8_t width;
//     uint8_t health;
//     bool rendered = false;
//     const uint16_t* zombie_image_ptr;  // assign in code, not here
// } zombie_t;

// void Zombie_Init(zombie_t* zombie_ptr, uint8_t x, uint8_t y, uint8_t vy, const uint16_t* image_ptr);
// void Zombie_Update(zombie_t* z);
// void Zombie_Spawn();
// void Zombie_Draw(zombie_t* z);
// void Zombie_Kill(zombie_t* z);

// extern zombie_t zombie_sprites_array[MAX_ZOMBIES];
// extern uint8_t spawncount;
// extern bool spawn_request;

extern uint32_t Random(uint32_t n);
extern uint32_t tick_counter;

extern player_t Player1;
extern player_t Player2;

#endif  // ENTITIES_H
