#include <cstdint>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "CollisionsAndBullets.h"
#include "Entities.h"
#include "Images.h"

extern uint8_t bomb_flag;

void setBulletPosandDirection(bullet_t* bullet, player_t* player)
{
	if(player->direction== East){
		bullet->x = player->x+(player->width);
		bullet->y = player->y+(player->height/2);
		bullet->direction = East;
	}
	if(player->direction== West){
        bullet->x = player->x;
		bullet->y = player->y+((player->height)-7);
		bullet->direction = West;

	}
	if(player->direction== South){
		bullet->x = player->x+9;
		bullet->y = player->y;
	    bullet->direction = South;

	}
	if(player->direction== North){
		bullet->x = player->x + 14;
		bullet->y = player->y+((player->height));;
		bullet->direction = North;

	}
	if(player->direction== SouthEast){
		bullet->x = player->x +2;
		bullet->y = player->y+(player->height);
		bullet->direction = SouthEast;

	}
	if(player->direction== SouthWest){
		bullet->x = player->x;
		bullet->y = player->y+3;
		bullet->direction = SouthWest;

	}
	if(player->direction== NorthEast){
		bullet->x = player->x+player->width;
		bullet->y = player->y+player->height;
		bullet->direction = NorthEast;

	}
	if(player->direction== NorthWest){
		bullet->x = player->x + ((player->width));
		bullet->y = player->y -3;
		bullet->direction = NorthWest;

	}
}

void moveBullet(bullet_t* bullet){
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullet[i].active == true) {
            if (!isBulletOutOfBounds(&bullet[i])) {
                if(bullet[i].direction == East){
                    bullet[i].x += 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].x -= 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            GPIOA->DOUTSET31_0 = (1 << 28);
                            bullet[i].active = false;
                            bullet[i].x -= 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                            GPIOA->DOUTCLR31_0 = (1 << 28);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            GPIOA->DOUTSET31_0 = (1 << 28);
                            bullet[i].active = false;
                            bullet[i].x -= 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                            GPIOA->DOUTCLR31_0 = (1 << 28);
                        }
                    }
                }

                if(bullet[i].direction== West){
                    bullet[i].x -= 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].x += 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].x += 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].x += 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== North){
                    bullet[i].y += 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y -= 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== South){
                    bullet[i].y -= 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y += 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== NorthWest){
                    bullet[i].y -= 1;
                    bullet[i].x += 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y += 1;
                        bullet[i].x -= 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            bullet[i].x -= 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            bullet[i].x -= 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== SouthWest){
                    bullet[i].y -= 1;
                    bullet[i].x -= 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y += 1;
                        bullet[i].x += 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            bullet[i].x += 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y += 1;
                            bullet[i].x += 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== NorthEast){
                    bullet[i].y += 1;
                    bullet[i].x += 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y -= 1;
                        bullet[i].x -= 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            bullet[i].x -= 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            bullet[i].x -= 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }

                if(bullet[i].direction== SouthEast){
                    bullet[i].y += 1;
                    bullet[i].x -= 1;

                    if (checkBulletHitsBox(bullet)) {
                        bullet[i].active = false;
                        bullet[i].y -= 1;
                        bullet[i].x += 1;
                        ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                    }

                    if (bullet[i].player == 1) {
                        if (checkBulletHitsPlayer(&bullet[i], &Player1)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            bullet[i].x += 1;
                            Player1.health -= 1;
                            if (Player1.health <= 0) {
                                ST7735_FillRect(Player1.x, Player1.y, Player1.width, Player1.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    } else {
                        if (checkBulletHitsPlayer(&bullet[i], &Player2)) {
                            bullet[i].active = false;
                            bullet[i].y -= 1;
                            bullet[i].x += 1;
                            Player2.health -= 1;
                            if (Player2.health <= 0) {
                                ST7735_FillRect(Player2.x, Player2.y, Player2.width, Player2.height, ST7735_SAND);
                            }
                            ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                        }
                    }
                }
            } else {
                bullet[i].active = false;
                ST7735_FillRect(bullet[i].x, bullet[i].y - 4, bullet[i].width, bullet[i].height, ST7735_SAND);
                continue;
            }
        }
    }
}


