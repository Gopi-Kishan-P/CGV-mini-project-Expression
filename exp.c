#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

static int menu_id;
static int sub_menu;
static int submenu2;
static int submenu_id;
static int window;
static int value = 0;

char infix[50] = "6+3-4/2*3", postfix[50];
int infixLen;
int postfixLen;
int width = 800, height = 800;
int screen = 0;
const int stackDisplayList = -999;
float stackHeight = 0.0;
float try = 0;
float no = 0;
char stack[50];
int stkTop = -1;
char temp[2];
int infixAnimateComplete = 0;

struct Point
{
    int x, y;
};

struct Point i0 = {250, 650};
struct Point i1 = {250 + 1 * 30, 650};
struct Point i2 = {250 + 2 * 30, 650};
struct Point i3 = {250 + 3 * 30, 650};
struct Point i4 = {250 + 4 * 30, 650};
struct Point i5 = {250 + 5 * 30, 650};
struct Point i6 = {250 + 6 * 30, 650};
struct Point i7 = {250 + 7 * 30, 650};
struct Point i8 = {250 + 8 * 30, 650};

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
    if (i == 1)
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
        case 3:
            break;
        }
    }
    glutPostRedisplay();
}
void demo_menu(int num)
{
    switch (num)
    {
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    }
}

void screen_menu(int num)
{
    switch (num)
    {
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    }
}

void createMenu(void)
{
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Kishore A H ( 1AY18CS052 )", 2);
    glutAddMenuEntry("Gopi Kishan P ( 1AY18CS040 )", 3);
    submenu2 = glutCreateMenu(screen_menu);
    glutAddMenuEntry("Welcome Screen", 9);
    glutAddMenuEntry("Infix to Postfix Expression Screen", 10);
    glutAddMenuEntry("Evaluation of Postfix Expression Screen", 11);
    glutAddMenuEntry("End Screen", 12);
    sub_menu = glutCreateMenu(demo_menu);
    glutAddMenuEntry("Press 'Left Mouse Button' to go to Next Screen", 5);
    glutAddMenuEntry("Press 'N' to go to Next Screen", 6);
    glutAddMenuEntry("Press 'Space Bar' to go to Next Screen", 7);
    glutAddMenuEntry("Press Q to quit and N to start", 8);
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Instructions", sub_menu);
    glutAddSubMenu("Screens", submenu2);
    glutAddSubMenu("About", submenu_id);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int F(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 4;
    case '#':
        return -1;
    default:
        return 8;
    }
}

int G(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 3;
    case '#':
        return 0;
    default:
        return 7;
    }
}

void moveToPostfix(char ch)
{
    postfixLen = strlen(postfix);
    postfix[postfixLen] = ch;
    postfix[postfixLen + 1] = '\0';
    postfixLen++;
}

int precedence(char op)
{
    switch (op)
    {
    case '/':
    case '*':
        return 2;
    case '-':
    case '+':
        return 1;
    }
}

char popFromStack()
{
    char ch = stack[stkTop];
    stkTop--;
    return ch;
}

void pushToStack(char op)
{
    stkTop++;
    stack[stkTop] = op;
}

void infix_to_postfix()
{
    char ch;
    for (int i = 0; i < strlen(infix); i++)
    {
        char ch;
        ch = infix[i];
        if (isdigit(ch))
            moveToPostfix(ch);
        else
        {
            while (precedence(stack[stkTop]) >= precedence(infix[i]))
                moveToPostfix(popFromStack());
            pushToStack(infix[i]);
        }
    }
    while (stkTop != -1)
        moveToPostfix(popFromStack());
}

double compute(char symbol, double op1, double op2)
{
    switch (symbol)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    default:
        return 0;
    }
}

void evaluate_postfix() //function for evalulation of postfix exp
{
    double s[20], res, op1, op2;
    int top, i;
    char postfix[20], symbol;

    top = -1;
    for (i = 0; i < strlen(postfix); i++)
    {
        symbol = postfix[i];
        if (isdigit(symbol))
            s[++top] = symbol - '0';
        else
        {
            op2 = s[top--];
            op1 = s[top--];
            res = compute(symbol, op1, op2);
            s[++top] = res;
        }
    }
    res = s[top--];
    printf("\nThe result is:%f\n", res);
}

