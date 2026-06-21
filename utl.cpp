/*Share between Embed & Full*/
#include "magik.h"
utilities util;

long utilities::random(long min, long max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<long> dist(min,max-1);
    return dist(gen);
}
int utilities::min(int a,int b){return(a<b)?a:b;}
int utilities::max(int a,int b){return(a>b)?a:b;}
char* utilities::format(const char* fmt,...){ // %s(string) %d(int) %f(float)
	static char buffer[1024];
	va_list args;
	va_start(args,fmt);
	vsprintf(buffer,fmt,args);
	va_end(args);
	return buffer;
}
bool utilities::getFlag(uint32_t v,uint8_t p){return(v>>p)&1ULL;}
void utilities::setFlag(uint32_t &v, uint8_t p, bool b){if (b)v|=(1ULL<<p);else v&=~(1ULL<<p);}
/*
flags |= (1 << 0);
flags |= (1 << 1);
flags |= (1 << 2);
flags |= (1 << 3);
*/
void utilities::delay(uint dur){iproc.delay(dur);}
