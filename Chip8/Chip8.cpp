#include"Chip8.h"

void init();
void display();

Chip8::Chip8() {
    
}

void Chip8::initialize() {
    // init decimal
    opcode = 0;
    I = 0;
    pc = 0x200;
    sp = -1;
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
    srand(time(NULL));
}
void Chip8::emulateCycle() {
    // fetch
    opcode = memory[pc] << 8 | memory[pc + 1];
    //print("0x%X\n", opcode);
    //print("PC : 0x%X\n", pc);
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
            // return; 
            pc = stack[sp];
            sp--;
            pc += 2;
            break;
        default:
            print("Error! Unknown opcode 0x%X\n", opcode);
            break;
        }
        break;
    case 0x1000:
        // 1NNN goto NNN
        //print("NNN -> %X\n", opcode & 0x0FFF);
        pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        // 2NNNN call subroutine at NNN
        sp++;
        stack[sp] = pc; //store current runtine
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
        reg[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
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
            // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
            //print("8XY6 V%d is %d\n", (opcode & 0x0F00) >> 8, (reg[(opcode & 0x0F00) >> 8]));
            if ((reg[(opcode & 0x0F00) >> 8] & 0x1) == 1) {
                reg[0xF] = 0x1;
            }
            else {
                reg[0xF] = 0x0;
                
            }
            reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x0F00) >> 8] >> 1;
            //print("Set V%d to %d\n", (opcode & 0x0F00) >> 8, reg[(opcode & 0x0F00)]);
            /*
            reg[0xF] = reg[(opcode & 0x0F00) >> 8] & 0x0001;
            reg[(opcode & 0x0F00) >> 8] >>= 1;
            */
            pc += 2;
            break;
        case 0x0007:
            // 8XY7 Vx=Vy-Vx
            if (reg[(opcode & 0x0F00) >> 8] < reg[(opcode & 0x00F0) >> 4]) {
                reg[0xF] = 1;
            }
            else {
                reg[0xF] = 0;
            }
            reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x00F0) >> 4] - reg[(opcode & 0x0F00) >> 8];
            pc += 2;
            break;
        case 0x000E:
            // 8XYE Vx<<=1
            //print("8XY6 V%d is %d\n", (opcode & 0x0F00) >> 8, (reg[(opcode & 0x0F00) >> 8]));
            //print("And %d\n", (reg[(opcode & 0x0F00) >> 8] & 0x80) >> 0x7);
            if (((reg[(opcode & 0x0F00) >> 8] & 0x80) >> 0x7) == 0x1) {
                reg[0xF] = 0x1;
            }
            else {
                reg[0xF] = 0x0;
            }
            // reg[0xF] = reg[(opcode & 0x0F00) >> 8] & 0x80;
            reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x0F00) >> 8] << 1;
            pc += 2;
            break;
        }
        break;
    case 0x9000:
        // 9XY0 Skips the next instruction if VX doesn¡¦t equal VY
        if (reg[(opcode & 0x0F00) >> 8] != reg[(opcode & 0x00F0) >> 4]) {
            pc += 4;
        }
        else{
            pc += 2;
        }
        break;
    case 0xA000:
        // ANNN Sets I to the address NNN.
        I = opcode & 0x0FFF;
        pc += 2;
        break;
    case 0xB000:
        // BNNN Jumps to the address NNN plus V0.
        pc = (opcode & 0x0FFF) + reg[0x0];
        break;
    case 0xC000:
        // CXNN
        reg[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
        pc += 2;
        break;
    case 0xD000:{
        // DXYN
        // draw(Vx,Vy,N)
        unsigned short x = reg[(opcode & 0x0F00) >> 8];
        unsigned short y = reg[(opcode & 0x00F0) >> 4];
        unsigned short height = (opcode & 0x000F);
        unsigned short rowPixel;
        reg[0xF] = 0;
        for (int i = 0; i < height; i++) {
            
            rowPixel = memory[I + i];
            //print("I=%d\n", I);
            //print("rowPixel=%X\n", rowPixel);
            for (int j = 0; j < 8; j++) {
                //print("rowPixel=%X\n", rowPixel);
                //print("current in 0x%X\n", (rowPixel & (0x80 >> j)) );
                if ((rowPixel & (0x80 >> j)) != 0) {
                    if (gfx[x + j + (y + i) * 64] == 1) {
                        reg[0xF] = 1;
                    }
                    gfx[x + j + (y + i) * 64] ^= 1;
                }
            }
        }
        drawFlag = true;
        pc += 2;
        break;
    }
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
            if (key[reg[(opcode & 0x0F00) >> 8]] == 0) {
                pc += 4;
            }
            else {
                pc += 2;
            }
            break;
        }
    case 0xF000:
        switch (opcode & 0x00FF) {
        case 0x0007:
            // FX07 Sets VX to the value of the delay timer
            reg[(opcode & 0x0F00) >> 8] = delay_timer;
            pc += 2;
            break;
        case 0x000A:{
            // FX0A A key press is awaited, and then stored in VX
            bool keyPress = false;
            for (int i = 0; i < 16; i++) {
                if (key[i] != 0) {
                    reg[(opcode & 0x0F00) >> 8] = i;
                    keyPress = true;
                }
            }
            if (!keyPress) return;
            pc += 2;
            break;
        }
        case 0x0015:
            // FX15 Sets the delay timer to VX.
            delay_timer = reg[(opcode & 0x0F00) >> 8];
            pc += 2;
            break;
        case 0x0018:
            // FX18 Sets the sound timer to VX.
            sound_timer = reg[(opcode & 0x0F00) >> 8];
            pc += 2;
            break;
        case 0x001E:
            // FX1E Adds VX to I
            I+= reg[(opcode & 0x0F00) >> 8];
            pc += 2;
            break;
        case 0x0029:
            // ??
            // FX29 Sets I to the location of the sprite for the character in VX.
            I = reg[(opcode & 0x0F00) >> 8] * 0x5;
            pc += 2;
            break;
        case 0x0033:
            // FX33
            //print("-------------------------------------------------FX33\n");
            memory[I] = reg[(opcode & 0x0F00) >> 8] / 100;
            memory[I + 1] = (reg[(opcode & 0x0F00) >> 8] / 10) % 10;
            memory[I + 2] = reg[(opcode & 0x0F00) >> 8] % 10;
            pc += 2;
            break;
        case 0x0055:
            // FX55
            //print("----> 0x%X\n", opcode);
            //print("Copy reg to mem from V0 to V%d, in memory %d to %d\n", (opcode & 0x0F00) >> 8, I, I + ((opcode & 0x0F00) >> 8));
            for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                memory[I + i] = reg[i];
            }
            //print("I= %d + %d + %d\n", I, (opcode & 0x0F00) >> 8, 1);
            I += ((opcode & 0x0F00) >> 8) + 1;
            //print("Current I is %d\n", I);
            pc += 2;
            break;
        case 0x0065:
            // FX65
            //print("----> 0x%X\n", opcode);
            //print("Copy mem to reg from V0 to V%d, in memory %d to %d\n", (opcode & 0x0F00) >> 8, I, I + ((opcode & 0x0F00) >> 8));
            for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                reg[i] = memory[I + i];
            }
            //print("I= %d + %d + %d\n", I, (opcode & 0x0F00) >> 8, 1);
            I += ((opcode & 0x0F00) >> 8) + 1;
            //print("Current I is %d\n", I);
            pc += 2;
            break;
        }
        break;
    default:
        print("Error! Unknown opcode 0x%X\n", opcode & 0x0FFF);
        break;
    }
    // timer--
    //print("%d\n", delay_timer);
    if (delay_timer > 0)
        delay_timer--;
    if (sound_timer > 0) {
        if (sound_timer == 1)
            printf("BEEP!\n");
        sound_timer--;
    }
    
}
void Chip8::loadGame(const char *filename) {
    initialize();
    print("Load Game : %s\n", filename);
    FILE *filePtr = fopen(filename, "rb");
    // get file size
    fseek(filePtr, 0L, SEEK_END);
    long fileSize = ftell(filePtr);
    fseek(filePtr, 0L, SEEK_SET);
    print("File Size : %d\n", fileSize);
    if (fileSize > (4096 - 512)) {
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
void Chip8::renderTest() {
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (gfx[x + y * 64]) {
                printf("O");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void Chip8::OpenGLInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}