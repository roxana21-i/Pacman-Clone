#include "game_logic.h"
#include "drawing.h"

// window size and update rate (60 fps)
int width = 840;
int height = 930;
int interval = 1000 / 60;

//square
float square_side = 30;

int pebble_counter = 0;

//pacman speed
float pacman_speed = 3;

//ghost spped
float ghost_speed = pacman_speed * 1.25;

//mouth animation
int open = 0;

//automatic movement
int direction;
bool move;

bool still_alive = true;

bool is_blue_mode = false;
int duration = 300;


int board[31][28] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,2,2,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void update(int value);
void keyboard();
void resetBoard();

/* class Ghost
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

    Ghost(int rows, int columns, int d, float r, float g, float b) {
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

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    int getI() {
        return i;
    }

    int getJ() {
        return j;
    }

    int getDirection() {
        return direction;
    }

    bool getMove() {
        return move;
    }

    float getR() {
        return colors[0];
    }

    float getG() {
        return colors[1];
    }

    float getB() {
        return colors[2];
    }

    void setDirection(int d) {
        direction = d;
    }

    void setMove(bool m) {
        move = m;
    }

    bool isDead() {
        return dead;
    }

    int getTimer() {
        return death_timer;
    }

    void decreaseTimer() {
        death_timer -= 1;
    }

    void moveUp(int distance) {
        y += distance;
        if (y % 30 == 0) {
            i = 30 - y / 30;
            //std::cout << i << std::endl;
        }
    }

    void moveDown(int distance) {
        y -= distance;
        if (y % 30 == 0) {
            i = 30 - y / 30;
            //std::cout << i << std::endl;
        }
    }

    void moveRight(int distance) {
        x += distance;
        //std::cout << j << std::endl;
        if (x % 30 == 0) {
            j = x / 30;
            //std::cout << j << std::endl;
        }
    }

    void moveLeft(int distance) {
        x -= distance;
        if (x % 30 == 0) {
            j = x / 30;
            //std::cout << j << " " << i << std::endl;
        }
    }

    void die() {
        i = 13;
        j = 13;

        x = j * 30;
        y = 900 - i * 30;

        direction = 1;

        dead = true;
        death_timer = 180;
    }

    bool checkWall(int i, int j) {
        if (board[i][j] == 0)
            return true;
        return false;
    }

    void checkPossibleMovement() {
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
}; */

/*class Pacman
{
    int position[2];
    int score;
    int lives;
    int coordinates[2];
    int orientation;

public:

    Pacman(int i, int j) {
        position[0] = i;
        position[1] = j;

        score = 0;
        lives = 3;
        coordinates[0] = j * 30;
        coordinates[1] = 900 - i * 30;
        orientation = 240;
    }

    void increaseScore(int points) {
        score += points;
    }

    void die() {
        if (lives > 0) {
            lives -= 1;
        }
        else {
            //death animation??
            //game over text over screen
            still_alive = false;
            std::cout << "U ded";
        }
    }

    int getX() {
        return coordinates[0];
    }

    void setX(int x) {
        coordinates[0] = x;
    }

    int getY() {
        return coordinates[1];
    }

    void setY(int y) {
        coordinates[1] = y;
    }

    int getI() {
        return position[0];
    }

    int getJ() {
        return position[1];
    }

    int getScore() {
        return score;
    }

    int getLives() {
        return lives;
    }

    void resetLives() {
        lives = 3;
    }

    void resetScore() {
        score = 0;
    }

    void moveUp(int distance) {
        coordinates[1] += distance;
        if (coordinates[1] % 30 == 0) {
            position[0] = 30 - coordinates[1] / 30;
            //std::cout << position[0] << std::endl;
        }
    }

    void moveDown(int distance) {
        coordinates[1] -= distance;
        if (coordinates[1] % 30 == 0) {
            position[0] = 30 - coordinates[1] / 30;
            //std::cout << position[0] << std::endl;
        }
    }

    void moveRight(int distance) {
        coordinates[0] += distance;
        if (coordinates[0] % 30 == 0) {
            position[1] = coordinates[0] / 30;
            //std::cout << position[1] << std::endl;
        }
    }

    void moveLeft(int distance) {
        coordinates[0] -= distance;
        if (coordinates[0] % 30 == 0) {
            position[1] = coordinates[0] / 30;
            std::cout << position[1] << " " << position[0] << std::endl;
        }
    }

    void setOrientation(int o) {
        orientation = o;

    }

    int getOrientation() {
        return orientation;
    }

    bool checkWall(int i, int j) {
        if (board[i][j] == 0 || board[i][j] == 2)
            return true;
        return false;
    }

    void moveTo(int i, int j) {
        position[0] = i;
        position[1] = j;

        coordinates[0] = j * 30;
        coordinates[1] = 900 - i * 30;
    }

    void moveToStart() {
        coordinates[0] = 30;
        coordinates[1] = 870;
        position[0] = 1;
        position[1] = 1;
    }
}; */



