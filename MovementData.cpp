#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"

#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "Images.h"
#include "MovementData.h"
#include "CollisionsAndBullets.h"

player_t Player1;
player_t Player2;

extern box_t TestBox;


void checkPlayerDirection(player_t* player)
{
	if(JoyX.Distance()<= 700){
		player->direction = West;
        player->player_image = PlayerWest;
	}
	if(JoyX.Distance()>= 900){
		player->direction = East;
        player->player_image = PlayerEast;
	}
	if(JoyY.Distance() >= 900){
		player->direction = South;
        player->player_image = PlayerSouth;
	}
	if(JoyY.Distance() <= 700){
		player->direction = North;
        player->player_image = PlayerNorth;
	}
	if((JoyX.Distance()<= 700)&&(JoyY.Distance() >= 900)){
		player->direction = SouthWest;
        player->player_image = PlayerSouthWest;
	}
	if((JoyX.Distance()<= 700)&&(JoyY.Distance() <= 700)){
		player->direction = SouthEast;
        player->player_image = PlayerSouthEast;
	}
	if((JoyX.Distance()>= 900)&&(JoyY.Distance() >= 900)){
		player->direction = NorthWest;
        player->player_image = PlayerNorthWest;
	}
	if((JoyX.Distance()>= 900)&&(JoyY.Distance() <= 700)){
		player->direction = NorthEast;
        player->player_image = PlayerNorthEast;
	}
}

void checkPlayerDirection2(player_t* player)
{
	if(Joy2X.Distance()<= 700){
		player->direction = West;
        player->player_image = PlayerWest;
	}
	if(Joy2X.Distance()>= 900){
		player->direction = East;
        player->player_image = PlayerEast;
	}
	if(Joy2Y.Distance() <= 700){
		player->direction = South;
        player->player_image = PlayerSouth;
	}
	if(Joy2Y.Distance() >= 900){
		player->direction = North;
        player->player_image = PlayerNorth;
	}
	if((Joy2X.Distance()<= 700)&&(Joy2Y.Distance() <= 700)){
		player->direction = SouthWest;
        player->player_image = PlayerSouthWest;
	}
	if((Joy2X.Distance()>= 900)&&(Joy2Y.Distance() <= 700)){
		player->direction = NorthWest;
        player->player_image = PlayerNorthWest;
	}
	if((Joy2X.Distance()<= 700)&&(Joy2Y.Distance() >= 900)){
		player->direction = SouthEast;
        player->player_image = PlayerSouthEast;
	}
	if((Joy2X.Distance()>= 900)&&(Joy2Y.Distance() >= 900)){
		player->direction = NorthEast;
        player->player_image = PlayerNorthEast;
	}
}

// void checkBulletDirectionAndPos(void)
// {
	
// 	if(player->){
// 		player->direction = East;
// 	}
// }

bool isMoving(player_t* player){
    if(((JoyX.Distance()<= 900) && (JoyX.Distance()>= 700))&&((JoyY.Distance()<= 900) && (JoyY.Distance()>= 700))){
		return false;
	}
    return true;
}

bool isMoving2(player_t* player){
    if(((Joy2X.Distance()<= 900) && (Joy2X.Distance()>= 700))&&((Joy2Y.Distance()<= 900) && (Joy2Y.Distance()>= 700))){
		return false;
	}
    return true;
}

void movePlayer(player_t* player){
		if(player->direction == North){
			(player->y)++;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->y)--;
			}
		}
		if(player->direction == South){
			(player->y)--;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->y)++;
			}
		}
		if(player->direction == East){
			(player->x)++;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)--;
			}
		}
		if(player->direction == West){
			(player->x)--;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)++;
			}
		}
		if(player->direction == NorthEast){
			(player->x)++;
			(player->y)++;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)--;
				(player->y)--;
			}

		}if(player->direction == NorthWest){

			(player->x)++;
			(player->y)--;
			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)--;
				(player->y)++;
			}

		}if(player->direction == SouthEast){
			(player->x)--;
			(player->y)++;

			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)++;
				(player->y)--;
			}

		}if(player->direction == SouthWest){
			(player->x)--;
			(player->y)--;

			if (isPlayerOutOfBounds(player) || checkPlayerHitsPlayer(&Player1, &Player2) || checkPlayerHitsBox(player)) {
				(player->x)++;
				(player->y)++;
			}
		}
}


// void moveBullet(void){
// 	if(bullet.direction == right){
// 		bullet->x += 1;
// 	}
// 	if(bullet.direction== left){
// 		bullet->x -= 1;
// 	}
// 	if(bullet.direction== up){
// 		bullet->y += 1;
// 	}
// 	if(bullet.direction== down){
// 		bullet->y -= 1;
// 	}
// 	if(bullet.direction== dRight){
// 		bullet->y -= 1;
// 		bullet->x += 1;
// 	}
// 	if(bullet.direction== dLeft){
// 		bullet->y -= 1;
// 		bullet->x -= 1;
// 	}
// 	if(bullet.direction== uRight){
// 		bullet.y += 1;
// 		bullet.x += 1;
// 	}
// 	if(bullet.direction== uLeft){
// 		bullet->y += 1;
// 		bullet->x -= 1;
// 	}
// }

// bool checkCollision (spriteData_t sprite1, spriteData_t sprite2)
// {
//     // Enforce screen boundaries 
//     if(player->xPos > (155 - player->width)) player->xPos--;
//     if(player->xPos < 5) player->xPos++;
//     if(player->yPos < 5) player->yPos++;
//     if((player->yPos + player->height) > 115) player->yPos--;

    
//     if ((sprite1->xPos + sprite1->width > sprite2->xPos) &&
//         (sprite1->xPos < sprite2->xPos + sprite2->width) &&
//         (sprite1->yPos + sprite1->height > sprite2->yPos) &&
//         (sprite1->yPos < sprite2->yPos + sprite2->height)) {
//         return true; // collision
//     }

//     return false; // no collision
// }


// bool checkboundaries ()
// {
//     // Enforce screen boundaries 
//     if(player->x > (155 - player->width))
//         player->x--;
//     if(player->x < 5)
//         player->x++;
//     if(player->y < 5)
//         player->y++;
//     if((player->y + player->height) > 115) 
//         player->y--;
// }