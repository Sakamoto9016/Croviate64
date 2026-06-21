/*Warning: do not operate, you may loose a hand. Loose, it's the lose with double o(oo), yeah, get it? get it? no? bruh, fine.*/
#include "magik.h"
graphics gfx;

static const uint8_t bayer4x4[4][4]={{0,8,2,10},{12,4,14,6},{3,11,1,9},{15,7,13,5}};
static inline void swap16(int32_t &a,int32_t &b){int32_t t=a;a=b;b=t;}

uint8_t graphics::embed[64][8]={
	{0xC0,0xA0,0x90,0x88,0x98,0xE8,0x30,0x00},
	{0x38,0x28,0x6E,0xA2,0x82,0x42,0x3C,0x00},
	{0xA0,0x40,0x40,0x40,0x40,0x40,0xA0,0x00},
	{0x00,0x40,0x60,0x70,0x60,0x10,0x00,0x00},
	{0x00,0x10,0x10,0x5C,0x7C,0x3C,0x00,0x00}
};
uint16_t graphics::offsetX=0;
uint16_t graphics::offsetY=0;
uint8_t graphics::scale=2;
uint32_t graphics::memory[gfx.memorySize];
uint32_t graphics::palette[256]={0x000000,0x111111,0x222222,0x333333,0x444444,0x555555,0x666666,0x777777,0x888888,0x999999,0xaaaaaa,0xbbbbbb,0xcccccc,0xdddddd,0xeeeeee,0xffffff,0x007f7f,0x3fbfbf,0x00ffff,0xbfffff,0x8181ff,0x0000ff,0x3f3fbf,0x00007f,0x0f0f50,0x7f007f,0xbf3fbf,0xf500f5,0xfd81ff,0xffc0cb,0xff8181,0xff0000,0xbf3f3f,0x7f0000,0x551414,0x7f3f00,0xbf7f3f,0xff7f00,0xffbf81,0xffffbf,0xffff00,0xbfbf3f,0x7f7f00,0x007f00,0x3fbf3f,0x00ff00,0xafffaf,0x00bfff,0x007fff,0x4b7dc8,0xbcafc0,0xcbaa89,0xa6a090,0x7e9494,0x6e8287,0x7e6e60,0xa0695f,0xc07872,0xd08a74,0xe19b7d,0xebaa8c,0xf5b99b,0xf6c8af,0xf5e1d2,0x7f00ff,0x573b3b,0x73413c,0x8e5555,0xab7373,0xc78f8f,0xe3abab,0xf8d2da,0xe3c7ab,0xc49e73,0x8f7357,0x73573b,0x3b2d1f,0x414123,0x73733b,0x8f8f57,0xa2a255,0xb5b572,0xc7c78f,0xdadaab,0xededc7,0xc7e3ab,0xabc78f,0x8ebe55,0x738f57,0x587d3e,0x465032,0x191e0f,0x235037,0x3b573b,0x506450,0x3b7349,0x578f57,0x73ab73,0x64c082,0x8fc78f,0xa2d8a2,0xe1f8fa,0xb4eeca,0xabe3c5,0x87b48e,0x507d5f,0x0f6946,0x1e2d23,0x234146,0x3b7373,0x64abab,0x8fc7c7,0xabe3e3,0xc7f1f1,0xbed2f0,0xabc7e3,0xa8b9dc,0x8fabc7,0x578fc7,0x57738f,0x3b5773,0x0f192d,0x1f1f3b,0x3b3b57,0x494973,0x57578f,0x736eaa,0x7676ca,0x8f8fc7,0xababe3,0xd0daf8,0xe3e3ff,0xab8fc7,0x8f57c7,0x73578f,0x573b73,0x3c233c,0x463246,0x724072,0x8f578f,0xab57ab,0xab73ab,0xebace1,0xffdcf5,0xe3c7e3,0xe1b9d2,0xd7a0be,0xc78fb9,0xc87da0,0xc35a91,0x4b2837,0x321623,0x280a1e,0x401811,0x621800,0xa5140a,0xda2010,0xd5524a,0xff3c0a,0xf55a32,0xff6262,0xf6bd31,0xffa53c,0xd79b0f,0xda6e0a,0xb45a00,0xa04b05,0x5f3214,0x53500a,0x626200,0x8c805a,0xac9400,0xb1b10a,0xe6d55a,0xffd510,0xffea4a,0xc8ff41,0x9bf046,0x96dc19,0x73c805,0x6aa805,0x3c6e14,0x283405,0x204608,0x0c5c0c,0x149605,0x0ad70a,0x14e60a,0x7dff73,0x4bf05a,0x00c514,0x05b450,0x1c8c4e,0x123832,0x129880,0x06c491,0x00de6a,0x2deba8,0x3cfea5,0x6affcd,0x91ebff,0x55e6ff,0x7dd7f0,0x08ded5,0x109cde,0x055a5c,0x162c52,0x0f377d,0x004a9c,0x326496,0x0052f6,0x186abd,0x2378dc,0x699dc3,0x4aa4ff,0x90b0ff,0x5ac5ff,0xbeb9fa,0x786ef0,0x4a5aff,0x6241f6,0x3c3cf5,0x101cda,0x0010bd,0x231094,0x0c2148,0x5010b0,0x6010d0,0x8732d2,0x9c41ff,0xbd62ff,0xb991ff,0xd7a5ff,0xd7c3fa,0xf8c6fc,0xe673ff,0xff52ff,0xda20e0,0xbd29ff,0xbd10c5,0x8c14be,0x5a187b,0x641464,0x410062,0x320a46,0x551937,0xa01982,0xc80078,0xff50bf,0xff6ac5,0xfaa0b9,0xfc3a8c,0xe61e78,0xbd1039,0x98344d,0x911437};
uint8_t graphics::borderValue=0;
uint16_t graphics::size=gfx.width*gfx.height;

