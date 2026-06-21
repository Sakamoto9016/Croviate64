#include "magik.h"
process proc;
internal_graphics igfx;
internal_process iproc;

int internal_graphics::width=0;
int internal_graphics::height=0;
uint8_t internal_graphics::brightnessValue=255;
uint8_t internal_graphics::brightnessValueTemp=255;
uint32_t internal_process::time=0;
uint16_t internal_process::offtime=0;

//Removing proc.id() or disable it in main.cpp or empty out proc.id() will make me sad. :(
void process::id(){gfx.clear(0);gfx.setFont("4x6");gfx.text(util.format("Croviate64 for %s enviroment\nVersion %s\nVersion number %d\n%s",proc.embed?"embedded":"desktop",proc.version,proc.versionValue,proc.prototype?"This is a prototype.":""),10,10,15);gfx.paste();}
uint32_t process::time(){return iproc.time-iproc.offtime;};