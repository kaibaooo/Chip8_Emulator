#include"Chip8.h"

void OpenGLrender();
Chip8 chip8;

int main(int argc, char* argv[]) {
    chip8.initialize();
    //chip8.loadGame("tetris.c8");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 640);
    glutCreateWindow("CHIP8");
    chip8.OpenGLInit();
    glutDisplayFunc(OpenGLrender);
    

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
    
    chip8.memory[0x241] = 0x00;
    chip8.memory[0x242] = 0x0A;
    //system("pause");
    glutMainLoop();
    //for(;;){
        
        //print("Prev opcode 0x%X\n", chip8.opcode);
        //system("pause");
        
    //}
    system("pause");
    return 0;
}

void OpenGLrender() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON); {
        glVertex3f(-5.0, 5.0, 0.0); // The top left corner  
        glVertex3f(wPx - 5, 5.0, 0.0); // The top right corner 
        glVertex3f(-5.0, 5 - hPx, 0.0); // The bottom left corner  
        glVertex3f(wPx - 5, 5 - hPx, 0.0); // The bottom right corner

    }
    glEnd();
    chip8.emulateCycle();
    if (chip8.drawFlag) {

        chip8.drawFlag = false;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 640; i += 20) {
        for (int j = 0; j < 1280; j+=20) {
            print("%d", chip8.gfx[j / 20 + i / 20 * 64]);
            if (chip8.gfx[j / 20 + i / 20 * 64] == 1) {
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_POLYGON); {
                    glVertex3f(-5.0 + j, 5.0 - i, 0.0); // The top left corner  
                    glVertex3f(wPx - 5 + j, 5.0 - i, 0.0); // The top right corner 
                    glVertex3f(-5.0 + j, 5 - hPx - i, 0.0); // The bottom left corner  
                    glVertex3f(wPx - 5 + j, 5 - hPx - i, 0.0); // The bottom right corner

                }
                glEnd();
                //glFlush();
            }
            /*
            else {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_POLYGON); {
                    glVertex3f(-5.0 + j, 5.0 - i, 0.0); // The top left corner  
                    glVertex3f(wPx - 5 + j, 5.0 - i, 0.0); // The top right corner 
                    glVertex3f(-5.0 + j, 5 - hPx - i, 0.0); // The bottom left corner  
                    glVertex3f(wPx - 5 + j, 5 - hPx - i, 0.0); // The bottom right corner

                }
                glEnd();
                glFlush();
            }
            */
            
        }
        print("\n");
    }
    print("OpenGLrender End\n");
    return;
}