/*function does share*/
uint8_t graphics::rgbSplit(uint8_t c,char s){uint32_t p=gfx.palette[c];switch(s){case'r':return(p>>16)&0xFF;case'g':return(p>>8)&0xFF;case'b':return p&0xFF;default:return 0;}}
uint32_t graphics::rgbMerge(uint8_t r,uint8_t g,uint8_t b){return (r<<16)|(g<<8)|b;}
uint32_t graphics::getPalette(uint8_t c){return gfx.palette[c];}
void graphics::setPalette(uint8_t c,uint32_t rgb){gfx.palette[c]=rgb;}
uint8_t graphics::rgbLuminosity(uint8_t r,uint8_t g,uint8_t b){return(uint8_t)(0.299f*r+0.587f*g+0.114f*b);}

void graphics::brightness(uint8_t v){igfx.brightnessMethod(v);}
void graphics::clear(uint8_t c){for(int i=0;i<gfx.size;i++)gfx.memory[i]=c;}
void graphics::paste(){igfx.renderMethod();}
void graphics::border(uint8_t c){borderValue=c;}

uint16_t clipx1=0;uint16_t clipy1=0;uint16_t clipx2=0;uint16_t clipy2=0;
uint8_t graphics::pixel(int16_t x,int16_t y,uint8_t c){if(x>=(clipx2==0?gfx.width:clipx2)||y>=(clipy2==0?gfx.height:clipy2)||x<clipx1||y<clipy1)return 0;gfx.memory[y*gfx.width+x]=gfx.color?c:(c>0?1:0);return 0;}
void graphics::clip(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){clipx1=x1;clipx2=x2;clipy1=y1;clipy2=y2;}

uint8_t graphics::eyedropper(int16_t x,int16_t y){
	if(x>=gfx.width||y>=gfx.height||x<0||y<0)return 0;
	return gfx.memory[y*gfx.width+x];
}
void graphics::lineH(int16_t x,int16_t y,uint16_t w,uint8_t c){for(int i=0;i<w;i++)gfx.pixel(x+i,y,c);}
void graphics::lineV(int16_t x,int16_t y,uint16_t w,uint8_t c){for(int i=0;i<w;i++)gfx.pixel(x,y+i,c);}
void graphics::rectFrame(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c){if(w==0||h==0)return;gfx.lineH(x,y,w,c);gfx.lineH(x,y+h-1,w,c);gfx.lineV(x,y,h,c);gfx.lineV(x+w-1,y,h,c);}
void graphics::rectFill(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c){for(int i=0;i<h;i++)gfx.lineH(x,y+i,w,c);}
void graphics::rectDither(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t t,uint8_t c){if(t>15)t=15;for(uint16_t iy=0;iy<h;iy++)for(uint16_t ix=0;ix<w;ix++){uint8_t threshold=bayer4x4[(y+iy)&3][(x+ix)&3];if(t>threshold)gfx.pixel(x+ix,y+iy,c);};}

void graphics::rectHighlight(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c,uint8_t bg,uint8_t fg){
	int32_t s=w*h;
	for(int i=0;i<s;i++){
		uint8_t cc=gfx.eyedropper(x+i%w,y+i/w);
		if (cc==c)cc=fg;else cc=bg;
		gfx.pixel(x+i%w,y+i/w,cc);
	}
}

