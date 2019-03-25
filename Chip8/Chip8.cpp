#include"Chip8.h"

Chip8::Chip8() {

}

void Chip8::initialize() {
    // init decimal
    opcode = 0;
    I = 0;
    pc = 0x200;
    sp = 0;
    drawFlag = true;
    delay_timer = 0;
    sound_timer = 0;
    // init array memory
    for (int i = 0; i < 4096; i++) {
        memory[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        reg[i] = 0;
    }
    for (int i = 0; i < 2048; i++) {
        gfx[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        //*(stack + i) = 0;
        stack[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        key[i] = 0;
    }
    //??
    srand(time(NULL));
}
void Chip8::emulateCycle() {
    // fetch
    opcode = memory[pc] << 8 | memory[pc + 1];
    
}