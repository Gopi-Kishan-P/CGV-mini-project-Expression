#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

char in[50] = "6+3-4/2*3", post[50];
int len;
int width = 800, height = 800;
int view = 0;
const int stackDisplayList = -999;
int stack = 1;
float stackHeight = 0.0;
float try = 0;
float no = 0;

void drawCustomCube(double tx, double ty, double tz, double sx, double sy, double sz, double rz)
{
    glRotated(45, 0, 1, 0);
    glRotated(rz, 0, 0, 1);
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
    char e1[50] = "Expression :  ";
    for (int i = 0; i < len; i++)
    {
        char ch = in[i];
        char temp[3];
        temp[0] = ch;
        temp[1] = ' ';
        temp[2] = '\0';
        strcat(e1, temp);
    }
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

    glNewList(stackDisplayList, GL_COMPILE); // Display List
    glColor3f(0.6, 0.7, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(50, 450);
    glVertex2f(50, 50);
    glVertex2f(150, 50);
    glVertex2f(150, 450);
    glEnd();
    displayString(75, 25, "Stack", 2);
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
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1);
        glClearColor(0, 0, 0.3, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = in[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (view == 2)
    {
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1);
        glPushMatrix();
        glTranslatef(try, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = in[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glPopMatrix();
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
        try -= 0.5;
    }
    else if (view == 3)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1);
        glClearColor(0, 0, 0.3, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = in[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (view == 4)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1);
        glPushMatrix();
        glTranslatef(no, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = in[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glPopMatrix();
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
        no -= 0.5;
    }
    else if (view == 5)
    {
        float ambient[] = {1, 1, 1, 1};
        float light_pos[] = {0.3, 0.3, 0.3, 1};
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.9, 1);
        glColor3f(1.0, 1.0, 1.0);
        drawCustomCube(0, 0, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(0, 0.15, 0, 0.3, 0.03, 0.03, 0);
        glFlush();
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else
    {
        exit(0);
    }
}

void mouseFunction(int button, int state, int x, int y) // Mouse Input Function
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        view++;
    }
}
void keyboardFunction(unsigned char key, int x, int y) // Keybard Input Function
{
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    len = strlen(in);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Infix and Postfix Expression");
    glutDisplayFunc(display);
    glutMouseFunc(mouseFunction);
    glutKeyboardFunc(keyboardFunction);
    glutMainLoop();
    return 0;
}