/* void drawCircleFan(GLfloat x, GLfloat y, int o) {
    GLfloat twicePi = 2.0f * M_PI;
    GLfloat radius = 12;
    int triangleAmount = 360; //# of triangles used to draw circle
    int i;

    if (o == 320) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 0);
        glVertex2f(x, y); // center of circle
        for (i = 40 - open; i <= 320 + open; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 0);
        glVertex2f(x, y); // center of circle
        for (i = 0; i <= o + open; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 1, 0);
        glVertex2f(x, y); // center of circle
        for (i = o + 80 - open; i <= 360; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }

    open += 3;
}

void drawText(float x, float y, std::string text) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void drawTextBig(float x, float y, std::string text) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
}

void drawEmptyRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawOpaqueRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor4f(r, g, b, 0.3f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(2);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawPoint(float x, float y, float r, float g, float b, float size) {
    glColor3f(r, g, b);
    glPointSize(size);

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawPacman(GLfloat x, GLfloat y, int o) {
    int i;
    int triangleAmount = 360; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * M_PI;
    GLfloat radius = 12;

    x += 15;
    y += 15;

    //std::cout << open << " " << close << std::endl;

    if (open == 60)
        open = 0;

    drawCircleFan(x, y, o);
}

void drawGhost(GLfloat x, GLfloat y, float r, float g, float b) {
    int i;
    int triangleAmount = 360; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * M_PI;
    GLfloat radius = 10;

    GLfloat circlex = x + 15;
    GLfloat circley = y + 20;

    //draw the circle head part
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(circlex, circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            circlex + (radius * cos(i * twicePi / triangleAmount)),
            circley + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    //draw rectangle head part
    drawRect(x + 5, y + 10, 20, 10, r, g, b);

    //eye
    radius = 4;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex2f(circlex, circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            circlex + (radius * cos(i * twicePi / triangleAmount)),
            circley + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    radius = 2;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex2f(circlex, circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            circlex + (radius * cos(i * twicePi / triangleAmount)),
            circley + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    //draw small ghost feet
    GLfloat small_circlex = x + 8.80;
    GLfloat small_circley = y + 10;
    GLfloat small_radius = 3.35;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(small_circlex, small_circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            small_circlex + (small_radius * cos(i * twicePi / triangleAmount)),
            small_circley + (small_radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    small_circlex += 6.7;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(small_circlex, small_circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            small_circlex + (small_radius * cos(i * twicePi / triangleAmount)),
            small_circley + (small_radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    small_circlex += 6.65;
    small_radius = 3.3;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(small_circlex, small_circley); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            small_circlex + (small_radius * cos(i * twicePi / triangleAmount)),
            small_circley + (small_radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

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
        //std::cout << x << " ";
    }
}

void drawBoard() {
    int j;

    //draw the filled part
    for (int i = 0; i < 31; i++) {
        for (j = 0; j < 28; j++) {
            if (board[i][j] == 0) {
                drawEmptyRect(30 * j, 900 - 30 * i, 30, 30, 0.0f, 0.0f, 0.0f);
                //drawText(30 * j + 15, 900 - 30 * i + 15, "0");
            }
            else if (board[i][j] == 1) {
                drawPoint(30 * j + 15, 900 - 30 * i + 15, 255, 255, 255, 3.0f);
                if ((i == 1 && j == 26) || (i == 29 && j == 1) || (i == 29 && j == 26))
                    drawPoint(30 * j + 15, 900 - 30 * i + 15, 255, 255, 255, 10.0f);
                //drawText(30 * j + 15, 900 - 30 * i + 15, "1");
            }

        }
    }

    //make an outline
    for (int i = 0; i < 31; i++) {
        for (j = 0; j < 28; j++) {
            if (board[i][j] == 0) {
                //left
                if (j != 0 && (board[i][j - 1] == 1 || board[i][j - 1] == -1))
                    drawLine(30 * j, 900 - 30 * i, 30 * j, 900 - 30 * i + 30, 0, 37, 255);
                //right
                if (j != 27 && (board[i][j + 1] == 1 || board[i][j + 1] == -1))
                    drawLine(30 * j + 30, 900 - 30 * i, 30 * j + 30, 900 - 30 * i + 30, 0, 37, 255);
                //bottom
                if (i != 27 && (board[i + 1][j] == 1 || board[i + 1][j] == -1))
                    drawLine(30 * j, 900 - 30 * i, 30 * j + 30, 900 - 30 * i, 0, 37, 255);

                //top
                if (i != 0 && (board[i - 1][j] == 1 || board[i - 1][j] == -1))
                    drawLine(30 * j, 900 - 30 * i + 30, 30 * j + 30, 900 - 30 * i + 30, 0, 37, 255);
            }
        }
    }
}
*/

