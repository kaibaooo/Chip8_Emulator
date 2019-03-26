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
        memory[i] = chip8_fontset[i];
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
            // 00E0 disp_clear() 
            for (int i = 0; i < 2048; i++) {
                gfx[i] = 0x0;
            }
            drawFlag = true;
            pc += 2;
            break;
        case 0x000E:
            // 00EE
            // return; <=======
            sp--;
            pc = stack[sp];
            pc += 2;
            break;
        default:
            print("Error! Unknown opcode 0x%X\n", opcode);
            break;
        }
    case 0x1000:
        // 1NNN goto NNN
        pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        // 2NNNN call subroutine at NNN
        stack[sp] = pc; //store current runtine
        sp++;
        pc = opcode & 0x0FFF;
        break;
    case 0x3000:
        // 3XNN Skips the next instruction if VX equals NN. 
        if (reg[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
            pc += 4;
        }
        else {
            pc += 2;
        }
        break;
    case 0x4000:
        // 4XNN Skips the next instruction if VX doesn¡¦t equal NN.
        if (reg[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
            pc += 4;
        }
        else {
            pc += 2;
        }
        break;
    case 0x5000:
        // 5XY0 Skips the next instruction if VX equals VY. 
        if (reg[(opcode & 0x0F00) >> 8] == reg[(opcode & 0x00F0) >> 4]) {
            pc += 4;
        }
        else {
            pc += 2;
        }
        break;
    case 0x6000:
        // 6XNN Sets VX to NN.
        reg[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
        pc += 2;
        break;
    case 0x7000:
        // 7XNN Adds NN to VX. (Carry flag is not changed)
        reg[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
        pc += 2;
        break;
    case 0x8000:
        switch (opcode & 0x000F) {
        case 0x0000:
            // 8XY0 Sets VX to the value of VY.
            reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0001:
            // 8XY1 VX = VX or VY
            reg[(opcode & 0x0F00) >> 8] |= reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0002:
            // 8XY2 VX = VX&VY
            reg[(opcode & 0x0F00) >> 8] &= reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0003:
            // 8XY2 VX = VX^VY
            reg[(opcode & 0x0F00) >> 8] ^= reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0004: //Vx += Vy
            if (reg[(opcode & 0x00F0) >> 4] > (0xFF - reg[(opcode & 0x0F00) >> 8])) {
                reg[0xF] = 1;
            }
            else {
                reg[0xF] = 0;
            }
            reg[(opcode & 0x0F00) >> 8] += reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0005:
            // 8XY5 Vx -= Vy
            if (reg[(opcode & 0x00F0) >> 4] > reg[(opcode & 0x0F00) >> 8]) {
                reg[0xF] = 0;
            }
            else {
                reg[0xF] = 1;
            }
            reg[(opcode & 0x0F00) >> 8] -= reg[(opcode & 0x00F0) >> 4];
            pc += 2;
            break;
        case 0x0006:
            // 8XY6 Vx>>=1
            reg[0xF] = reg[(opcode & 0x0F00) >> 8] & 0x1;
            reg[(opcode & 0x0F00) >> 8] >>= 1;
            pc += 2;
            break;
        case 0x0007:
            // 8XY7 Vx=Vy-Vx
            if (reg[(opcode & 0x0F00) >> 8] > reg[(opcode & 0x00F0) >> 4]) {
                reg[0xF] = 0;
            }
            else {
                reg[0xF] = 1;
            }
            reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x00F0) >> 4] - reg[(opcode & 0x0F00) >> 8];
            pc += 2;
            break;
        case 0x000E:
            // 8XYE Vx<<=1
            reg[0xF] = reg[(opcode & 0x0F00) >> 8] & 0x80;
            reg[(opcode & 0x0F00) >> 8] <<= 1;
            pc += 2;
            break;
        }
    case 0x9000:

        pc += 2;
        break;
    case 0xA000:
        I = opcode & 0x0FFF;
        pc += 2;
        break;
    case 0xD000: 
        // DXYN
        // draw(Vx,Vy,N)
        unsigned char x = (opcode & 0x0F00) >> 8;
        unsigned char y = (opcode & 0x00F0) >> 4;
        unsigned char height = (opcode & 0x000F);
        unsigned rowPixel;
        reg[0xF] = 0;
        for (int i = 0; i < height; i++) {
            rowPixel = memory[I + i];
            for (int j = 0; j < 8; j++) {
                if (rowPixel & (0x80 >> i) != 0) {
                    if (gfx[x + i + (y + j) * 64]) {
                        reg[0xF] = 0;
                    }
                    gfx[x + i + (y + j) * 64] ^= 1;
                }
            }
        }
        drawFlag = true;
        pc += 2;
        break;
    case 0xE000:
        switch (opcode & 0x00FF) {
        case 0x009E:
            // EX9E if(key()==Vx)
            // Skips the next instruction if the key stored in VX is pressed.
            if (key[reg[(opcode & 0x0F00) >> 8]] != 0) {
                pc += 4;
            }
            else {
                pc += 2;
            }
            break;
        case 0x00A1:
            // EXA1 if(key()!=Vx)    
            // Skips the next instruction if the key stored in VX isn¡¦t pressed
            break;
        }
    case 0xF000:
        switch (opcode & 0x00FF) {
        case 0x0033:
            memory[I] = reg[(opcode & 0x0F00) >> 8] / 100;
            memory[I + 1] = reg[(opcode & 0x0F00) >> 8] % 100 / 10;
            memory[I + 2] = reg[(opcode & 0x0F00) >> 8] % 10;
            pc += 2;
        }
        break;
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