void graphics::clearDither(uint8_t t,uint8_t c){gfx.rectDither(0,0,gfx.width,gfx.height,t,c);}
void graphics::line(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t c){
	int32_t dx=abs(x2-x1),sx=x1<x2?1:-1;
	int32_t dy=-abs(y2-y1),sy=y1<y2?1:-1;
	int32_t err=dx+dy,e2;
	while(1){
		gfx.pixel(x1,y1,c);
		if(x1==x2 && y1==y2)break;
		e2=2*err;
		if(e2>=dy){err+=dy; x1+=sx;}
		if(e2<=dx){err+=dx; y1+=sy;}
	}
}
void graphics::lineDash(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t p,uint8_t s,uint8_t c){
	if(s==0)s==1;
	int32_t dx=abs(x2-x1),sx=x1<x2?1:-1;
	int32_t dy=-abs(y2-y1),sy=y1<y2?1:-1;
	int32_t err=dx+dy,e2;
	uint8_t counter=p;
	while(1){
		if((counter/s)%2==0) gfx.pixel(x1,y1,c);
		counter++;
		if(x1==x2&&y1==y2)break;
		e2=2*err;
		if(e2>=dy){err+=dy; x1+=sx;}
		if(e2<=dx){err+=dx; y1+=sy;}
	}
}
void graphics::elipFrame(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c){
	int32_t a=w>>1;
	int32_t b=h>>1;
	int32_t cx=x+a;
	int32_t cy=y+b;
	int32_t a2=a*a;
	int32_t b2=b*b;
	int32_t dx=0;
	int32_t dy=b;
	int32_t d1=b2-a2*b+(a2>>2);

	while(b2*dx<=a2*dy){
		gfx.pixel(cx+dx,cy+dy,c);
		gfx.pixel(cx-dx,cy+dy,c);
		gfx.pixel(cx+dx,cy-dy,c);
		gfx.pixel(cx-dx,cy-dy,c);
	        if(d1<0)d1+=b2*(2*dx+3);
		else{d1+=b2*(2*dx+3)+a2*(-2*dy+2);dy--;}
		dx++;
	}

	int32_t d2=b2*(dx+0.5)*(dx+0.5)+a2*(dy-1)*(dy-1)-a2*b2;
	while(dy >= 0){
		gfx.pixel(cx+dx,cy+dy,c);
		gfx.pixel(cx-dx,cy+dy,c);
		gfx.pixel(cx+dx,cy-dy,c);
		gfx.pixel(cx-dx,cy-dy,c);

		if(d2>0)d2+=a2*(-2*dy+3);
		else{d2+=b2*(2*dx+2)+a2*(-2*dy+3);dx++;}
		dy--;
	}
}
void graphics::elipFill(int16_t x,int16_t y,uint16_t w,uint16_t h,uint8_t c){
	int32_t a=w>>1;
	int32_t b=h>>1;
	if(b==0)return;
	int32_t cx=x+a;
	int32_t cy=y+b;
	for(int32_t iy=-b;iy<=b;iy++){
		float fy=(float)iy/b;
		float fx=a*sqrtf(1.0f-fy*fy);
		int32_t ix=(int32_t)fx;
		gfx.lineH(cx-ix,cy+iy,ix*2+1,c);
	}
}
void graphics::circFill(int16_t x,int16_t y,uint16_t r,uint8_t c){gfx.elipFill(x,y,r*2,r*2,c);}
void graphics::circFrame(int16_t x,int16_t y,uint16_t r,uint8_t c){gfx.elipFrame(x,y,r*2,r*2,c);}
void graphics::triFrame(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint8_t c){
	gfx.line(x1,y1,x2,y2,c);
	gfx.line(x2,y2,x3,y3,c);
	gfx.line(x3,y3,x1,y1,c);
}

