#include "magik.h"
sound snd;
sound::sound():device(0),frequency(440.0),phase(0.0),playing(false){}
void sound::init(){
	SDL_AudioSpec want{};
	want.freq=48000;
	want.format=AUDIO_F32SYS;
	want.channels=1;
	want.samples=1024;
	want.callback=audioCallback;
	want.userdata=this;
	device=SDL_OpenAudioDevice(nullptr,0,&want,nullptr,0);
	if(device!=0)SDL_PauseAudioDevice(device,0);
}
sound::~sound(){if(device!=0)SDL_CloseAudioDevice(device);}
void sound::tone(double freq){frequency=freq;playing=true;}
void sound::noTone(){playing=false;}

void sound::audioCallback(void* userdata, Uint8* stream, int len){
	sound* self=static_cast<sound*>(userdata);
	float* buffer=reinterpret_cast<float*>(stream);
	int samples=len/sizeof(float);
	for(int i=0;i<samples;i++){
		if(self->playing){
			buffer[i]=std::sin(self->phase)*0.2f;
			self->phase+=2.0*M_PI*self->frequency/48000.0;
			if(self->phase>2.0*M_PI)self->phase-=2.0*M_PI;
		}else buffer[i]=0.0f;
	}
}

uint32_t sound::noteIndex(const char *s){
	int note;
	switch(toupper((unsigned char)s[0])){
		case'C':note=0;break;case'D':note=2;break;
		case'E':note=4;break;case'F':note=5;break;
		case'G':note=7;break;case'A':note=9;break;
		case'B':note=11;break;default:return -1;
	}
	int pos=1;
	if(s[pos]=='#'){note++;pos++;}
	int octave=s[pos]-'1';
	if(octave<0||octave>7)return -1;
	return octave*12+note;
}