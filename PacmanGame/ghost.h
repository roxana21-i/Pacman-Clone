/*
DEFINITON OF GHOST CLASS
*/

#pragma once
#ifndef GHOST_H
#define GHOST_H
class Ghost
{
    int x;
    int y;
    int i;
    int j;
    int mode;

    float colors[3];

    int direction;
    int prev_dir;
    bool move;

    bool dead;
    int death_timer;

public:

    Ghost(int rows, int columns, int d, float r, float g, float b);

    float getX();

    float getY();

    int getI();

    int getJ();

    int getDirection();

    bool getMove();

    float getR();

    float getG();

    float getB();

    void setDirection(int d);

    void setMove(bool m);

    bool isDead();

    int getTimer();

    void decreaseTimer();

    void moveUp(int distance);

    void moveDown(int distance);

    void moveRight(int distance);

    void moveLeft(int distance);

    void die();

    bool checkWall(int i, int j);

    void checkPossibleMovement();
};

#endif