void graphics::triFill(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3,uint8_t c){
	int32_t sx1=x1,sy1=y1;
	int32_t sx2=x2,sy2=y2;
	int32_t sx3=x3,sy3=y3;
	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
	if(sy2>sy3){swap16(sy2,sy3);swap16(sx2,sx3);}
	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
	auto edgeInterp=[](int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t y){if(y1==y0)return x0;return x0+(y-y0)*(x1-x0)/(y1-y0);};
	for(int32_t y=sy1;y<=sy3;y++){
		int32_t xa,xb;
		if(y<sy2){
			xa=edgeInterp(sx1,sy1,sx2,sy2,y);
			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
		}else{
			xa=edgeInterp(sx2,sy2,sx3,sy3,y);
			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
		}
		if(xa>xb){int32_t t=xa;xa=xb;xb=t;}
		gfx.lineH(xa,y,xb-xa+1,c);
	}
}
void graphics::polyFrame(point_t* p,uint16_t count,uint8_t c){
	if (count<2)return;
	for(uint16_t i=0;i<count;i++){
		uint16_t j=(i+1)%count;
		gfx.line(p[i].x,p[i].y,p[j].x,p[j].y,c);
	}
}
void graphics::polyFill(point_t* p,uint16_t count,uint8_t c){
	if(count<3)return;
	int32_t minY=32767;
	int32_t maxY=-32768;
	for(uint16_t i=0;i<count;i++){
		if(p[i].y<minY)minY=p[i].y;
		if(p[i].y>maxY)maxY=p[i].y;
	}
	minY=util.max(minY,0);
	maxY=util.min(maxY,gfx.height-1);
	for(int32_t y=minY;y<=maxY;y++){
		int32_t nodeX[32];
		uint16_t nodes=0;
		for(uint16_t i=0,j=count-1;i<count;j=i++){
			int32_t yi=p[i].y;
			int32_t yj=p[j].y;
			if((yi<y&&yj>=y)||(yj<y&&yi>=y)){
				int32_t xi=p[i].x;
				int32_t xj=p[j].x;
				nodeX[nodes++]=xi+(y-yi)*(xj-xi)/(yj-yi);
				if(nodes>=32)break;
			}
		}
		for(uint16_t i=0;i<nodes-1;i++){
			for(uint16_t j=i+1;j<nodes;j++){
				if(nodeX[i]>nodeX[j]){
					int32_t t=nodeX[i];
					nodeX[i]=nodeX[j];
					nodeX[j]=t;
				}
			}
		}
		for(uint16_t i=0;i+1<nodes;i+=2){
			int32_t xStart=nodeX[i];
			int32_t xEnd=nodeX[i+1];
			gfx.lineH(xStart,y,xEnd-xStart+1,c);
		}
	}
}
void graphics::setFont(const char* fontname){
	for(int i=0;i<fontCount;i++){
		if(strcmp(fonts[i].name,fontname)==0){
			fontIndex = i;
			return;
		}
	}
	fontIndex=0;
}
uint8_t graphics::fontWidth(){return fonts[fontIndex].width;}
uint8_t graphics::fontHeight(){return fonts[fontIndex].height;}
uint16_t graphics::textWidth(const char* text){if(!text)return 0;return strlen(text)*fonts[fontIndex].width;}
static bool fontPixel(const font& f,const uint8_t* glyph,int x,int y){if(x>=f.width||y>=f.height)return false;int bytesPerRow=f.bufw/8;int byteIndex=y*bytesPerRow+(x/8);int bitIndex=7-(x%8);return(glyph[byteIndex]>>bitIndex)&1;}
static int resolveGlyphIndex(const font& f,unsigned char ch){int index=-1;index=ch-32;if(index<0||index>=f.count){if(f.repl){index=f.repl[ch];}}if(index<0||index>=f.count){index=0;}return index;}
void graphics::glyph(char ch,int16_t x,int16_t y,uint8_t c){
	const font& f=fonts[fontIndex];
	int index=resolveGlyphIndex(f,(unsigned char)ch);
	int glyphSize=(f.bufw*f.bufh)/8;
	int ox=f.offsetX;
	int oy=f.offsetY;
	const uint8_t* glyph=f.data+index*glyphSize;
	for(int gy=0;gy<f.height;gy++)for(int gx=0;gx<f.width;gx++)if(fontPixel(f,glyph,gx,gy))gfx.pixel(x+gx+ox,y+gy+oy,c);
}
void graphics::text(const char* text,int16_t x,int16_t y,uint8_t c){
	if(!text)return;
	const font& f=fonts[fontIndex];
	int16_t cx=x;
	int16_t cy=y;
	while(*text){
		if(*text=='\n'){
		cx=x;cy+=f.height;
		text++;
		continue;
		}
		gfx.glyph(*text,cx,cy,c);
		cx+=f.width;text++;
	}
}
void graphics::cell(uint8_t* d,int16_t x,int16_t y,uint8_t c){
	for(int row=0;row<8;row++){
		uint8_t byte=d[row];
		for(int col=0;col<8;col++)if(byte&(1<<(7-col)))gfx.pixel(x+col,y+row,c);
	}
}