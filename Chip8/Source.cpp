#include"Chip8.h"

void OpenGLrender();
void OpenGLInit();
void controller(unsigned char, int, int);
void controllerUP(unsigned char, int, int);
Chip8 chip8;

int main(int argc, char* argv[]) {
    chip8.initialize();
    chip8.loadGame("ROM\\BC_test_ROM.ch8");
    // freeglut init
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 640);
    glutCreateWindow("CHIP8");
    OpenGLInit();
    glutKeyboardFunc(controller);
    glutKeyboardUpFunc(controllerUP);
    glutDisplayFunc(OpenGLrender);
    glutIdleFunc(OpenGLrender);
    glutMainLoop();
    system("pause");
    return 0;
}

void OpenGLrender() {
    chip8.emulateCycle();
    Sleep(1);
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
            //print("\n");
        }
        

        //glFinish();
        //glutSwapBuffers();
        //glFlush();
        glutSwapBuffers();
        chip8.drawFlag = false;
    }
    
    //print("OpenGLrender End\n");
    //glutPostRedisplay();
    return;
}


void OpenGLInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}
void controller(unsigned char key, int x, int y) {
    //print("Press %d\n", key);
    if (key == '1') chip8.key[0x1] = 1; // Press X mapping to 1
    else if (key == '2') chip8.key[0x2] = 1; // Press 2 mapping to 2
    else if (key == '3') chip8.key[0x3] = 1; // Press 3 mapping to 3
    else if (key == '4') chip8.key[0xC] = 1; // Press 4 mapping to C

    else if (key == 'q') chip8.key[0x4] = 1; // Press q mapping to 4
    else if (key == 'w') chip8.key[0x5] = 1; // Press w mapping to 5
    else if (key == 'e') chip8.key[0x6] = 1; // Press e mapping to 6
    else if (key == 'r') chip8.key[0xD] = 1; // Press r mapping to D
    
    else if (key == 'a') chip8.key[0x7] = 1; // Press a mapping to 7
    else if (key == 's') chip8.key[0x8] = 1; // Press s mapping to 8
    else if (key == 'd') chip8.key[0x9] = 1; // Press d mapping to 9
    else if (key == 'f') chip8.key[0xE] = 1; // Press f mapping to E
    
    else if (key == 'z') chip8.key[0xA] = 1; // Press z mapping to A
    else if (key == 'x') chip8.key[0x0] = 1; // Press x mapping to 0
    else if (key == 'c') chip8.key[0xB] = 1; // Press c mapping to B
    else if (key == 'v') chip8.key[0xF] = 1; // Press v mapping to F
    else return;

}
void controllerUP(unsigned char key, int x, int y) {
    //print("Pressup %d\n", key);
    if (key == '1') chip8.key[0x1] = 0; // Press X mapping to 1
    else if (key == '2') chip8.key[0x2] = 0; // Press 2 mapping to 2
    else if (key == '3') chip8.key[0x3] = 0; // Press 3 mapping to 3
    else if (key == '4') chip8.key[0xC] = 0; // Press 4 mapping to C

    else if (key == 'q') chip8.key[0x4] = 0; // Press q mapping to 4
    else if (key == 'w') chip8.key[0x5] = 0; // Press w mapping to 5
    else if (key == 'e') chip8.key[0x6] = 0; // Press e mapping to 6
    else if (key == 'r') chip8.key[0xD] = 0; // Press r mapping to D

    else if (key == 'a') chip8.key[0x7] = 0; // Press a mapping to 7
    else if (key == 's') chip8.key[0x8] = 0; // Press s mapping to 8
    else if (key == 'd') chip8.key[0x9] = 0; // Press d mapping to 9
    else if (key == 'f') chip8.key[0xE] = 0; // Press f mapping to E

    else if (key == 'z') chip8.key[0xA] = 0; // Press z mapping to A
    else if (key == 'x') chip8.key[0x0] = 0; // Press x mapping to 0
    else if (key == 'c') chip8.key[0xB] = 0; // Press c mapping to B
    else if (key == 'v') chip8.key[0xF] = 0; // Press v mapping to F
    else return;
}