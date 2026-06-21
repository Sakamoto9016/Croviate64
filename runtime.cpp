#include "magik.h"

const char* st[8]={"c4","g4","e4","c5","e5","g5","c6","c6"};
uint8_t qq=0;
uint32_t nxt=0;
void process::init(){
}
void process::runtime() {
	gfx.clear(gfx.color?7:0);
	uint32_t now=proc.time();
	/*
	if(qq<8&&now>=nxt){
		snd.tone(snd.noteFrequency[snd.noteIndex(st[qq])]);
		qq++;nxt=now+200;
	}
	if (qq>=8)snd.noTone();
	*/
	if(inp.btn(13)){
		gfx.text("Something pressed",0,0,15);
	}
	gfx.paste();
}