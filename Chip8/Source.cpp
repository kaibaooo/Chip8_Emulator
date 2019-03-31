#include"Chip8.h"

void OpenGLrender();
void OpenGLInit();
Chip8 chip8;

int main(int argc, char* argv[]) {
    chip8.initialize();
    chip8.loadGame("BC_test_ROM.ch8");
    // freeglut init
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 640);
    glutCreateWindow("CHIP8");
    OpenGLInit();
    glutDisplayFunc(OpenGLrender);
    
    // character test ROM
    /*
    int xInit = 0x1;
    int yInit = 0;
    for (unsigned char i = 0; i < 0x10; i++) {
        
        if (i == 0x9) {
            xInit = 0x1;
            yInit = 0x6;
        }
        // register 0 => x cord
        chip8.memory[0x200 + i * 8] = 0x60;
        chip8.memory[0x201 + i * 8] = xInit;
        // register 1 => y cord
        chip8.memory[0x202 + i * 8] = 0x61;
        chip8.memory[0x203 + i * 8] = yInit;
        // I
        chip8.memory[0x204 + i * 8] = 0xA0;
        chip8.memory[0x205 + i * 8] = 0x00 + 0x05 * i;
        // print
        chip8.memory[0x206 + i * 8] = 0xD0;
        chip8.memory[0x207 + i * 8] = 0x15;
        xInit += 0x5;
    }
    */
    glutMainLoop();
    /*
    for (;;) {
        chip8.emulateCycle();
        if (chip8.drawFlag) {
            system("cls");
            chip8.renderTest();
            chip8.drawFlag = false;
        }
        
    }
    */
    system("pause");
    return 0;
}

void OpenGLrender() {
    chip8.emulateCycle();
    if (chip8.drawFlag) {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        for (int i = 0; i < 640; i += 20) {
            for (int j = 0; j < 1280; j += 20) {
                //print("%d", chip8.gfx[j / 20 + i / 20 * 64]);
                if (chip8.gfx[j / 20 + i / 20 * 64] == 1) {
                    //glColor3f(1.0, 1.0, 1.0);
                    glBegin(GL_QUADS); {
                        glVertex3f(-5.0 + j / 20.0 * wPx        , 5.0 - hPx - i / 20.0 * hPx    , 0.0); // The bottom left corner  
                        glVertex3f(-5.0 + j / 20.0 * wPx        , 5.0 - i / 20.0 * hPx          , 0.0); // The top left corner  
                        glVertex3f(wPx - 5.0 + j / 20 * wPx     , 5.0 - i / 20.0 * hPx          , 0.0); // The top right corner 
                        glVertex3f(wPx - 5.0 + j / 20.0 * wPx   , 5.0 - hPx - i / 20.0 * hPx    , 0.0); // The bottom right corner

                    }
                    glEnd();
                    
                }

            }
            print("\n");
        }
        glFlush();
        chip8.drawFlag = false;
    }
    
    //print("OpenGLrender End\n");
    glutPostRedisplay();
    return;
}


void OpenGLInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}