#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

static int menu_id;
static int sub_menu;
static int submenu2;
static int submenu_id;
static int window;
static int value = 0;

int play = 1;

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
int postfixAnimateComplete = 0;
float result;

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

struct Point p0 = {250, 650};
struct Point p1 = {250 + 1 * 30, 650};
struct Point p2 = {250 + 2 * 30, 650};
struct Point p3 = {250 + 3 * 30, 650};
struct Point p4 = {250 + 4 * 30, 650};
struct Point p5 = {250 + 5 * 30, 650};
struct Point p6 = {250 + 6 * 30, 650};
struct Point p7 = {250 + 7 * 30, 650};
struct Point p8 = {250 + 8 * 30, 650};
struct Point p9 = {340, 500};
struct Point p10 = {340, 500};
struct Point p11 = {340, 500};

int dpSix = 1;
int dpEquals = 0;
int dpPlus = 1;
int dpThree1 = 1;
int dpThree2 = 1;
int dpNine = 0;
int dpFour = 1;
int dpPTwo = 1;
int dpTwo = 0;
int dpDiv = 1;
int dpSixR = 0;
int dpStar = 1;
int dpMinus = 1;
int dpThreeR = 0;

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
    glutAddMenuEntry("Press 'P' to to Pause or Play Animation", 20);
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