void displayString(int x, int y, char *string, int font, char color)
{
    int infixLen, i;
    switch (color)
    {
    case 'g':
        glColor3f(0.0, 1.0, 0.0);
        break;
    case 'b':
        glColor3f(0.7, 0.8, 1.0);
        break;
    case 'p':
        glColor3f(1.0, 0.0, 1.0);
        break;
    case 'o':
        glColor3f(1.0, 0.5, 0.0);
        break;

    default:
        break;
    }
    glRasterPos2f(x, y);
    infixLen = (int)strlen(string);
    for (i = 0; i < infixLen; i++)
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
    for (int i = 0; i < infixLen; i++)
    {
        char ch = infix[i];
        char temp[3];
        temp[0] = ch;
        temp[1] = ' ';
        temp[2] = '\0';
        strcat(e1, temp);
    }
    glClearColor(0.0, 0.3, 0.1, 1);
    displayString(220, 700, "INFIX TO POSTFIX EXPRESSION", 1, 'g');
    displayString(360, 670, "AND", 1, 'g');
    displayString(180, 640, "EVALUATION OF POSTFIX EXPRESSION", 1, 'g');
    displayString(500, 70, "Mini Project By : ", 2, 'g');
    displayString(500, 45, "Gopi Kishan P ( 1AY18CS040 )", 2, 'g');
    displayString(500, 20, "Kishore A H ( 1AY18CS052 )", 2, 'g');
    displayString(10, 520, e1, 2, 'g');
    displayString(200, 300, "**** For Instructions, Click 'Right Mouse' Button ****", 2, 'g');
    displayString(350, 400, "START", 1, 'g');
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
    displayString(60, 20, "STACK", 1, 'g');
    glBegin(GL_LINE_STRIP);
    glVertex2f(50, 350);
    glVertex2f(50, 50);
    glVertex2f(150, 50);
    glVertex2f(150, 350);
    glEnd();
    glEndList();
}

char *singleCharString(char *str, int i)
{
    temp[0] = str[i];
    temp[1] = '\0';
    return temp;
}

int i1x = 0;
int i1y = 0;
int i3x = 0;
int i3y = 0;
int i5x = 0;
int i5y = 0;
int i7x = 0;
int i7y = 0;

