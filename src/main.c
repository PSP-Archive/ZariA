/*
Z@ria v0.1 

Application par Roomain ; je vous prierai de laisser ce code merci ;)

Et de me laisser dans le read-me ce serait sympa :p
*/

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <string.h>
#include <pspgu.h>
#include <png.h>
#include "graphics.h"
#include "mp3player.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h> 







PSP_MODULE_INFO("Z@riA", 0x0800, 1, 0);

PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_VSH);

#define PROGRAM "EBOOT.PBP"

Image* perso;
Image* ennemie;
Image* fond;
Image* block;
Image* sol;
Image* end;
Image* persoGauche;
Image* intersection;
SDL_Rect positionFond;

int playerx = 0;
int oldx = 50;
int playery = 202;
int oldy = 202;
int collision = 0;
int saut = 0;
int total;
int pauseP = 0;
int b;
int a;
int c;
int e;
int sautspeed = 15;

int playergravity = 202;

int vie = 2;

int avancement;

int pcent;

//SDL_Rect background_position;

//background_position.x = 0;
//background_position.y = 0;

int longueur = 3100; // la longueur du parcours (en px)
int pourcents;

char * tpourcents = "";

char *pts = "";

int points=0;

int aleatoire;

int nombreBlocks = 11;

int sens = 1;

int posFond=480;





Mix_Chunk *boum = NULL;
Mix_Chunk * paf = NULL;
Mix_Music * musique = NULL;

SDL_Surface *fondSDL = NULL;


SDL_Surface *ecranSS;


char *pr = "";
char *vitalite = "";
	





int chargement(void)
{
 printTextScreen(185, 120, "Chargement...", 0xFFFFFF);
 
 flipScreen();
 
 /*	 #############################
	CHARGEMENT DES IMAGES
	#############################
 */
 
perso = loadImage("./Fichiers/Images/mario.png");
fond = loadImage("./Fichiers/Images/background.png");
block = loadImage("./Fichiers/Images/block.png");
sol = loadImage("./Fichiers/Images/sol.png");
ennemie = loadImage("./Fichiers/Images/ennemie.png");
end = loadImage("./Fichiers/Images/end.png");
persoGauche = loadImage("./Fichiers/Images/mario2.png");

intersection = loadImage("./Fichiers/Images/intersection.png");





 
}


void loadeboot(char *pbpath)
{
//char *pbpath;
const u32 pbplen = strlen(pbpath)+1;
struct SceKernelLoadExecParam eloader;
eloader.args = pbplen;
eloader.argp = pbpath;
eloader.key = NULL;
eloader.size = sizeof(eloader) + pbplen;
sceKernelLoadExec(pbpath,&eloader);

}


int music(void)
{
// on passe la fréquence à 333mhZ, c'est mieux pour les musiques et pour jeu ;)
	scePowerSetClockFrequency(333, 333, 166);

		//  pspAudioInit();
        //  MP3_Init(1);
        //  MP3_Load("music.mp3");
        //  MP3_Play();
		  
		    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); 
			
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024); 
			
			musique = Mix_LoadMUS("./Fichiers/Sons/music.ogg"); 
			paf = Mix_LoadWAV("./Fichiers/Sons/paf.wav");
			boum = Mix_LoadWAV("./Fichiers/Sons/boum.wav");
			
			Mix_PlayMusic(musique, 1); 
		
		
		
		  

		  
}