void postfix_to_result() //function for evalulation of postfix exp
{
    double s[20], res, op1, op2;
    int top, try = 50;
    char symbol;

    top = -1;
    for (int pp = 0; pp < postfixLen; pp++)
    {
        symbol = postfix[pp];

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
    result = res;
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
        glColor3f(1.0, 1.0, 0.0);
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

void getSpacedExpression(char *src, char *exp, int expLen)
{
    for (int i = 0; i < expLen; i++)
    {
        char temp[3];
        temp[0] = exp[i];
        temp[1] = ' ';
        temp[2] = '\0';
        strcat(src, temp);
    }
}

void displayWelcomeScreen()
{
    char in1[50] = "Infix Expression :  ";
    char post1[50] = "Postfix Expression :  ";
    char res1[20] = "Result = ";
    char resStr[5];
    gcvt(result, 3, resStr);
    strcat(res1, resStr);
    getSpacedExpression(in1, infix, infixLen);
    getSpacedExpression(post1, postfix, infixLen);
    glClearColor(0.0, 0.3, 0.0, 1);
    displayString(220, 700, "INFIX TO POSTFIX EXPRESSION", 1, 'g');
    displayString(360, 670, "AND", 1, 'g');
    displayString(180, 640, "EVALUATION OF POSTFIX EXPRESSION", 1, 'g');
    displayString(500, 70, "Mini Project By : ", 2, 'g');
    displayString(500, 45, "Gopi Kishan P ( 1AY18CS040 )", 2, 'g');
    displayString(500, 20, "Kishore A H ( 1AY18CS052 )", 2, 'g');
    displayString(10, 520, in1, 2, 'g');
    displayString(10, 490, post1, 2, 'g');
    displayString(10, 460, res1, 2, 'g');
    displayString(200, 250, "**** For Instructions, Click 'Right Mouse' Button ****", 2, 'g');
    displayString(275, 350, "START VISUALIZATION", 1, 'g');
}

void myInit()
{
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glNewList(stackDisplayList, GL_COMPILE); // Display List
    glColor3f(1.0, 0.0, 1.0);
    displayString(60, 20, "STACK", 1, 'p');
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
int l1 = 0;
int l2 = 0;
int l3 = 0;

void displayStackLineIn()
{
    if (i1.y <= 100 || i3.y <= 100) // Line 1
    {
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(50, 120);
        glVertex2f(150, 120);
        glEnd();
    }
    if (i5.y <= 170 || i7.y <= 170) // Line 2
    {
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(50, 200);
        glVertex2f(150, 200);
        glEnd();
    }
}

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
    // if(l1==0)
    //     displayStackLine(1, 120);
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
        // if(l1==0) l1++;
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
    // if(l1==1)
    //     displayStackLine(1, 120);
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
        if (l1 == 1)
            l1++;
        i3.y++;
        return;
    }
    if (i3.x <= 490)
    {
        if (i3.x == 490)
            infixAnimateComplete = 1;
        i3.x++;
        return;
    }
}

int p0x = 0;
int p0y = 0;
int p1x = 0;
int p1y = 0;
int p3x = 0;
int p3y = 0;
int p4x = 0;
int p4y = 0;
int p6x = 0;
int p6y = 0;
int p9x = 0;
int p9y = 0;
int p10x = 0;
int p10y = 0;
int p11x = 0;
int p11y = 0;

void displayStackLinePost()
{
    if (p0.y <= 100 || p9.y <= 100) // Line 1
    {
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(50, 120);
        glVertex2f(150, 120);
        glEnd();
    }
    if (p1.y <= 170 || p3.y <= 170 || p10.y <= 170 || p11.y <= 170) // Line 2
    {
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(50, 190);
        glVertex2f(150, 190);
        glEnd();
    }
    if (p4.y <= 240 || p6.y <= 240) // Line 3
    {
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(50, 260);
        glVertex2f(150, 260);
        glEnd();
    }
}

void animatePosttoRes()
{
    if (!p0x && p0.x >= 91)
    {
        if (p0.x == 91)
            p0x = 1;
        p0.x--;
        return;
    }
    if (!p0y && p0.y >= 85)
    {
        if (p0.y == 85)
            p0y = 1;
        p0.y--;
        return;
    }
    if (!p1x && p1.x >= 91)
    {
        if (p1.x == 91)
            p1x = 1;
        p1.x--;
        return;
    }
    if (!p1y && p1.y >= 150)
    {
        if (p1.y == 150)
            p1y = 1;
        p1.y--;
        return;
    }
    if (p2.y > 500)
    {
        p2.y--;
        return;
    }
    if (p2.x > 250)
    {
        p2.x--;
        return;
    }
    if (p1.y < 500)
    {
        p1.y++;
        return;
    }
    if (p1.x < 280)
    {
        p1.x++;
        return;
    }
    if (p0.y < 500)
    {
        p0.y++;
        return;
    }
    if (p0.x <= 220)
    {
        if (p0.x >= 219)
        {
            dpEquals = 1;
        }
        p0.x++;
        return;
    }
    dpNine = 1;
    dpSix = 0;
    dpPlus = 0;
    dpThree1 = 0;
    dpEquals = 0;
    if (!p9x && p9.x >= 91)
    {
        if (p9.x == 91)
            p9x = 1;
        p9.x--;
        return;
    }
    if (!p9y && p0.y >= 85)
    {
        if (p9.y == 85)
            p9y = 1;
        p9.y--;
        return;
    }
    if (!p3x && p3.x >= 91)
    {
        if (p3.x == 91)
            p3x = 1;
        p3.x--;
        return;
    }
    if (!p3y && p3.y >= 150)
    {
        if (p3.y == 150)
            p3y = 1;
        p3.y--;
        return;
    }
    if (!p4x && p4.x >= 91)
    {
        if (p4.x == 91)
            p4x = 1;
        p4.x--;
        return;
    }
    if (!p4y && p4.y >= 215)
    {
        if (p4.y == 215)
            p4y = 1;
        p4.y--;
        return;
    }
    if (p5.y > 500)
    {
        p5.y--;
        return;
    }
    if (p5.x > 250)
    {
        p5.x--;
        return;
    }
    if (p4.y < 500)
    {
        p4.y++;
        return;
    }
    if (p4.x < 280)
    {
        p4.x++;
        return;
    }
    if (p3.y < 500)
    {
        p3.y++;
        return;
    }
    if (p3.x <= 214)
    {
        if (p3.x >= 213)
        {
            dpEquals = 1;
        }
        p3.x++;
        return;
    }
    dpPTwo = 0;
    dpTwo = 1;
    dpFour = 0;
    dpDiv = 0;
    if (!p10x && p10.x >= 91)
    {
        if (p10.x == 91)
            p10x = 1;
        p10.x--;
        return;
    }
    if (!p10y && p10.y >= 150)
    {
        if (p10.y == 150)
            p10y = 1;
        p10.y--;
        return;
    }
    if (!p6x && p6.x >= 91)
    {
        if (p6.x == 91)
            p6x = 1;
        p6.x--;
        return;
    }
    if (!p6y && p6.y >= 215)
    {
        if (p6.y == 215)
            p6y = 1;
        p6.y--;
        return;
    }
    if (p7.y > 500)
    {
        p7.y--;
        return;
    }
    if (p7.x > 250)
    {
        p7.x--;
        return;
    }
    if (p6.y < 500)
    {
        p6.y++;
        return;
    }
    if (p6.x < 280)
    {
        p6.x++;
        return;
    }
    if (p10.y < 500)
    {
        p10.y++;
        return;
    }
    if (p10.x <= 220)
    {
        if (p10.x >= 219)
        {
            dpEquals = 1;
        }
        p10.x++;
        return;
    }

    dpThree2 = 0;
    dpTwo = 0;
    dpStar = 0;
    dpSixR = 1;
    if (!p11x && p11.x >= 91)
    {
        if (p11.x == 91)
            p11x = 1;
        p11.x--;
        return;
    }
    if (!p11y && p11.y >= 150)
    {
        if (p11.y == 150)
            p11y = 1;
        p11.y--;
        return;
    }
    if (p8.y > 500)
    {
        p8.y--;
        return;
    }
    if (p8.x > 250)
    {
        p8.x--;
        return;
    }
    if (p11.y < 500)
    {
        p11.y++;
        return;
    }
    if (p11.x < 280)
    {
        p11.x++;
        return;
    }
    // if (p11.y < 500)
    // {
    //     p11.y++;
    //     return;
    // }
    // if (p11.x <= 214)
    // {
    //     p11.x++;
    //     return;
    // }
    // if (p9.y < 500)
    // {
    //     p9.y++;
    //     return;
    // }
    // if (p9.x < 280)
    // {
    //     p9.x++;
    //     return;
    // }
    if (p9.y < 500)
    {
        p9.y++;
        return;
    }
    if (p9.x <= 214)
    {
        if (p9.x >= 213)
        {
            dpEquals = 1;
        }
        p9.x++;
        return;
    }
    dpThreeR = 1;
    dpSixR = 0;
    dpMinus = 0;
    dpNine = 0;
    postfixAnimateComplete = 1;
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
        if (infixAnimateComplete)
            displayString(35, 500, "Postfix Expression : ", 1, 'g');
        displayString(i0.x, i0.y, singleCharString(infix, 0), 1, 'g');
        displayString(i1.x, i1.y, singleCharString(infix, 1), 1, 'g');
        displayString(i2.x, i2.y, singleCharString(infix, 2), 1, 'g');
        displayString(i3.x, i3.y, singleCharString(infix, 3), 1, 'g');
        displayString(i4.x, i4.y, singleCharString(infix, 4), 1, 'g');
        displayString(i5.x, i5.y, singleCharString(infix, 5), 1, 'g');
        displayString(i6.x, i6.y, singleCharString(infix, 6), 1, 'g');
        displayString(i7.x, i7.y, singleCharString(infix, 7), 1, 'g');
        displayString(i8.x, i8.y, singleCharString(infix, 8), 1, 'g');
        glCallList(stackDisplayList);
        displayStackLineIn();
        if (play)
            animateIntoPost();
        glutPostRedisplay();
        glutSwapBuffers();
    }
    else if (screen == 3)
    {
        myInit();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
        displayString(150, 750, "EVALUATION OF POSTFIX EXPRESSION", 1, 'o');
        displayString(40, 650, "Postfix Expression : ", 1, 'o');
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
        if (postfixAnimateComplete)
            displayString(200, 500, "Result   = ", 1, 'o');
        if (dpSix)
            displayString(p0.x, p0.y, singleCharString(postfix, 0), 1, 'o');
        if (dpThree1)
            displayString(p1.x, p1.y, singleCharString(postfix, 1), 1, 'o');
        if (dpPlus)
            displayString(p2.x, p2.y, singleCharString(postfix, 2), 1, 'o');
        if (dpFour)
            displayString(p3.x, p3.y, singleCharString(postfix, 3), 1, 'o');
        if (dpPTwo)
            displayString(p4.x, p4.y, singleCharString(postfix, 4), 1, 'o');
        if (dpDiv)
            displayString(p5.x, p5.y, singleCharString(postfix, 5), 1, 'o');
        if (dpThree2)
            displayString(p6.x, p6.y, singleCharString(postfix, 6), 1, 'o');
        if (dpStar)
            displayString(p7.x, p7.y, singleCharString(postfix, 7), 1, 'o');
        if (dpMinus)
            displayString(p8.x, p8.y, singleCharString(postfix, 8), 1, 'o');
        if (dpEquals)
        {
            displayString(310, 500, "=", 1, 'o');
            sleep(1);
        }
        if (dpNine)
            displayString(p9.x, p9.y, "9", 1, 'o');
        if (dpTwo)
            displayString(p10.x, p10.y, "2", 1, 'o');
        if (dpThreeR)
            displayString(310, p10.y, "3", 1, 'o');
        if (dpSixR)
            displayString(p11.x, p11.y, "6", 1, 'o');
        glCallList(stackDisplayList);
        displayStackLinePost();
        if (play)
            animatePosttoRes();
        glutPostRedisplay();
        glutSwapBuffers();
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

    if (key == 'p' || key == 'P')
        play = (play == 0) ? 1 : 0;
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
    postfix_to_result();
    printf("Result = %.2f\n", result);
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