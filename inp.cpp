#include "magik.h"
input inp;
int16_t input::mouseX=0;
int16_t input::mouseY=0;
bool input::mouseL=false;
bool input::mouseR=false;
bool input::mouseM=false;
int8_t input::mouseScrollX=0;
int8_t input::mouseScrollY=0;
uint8_t input::keyboardActive[8]={0};
uint8_t input::keyboardMap[256]={0};

bool input::mouseInArea(int16_t x1,int16_t y1,int16_t x2,int16_t y2,bool v){
	int16_t minX=util.min(x1,x2);
	int16_t maxX=util.max(x1,x2);
	int16_t minY=util.min(y1,y2);
	int16_t maxY=util.max(y1,y2);

	if(v)for(int x=minX;x<maxX;x++)for(int y=minY;y<maxY;y++)gfx.pixel(x,y,util.random(0,0xffffff));
	return(inp.mouseX>=minX&&inp.mouseX<=maxX-1&&inp.mouseY>=minY&&inp.mouseY<=maxY-1);
}
bool input::mouseInRect(int16_t x,int16_t y,uint16_t w,uint16_t h,bool v){
	return inp.mouseInArea(x,y,x+w,y+h,v);
}

bool mouseLPrev=false;
bool mouseRPrev=false;
void internal_process::mouseInit(){}
void internal_process::mouseRuntime(){
	mouseLPrev=inp.mouseL;
	mouseRPrev=inp.mouseR;
}

bool input::mouseLeftTap(){return inp.mouseL&&!mouseLPrev;}
bool input::mouseRightTap(){return inp.mouseR&&!mouseRPrev;}

void internal_process::keyboardInit(){
	/*have some of these filled*/
	uint8_t letterOffset=1;		//26 entries	english letters
	uint8_t numberOffset=27;	//10 entries	number bar
	uint8_t actionOffset=37;	//5 entries		Enter Esc Backspace Tab Space
	uint8_t sym1Offset=42;		//5 entries		- = [ ] backslash
	uint8_t sym2Offset=48;		//6 entries		; ' ` , . /
	uint8_t capsLockOffset=54;	//1 entry
	uint8_t functionOffset=55;	//12 entries	function keys
	uint8_t scrollLockOffset=68;//1 entry
	uint8_t navigationOffset=69;//7 entries		Pause Insert Home PgUp Del End PgDn
	uint8_t arrowOffset=76;		//4 entries		R L U D

	uint8_t numLockOffset=80;	//1 entry
	uint8_t numSymOffset=81;	//4 entries		/ * - +
	uint8_t numEnterOffset=85;	//1 entry
	uint8_t numNumberOffset=86;	//11 entries		1 to 0 and .

	uint8_t menuOffset=98;		//1 entry

	uint8_t powerLeftOffset=221;//4 entries		Ctrl Shift Alt Super
	uint8_t powerRghtOffset=225;//4 entries		Ctrl Shift Alt Super

	uint8_t pointer=0;
	for(int i=0;i<26;i++){pointer++;inp.keyboardMap[pointer]=letterOffset+i;}
	for(int i=0;i<10;i++){pointer++;inp.keyboardMap[pointer]=numberOffset+i;}
	for(int i=0;i<5;i++){pointer++;inp.keyboardMap[pointer]=sym1Offset+i;}
	for(int i=0;i<6;i++){pointer++;inp.keyboardMap[pointer]=sym2Offset+i;}
	for(int i=0;i<4;i++){pointer++;inp.keyboardMap[pointer]=arrowOffset+i;}
	for(int i=0;i<5;i++){pointer++;inp.keyboardMap[pointer]=actionOffset+i;}
	for(int i=0;i<1;i++){pointer++;inp.keyboardMap[pointer]=capsLockOffset+i;}
	for(int i=0;i<1;i++){pointer++;inp.keyboardMap[pointer]=scrollLockOffset+i;}
	for(int i=0;i<1;i++){pointer++;inp.keyboardMap[pointer]=numLockOffset+i;}
	for(int i=0;i<7;i++){pointer++;inp.keyboardMap[pointer]=navigationOffset+i;}
	for(int i=0;i<12;i++){pointer++;inp.keyboardMap[pointer]=functionOffset+i;}
	for(int i=0;i<4;i++){pointer++;inp.keyboardMap[pointer]=powerLeftOffset+i;}
	for(int i=0;i<4;i++){pointer++;inp.keyboardMap[pointer]=powerRghtOffset+i;}
	for(int i=0;i<1;i++){pointer++;inp.keyboardMap[pointer]=menuOffset+i;}
	for(int i=0;i<4;i++){pointer++;inp.keyboardMap[pointer]=numSymOffset+i;}
	for(int i=0;i<11;i++){pointer++;inp.keyboardMap[pointer]=numNumberOffset+i;}
	for(int i=0;i<1;i++){pointer++;inp.keyboardMap[pointer]=numEnterOffset+i;}
}
uint8_t internal_process::keyConvert(uint16_t k){
	for(uint8_t i=0;i<256;i++)if(inp.keyboardMap[i]==k)return i;
	return 0;
}
void internal_process::keyDown(uint16_t key){
    for(int i=0;i<8;i++)if(inp.keyboardActive[i]==key)return;
    for(int i=0;i<8;i++){if(inp.keyboardActive[i]==0){inp.keyboardActive[i]=key;return;}}
}
void internal_process::keyUp(uint16_t key){
	for(int i=0;i<8;i++){
		if(inp.keyboardActive[i]==key){
			inp.keyboardActive[i]=0;
			for(int j=i;j<7;j++)inp.keyboardActive[j]=inp.keyboardActive[j+1];
			inp.keyboardActive[7]=0;
			return;
		}
	}
}
bool keyboardPrev[256]={0};
uint16_t keyboardTime[256]={0};
uint16_t keyboardRepeat[256]={0};
void internal_process::keyboardRuntime(){
	for(int i=0;i<256;i++){
		bool held=inp.keyState(i);
		if(held)keyboardTime[i]++;
		else keyboardTime[i]=0;
		keyboardPrev[i]=held;
	}
}


bool input::keyState(uint8_t k){
	for(int i=0;i<8;i++)if(inp.keyboardActive[i]==k)return true;
	return false;
}
bool input::keyTouch(uint8_t k,uint8_t a,uint8_t b){
	if(!inp.keyState(k))return false;
	uint16_t t=keyboardTime[k];
	if(t==1)return true;
	if(t<(a*2))return false;
	return ((t-(a*2))%(b*2))==0;
}