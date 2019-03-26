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
    //load fontset
    for (int i = 0; i < 80; i++) {

    }
    //??
    srand(time(NULL));
}
void Chip8::emulateCycle() {
    // fetch
    opcode = memory[pc] << 8 | memory[pc + 1];
    // decode
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (opcode & 0x000F) {
        case 0x0000:
            // disp_clear() <=======
            break;
        case 0x000E:
            // return; <=======
            break;
        default:
            print("Error! Unknown opcode 0x%X\n", opcode);
            break;
        }
    case 0x1000:
        stack[sp] = pc; //record current runtine
        sp++;
        pc = opcode & 0x0FFF;
        break;
    case 0x8000:
        switch (opcode & 0x000F) {
        case 0x0004: //Vx += Vy
            if (reg[(opcode & 0x00F0) >> 4] > reg[(opcode & 0x0F00) >> 8]) {
                reg[0x000F] = 1;
            }
            else {
                reg[0x000F] = 0;
            }
            reg[(opcode & 0x0F00) >> 8] += reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        }
    case 0xA000:
        I = opcode & 0x0FFF;
        pc += 2;
    case 0xF000:
        switch (opcode & 0x00FF) {
        case 0x0033:
            memory[I] = reg[(opcode & 0x0F00) >> 8] / 100;
            memory[I + 1] = reg[(opcode & 0x0F00) >> 8] % 100 / 10;
            memory[I + 2] = reg[(opcode & 0x0F00) >> 8] % 10;
            pc += 2;
        }
    default:
        print("Error! Unknown opcode 0x%X\n", opcode & 0x0FFF);
        break;
    }
    // timer--
    if (delay_timer > 0)
        delay_timer--;
    
    
}
void Chip8::loadGame(const char *filename) {
    print("Load Game : %s\n", filename);
    FILE *filePtr = fopen(filename, "rb");
    // get file size
    fseek(filePtr, 0L, SEEK_END);
    long fileSize = ftell(filePtr);
    fseek(filePtr, 0L, SEEK_SET);
    print("File Size : %d\n", fileSize);
    if (fileSize < (4096 - 512)) {
        print("File is too big\n");
        return;
    }
    char * buffer = (char*)malloc(sizeof(char) * fileSize);
    fread(buffer, 1, fileSize, filePtr);
    print("Loading file....\n");
    for (int i = 0; i < fileSize; i++) {
        memory[512 + i] = buffer[i];
    }
    print("Loaded!\n");
    
}