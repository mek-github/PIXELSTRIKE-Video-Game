#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Entities.h"

void checkPlayerDirection(player_t* player);
bool isMoving(player_t* player);

void checkPlayerDirection2(player_t* player);
bool isMoving2(player_t* player);

void movePlayer(player_t* player);
// void moveBullet(void);
// bool checkCollision (spriteData_t sprite1, spriteData_t sprite2);
// bool checkboundaries ();