#include"Chip8.h"

Chip8 chip8;

int main() {
    chip8.initialize();
    chip8.loadGame("tetris.c8");
    system("pause");
    for(;;){
        chip8.emulateCycle();
        chip8.renderTest();
        if (chip8.drawFlag) {
            system("cls");
            chip8.drawFlag = false;
        }
    }
    system("pause");
    return 0;
}
void keyboardDown(unsigned char key, int x, int y) {
    if (key == 27)    // esc
        exit(0);

    if (key == '1')		chip8.key[0x1] = 1;
    else if (key == '2')	chip8.key[0x2] = 1;
    else if (key == '3')	chip8.key[0x3] = 1;
    else if (key == '4')	chip8.key[0xC] = 1;

    else if (key == 'q')	chip8.key[0x4] = 1;
    else if (key == 'w')	chip8.key[0x5] = 1;
    else if (key == 'e')	chip8.key[0x6] = 1;
    else if (key == 'r')	chip8.key[0xD] = 1;

    else if (key == 'a')	chip8.key[0x7] = 1;
    else if (key == 's')	chip8.key[0x8] = 1;
    else if (key == 'd')	chip8.key[0x9] = 1;
    else if (key == 'f')	chip8.key[0xE] = 1;

    else if (key == 'z')	chip8.key[0xA] = 1;
    else if (key == 'x')	chip8.key[0x0] = 1;
    else if (key == 'c')	chip8.key[0xB] = 1;
    else if (key == 'v')	chip8.key[0xF] = 1;

    //printf("Press key %c\n", key);
}

void keyboardUp(unsigned char key, int x, int y) {
    if (key == '1')		chip8.key[0x1] = 0;
    else if (key == '2')	chip8.key[0x2] = 0;
    else if (key == '3')	chip8.key[0x3] = 0;
    else if (key == '4')	chip8.key[0xC] = 0;

    else if (key == 'q')	chip8.key[0x4] = 0;
    else if (key == 'w')	chip8.key[0x5] = 0;
    else if (key == 'e')	chip8.key[0x6] = 0;
    else if (key == 'r')	chip8.key[0xD] = 0;

    else if (key == 'a')	chip8.key[0x7] = 0;
    else if (key == 's')	chip8.key[0x8] = 0;
    else if (key == 'd')	chip8.key[0x9] = 0;
    else if (key == 'f')	chip8.key[0xE] = 0;

    else if (key == 'z')	chip8.key[0xA] = 0;
    else if (key == 'x')	chip8.key[0x0] = 0;
    else if (key == 'c')	chip8.key[0xB] = 0;
    else if (key == 'v')	chip8.key[0xF] = 0;
}
