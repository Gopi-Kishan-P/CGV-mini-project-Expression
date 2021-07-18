#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

char in[50], post[50];
int width = 800, height = 800;
int view = 0;
const int stackDisplayList = -999;
int stack = 1;
float stackHeight = 0.0;

void obj(double tx, double ty, double tz, double sx, double sy, double sz)
{
	glRotated(50, 0, 1, 0);
	glRotated(10, -1, 0, 0);
	glRotated(11.7, 0, 0, -1);
	glTranslated(tx, ty, tz);
	glScaled(sx, sy, sz);
	glutSolidCube(1);
	glLoadIdentity();
}

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

void displayWelcomeScreen()
{
    char e1[50] = "Expression : ";
    strcat(e1, in);
    glClearColor(0.1, 0.2, 0.9, 1);
    displayString(220, 700, "INFIX TO POSTFIX EXPRESSION", 1);
    displayString(360, 670, "AND", 1);
    displayString(180, 640, "EVALUATION OF POSTFIX EXPRESSION", 1);
    displayString(500, 70, "Mini Project By : ", 2);
    displayString(650, 45, "Gopi Kishan P", 2);
    displayString(650, 20, "Kishore AH", 2);
    displayString(10, 520, e1, 2);
    displayString(10, 100, "Instructions : ", 2);
    displayString(40, 70, "Click 'Left Mouse' Button", 2);
    displayString(65, 50, "or", 2);
    displayString(40, 30, "Press 'N' Key", 2);
    displayString(45, 10, "to go to Next Step", 2);
    displayString(350, 400, "START", 1);
}

void myInit()
{
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glNewList(stackDisplayList, GL_COMPILE);
        glColor3f(0.6, 0.7, 1.0);
        glBegin(GL_LINE_STRIP);
            glVertex2f(50, 500);
            glVertex2f(50, 50);
            glVertex2f(150, 50);
            glVertex2f(150, 500);
        glEnd();
    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (view == 0)
    {
        myInit();
        displayWelcomeScreen();
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (view == 1)
    {
        glClearColor(0, 0, 0.3, 1);
        displayString(180, 700, in, 1);
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
}

void mouseFunction(int button, int state, int x, int y) // Mouse Input Function
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        view = 1;
    }
}
void keyboardFunction(unsigned char key, int x, int y) // Keybard Input Function
{
    view = 1;
}

int main(int argc, char **argv)
{
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