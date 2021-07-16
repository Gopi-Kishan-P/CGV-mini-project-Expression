#include<stdio.h>
#include<GL/glut.h>

char in[50], post[50];
int width = 900, height = 800;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv){
    printf("\nEnter an Expression containing operators + - * / ^ ( ) and digits 0-9\n");
    scanf("%s", in);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("Infix and Postfix Expression");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}