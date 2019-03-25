#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
class Chip8 {
public:
    //opcode
    unsigned short opcode;
    //4K memory in total
    //Memory mapping
    // 0x000 - 0x1FF - Chip 8 interpreter(contains font set in emu)
    // 0x050 - 0x0A0 - Used for the built in 4x5 pixel font set(0 - F)
    // 0x200 - 0xFFF - Program ROM and work RAM
    unsigned char memory[4096];
    //CPU register
    unsigned char reg[16];
    //Index register
    unsigned short I;
    //program counter
    unsigned short pc;
    // graphics
    unsigned char gfx[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    // perform a jump or call a subroutine, store the program counter in the stack before proceeding
    unsigned short stack[16];
    // remember which level of the stack is used
    unsigned short sp;  
    // input
    unsigned char key[16];
    bool drawFlag;
    
    Chip8();
    void initialize();
    void loadGame(char *);
    void emulateCycle();
    void setKeys();
};