//void restart() {
//    pacman.moveToStart();
//    pacman.resetLives();
//    pacman.resetScore();
//}


//std::string int2str(int x) {
//    // converts int to string
//    std::stringstream ss;
//    ss << x;
//    return ss.str();
//}

//void keyboard() {
//
//    if (GetAsyncKeyState(VK_UP)) {
//        //std::cout << pacman.getI() << " " << pacman.getJ() << board[pacman.getI()][pacman.getJ()] << "\n";
//
//        if (!pacman.checkWall(pacman.getI() - 1, pacman.getJ())) {
//            direction = 1;
//            move = true;
//        }
//        else {
//            std::cout << "Wall";
//        }
//    }
//    if (GetAsyncKeyState(VK_DOWN)) {
//        //std::cout << pacman.getI() << " " << pacman.getJ() << board[pacman.getI()][pacman.getJ()] << "\n";
//        if (!pacman.checkWall(pacman.getI() + 1, pacman.getJ())) {
//            direction = 2;
//            move = true;
//        }
//        else {
//            std::cout << "Wall";
//        }
//    }
//    if (GetAsyncKeyState(VK_LEFT)) {
//        //std::cout << pacman.getI() << " " << pacman.getJ() << board[pacman.getI()][pacman.getJ()] << "\n";
//        if (!pacman.checkWall(pacman.getI(), pacman.getJ() - 1)) {
//            direction = 3;
//            move = true;
//        }
//        else {
//            std::cout << "Wall";
//        }
//    }
//
//    if (GetAsyncKeyState(VK_RIGHT)) {
//        //std::cout << pacman.getI() << " " << pacman.getJ() << " " << board[pacman.getI()][pacman.getJ()] << "\n";
//        //std::cout << pacman.getI() << " " << pacman.getJ() + 1 << " " << board[pacman.getI()][pacman.getJ() + 1] << "\n";
//        if (!pacman.checkWall(pacman.getI(), pacman.getJ() + 1)) {
//            direction = 4;
//            move = true;
//        }
//        else {
//            std::cout << "Wall";
//        }
//    }
//
//    if (GetAsyncKeyState(VK_W)) {
//        resetBoard();
//        restart();
//        still_alive = true;
//    }
//
//}
//
//void movePacman() {
//    if (direction == 1) {
//        move = !pacman.checkWall(pacman.getI() - 1, pacman.getJ());
//        if (move) {
//            pacman.moveUp(pacman_speed);
//            pacman.setOrientation(50);
//        }
//    }
//    if (direction == 2) {
//        move = !pacman.checkWall(pacman.getI() + 1, pacman.getJ());
//        if (move) {
//            pacman.moveDown(pacman_speed);
//            pacman.setOrientation(230);
//        }
//    }
//    if (direction == 3) {
//        move = !pacman.checkWall(pacman.getI(), pacman.getJ() - 1);
//        if (move) {
//            pacman.moveLeft(pacman_speed);
//            pacman.setOrientation(140);
//        }
//        if (pacman.getI() == 14 && pacman.getJ() == 0) {
//            pacman.increaseScore(10);
//            board[pacman.getI()][pacman.getJ()] = -1;
//            pebble_counter += 1;
//            pacman.moveTo(14, 27);
//        }
//    }
//    if (direction == 4) {
//        move = !pacman.checkWall(pacman.getI(), pacman.getJ() + 1);
//        if (move) {
//            pacman.moveRight(pacman_speed);
//            pacman.setOrientation(320);
//        }
//        if (pacman.getI() == 14 && pacman.getJ() == 27) {
//            pacman.increaseScore(10);
//            board[pacman.getI()][pacman.getJ()] = -1;
//            pebble_counter += 1;
//            pacman.moveTo(14, 0);
//        }
//    }
//}

