#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>

char in[50], post[50];
int width = 900, height = 800;
int view = 0;

void displayString(int x, int y, char *string, int font)
{
    int len, i;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        if (font == 1)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
        if (font == 2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        if (font == 3)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
        if (font == 4)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
    }
}

void displayWelcomeScreen(){
    char e1[50] = "Expression : ";
    strcat(e1, in);
    glClearColor(0.1, 0.2, 0.9, 1);
    displayString(150, 440, "INFIX TO POSTFIX EXPRESSION", 1);
    displayString(230, 420, "AND", 1);
    displayString(120, 400, "EVALUATION OF POSTFIX EXPRESSION", 1);
    displayString(350, 50, "Mini Project By : ", 2);
    displayString(430, 30, "Gopi Kishan P", 2);
    displayString(430, 10, "Kishore AH", 2);
    displayString(10, 350, e1, 2);
    displayString(10, 100, "Instructions : ", 2);
    displayString(10, 80, "Click 'Left Mouse' Button", 2);
    displayString(15, 65, "or", 2);
    displayString(10, 50, "Press 'N' Key", 2);
    displayString(15, 35, "to go to Next Step", 2);
    displayString(230, 250, "START", 1);
    glutPostRedisplay();
    glutSwapBuffers();
}

void myInit()
{
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(view == 0)
    {
        myInit();
        displayWelcomeScreen();
    }
    else if (view == 1)
    {
        glLoadIdentity();
        glClearColor(0, 0, 0.3, 1);
        glutPostRedisplay();
        glutSwapBuffers();
    }
}

void mouseFunction(int button, int state, int x, int y) // Mouse Input Function
{
    view = 1;
}
void keyboardFunction(unsigned char key, int x, int y) // Keybard Input Function
{
    view = 1;
}

int main(int argc, char **argv){
    printf("\nEnter an Expression containing operators + - * / ^ ( ) and digits 0-9\n");
    scanf("%s", in);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Infix and Postfix Expression");
    glutDisplayFunc(display);
    glutMouseFunc(mouseFunction);
    glutKeyboardFunc(keyboardFunction);
    glutMainLoop();
    return 0;
}