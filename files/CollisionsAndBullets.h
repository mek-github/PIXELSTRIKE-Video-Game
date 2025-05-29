#include <cstdint>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "Entities.h"
#include "../inc/ST7735.h"

void setBulletPosandDirection(bullet_t* bullet, player_t* player);
void moveBullet(bullet_t* bullet);
bool checkPlayerHitsBox(player_t* player);
bool checkBulletHitsBox(bullet_t* bullet);
uint8_t checkBombCollision(player_t* player);
bool checkPlayerHitsPlayer(player_t* player, player_t* player2);
bool checkBulletHitsPlayer(bullet_t* bullet, player_t* player);
// bool checkBulletHitsBox(Bullet* bullet, Box* box);
bool isPlayerOutOfBounds(Player* player);
bool isBulletOutOfBounds(Bullet* bullet);
