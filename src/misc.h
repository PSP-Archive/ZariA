// See LICENSE.TXT for license agreement.

#ifndef MISC_H
#define MISC_H

#include <psptypes.h>
#include <stdlib.h>

// Vertex type
//
typedef struct Vertex_t
{
	float u,v; // tex coords
	unsigned int color; // 32-bit color
	float x,y,z;
}
Vertex;

Vertex getVertex(float u,float v,u32 color,float x, float y,float z);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define	PSP_LINE_SIZE 512

void initGraphics();
void endGraphics();
void startDrawing();
void endDrawing();
void clearScreen();
void flipScreen();
void printTextScreen(const char* text, int x, int y, u32 color);

#endif
