#ifndef OBFUSCATE_H
#define OBFUSCATE_H

/*Start of Binded headers*/
		typedef struct{int16_t x,y;}point_t;
		extern SDL_Texture* texture; 
		extern SDL_Renderer* renderer;

		struct font{const char* name;uint8_t bufw;uint8_t bufh;uint8_t width;uint8_t height;uint8_t count;const uint8_t* repl;const uint8_t* data;const int8_t offsetX;const int8_t offsetY;};extern font fonts[];extern uint8_t fontCount;extern uint8_t fontIndex;
/*End of Binded headers*/

class internal_graphics{public: /*share*/
	static uint8_t brightnessValue;
	static uint8_t brightnessValueTemp;
	static int width; /*ignore*/
	static int height; /*ignore*/
	uint16_t color(uint32_t rgb);
	void buffer();
	void clear(uint32_t c);
	void pixel(uint16_t x, uint16_t y, uint32_t c);
	void brightness(uint8_t v);

	void brightnessMethod(uint8_t v);
	void renderMethod();
};extern internal_graphics igfx;
class internal_process{public:
	static uint32_t time;
	static uint16_t offtime;

	void keyboardInit();
	void mouseInit();
	uint8_t keyConvert(uint16_t k);
	void keyDown(uint16_t key);
	void keyUp(uint16_t key);
	void keyboardRuntime();
	void mouseRuntime();
	void delay(uint dur);
};extern internal_process iproc;
#endif