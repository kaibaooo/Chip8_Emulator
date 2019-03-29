#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <GL/glut.h>
#pragma warning(disable:4996)
#define print printf
#define wPx 0.15625
#define hPx 0.3125

class Chip8 {
public:
    //fontset
    unsigned char chip8_fontset[80] =
    {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    //opcode
    unsigned short opcode;
    // 4KB memory in total
    // Memory mapping
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
    void loadGame(const char *);
    void emulateCycle();
    void setKeys();
    void OpenGLrender();
    void renderTest();
    void OpenGLInit();
};