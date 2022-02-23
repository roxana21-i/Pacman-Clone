#include "game_logic.h"

//player character
extern Pacman pacman(1, 1);

//enemy ghosts
extern Ghost ghost1(1, 26, 2, 1.0f, 0.0f, 0.0f);
extern Ghost ghost2(21, 12, 3, 0.0f, 1.0f, 0.0f);
extern Ghost ghost3(8, 12, 2, 1.0f, 1.0f, 0.0f);
extern Ghost ghost4(29, 15, 1, 0.0f, 1.0f, 1.0f);

void drawLives() {
    int x = 735;
    int y = 915;

    int triangleAmount = 360; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * M_PI;
    GLfloat radius = 9;

    for (int i = 1; i <= pacman.getLives(); i++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 0);
        glVertex2f(x, y); // center of circle
        for (int j = 40; j <= 320; j++) {
            glVertex2f(
                x + (radius * cos(j * twicePi / triangleAmount)),
                y + (radius * sin(j * twicePi / triangleAmount))
            );
        }
        glEnd();
        x += 30;
    }
}

void restart() {
    pacman.moveToStart();
    pacman.resetLives();
    pacman.resetScore();
}

void keyboard() {

    if (GetAsyncKeyState(VK_UP)) {
        if (!pacman.checkWall(pacman.getI() - 1, pacman.getJ())) {
            direction = 1;
            move = true;
        }
        else {
            std::cout << "Wall";
        }
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        if (!pacman.checkWall(pacman.getI() + 1, pacman.getJ())) {
            direction = 2;
            move = true;
        }
        else {
            std::cout << "Wall";
        }
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        if (!pacman.checkWall(pacman.getI(), pacman.getJ() - 1)) {
            direction = 3;
            move = true;
        }
        else {
            std::cout << "Wall";
        }
    }

    if (GetAsyncKeyState(VK_RIGHT)) {
        if (!pacman.checkWall(pacman.getI(), pacman.getJ() + 1)) {
            direction = 4;
            move = true;
        }
        else {
            std::cout << "Wall";
        }
    }

    if (GetAsyncKeyState(VK_W)) {
        resetBoard();
        restart();
        still_alive = true;
    }

}

void movePacman() {
    if (direction == 1) {
        move = !pacman.checkWall(pacman.getI() - 1, pacman.getJ());
        if (move) {
            pacman.moveUp(pacman_speed);
            pacman.setOrientation(50);
        }
    }
    if (direction == 2) {
        move = !pacman.checkWall(pacman.getI() + 1, pacman.getJ());
        if (move) {
            pacman.moveDown(pacman_speed);
            pacman.setOrientation(230);
        }
    }
    if (direction == 3) {
        move = !pacman.checkWall(pacman.getI(), pacman.getJ() - 1);
        if (move) {
            pacman.moveLeft(pacman_speed);
            pacman.setOrientation(140);
        }
        if (pacman.getI() == 14 && pacman.getJ() == 0) {
            pacman.increaseScore(10);
            board[pacman.getI()][pacman.getJ()] = -1;
            pebble_counter += 1;
            pacman.moveTo(14, 27);
        }
    }
    if (direction == 4) {
        move = !pacman.checkWall(pacman.getI(), pacman.getJ() + 1);
        if (move) {
            pacman.moveRight(pacman_speed);
            pacman.setOrientation(320);
        }
        if (pacman.getI() == 14 && pacman.getJ() == 27) {
            pacman.increaseScore(10);
            board[pacman.getI()][pacman.getJ()] = -1;
            pebble_counter += 1;
            pacman.moveTo(14, 0);
        }
    }
}

void checkScore() {
    if (board[pacman.getI()][pacman.getJ()] == 1) {
        if ((pacman.getI() == 1 && pacman.getJ() == 26) || (pacman.getI() == 29 && pacman.getJ() == 1) || (pacman.getI() == 29 && pacman.getJ() == 26)) {
            pacman.increaseScore(100);
            if (is_blue_mode == true) {
                duration += 300;
            }
            else {
                is_blue_mode = true;
            }
        }
        else
            pacman.increaseScore(10);
        board[pacman.getI()][pacman.getJ()] = -1;
        pebble_counter += 1;
    }

    if (pebble_counter == 300) {
        pebble_counter = 0;
        resetBoard();
    }
}

