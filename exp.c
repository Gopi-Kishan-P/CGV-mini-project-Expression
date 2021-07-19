#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

static int menu_id;
static int sub_menu;
static int submenu_id;
static int window;
static int value = 0;

char infix[50] = "6+3-4/2*3", postfix[50];
int len;
int width = 800, height = 800;
int screen = 0;
const int stackDisplayList = -999;
int stack = 1;
float stackHeight = 0.0;
float try = 0;
float no = 0;

void obj(double tx, double ty, double tz, double sx, double sy, double sz)
{
	glRotated(45, 0, 1, 0); 
	glTranslated(tx, ty, tz);
	glScaled(sx, sy, sz);
	glutSolidCube(1);
	glLoadIdentity();
}

void menu(int num)
{
	if (num == 0)
	{
        glutDestroyWindow(window);
        exit(0);
	}
	else
    {
      switch (num)
      {
        case 2:
        case 3:
        case 10: break;
      }
	}
	glutPostRedisplay();
}
void demo_menu(int num)
{
    switch(num)
    {
        case 5:
        case 6: 
        case 7:
        case 8: break;
    }
 }

void createMenu(void)
{ 
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Kishore A H", 2);
    glutAddMenuEntry("Gopi Kishan P", 3);
    sub_menu=glutCreateMenu(demo_menu);
	glutAddMenuEntry("Press Left Mouse Button for Next screen",5);
	glutAddMenuEntry("Press UP key for Zoom In in End Screen",6);
	glutAddMenuEntry("Press DOWN key for Zoom Out in End Screen",7);
	glutAddMenuEntry("Press Q to quit and N to start",8);
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Instructions", sub_menu);
	glutAddSubMenu("About", submenu_id);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void displayString(int x, int y, char *string, int font)
{
    int len, i;
    glColor3f(0.1, 0.2, 1.0);
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
        char ch = infix[i];
        char temp[3];
        temp[0] = ch;
        temp[1] = ' ';
        temp[2] = '\0';
        strcat(e1, temp);
    }
    glClearColor(0.8, 1.0, 0.6, 1);
    displayString(220, 700, "INFIX TO POSTFIX EXPRESSION", 1);
    displayString(360, 670, "AND", 1);
    displayString(180, 640, "EVALUATION OF POSTFIX EXPRESSION", 1);
    displayString(500, 70, "Mini Project By : ", 2);
    displayString(650, 45, "Gopi Kishan P", 2);
    displayString(650, 20, "Kishore A H", 2);
    displayString(10, 520, e1, 2);
    displayString(200, 300, "**** For Instructions, Click 'Right Mouse' Button ****", 2);
    // displayString(60, 120, "", 2);
    // displayString(65, 50, "or", 2);
    // displayString(40, 30, "Press 'N' Key", 2);
    // displayString(45, 10, "to go to Next Step", 2);
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
    displayString(60, 20, "STACK", 1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(50, 450);
    glVertex2f(50, 50);
    glVertex2f(150, 50);
    glVertex2f(150, 450);
    glEnd();
    displayString(320, 220, "Expression", 1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(250, 300);
    glVertex2f(250, 250);
    glVertex2f(500, 250);
    glVertex2f(500, 300);
    glVertex2f(250, 300);

    glEnd();
    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (screen == 0)
    {
        myInit();
        displayWelcomeScreen();
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 1)
    {
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1);
        glClearColor(0.4, 0.1, 0.0, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 2)
    {
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1);
        glPushMatrix();
        glTranslatef(try, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
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
    else if (screen == 3)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1);
        glClearColor(0, 0, 0.3, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1);
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 4)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1);
        glPushMatrix();
        glTranslatef(no, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
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
    else if (screen == 5)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.9, 1);
        glColor3f(1.0, 1.0, 1.0);
        glutSolidCube(1);
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
        screen++;
    }
}
void keyboardFunction(unsigned char key, int x, int y) // Keybard Input Function
{
    if (key == 'Q' || key == 'q')
        exit(0);
}

void myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w, 2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
		glOrtho(-2.0*(GLfloat)w/(GLfloat)h, 2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    len = strlen(infix);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Infix and Postfix Expression");
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutMouseFunc(mouseFunction);
    createMenu();
    glutKeyboardFunc(keyboardFunction);
    glutMainLoop();
    return 0;
}