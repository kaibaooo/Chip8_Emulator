#include"Chip8.h"

Chip8 chip8;

int main() {
    chip8.initialize();
    //chip8.loadGame("tetris.c8");
    
    for (unsigned char i = 0; i < 0x10; i++) {
        // register 0 => x cord
        chip8.memory[0x200 + i * 8] = 0x60;
        chip8.memory[0x201 + i * 8] = 0x01 + 0x05 * i;
        // register 1 => y cord
        chip8.memory[0x202 + i * 8] = 0x61;
        chip8.memory[0x203 + i * 8] = 0x00;
        // I
        chip8.memory[0x204 + i * 8] = 0xA0;
        chip8.memory[0x205 + i * 8] = 0x00 + 0x05 * i;
        // print
        chip8.memory[0x206 + i * 8] = 0xD0;
        chip8.memory[0x207 + i * 8] = 0x15;
    }
    
    
    
    /*
    // register 0 => x cord
    chip8.memory[0x200] = 0x60;
    chip8.memory[0x201] = 0x01;
    // register 1 => y cord
    chip8.memory[0x202] = 0x61;
    chip8.memory[0x203] = 0x00;
    // I
    chip8.memory[0x204] = 0xA0;
    chip8.memory[0x205] = 0x00;
    // print
    chip8.memory[0x206] = 0xD0;
    chip8.memory[0x207] = 0x15;
    
    
    // register 0 => x cord
    chip8.memory[0x208] = 0x60;
    chip8.memory[0x209] = 0x06;
    // register 1 => y cord
    chip8.memory[0x20A] = 0x61;
    chip8.memory[0x20B] = 0x00;
    // I
    chip8.memory[0x20C] = 0xA0;
    chip8.memory[0x20D] = 0x05;
    // print
    chip8.memory[0x20E] = 0xD0;
    chip8.memory[0x20F] = 0x15;
    */
    
    system("pause");

    for(;;){
        if (chip8.drawFlag) {
            system("cls");
            chip8.drawFlag = false;
        }
        chip8.emulateCycle();
        chip8.renderTest();

        
        print("Prev opcode 0x%X\n", chip8.opcode);
        system("pause");
        
    }
    system("pause");
    return 0;
}