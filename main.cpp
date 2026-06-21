//g++ main.cpp gfx.cpp runtime.cpp fnt.cpp utl.cpp cfg.cpp inp.cpp spl.cpp snd.cpp obf.cpp -lSDL2 -o Croviate&&./Croviate
/*
			CROVIATE64
	A MIDLY PROUD SHIT OF NEROXIDE UNITED CORP.
	(That's my company name btw heehee)
	Made by Andrew Dexembre(AndrewDaGentleman)
	And a property of NrxUni

	Mind you... Croviate was born at wayyyyyyy back in 10/04/2026
	Remember to celebrate Croviate birthday! Idk I was joking

*/
#include "magik.h"

SDL_Renderer* renderer;
SDL_Texture* texture;
bool running=true;


/*Binding*/
	uint16_t internal_graphics::color(uint32_t rgb) {
		//Put your correct color algorthm here...
		return 0;
	}

	void internal_graphics::clear(uint32_t c){
		//Put your clear API here...
		c=gfx.palette[c];
		uint8_t r=(c>>16)&0xFF;uint8_t g=(c>>8)&0xFF;uint8_t b=c&0xFF;
		SDL_SetRenderDrawColor(renderer,r,g,b,0xff);
		SDL_RenderClear(renderer);
	}

	void internal_graphics::buffer(){
		//Put your buffer API here...
		SDL_RenderPresent(renderer);
	}

	void internal_graphics::pixel(uint16_t x, uint16_t y, uint32_t c){
		//Put your pixel API here...
		uint8_t r=(c>>16)&0xFF;uint8_t g=(c>>8)&0xFF;uint8_t b=c&0xFF;
		SDL_SetRenderDrawColor(renderer,r,g,b,0xff);
		SDL_RenderDrawPoint(renderer,x,y);
	}

	void internal_graphics::brightness(uint8_t v){
		//Put your brightness API here...
	}

	void internal_process::delay(uint dur){
		//Put your kind of delay(ms) here...
		SDL_Delay(dur);
	}

	bool input::btn(uint8_t a){
					/*HOW TO BIND BUTTONS*/
		/*
			Just remember this:
			0 = up		1 = down	2 = left
			3 = right	4 = A		5 = B
			6 = X		7 = Y		8 = LS
			9 = RS		10= START	11= SELECT
			else = any
		*/
		bool button_array[12]={
			inp.keyState(51), //arrow up
			inp.keyState(50), //arrow down
			inp.keyState(49), //arrow left
			inp.keyState(48), //arrow right
			inp.keyState(26), //z
			inp.keyState(24), //x
			inp.keyState(1),  //a
			inp.keyState(19), //s
			inp.keyState(79), //left ctrl
			inp.keyState(83), //right ctrl
			inp.keyState(52), //enter
			inp.keyState(56)  //space
			
		}; //Put your button reading logic that returns bool here
		if(a<12){
			return button_array[a];
		}else{
			for(int i=0;i<12;i++)if(button_array[i])return true;
		}
		return false;
	}



int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	snd.init();
	SDL_Window* window=SDL_CreateWindow(util.format("Croviate64 %s (%s)%s",proc.codename,proc.version,proc.prototype?"  Warning: Unreleased version":""),
	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
	(gfx.width+16)*gfx.scale,(gfx.height+16)*gfx.scale,
	SDL_WINDOW_RESIZABLE);
	SDL_ShowCursor(SDL_DISABLE);
	renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	texture=SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,
		gfx.width,gfx.height
	);
	SDL_Event event;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
	iproc.keyboardInit();
	proc.init();
	while(running){
		iproc.time=SDL_GetTicks();
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT)running=false;

			inp.mouseScrollX=0;
			inp.mouseScrollY=0;
			if(event.type==SDL_MOUSEMOTION){
				inp.mouseX=(event.motion.x-gfx.offsetX)/gfx.scale;
				inp.mouseY=(event.motion.y-gfx.offsetY)/gfx.scale;
				if(inp.mouseX<0)inp.mouseX=0;
				if(inp.mouseX>=gfx.width)inp.mouseX=gfx.width-1;
				if(inp.mouseY<0)inp.mouseY=0;
				if(inp.mouseY>=gfx.height)inp.mouseY=gfx.height-1;
			}
			if(event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button==SDL_BUTTON_LEFT)inp.mouseL=true;
				if(event.button.button==SDL_BUTTON_RIGHT)inp.mouseR=true;
				if(event.button.button==SDL_BUTTON_MIDDLE)inp.mouseM=true;
			}
			if(event.type==SDL_MOUSEBUTTONUP){            
				if(event.button.button==SDL_BUTTON_LEFT)inp.mouseL=false;
				if(event.button.button==SDL_BUTTON_RIGHT)inp.mouseR=false;
				if(event.button.button==SDL_BUTTON_MIDDLE)inp.mouseM=false;
			}
			if(event.type==SDL_MOUSEWHEEL){
				inp.mouseScrollX=event.wheel.x;
				inp.mouseScrollY=event.wheel.y;
			}

			if(event.type==SDL_KEYUP||event.type==SDL_KEYDOWN){
				int16_t keyq=event.key.keysym.scancode-3;
				int8_t keyqq=iproc.keyConvert(keyq<0?0:keyq);
				if(event.type==SDL_KEYDOWN)iproc.keyDown(keyqq);
				if(event.type==SDL_KEYUP)iproc.keyUp(keyqq);
			}
		}
		SDL_GetWindowSize(window,&igfx.width,&igfx.height);
		iproc.keyboardRuntime();
		iproc.mouseRuntime();
		if(iproc.time/1000<2)proc.id();else if(gfx.splash())proc.runtime();
		
		for(int i=0;i<8;i++)printf("%d ",inp.keyboardActive[i]);printf("\n");
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