void niveau1()
{

playerx=50;
playery=193;

initGraphics();
SetupCallbacks();

chargement();
music();








// Informations du niveau

long positionXBlocks[11];
long positionYBlocks[11];

//Contenu



positionXBlocks[0] = 178;
positionYBlocks[0] = 198;

positionXBlocks[1] = 493;
positionYBlocks[1] = 198;

positionXBlocks[2] = 903;
positionYBlocks[2] = 198;

positionXBlocks[3] = 1252;
positionYBlocks[3] = 198;

positionXBlocks[4] = 1645;
positionYBlocks[4] = 198;

positionXBlocks[5] = 1764;
positionYBlocks[5] = 198;

positionXBlocks[6] = 2024;
positionYBlocks[6] = 198;

positionXBlocks[7] = 2345;
positionYBlocks[7] = 198;

positionXBlocks[8] = 2524;
positionYBlocks[8] = 198;

positionXBlocks[9] = 2692;
positionYBlocks[9] = 198;

positionXBlocks[10] = 4000;
positionYBlocks[10] = 198;


//---------------FIN----------------





long positionXEnnemie[12];
long positionYEnnemie[12];



 /*	 #############################
	POSITION DES ENNEMIES
	#############################
 */

positionXEnnemie[0] = 1000;
positionYEnnemie[0] = 202;

positionXEnnemie[1] = 1450;
positionYEnnemie[1] = 202;

positionXEnnemie[2] = 1800;
positionYEnnemie[2] = 202;

positionXEnnemie[3] = 2100;
positionYEnnemie[3] = 202;


positionXEnnemie[4] = 2250;
positionYEnnemie[4] = 202;

positionXEnnemie[5] = 2400;
positionYEnnemie[5] = 202;

positionXEnnemie[6] = 2600;
positionYEnnemie[6] = 202;

positionXEnnemie[7] = 2650;
positionYEnnemie[7] = 202;


positionXEnnemie[8] = 2650;
positionYEnnemie[8] = 202;

positionXEnnemie[9] = 2700;
positionYEnnemie[9] = 202;

positionXEnnemie[10] = 2800;
positionYEnnemie[10] = 202;

positionXEnnemie[11] = 3050;
positionYEnnemie[11] = 202;


 /*	 #############################
	POSITION DES BLOCKS
	#############################
 */


/*
positionXBlocks[0] = 102;
positionYBlocks[0] = 230;

positionXBlocks[1] = 180;
positionYBlocks[1] = 199;

positionXBlocks[2] = 270;
positionYBlocks[2] = 168;

positionXBlocks[3] = 180;
positionYBlocks[3] = 230;

positionXBlocks[4] = 270;
positionYBlocks[4] = 199;

positionXBlocks[5] = 270;
positionYBlocks[5] = 230;*/


while(1)
{


if(!Mix_PlayingMusic() == 1)
{
Mix_PlayMusic(musique, 1); 
}

	oldx = playerx;
	oldy = playery;
	

	
	for (avancement=0 ; avancement<12 ; avancement++)
	{
	if(positionXEnnemie[avancement]>350)
	{
	if(pauseP<1){
	positionXEnnemie[avancement] = positionXEnnemie[avancement] - 1;
	}
	}
	else
	{
	int pourcents;
	pourcents = (playerx/longueur)*100;
	
	int aleatoire = (2 + ((float) rand() / RAND_MAX * (100 - 2 + 1))); 
	if(aleatoire<=pourcents)
	{
	positionXEnnemie[avancement] = (1000 + ((float) rand() / RAND_MAX * (longueur - 1000 + 1))); 
	}

	}
	}
	
	
	SceCtrlData pad;
    sceCtrlReadBufferPositive(&pad, 1);
	
	
	
	
	
	
	int avancer(void)
{







	
	if (pad.Buttons & PSP_CTRL_LEFT)
	{
	

	playerx = playerx - 2;
	posFond = posFond + 2;

	if (pad.Buttons & PSP_CTRL_SQUARE)
	{
	playerx = playerx - 2;
	posFond = posFond + 2;
	}
	
	sens = 0;
	
	
	}
	
	if (pad.Buttons & PSP_CTRL_RIGHT)
	{
	
	if (pad.Buttons & PSP_CTRL_SQUARE)
	{
	playerx = playerx + 2;
	posFond = posFond - 2;
	}
	playerx = playerx + 2;
	posFond = posFond - 2;
	
	sens = 1;
	
	}
	


	
	
	
	
	

	if(playerx<1){
	playerx = oldx;
	}
	
	for (e=0 ; e<50 ; e++)
	{
		
	if ((playerx+32 > positionXEnnemie[e]) && (playerx < positionXEnnemie[e]+35) && (playery+35 > positionYEnnemie[e]) && (playery < positionYEnnemie[e]+32 ))
	{
	{
	if(playery>230-10-20 && saut==0)
	{
	Mix_PlayChannel( -1, paf, 0 );
	vie--;
	playerx = playerx - 100;
	printTextScreen(130, 123, "Vous venez de perdre une vie !", 0xFF0000);
	printTextScreen(130, 133, "Reprise du jeu dans 3 secondes", 0xFFFFFF);
	flipScreen();
	sceKernelDelayThread(3*1000*1000);
	}
	}
	}
	

	
	

}}


int checkPause(void)
{


	if (pad.Buttons & PSP_CTRL_START)
	{
	if(pauseP==0)
	{
	pauseP=1;
	}


	}
	
	
	if(pauseP==1)
	{
	
	playerx = oldx;
	playery = oldy;

  
	}
	if(pad.Buttons & PSP_CTRL_CIRCLE)
	{
	pauseP=0;
	}
	
	}



	int st;
	
	int verifCollision()
	{
	
	
	
	for (b=0 ; b<nombreBlocks ; b++)
	{
	
	int ply32;
	int plx23;
	int px32;
	int py32;
	
	
	ply32 = playery + 35;
	plx23 = playerx + 30;
	px32 = positionXBlocks[b] + 46;
	py32 = positionYBlocks[b] + 38;
	
	

	
	if ((plx23 > positionXBlocks[b]) && (playerx < px32) && (ply32 > positionYBlocks[b]) && (playery < ply32 ))
	{
	playerx = oldx;
	playery = oldy;
	st = 1;
	
	if(playery<199){
	
	
	if (pad.Buttons & PSP_CTRL_LEFT)
	{
	
	if (pad.Buttons & PSP_CTRL_SQUARE)
	{
	playerx = playerx - 2;
	posFond = posFond + 2;
	}
	
	playerx = playerx - 2;
	posFond = posFond + 2;
	


	sens=0;
	
	}
	
	if (pad.Buttons & PSP_CTRL_RIGHT)
	{
	
	if (pad.Buttons & PSP_CTRL_SQUARE)
	{
	playerx = playerx + 2;
	posFond = posFond - 2;
	}
	playerx = playerx + 2;
	posFond = posFond - 2;
	
	sens = 1;

	}


	
	}
	
	
	
	}
	

	

	
	}
	

	
	}
	
	
	

	
	
	
	
	

	
	
	
	
int sauter()
{

//oldx = playerx;
//oldy = playery;

	if (pad.Buttons & PSP_CTRL_CROSS)
	{
	if(pauseP==0)
	{
	saut=2;
	}
	}


int pg;
	
	if(saut==2){
	
	sautspeed = sautspeed - 1;
	
	pg = 237 - playery;
	playergravity = playergravity - sautspeed;
	}
	
	
	if(playery==166 && saut>0)
	{
	playergravity = 166;
	}
	
	if(playergravity<0)
	{
	saut=1;
	}
	
	if(playergravity<202 && saut==1)
	{
	int s3;
	s3 = sautspeed + 3;
	playergravity = pg + s3;
	
	}
	
	if(playergravity==202){
	sautspeed=15;
	saut=0;
	}
	
	if(playergravity>202)
	{
	playergravity=202;
	}
	
	playery = playergravity;
	
	int s;
	for (s=0 ; s<12 ; s++)
	{
	
	
	if((playerx + 23 > positionXEnnemie[s]) && (playerx<(positionXEnnemie[s]+23)) && ((playery + 32)>positionYEnnemie[s]) && (playery<(positionYEnnemie+23)) && saut>0)
	{
	
	
	pourcents = (playerx/(longueur/100));
	
	aleatoire = (2 + ((float) rand() / RAND_MAX * (100 - 2 + 1))); 

	
	if(playery<239)
	{
	{
	if(aleatoire>=pourcents)
	{
	positionXEnnemie[s] = (playerx + ((float) rand() / RAND_MAX * ((longueur+700) - playerx + 1)));
	}
	else
	{
	positionXEnnemie[s] = 500000;
	}
	
	playery = 193;
	points = points + 100;
	Mix_PlayChannel( -1, boum, 0 );
	}
	}
	
	
	
	if(playery>241)
	{
	Mix_PlayChannel( -1, paf, 0 );
	vie--;
	playerx = playerx - 100;
	printTextScreen(130, 123, "Vous venez de perdre une vie !", 0xFF0000);
	printTextScreen(130, 133, "Reprise du jeu dans 3 secondes", 0xFFFFFF);
	flipScreen();
	sceKernelDelayThread(3*1000*1000);
	}
	}
	
	}
	
	
	verifCollision();

	}
	
	
	



	
	
	
	
	
	
	
	avancer();
	sauter();
	checkPause();
	
	if(posFond==0)
	{
	posFond=480;
	}
	if(posFond==480){
	posFond=0;
	}

	if(posFond==0)
	{
	posFond=480;
	}
	
	blitImageToScreen(0, 0, 480, 272, fond, posFond+485, 0);
	blitImageToScreen(0, 0, 480, 272, fond, posFond, 0);
	
	
	
	
	

	
	if(playerx<240)
	{
	if(sens==0)
	{
	blitAlphaImageToScreen(0, 0, perso->imageWidth, perso->imageHeight, persoGauche, playerx, playery);
	}
	else
	{
	blitAlphaImageToScreen(0, 0, perso->imageWidth, perso->imageHeight, perso, playerx, playery);
	}
	}
	else
	{
	if(sens==0)
	{
	blitAlphaImageToScreen(0, 0, perso->imageWidth, perso->imageHeight, persoGauche, 240, playery);
	}
	else
	{
	blitAlphaImageToScreen(0, 0, perso->imageWidth, perso->imageHeight, perso, 240, playery);
	}
	}
	//blitAlphaImageToScreen(0, 0, sol->imageWidth, sol->imageHeight, sol, 0, 262);
	//verifCollision();
	
		verifCollision();
		
	
	if(st==1)
	{
	//printTextScreen(5, 5, "Collision !", 0xFFFFFF);
	//flipScreen();
	}
	
	//printTextScreen(5, 15, playery, 0xFFFFFF);
	
	int diff;
	int stx;
	int a;
		int z;
	for (z=0 ; z<12 ; z++)
	{
	if(playerx<240)
	{
	
	blitAlphaImageToScreen(0, 0, ennemie->imageWidth, ennemie->imageHeight, ennemie, positionXEnnemie[z], positionYEnnemie[z]);
	}
	else
	{
	int difference;
	difference = playerx - 240;
	int stx2;
	stx2 = positionXEnnemie[z] - difference;
	if(stx2<481 && stx2>-35)
	{
	blitAlphaImageToScreen(0, 0, ennemie->imageWidth, ennemie->imageHeight, ennemie, stx2, positionYEnnemie[z]);
	}
	}
	}
	
	
	for (a=0 ; a<nombreBlocks ; a++)
	{
	if(playerx<240)
	{
	blitAlphaImageToScreen(0, 0, block->imageWidth, block->imageHeight, block, positionXBlocks[a], positionYBlocks[a]);
	}
	else
	{
	diff = playerx - 240;
	stx = positionXBlocks[a] - diff;
	if(stx<481 && stx>-64)
	{
	blitAlphaImageToScreen(0, 0, block->imageWidth, block->imageHeight, block, stx, positionYBlocks[a]);
	}
	}
	
	}
	
	if(playerx>2500)
	{
	int diffe = playerx - 240;
	blitAlphaImageToScreen(0, 0, end->imageWidth, end->imageHeight, end, (longueur-diffe), 137);
	if(playerx==longueur+50)
	{
	break;
	}
	}

	
	
	if(pauseP==1)
	{
  printTextScreen(173, 123, "Jeu en pause !", 0xFFFFFF);
  printTextScreen(157, 133, "Rond pour reprendre...", 0xFF0000);
	}
	
	
	pr = "";
	vitalite = "";
	pts="";
	
	pcent = playerx/(longueur/100);
	
	
	if (pad.Buttons & PSP_CTRL_TRIANGLE)
	{
	sprintf(pr,"Pourcentage accompli : %i %", pcent);
	
	
	
	
	
	printTextScreen(5, 3, pr, 0xFF0000);
	sprintf(vitalite, "Vies restantes : %i", vie);
	printTextScreen(5, 13, vitalite, 0x0000FF);
	
	sprintf(pts, "Points : %i", points);
	printTextScreen(5, 23, pts, 0xAE00FF);
	
	}
	
	
	flipScreen();
//	clearScreen(0x000000);

	//sceKernelDelayThread(1000);
	
	if(vie<0)
	{
	// break;
	 niveau1();
	 
	}
	
}



	



}

int main(void)
{
niveau1();
}
