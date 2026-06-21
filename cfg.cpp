#include "magik.h"

uint32_t highdump[gfx.memorySize];
void internal_graphics::renderMethod(){
	for(int i=0;i<gfx.memorySize;i++)highdump[i]=gfx.palette[gfx.color?gfx.memory[i]:(gfx.memory[i]>0?15:0)];
	igfx.clear(gfx.borderValue);
	int sW=igfx.width/gfx.width;
	int sH=igfx.height/gfx.height;
	gfx.scale=(sW<sH)?sW:sH;
	if(gfx.scale<1)gfx.scale=1;
	gfx.offsetX=(igfx.width-gfx.width*gfx.scale)/2;
	gfx.offsetY=(igfx.height-gfx.height*gfx.scale)/2;
	SDL_UpdateTexture(texture,NULL,highdump,gfx.width*4);
	SDL_RenderClear(renderer);
	SDL_Rect dst={
		gfx.offsetX,gfx.offsetY,
		gfx.width*gfx.scale,
		gfx.height*gfx.scale};
	SDL_RenderCopy(renderer,texture,NULL,&dst);
	igfx.buffer();
}

void internal_graphics::brightnessMethod(uint8_t v){
	igfx.brightnessValue=v;
}