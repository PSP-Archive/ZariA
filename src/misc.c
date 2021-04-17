#include "misc.h"
#include "vram.h"
#include <string.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

static unsigned int __attribute__((aligned(16))) g_dlist[262144];

extern u8 msx[];

#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCR_HEIGHT*4)

int g_dispNumber = 0;
u32 *g_vram_base = (u32*) (0x40000000 | 0x04000000);

void *fbp0;
void *fbp1;
void *zbp;

Vertex getVertex(float u,float v,u32 color,float x, float y,float z)
{
	Vertex vert;
	vert.u = u;
	vert.v = v;
	vert.color = color;
	vert.x = x;
	vert.y = y;
	vert.z = z;
	return vert;
}

void initGraphics()
{
// Setup GU

	// g_vram_base = (u32*) (0x40000000 | 0x04000000);	

	fbp0 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	fbp1 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	zbp = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);
	
	sceGuInit();
 
	sceGuStart(GU_DIRECT,g_dlist);
	sceGuDrawBuffer(GU_PSM_8888,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CCW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuAlphaFunc(GU_GREATER,0,0xff);
	sceGuDisable(GU_CULL_FACE); 
	sceGuEnable(GU_DEPTH_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_ALPHA_TEST);
	sceGuEnable(GU_TEXTURE_2D);
	
	sceGuTexMode(GU_PSM_8888,0,0,1);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
	sceGuTexFilter(GU_NEAREST,GU_NEAREST);
	sceGuTexWrap(GU_CLAMP,GU_CLAMP);
	sceGuTexScale(1,1);
	sceGuTexOffset(0,0);
	sceGuAmbientColor(0xffffffff);
	
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(1);
}

void endGraphics()
{
	sceGuTerm();
}

void startDrawing()
{
	sceGuStart(GU_DIRECT,g_dlist);
	
	sceGuClearColor(0);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumOrtho(0,480,272,0,-1,1);
	
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();

	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();
}

void endDrawing()
{
	sceGuFinish();
	sceGuSync(0,0);
}

void clearScreen()
{
	sceGuClearColor(0);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
}

void flipScreen()
{
	fbp0 = sceGuSwapBuffers();
	g_dispNumber ^= 1;
}

u32* getVramDrawBuffer()
{
	u32* vram = (u32*) g_vram_base;
	if (g_dispNumber== 0) 
		vram += FRAMEBUFFER_SIZE / sizeof(u32);
	return vram;
}

// adapted from graphics.c
//
void printTextScreen(const char* text, int x, int y, u32 color)
{
	int c, i, j, l;
	u8 *font;
	u32 *vram_ptr;
	u32 *vram;

	for (c = 0; (unsigned)c < strlen(text); c++) {
		if (x < 0 || x + 8 > SCR_WIDTH || y < 0 || y + 8 > SCR_HEIGHT) 
			break;
		char ch = text[c];
		vram = getVramDrawBuffer() + x + y * PSP_LINE_SIZE;
		
		font = &msx[ (int)ch * 8];
		for (i = l = 0; i < 8; i++, l += 8, font++) {
			vram_ptr  = vram;
			for (j = 0; j < 8; j++) {
				if ((*font & (128 >> j))) *vram_ptr = color;
				vram_ptr++;
			}
			vram += PSP_LINE_SIZE;
		}
		x += 8;
	}
}