//void resetBoard() {
//    for (int i = 0; i < 31; i++) {
//        for (int j = 0; j < 28; j++) {
//            if (board[i][j] == -1)
//                board[i][j] = 1;
//        }
//    }
//}

//void checkScore() {
//    if (board[pacman.getI()][pacman.getJ()] == 1) {
//        if ((pacman.getI() == 1 && pacman.getJ() == 26) || (pacman.getI() == 29 && pacman.getJ() == 1) || (pacman.getI() == 29 && pacman.getJ() == 26)) {
//            pacman.increaseScore(100);
//            if (is_blue_mode == true) {
//                duration += 300;
//            }
//            else {
//                is_blue_mode = true;
//            }
//        }
//        else
//            pacman.increaseScore(10);
//        board[pacman.getI()][pacman.getJ()] = -1;
//        pebble_counter += 1;
//    }
//
//    if (pebble_counter == 300) {
//        pebble_counter = 0;
//        resetBoard();
//    }
//}

//void moveGhost(Ghost& ghost) {
//
//    if (ghost.isDead() == true && ghost.getTimer() > 0) {
//        ghost.decreaseTimer();
//    }
//    else {
//        if (ghost.getMove() == false)
//            ghost.checkPossibleMovement();
//
//        if (ghost.getDirection() == 1) {
//            ghost.setMove(!ghost.checkWall(ghost.getI() - 1, ghost.getJ()));
//            if (ghost.getMove()) {
//                ghost.moveUp(ghost_speed);
//            }
//        }
//        if (ghost.getDirection() == 2) {
//            ghost.setMove(!ghost.checkWall(ghost.getI() + 1, ghost.getJ()));
//            if (ghost.getMove()) {
//                ghost.moveDown(ghost_speed);
//            }
//        }
//        if (ghost.getDirection() == 3) {
//            ghost.setMove(!ghost.checkWall(ghost.getI(), ghost.getJ() - 1));
//            if (ghost.getMove()) {
//                ghost.moveLeft(ghost_speed);
//            }
//        }
//        if (ghost.getDirection() == 4) {
//            ghost.setMove(!ghost.checkWall(ghost.getI(), ghost.getJ() + 1));
//            if (ghost.getMove()) {
//                ghost.moveRight(ghost_speed);
//            }
//        }
//    }
//}
//
//void checkCollision(Ghost& ghost) {
//    if (pacman.getI() == ghost.getI() && pacman.getJ() == ghost.getJ()) {
//        if (is_blue_mode) {
//            pacman.increaseScore(200);
//            ghost.die();
//        }
//        else {
//            pacman.die();
//            pacman.moveToStart();
//        }
//    }
//}
//
//void checkColisions() {
//    checkCollision(ghost1);
//    checkCollision(ghost2);
//    checkCollision(ghost3);
//    checkCollision(ghost4);
//}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Pacman");

    glutDisplayFunc(draw);
    glutTimerFunc(interval, update, 0);

    enable2D(width, height);
    glColor3f(1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}
