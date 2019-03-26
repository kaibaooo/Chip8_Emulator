#include"Chip8.h"

Chip8 chip8;

int main() {
    chip8.loadGame("testFile.txt");
    system("pause");
    return 0;
}