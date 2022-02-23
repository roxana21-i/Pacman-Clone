/*
VARIOUS FUNCTIONS FOR DRAWING ELEMENTS ON THE SCREEN
*/

#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include "globals.h"

void drawCircleFan(GLfloat x, GLfloat y, int o);

void drawText(float x, float y, std::string text);

void drawTextBig(float x, float y, std::string text);

void drawEmptyRect(float x, float y, float width, float height, float r, float g, float b);

void drawRect(float x, float y, float width, float height, float r, float g, float b);

void drawOpaqueRect(float x, float y, float width, float height, float r, float g, float b);

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b);

void drawPoint(float x, float y, float r, float g, float b, float size);

void drawPacman(GLfloat x, GLfloat y, int o);

void drawGhost(GLfloat x, GLfloat y, float r, float g, float b);

void drawBoard();

#endif