void moveGhost(Ghost& ghost) {

    if (ghost.isDead() == true && ghost.getTimer() > 0) {
        ghost.decreaseTimer();
    }
    else {
        if (ghost.getMove() == false)
            ghost.checkPossibleMovement();

        if (ghost.getDirection() == 1) {
            ghost.setMove(!ghost.checkWall(ghost.getI() - 1, ghost.getJ()));
            if (ghost.getMove()) {
                ghost.moveUp(ghost_speed);
            }
        }
        if (ghost.getDirection() == 2) {
            ghost.setMove(!ghost.checkWall(ghost.getI() + 1, ghost.getJ()));
            if (ghost.getMove()) {
                ghost.moveDown(ghost_speed);
            }
        }
        if (ghost.getDirection() == 3) {
            ghost.setMove(!ghost.checkWall(ghost.getI(), ghost.getJ() - 1));
            if (ghost.getMove()) {
                ghost.moveLeft(ghost_speed);
            }
        }
        if (ghost.getDirection() == 4) {
            ghost.setMove(!ghost.checkWall(ghost.getI(), ghost.getJ() + 1));
            if (ghost.getMove()) {
                ghost.moveRight(ghost_speed);
            }
        }
    }
}

void checkCollision(Ghost& ghost) {
    if (pacman.getI() == ghost.getI() && pacman.getJ() == ghost.getJ()) {
        if (is_blue_mode) {
            pacman.increaseScore(200);
            ghost.die();
        }
        else {
            pacman.die();
            pacman.moveToStart();
        }
    }
}

void checkColisions() {
    checkCollision(ghost1);
    checkCollision(ghost2);
    checkCollision(ghost3);
    checkCollision(ghost4);
}

std::string int2str(int x) {
    // converts int to string
    std::stringstream ss;
    ss << x;
    return ss.str();
}

void resetBoard() {
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 28; j++) {
            if (board[i][j] == -1)
                board[i][j] = 1;
        }
    }
}

void draw() {
    // clear (has to be done at the beginning)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawBoard();

    drawPacman(pacman.getX(), pacman.getY(), pacman.getOrientation());

    if (is_blue_mode == false) {
        drawGhost(ghost1.getX(), ghost1.getY(), ghost1.getR(), ghost1.getG(), ghost1.getB());
        drawGhost(ghost2.getX(), ghost2.getY(), ghost2.getR(), ghost2.getG(), ghost2.getB());
        drawGhost(ghost3.getX(), ghost3.getY(), ghost3.getR(), ghost3.getG(), ghost3.getB());
        drawGhost(ghost4.getX(), ghost4.getY(), ghost4.getR(), ghost4.getG(), ghost4.getB());
    }
    else {
        drawGhost(ghost1.getX(), ghost1.getY(), 0, 0, 1);
        drawGhost(ghost2.getX(), ghost2.getY(), 0, 0, 1);
        drawGhost(ghost3.getX(), ghost3.getY(), 0, 0, 1);
        drawGhost(ghost4.getX(), ghost4.getY(), 0, 0, 1);
    }

    drawLives();
    drawText(30, height - 15, "Score: " + int2str(pacman.getScore()));

    if (still_alive == false) {
        drawOpaqueRect(0, 0, 840, 930, 0.0f, 0.0f, 0.0f);
        drawTextBig(11.5 * 30, 900 - 13 * 30, "GAME OVER");
        drawTextBig(11.5 * 30, 900 - 14 * 30, "Press W to start again");
        keyboard();
    }

    // swap buffers (has to be done at the end)
    glutSwapBuffers();
}

void update(int value) {
    // input handling
    keyboard();

    movePacman();

    checkScore();

    if (is_blue_mode && duration > 0)
        duration -= 1;
    else {
        is_blue_mode = false;
        duration = 300;
    }


    moveGhost(ghost1);
    moveGhost(ghost2);
    moveGhost(ghost3);
    moveGhost(ghost4);

    checkColisions();

    // Call update() again in 'interval' milliseconds
    //if (still_alive)
    glutTimerFunc(interval, update, 0);

    // Redisplay frame
    glutPostRedisplay();
}


void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
