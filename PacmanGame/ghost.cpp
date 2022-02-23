#include "ghost.h"
#include "globals.h"

    Ghost::Ghost(int rows, int columns, int d, float r, float g, float b) {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
        i = rows;
        j = columns;
        direction = d;
        move = true;
        dead = false;
        death_timer = 180;

        x = j * 30;
        y = 900 - i * 30;
    }

    float Ghost::getX() {
        return x;  
    }

    float Ghost::getY() {
        return y;
    }

    int Ghost::getI() {
        return i;
    }

    int Ghost::getJ() {
        return j;
    }

    int Ghost::getDirection() {
        return direction;
    }

    bool Ghost::getMove() {
        return move;
    }

    float Ghost::getR() {
        return colors[0];
    }

    float Ghost::getG() {
        return colors[1];
    }

    float Ghost::getB() {
        return colors[2];
    }

    void Ghost::setDirection(int d) {
        direction = d;
    }

    void Ghost::setMove(bool m) {
        move = m;
    }

    bool Ghost::isDead() {
        return dead;
    }

    int Ghost::getTimer() {
        return death_timer;
    }

    void Ghost::decreaseTimer() {
        death_timer -= 1;
    }

    void Ghost::moveUp(int distance) {
        y += distance;
        if (y % 30 == 0) {
            i = 30 - y / 30;
            //std::cout << i << std::endl;
        }
    }

    void Ghost::moveDown(int distance) {
        y -= distance;
        if (y % 30 == 0) {
            i = 30 - y / 30;
            //std::cout << i << std::endl;
        }
    }

    void Ghost::moveRight(int distance) {
        x += distance;
        //std::cout << j << std::endl;
        if (x % 30 == 0) {
            j = x / 30;
            //std::cout << j << std::endl;
        }
    }

    void Ghost::moveLeft(int distance) {
        x -= distance;
        if (x % 30 == 0) {
            j = x / 30;
            //std::cout << j << " " << i << std::endl;
        }
    }

    void Ghost::die() {
        i = 13;
        j = 13;

        x = j * 30;
        y = 900 - i * 30;

        direction = 1;

        dead = true;
        death_timer = 180;
    }

    bool Ghost::checkWall(int i, int j) {
        if (board[i][j] == 0)
            return true;
        return false;
    }

    void Ghost::checkPossibleMovement() {
        srand(time(NULL));
        int posibilities[4] = { 0,0,0,0 };
        int random = rand() % 4;

        if (checkWall(i - 1, j) == false && direction != 2)
            posibilities[0] = 1;
        if (checkWall(i + 1, j) == false && direction != 1)
            posibilities[1] = 1;
        if (checkWall(i, j - 1) == false && direction != 4)
            posibilities[2] = 1;
        if (checkWall(i, j + 1) == false && direction != 3)
            posibilities[3] = 1;

        while (posibilities[random] != 1)
            random = rand() % 4;


        direction = random + 1;

        //std::cout << prev_dir << " " << direction << std::endl;
    }