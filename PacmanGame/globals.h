/*
DEFINITION OF GLOBALS AND IMPORTS USED ACCROSS MULTIPLE FILES
*/

#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glut.h>
#include<GL/freeglut.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// keycodes
#define VK_W 0x57
#define VK_S 0x53

#include "pacman.h"
#include "ghost.h"

// window size and update rate (60 fps)
extern int width;
extern int height;
extern int interval;

//square
extern float square_side;

extern int pebble_counter;

//pacman speed
extern float pacman_speed;

//ghost spped
extern float ghost_speed;

//mouth animation
extern int open;

//automatic movement
extern int direction;
extern bool move;

//status of pacman
extern bool still_alive;

//when eating the ghost
extern bool is_blue_mode;
extern int duration;

//game screen
extern int board[31][28];

#endif