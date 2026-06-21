/*Configurations*/
	//HI, so u see, scrolling down just to adijust something justttttttttt take too much time and effort so...
	//Let's do some fun, exciting than ever trivia questions!
	
	/*Do you want to enable splash?*/
		#define _SplshEn true		/*true false*/
	
	/*How big is the screen during runtime?*/
		/*Width*/
		#define _DispW	 256		/*32 to 256*/

		/*Height*/
		#define _DispH	 192		/*32 to 192*/

	/*Does your screen have colors or just dark and light?*/
		#define _ColorEn true		/*true false*/

#ifndef MAGIK_H
#define MAGIK_H

#include <SDL2/SDL.h>

#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <cstdint>
#include <math.h>
#include <string>
#include <random>
#include <cmath>

#include "obf.h"

class process{public: /*share*/
	/*Croviate Properties*/
		static constexpr const char* version="0.1.040526";
		static constexpr const char* codename="Lunar";
		static constexpr const char* distro="Mainstream";
		static constexpr bool prototype=true;
		static constexpr bool embed=false;
		static constexpr uint32_t versionValue=0;
	/*Big API*/
		void init();
		void runtime();
	/*API*/
		uint32_t time();

	/*Not your typical stuff.*/
		void id();
};extern process proc;
class utilities{public: /*share*/
	/*Math Additions*/
		long random(long min, long max);
		int min(int a,int b);
		int max(int a,int b);
	/*String Additions*/
		char* format(const char* fmt,...);
	/*Data Additions*/
		bool getFlag(uint32_t v,uint8_t p);
		void setFlag(uint32_t &v, uint8_t p, bool b);
	/*Sleep Additions*/
		void delay(uint dur);
};extern utilities util;
class graphics{public: /*share*/
	/*Memory*/
		static constexpr uint32_t memorySize=256*192;
		static uint32_t memory[memorySize];
	/*Palette*/
		static uint32_t palette[256];
	/*Display*/
		static uint16_t offsetX; /*ignore*/
		static uint16_t offsetY; /*ignore*/
		static constexpr uint16_t width=_DispW;
		static constexpr uint16_t height=_DispH;
		static uint16_t size; /*ignore*/
		static uint8_t scale; /*ignore*/
		static constexpr bool color=_ColorEn;
		static uint8_t borderValue;
	/*Data*/
		static uint8_t embed[64][8];

	/*Functions*/
		/*Brightness*/
			void brightness(uint8_t v);
		/*Basics*/
			void clear(uint8_t c);
			void clearDither(uint8_t t,uint8_t c);
			void border(uint8_t c);
			uint8_t pixel(int16_t x,int16_t y,uint8_t c);
			uint8_t eyedropper(int16_t x,int16_t y);
			void clip(uint16_t x1=0, uint16_t y1=0, uint16_t x2=0, uint16_t y2=0);
			void paste();
		/*RGB Math-ing*/
			uint8_t rgbSplit(uint8_t c,char s);
			uint32_t rgbMerge(uint8_t r,uint8_t g,uint8_t b);
			uint8_t rgbLuminosity(uint8_t r,uint8_t g,uint8_t b);
		/*Palette*/
			uint32_t getPalette(uint8_t c);
			void setPalette(uint8_t c,uint32_t rgb);
		/*Draw*/
			/*Line*/
				void lineH(int16_t x,int16_t y,uint16_t w,uint8_t c);
				void lineV(int16_t x,int16_t y,uint16_t w,uint8_t c);
				void line(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t c);
				void lineDash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t p,uint8_t s,uint8_t c);
			/*Rectangle*/
				void rectFrame(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c);
				void rectFill(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c);
				void rectHighlight(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c,uint8_t bg,uint8_t fg);
				void rectDither(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t t,uint8_t c);
			/*Ellipse*/
				void elipFrame(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c);
				void elipFill(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c);
			/*Circle*/
				/*(top left not from center)*/
				void circFrame(int16_t x,int16_t y,uint16_t r,uint8_t c);
				void circFill(int16_t x,int16_t y,uint16_t r,uint8_t c);
			/*Triangle*/
				void triFrame(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint8_t c);
				void triFill(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint8_t c);
			/*Polygon*/
				void polyFrame(point_t* p,uint16_t count,uint8_t c);
				void polyFill(point_t* p,uint16_t count,uint8_t c);
			/*Font*/
				void setFont(const char* fontname);
				uint8_t fontWidth();
				uint8_t fontHeight();
				uint16_t textWidth(const char* text);
			/*Char*/
				void glyph(char ch,int16_t x,int16_t y,uint8_t c);
				void text(const char* text,int16_t x,int16_t y,uint8_t c);
			/*Sprite*/
				void cell(uint8_t* d,int16_t x,int16_t y,uint8_t c);
			/*Splash*/
				bool splash(bool enable=_SplshEn);
};extern graphics gfx;
class input{public: /*share*/
	/*Mouse*/
		/*Properties*/
			static constexpr bool mouse=true; /*ignore*/
		/*API*/
			static int16_t mouseX; /*ignore*/
			static int16_t mouseY; /*ignore*/
			static bool mouseL; /*ignore*/
			static bool mouseR; /*ignore*/
			static bool mouseM; /*ignore*/
			static int8_t mouseScrollX; /*ignore*/
			static int8_t mouseScrollY; /*ignore*/
			bool mouseInArea(int16_t x1,int16_t y1,int16_t x2,int16_t y2,bool v);
			bool mouseInRect(int16_t x,int16_t y,uint16_t w,uint16_t h,bool v);
			bool mouseLeftTap();
			bool mouseRightTap();
	/*Keyboard*/
		/*Properties*/
			static constexpr bool keyboard=true; /*ignore*/
			static uint8_t keyboardMap[256]; /*ignore*/
		/*API*/
			static uint8_t keyboardActive[8]; /*ignore*/
			bool keyState(uint8_t k);
			bool keyTouch(uint8_t k,uint8_t a,uint8_t b);

	/*General*/
		/*Properties*/
			bool btn(uint8_t a=12);
};extern input inp;
class sound{
public:
	sound();
	~sound();
	void init();
	void tone(double freq);
	void noTone();
	uint32_t noteIndex(const char *s);
	static constexpr uint16_t noteFrequency[128]={33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,93,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186};
private:
	SDL_AudioDeviceID device;
	double frequency;
	double phase;
	bool playing;
	static void audioCallback(void* userdata, Uint8* stream, int len);
};extern sound snd;
#endif