void animateIntoPost()
{
    if (i0.y > 500)
    {
        i0.y--;
        return;
    }
    if (!i1x && i1.x >= 91)
    {
        if (i1.x == 91)
            i1x = 1;
        i1.x--;
        return;
    }
    if (!i1y && i1.y >= 85)
    {
        if (i1.y == 85)
            i1y = 1;
        i1.y--;
        return;
    }
    if (i2.y > 500)
    {
        i2.y--;
        return;
    }
    if (i2.x > 280)
    {
        i2.x--;
        return;
    }
    if (!i3x && i3.x >= 91)
    {
        if (i3.x == 91)
            i3x = 1;
        i3.x--;
        return;
    }
    if (i1.y < 500)
    {
        i1.y++;
        return;
    }
    if (i1.x < 310)
    {
        i1.x++;
        return;
    }
    if (!i3y && i3.y >= 85)
    {
        if (i3.y == 85)
            i3y = 1;
        i3.y--;
        return;
    }
    if (i4.y > 500)
    {
        i4.y--;
        return;
    }
    if (i4.x > 340)
    {
        i4.x--;
        return;
    }
    if (!i5x && i5.x >= 91)
    {
        if (i5.x == 91)
            i5x = 1;
        i5.x--;
        return;
    }
    if (!i5y && i1.y >= 150)
    {
        if (i5.y == 150)
            i5y = 1;
        i5.y--;
        return;
    }
    if (i6.y > 500)
    {
        i6.y--;
        return;
    }
    if (i6.x > 370)
    {
        i6.x--;
        return;
    }
    if (!i7x && i7.x >= 91)
    {
        if (i7.x == 91)
            i7x = 1;
        i7.x--;
        return;
    }
    if (i5.y < 500)
    {
        i5.y++;
        return;
    }
    if (i5.x < 400)
    {
        i5.x++;
        return;
    }
    if (!i7y && i1.y >= 150)
    {
        if (i7.y == 150)
            i7y = 1;
        i7.y--;
        return;
    }
    if (i8.y > 500)
    {
        i8.y--;
        return;
    }
    if (i8.x > 430)
    {
        i8.x--;
        return;
    }
    if (i7.y < 500)
    {
        i7.y++;
        return;
    }
    if (i7.x < 460)
    {
        i7.x++;
        return;
    }
    if (i3.y < 500)
    {
        i3.y++;
        return;
    }
    if (i3.x <= 490)
    {
        if(i3.x == 490)
            infixAnimateComplete = 1;
        i3.x++;
        return;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (screen == 0)
    {
        myInit();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
        displayWelcomeScreen();
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 1)
    {
        myInit();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1, 'g');
        displayString(50, 650, "Infix Expression : ", 1, 'g');
        glClearColor(0.0, 0.1, 0.2, 1);
        for (int i = 0; i < infixLen; i++)
        {
            displayString(250 + i * 30, 650, singleCharString(infix, i), 1, 'g');
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 2)
    {
        displayString(200, 750, "INFIX TO POSTFIX EXPRESSION", 1, 'g');
        if(infixAnimateComplete)
            displayString(35, 500, "Postfix Expression : ", 1, 'g');
        displayString(i0.x, i0.y, singleCharString(infix, 0), 1, 'b');
        displayString(i1.x, i1.y, singleCharString(infix, 1), 1, 'b');
        displayString(i2.x, i2.y, singleCharString(infix, 2), 1, 'b');
        displayString(i3.x, i3.y, singleCharString(infix, 3), 1, 'b');
        displayString(i4.x, i4.y, singleCharString(infix, 4), 1, 'b');
        displayString(i5.x, i5.y, singleCharString(infix, 5), 1, 'b');
        displayString(i6.x, i6.y, singleCharString(infix, 6), 1, 'b');
        displayString(i7.x, i7.y, singleCharString(infix, 7), 1, 'b');
        displayString(i8.x, i8.y, singleCharString(infix, 8), 1, 'b');
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
        animateIntoPost();
    }
    else if (screen == 3)
    {
        myInit();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1, 'o');
        glClearColor(0.2, 0.1, 0, 0);
        for (int i = 0; i < postfixLen; i++)
        {
            char ch = postfix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(250 + i * 30, 650, temp, 1, 'o');
        }
        glCallList(stackDisplayList);
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 4)
    {
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1, 'o');
        glPushMatrix();
        glTranslatef(no, 0.0, 0.0);
        for (int i = 0; i < postfixLen; i++)
        {
            char ch = postfix[i];
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            displayString(250 + i * 30, 650, temp, 1, 'o');
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
        glClearColor(0.0, 0.0, 0.8, 1);
        glColor3f(1.0, 1.0, 1.0);
        // To Display THANK YOU
        // T
        drawCustomCube(-0.87, 0.5, 0, 0.05, 0.3, 0.05, 0);
        drawCustomCube(-0.87, 0.64, 0, 0.3, 0.05, 0.05, 0);
        // H
        drawCustomCube(-0.49, 0.5, 0, 0.25, 0.05, 0.05, 0);
        drawCustomCube(-0.6, 0.5, 0, 0.05, 0.3, 0.05, 0);
        drawCustomCube(-0.35, 0.5, 0, 0.05, 0.3, 0.05, 0);
        // A
        drawCustomCube(-0.055, 0.45, 0, 0.15, 0.05, 0.05, 0);
        drawCustomCube(0.22, 0.45, 0, 0.05, 0.35, 0.05, 25);
        drawCustomCube(-0.35, 0.395, 0, 0.05, 0.35, 0.05, -25);
        // N
        drawCustomCube(0.56, 0.19, 0, 0.05, 0.35, 0.05, 40);
        drawCustomCube(0.20, 0.5, 0, 0.05, 0.3, 0.05, 0);
        drawCustomCube(0.425, 0.5, 0, 0.05, 0.3, 0.05, 0);
        // K
        drawCustomCube(0.79, -0.19, 0, 0.05, 0.20, 0.05, 45);
        drawCustomCube(0.09, 0.88, 0, 0.05, 0.20, 0.05, -45);
        drawCustomCube(0.6, 0.5, 0, 0.05, 0.3, 0.05, 0);
        // Y
        drawCustomCube(-0.3, -0.3, 0, 0.05, 0.20, 0.05, -45);
        drawCustomCube(-0.4, 0.4, 0, 0.05, 0.20, 0.05, 45);
        drawCustomCube(-0.495, -0.15, 0, 0.05, 0.2, 0.05, 0);
        // O
        drawCustomCube(-0.075, -0.225, 0, 0.27, 0.05, 0.05, 0);
        drawCustomCube(-0.075, 0.025, 0, 0.27, 0.05, 0.05, 0);
        drawCustomCube(-0.2, -0.1, 0, 0.05, 0.3, 0.05, 0);
        drawCustomCube(0.05, -0.1, 0, 0.05, 0.3, 0.05, 0);
        // U
        drawCustomCube(0.32, -0.225, 0, 0.25, 0.05, 0.05, 0);
        drawCustomCube(0.2, -0.1, 0, 0.05, 0.3, 0.05, 0);
        drawCustomCube(0.45, -0.1, 0, 0.05, 0.3, 0.05, 0);
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
    if (key == 'n' || key == 'N' || key == ' ')
        screen++;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Infix Expression : %s\n", infix);
    infix_to_postfix();
    printf("Postfix Expression : %s\n", postfix);
    glutInit(&argc, argv);
    infixLen = strlen(infix);
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