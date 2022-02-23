#include "globals.h"
#include "drawing.h"

void drawCircleFan(GLfloat x, GLfloat y, int o) {
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