// bool checkPlayerHitsBox(player_t* player, box_t* box)
// {
//     return ((player->x + player->width > box->x) &&
//             (player->x < box->x + box->width) &&
//             (player->y + player->height > box->y) &&
//             (player->y < box->y + box->height));

//     // return !(player->x + player->width <= box->x ||
//     //          player->x >= box->x + box->width ||
//     //          player->y + player->height <= box->y ||
//     //          player->y >= box->y + box->height);
// }

bool checkPlayerHitsBox(player_t* player) {
    int px = player->x;
    int py = player->y;
    int pw = player->width;
    int ph = player->height;

    // Box 1: (32, 71) to (63, 73)
    if (px < 63 && px + pw > 32 &&
        py < 67 && py + ph > 65)
        return true;

    // Box 2: (0, 112) to (52, 114)
    if (px < 52 && px + pw > 0 &&
        py < 114 && py + ph > 112)
        return true;

    // Box 3: (50, 115) to (52, 124)
    if (px < 52 && px + pw > 50 &&
        py < 124 && py + ph > 115)
        return true;

    // Box 4: (79, 96) to (102, 122)
    if (px < 102 && px + pw > 79 &&
        py < 122 && py + ph > 97)
        return true;

    // Box 5: (84, 34) to (127, 36)
    if (px < 127 && px + pw > 84 &&
        py < 36 && py + ph > 34)
        return true;
    
    if (px < 9 && px + pw > 0 &&
        py < 124 && py + ph > 116) {
            bomb_flag = 1;
            return true;
        }

    return false;
}

uint8_t checkBombCollision(player_t* player) {
    int px = player->x;
    int py = player->y;
    int pw = player->width;
    int ph = player->height;

    if (px < 12 && px + pw > 0 &&
        py < 129 && py + ph > 116)
        return 1;
    
    return 0;
}

bool checkBulletHitsBox(bullet_t* bullet) {
    int px = bullet->x;
    int py = bullet->y;
    int pw = bullet->width;
    int ph = bullet->height;

    // Box 1: (32, 71) to (63, 73)
    if (px < 63 && px + pw > 32 &&
        py < 67 && py + ph > 65)
        return true;

    // Box 2: (0, 112) to (52, 114)
    if (px < 52 && px + pw > 0 &&
        py < 114 && py + ph > 112)
        return true;

    // Box 3: (50, 115) to (52, 124)
    if (px < 52 && px + pw > 50 &&
        py < 124 && py + ph > 115)
        return true;

    // Box 4: (79, 96) to (102, 122)
    if (px < 102 && px + pw > 79 &&
        py < 122 && py + ph > 97)
        return true;

    // Box 5: (84, 34) to (127, 36)
    if (px < 127 && px + pw > 84 &&
        py < 36 && py + ph > 34)
        return true;

    return false;
}

bool checkPlayerHitsPlayer(player_t* player, player_t* player2)
{   
    if (player->health > 0 && player2->health > 0) {
    return ((player->x + player->width - 3 > player2->x) &&
            (player->x < player2->x + player2->width - 3) &&
            (player->y + player->height - 3 > player2->y) &&
            (player->y < player2->y + player2->height - 3));
    }
    return false;
}


// 2. Bullet Hits Player
bool checkBulletHitsPlayer(bullet_t* bullet, player_t* player)
{
    return ((bullet->x + bullet->width > player->x) &&
            (bullet->x < player->x + player->width) &&
            (bullet->y + bullet->height > player->y) &&
            (bullet->y < player->y + player->height));
}

// // 3. Bullet Hits Box
// bool checkBulletHitsBox(Bullet* bullet, Box* box)
// {
//     return ((bullet->x + bullet->width > box->x) &&
//             (bullet->x < box->x + box->width) &&
//             (bullet->y + bullet->height > box->y) &&
//             (bullet->y < box->y + box->height));
// }

// 4-> Player Out of Bounds
bool isPlayerOutOfBounds(Player* player)
{
    return (player->x <= 0 ||
            player->x > (128 - player->width) ||
            player->y <= 0 ||
            (player->y + player->height) > 160);
}

// 5-> Bullet Out of Bounds
bool isBulletOutOfBounds(Bullet* bullet)
{
    return (bullet->x <= 0 ||
            bullet->x > 134 ||    // adjust if your screen width differs
            bullet->y <= 0 ||
            bullet->y > 164);     // adjust if your screen height differs
}
