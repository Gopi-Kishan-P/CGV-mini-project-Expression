#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include<ctype.h>

static int menu_id;
static int sub_menu;
static int submenu2;
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

void drawCustomCube(double tx, double ty, double tz, double sx, double sy, double sz, double rz)
{
    glRotated(30, 0, 1, 0);
    glRotated(rz, 0, 0, 1);
    glTranslated(tx, ty, tz);
    glScaled(sx, sy, sz);
    glutSolidCube(1);
    glLoadIdentity();
}
void drawQuadricSurface(double tx, double ty, double tz, int i)
{
    glRotated(25, 0, 1, 0);
	glRotated(18, -1, 0, 0);
	glRotated(36.7, 0, 0, -1);
	glTranslated(tx, ty, tz);
    if(i==1)
        glutSolidTeapot(0.15);
    else
        glutSolidSphere(0.15, 100, 100);
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
        case 3: break;
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

 void screen_menu(int num)
{
    switch(num)
    {
        case 9: 
        case 10: 
        case 11:
        case 12: break;
    }
 }

void createMenu(void)
{ 
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Kishore A H ( 1AY18CS052 )", 2);
    glutAddMenuEntry("Gopi Kishan P ( 1AY18CS040 )", 3);
    submenu2 = glutCreateMenu(screen_menu);
    glutAddMenuEntry("Welcome Screen",9);
	glutAddMenuEntry("Infix to Postfix Expression Screen",10);
	glutAddMenuEntry("Evaluation of Postfix Expression screen",11);
	glutAddMenuEntry("End Screen",12);
    sub_menu=glutCreateMenu(demo_menu);
	glutAddMenuEntry("Press Left Mouse Button for Next screen",5);
	glutAddMenuEntry("Press UP key for Zoom In in End Screen",6);
	glutAddMenuEntry("Press DOWN key for Zoom Out in End Screen",7);
	glutAddMenuEntry("Press Q to quit and N to start",8);
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Instructions", sub_menu);
    glutAddSubMenu("Screens", submenu2);
	glutAddSubMenu("About", submenu_id);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int F(char symbol) 
{
    switch(symbol)
	{
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '#': return -1;
        default: return 8; 
     }
}

int G(char symbol) 
{
	switch(symbol)
	{
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '#': return 0;
        default: return 7; 
        }	
}

void infix_postfix(char infix[], char postfix[])
{
	int top, j, i;
	char s[30];
	char symbol;
	top = -1;
	s[++top] = '#';
	j = 0;
	for(i=0;i<strlen(infix);i++)
	{
		symbol = infix[i];
		while(F(s[top]) > G(symbol))
			postfix[j++] = s[top--];
		if(F(s[top]) != G(symbol))
			s[++top] = symbol;
		else
			top--;
	}
	while(s[top] != '#')
		postfix[j++] = s[top--];
	postfix[j] = '\0';
}

double compute(char symbol,double op1, double op2) 
{
	switch(symbol) 
	{
		case '+': return op1 + op2;
		case '-': return op1 - op2; 
		case '*': return op1 * op2; 
		case '/': return op1 / op2;
		default: return 0;
	} 
}

void ev_postfix() //function for evalulation of postfix exp
{
	double s[20], res, op1, op2; 
	int top, i;
	char postfix[20], symbol; 

	printf("\nEnter the postfix expression:\n"); 
	scanf("%s",postfix);
	top=-1;
	for(i=0; i<strlen(postfix); i++) 
	{
		symbol= postfix[i]; 
		if(isdigit(symbol))
			s[++top]= symbol-'0'; 
		else
		{
			op2 = s[top--]; 
			op1 = s[top--];
			res =compute(symbol, op1, op2); 
			s[++top]= res;
		} 
	}
	res =s[top--];
	printf("\nThe result is:%f\n",res); 
}



void displayString(int x, int y, char *string, int font, char color)
{
    int len, i;
    switch (color)
    {
    case 'gb' : glColor3f(0.0,0.1,0.1);
                break;
    case 'rg' : glColor3f(0.1,0.1,0.0);
                break;
    case 'o' : glColor3f(0.1,0.0,0.1);
                break;
    
    default:
        break;
    }
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
    displayString(220, 700, "INFIX TO POSTFIX EXPRESSION", 1,'rg');
    displayString(360, 670, "AND", 1, 'rg');
    displayString(180, 640, "EVALUATION OF POSTFIX EXPRESSION", 1,'rg');
    displayString(500, 70, "Mini Project By : ", 2,'rg');
    displayString(500, 45, "Gopi Kishan P ( 1AY18CS040 )", 2, 'rg');
    displayString(500, 20, "Kishore A H ( 1AY18CS052 )", 2, 'rg');
    displayString(10, 520, e1, 2, 'rg');
    displayString(200, 300, "**** For Instructions, Click 'Right Mouse' Button ****",2, 'gb');
    // displayString(60, 120, "", 2);
    // displayString(65, 50, "or", 2);
    // displayString(40, 30, "Press 'N' Key", 2);
    // displayString(45, 10, "to go to Next Step", 2);
    displayString(350, 400, "START", 1, 'rg');
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
    displayString(60, 20, "STACK", 1,'o');
    glBegin(GL_LINE_STRIP);
    glVertex2f(50, 450);
    glVertex2f(50, 50);
    glVertex2f(150, 50);
    glVertex2f(150, 450);
    glEnd();
    displayString(320, 220, "Expression", 1, 'o');
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
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1,'gb');
        glClearColor(0.0, 0.9, 0.5, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1,'rg');
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 2)
    {
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1, 'gb');
        glPushMatrix();
        glTranslatef(try, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1,'rg');
        }
        glPopMatrix();
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
        try -= 0.5;
    }
    else if (screen == 3)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1,'gb');
        glClearColor(0.1, 0.2, 0.5, 1);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1,'rg');
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 4)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1, 'gb');
        glPushMatrix();
        glTranslatef(no, 0.0, 0.0);
        for (int i = 0; i < len; i++)
        {
            char ch = infix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(180 + i * 30, 650, temp, 1, 'rg');
        }
        glPopMatrix();
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
        no -= 0.5;
    }
    else if (screen == 5)
    {
        float ambient[] = {1, 1, 1, 1};
        float light_pos[] = {-1, -1, -1.3, 1};
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
        // To Display THANK YOU
        // T
        drawCustomCube(-0.87, 0.5, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(-0.87, 0.64, 0, 0.3, 0.03, 0.03, 0);
        // H
        drawCustomCube(-0.49, 0.5, 0, 0.25, 0.03, 0.03, 0);
        drawCustomCube(-0.6, 0.5, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(-0.35, 0.5, 0, 0.03, 0.3, 0.03, 0);
        // A
        drawCustomCube(-0.055, 0.5, 0, 0.15, 0.03, 0.03, 0);
        drawCustomCube(0.22, 0.45, 0, 0.03, 0.35, 0.03, 25);
        drawCustomCube(-0.35, 0.395, 0, 0.03, 0.35, 0.03, -25);
        // N
        drawCustomCube(0.56, 0.19, 0, 0.03, 0.35, 0.03, 40);
        drawCustomCube(0.20, 0.5, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(0.425, 0.5, 0, 0.03, 0.3, 0.03, 0);
        // K
        drawCustomCube(0.79, -0.19, 0, 0.03, 0.20, 0.03, 45);
        drawCustomCube(0.09, 0.88, 0, 0.03, 0.20, 0.03, -45);
        drawCustomCube(0.6, 0.5, 0, 0.03, 0.3, 0.03, 0);
        // Y
        drawCustomCube(-0.3, -0.3, 0, 0.03, 0.20, 0.03, -45);
        drawCustomCube(-0.4, 0.4, 0, 0.03, 0.20, 0.03, 45);
        drawCustomCube(-0.495, -0.15, 0, 0.03, 0.2, 0.03, 0);
        // O
        drawCustomCube(-0.075, -0.235, 0, 0.27, 0.03, 0.03, 0);
        drawCustomCube(-0.075, 0.035, 0, 0.27, 0.03, 0.03, 0);
        drawCustomCube(-0.2, -0.1, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(0.05, -0.1, 0, 0.03, 0.3, 0.03, 0);
        // U
        drawCustomCube(0.32, -0.235, 0, 0.25, 0.03, 0.03, 0);
        drawCustomCube(0.2, -0.1, 0, 0.03, 0.3, 0.03, 0);
        drawCustomCube(0.45, -0.1, 0, 0.03, 0.3, 0.03, 0);
        glFlush();

        // teapot
        drawQuadricSurface(0.7, -0.35, 0, 1);
        // sphere
        drawQuadricSurface(-0.2, -1, 0, 2);
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