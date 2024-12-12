#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

// for splitting window
bool animationStarted = false;

//-----------------------------------------------------------------------
// variables declaration

int i,j,k;

// Big fish initial positions
GLfloat a[2] = {0.5f, 0.2f};        // X-axis
GLfloat b[2] = {0.15f, 0.28f};        // Y-axis

// group fish initial positions
GLfloat initial_x[9] = { 0.23f, 0.6f, 0.9f, 0.1f, 0.5f, 0.7f, 0.4f, 0.75f, 0.04f };
GLfloat initial_y[9] = { -0.2f, -0.2f, -0.2f,-0.12f, -0.125f, -0.145f, -0.245f, -0.245f, -0.245f};

// for group fish movement
GLfloat translateX[9] = { 0.008f, 0.008f, 0.008f, 0.008f, 0.008f, 0.008f, 0.008f, 0.008f, 0.008f};
GLfloat translateY;

// for sine wave of group fish
GLfloat amplitude = 0.1f;
GLfloat frequency = 2.5f;
GLfloat animateTime = 0.0f;

// Green Fish
GLfloat c[3] = {0.3f,0.6f,0.9f};
GLfloat d[3] = {-0.3f,-0.3f,-0.3f};

// Shark and bubble
float xb = 100, yb = 0, r = 0.5, x0 = 0, xo = 0, angle = 0.0, pi = 3.142;
float y11 = 0, y21 = 0, y31 = 0, y41 = 0, y51 = 0, y61 = 0, y71 = 0, y81 = 0, y91 = 0;
float y10 = 0, y12 = 0, y13 = 0, y14 = 0;
float s = 400, ss = 140;

float zones[8] = {-1.75,-1.25,-0.75,-0.25,0.25,0.75,1.25,1.75};

// Control fish
float winWidth = 750;
float winHeight = 500;

float destX=0.0f;
float destY=0.0f;

float animSpeed=0.02f;

float fishx = -2.0f;
float fishy = 0.0f;

bool flip = false;
// -------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// functions preparations

void movefish()
{
    //body
    glColor3f(0.0f,1.0f,0.71f);
    glBegin(GL_POLYGON);
    glVertex2f(fishx,fishy);
    glVertex2f(fishx+0.08f,fishy+0.07f);
    glVertex2f(fishx+0.2f,fishy+0.02f);
    glVertex2f(fishx+0.2f,fishy+0.02f);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.2f,fishy-0.02f);
    glVertex2f(fishx+0.2f,fishy-0.02f);
    glVertex2f(fishx+0.08f,fishy-0.07f);
    glVertex2f(fishx,fishy);
    glEnd();

    //fin
    glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.2f,fishy+0.02f);
    glColor3f(0.19f,0.77f,0.63f);
    glVertex2f(fishx+0.3f,fishy+0.07f);
    glVertex2f(fishx+0.25f,fishy);
    glVertex2f(fishx+0.3,fishy-0.07f);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.2f,fishy-0.02f);
    glEnd();

    //fin hands
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.08f,fishy+0.07f);
    glColor3f(0.19f,0.77f,0.63f);
    glVertex2f(fishx+0.16f,fishy+0.1f);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.14f,fishy+0.03f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,1.0f,0.71f);
    glVertex2f(fishx+0.085f,fishy-0.05f);
    glColor3f(0.19f,0.77f,0.63f);
    glVertex2f(fishx+0.16f,fishy-0.1f);
    glVertex2f(fishx+0.14f,fishy-0.03f);
    glEnd();

    //eye
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(3.5);
    glBegin(GL_POINTS);
    glVertex2f(fishx+0.056f,fishy+0.022f);
    glEnd();
}

void coontailLeaf(float rootX, float rootY)
{
    glLineWidth(2.5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(rootX,rootY);
    glVertex2f(rootX+0.05,rootY+0.015);
    glVertex2f(rootX+0.075,rootY+0.05);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(rootX,rootY);
    glVertex2f(rootX+0.02,rootY+0.015);
    glVertex2f(rootX+0.02,rootY+0.04);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(rootX,rootY);
    glVertex2f(rootX-0.02,rootY+0.015);
    glVertex2f(rootX-0.02,rootY+0.04);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(rootX,rootY);
    glVertex2f(rootX-0.05,rootY+0.015);
    glVertex2f(rootX-0.075,rootY+0.05);
    glEnd();
}

void coontailLeafNodesR(float root,float floor=-1.0)
{
    float carryR, carryF;
    carryR = root;
    carryF = floor;
    for(int i=0; i<4; i++)
    {
        if(i%2==0)
        {
            carryR+=0.1;
        }
        else
        {
            carryR+=0.05;
        }
        carryF+=(0.05)*(i+1);
        coontailLeaf(carryR,carryF);
    }
}

void coontailLeafNodesL(float root, float floor)
{
    float carryR, carryF;
    carryR = root;
    carryF = floor;
    for(int i=0; i<3; i++)
    {
        if(i%2==0)
        {
            carryR-=0.05;
        }
        else
        {
            carryR-=0.1;
        }
        carryF+=0.2;
        coontailLeaf(carryR,carryF);
    }
}

void coontailStemLeft(float root, float floor)
{
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.75,1.0,0.2);
    glVertex2f(root,floor);
    float carryR, carryF;
    carryR = root;
    carryF = floor;
    for(int i=0; i<3; i++)
    {
        if(i%2==0)
        {
            carryR-=0.05;
        }
        else
        {
            carryR-=0.1;
        }
        carryF+=0.2;
        glVertex2f(carryR,carryF);
    }
    glEnd();
}

void coontailStem(float root, float floor=-1.0)
{
    float leftX, leftY;
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.75,1.0,0.2);
    glVertex2f(root,floor);
    float carryR, carryF;
    carryR = root;
    carryF = floor;
    for(int i=0; i<4; i++)
    {
        if(i%2==0)
        {
            carryR+=0.1;
        }
        else
        {
            carryR+=0.05;
        }
        carryF+=(0.05)*(i+1);
        glVertex2f(carryR,carryF);
        if(i==1)
        {
            leftX = carryR;
            leftY = carryF;
        }
    }
    glEnd();
    coontailStemLeft(leftX,leftY);
    coontailLeafNodesL(leftX,leftY);
}

void background()
{
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.47,0.75); //darkest
    glVertex2f(2,-1);
    glColor3f(0.09,0.56,0.84); //darker
    glVertex2f(2,-0.5);
    glColor3f(0.18,0.59,0.93); //dark
    glVertex2f(2,0);
    glColor3f(0.22,0.69,0.97); //not that dark
    glVertex2f(2,0.5);
    glVertex2f(2,1);
    glVertex2f(-2,1);
    glVertex2f(-2,0.5);
    glColor3f(0.18,0.59,0.93);
    glVertex2f(-2,0);
    glColor3f(0.09,0.56,0.84);
    glVertex2f(-2,-0.5);
    glColor3f(0.0,0.47,0.75);
    glVertex2f(-2,-1);
    glEnd();
}

void smallFish(GLfloat x, GLfloat y)
{
    // Body
    glColor3f(0.9, 0.1, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x+0.1f, y+0.0f);
    glVertex2f(x+0.3f, y+0.04f);
    glVertex2f(x+0.39f, y+0.0f);
    glVertex2f(x+0.3f, y-0.04f);
    glEnd();

    // Tail
    glColor3f(0.9, 0.1, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x+0.15f, y+0.0f);

    glColor3ub( 245 %1, 245 %1000, 245 %1000 );
    glVertex2f(x+0.05f, y-0.045f);
    glVertex2f(x+0.08f, y+0.0f);
    glVertex2f(x+0.05f, y+0.045f);
    glEnd();

    //fin
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x+0.3, y+0.01);
    glVertex2f(x+0.3, y-0.005);

    glColor3ub( 245 %1, 245 %1000, 245 %1000 );
    glVertex2f(x+0.25,  y-0.024);
    glVertex2f(x+0.265, y+0.01);
    glVertex2f(x+0.25,  y+0.035);
    glEnd();

    // Eye
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);

    glBegin(GL_POINTS);
    glVertex2f(x+0.353f, y+0.01f);
    glEnd();
}

void goldFish()
{
    glPushMatrix();
    glScalef(1.0/2.8, 1.0/2.8, 1.0);

    // body
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(a[j]+0.0f,  b[j]+0.0f);
    glVertex2f(a[j]+0.55f, b[j]+0.21f);
    glVertex2f(a[j]+0.8f,  b[j]+0.0f);
    glVertex2f(a[j]+0.55f, b[j]-0.21f);
    glEnd();

    // Tail
    glBegin(GL_POLYGON);
    glVertex2f(a[j]+0.1f,  b[j]+0.0f);
    glColor3ub(rand()%500, rand()%500,0);

    glVertex2f(a[j]-0.3f,  b[j]-0.19f);
    glVertex2f(a[j]-0.2f, b[j]+0.0f);
    glVertex2f(a[j]-0.3f,  b[j]+0.19f);
    glEnd();

    // fin
    glBegin(GL_TRIANGLES);
    glColor3ub(rand()%500, rand()%500,0);
    glVertex2f(a[j]+0.55f,  b[j]+0.185f);

    glColor3f(a[j]+1.0, 0.0, 0.0);
    glVertex2f(a[j]+0.43f,  b[j]+0.1f);
    glVertex2f(a[j]+0.32f,  b[j]+0.4f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(rand()%500, rand()%500,0);
    glVertex2f(a[j]+0.55f,  b[j]-0.185f);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(a[j]+0.43f,  b[j]-0.1f);
    glVertex2f(a[j]+0.32f,  b[j]-0.4f);
    glEnd();

    // eye
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.5);
    glBegin(GL_POINTS);
    glVertex2f(a[j]+0.65f,  b[j]+0.05f);
    glEnd();

    glPopMatrix();
}

void Shark()
{
    // For Shark Body
    glBegin(GL_TRIANGLE_FAN);
    for (angle = 0; angle < 320; angle += 2)
    {
        glColor3ub(115, 116, 117);
        yb = (sin(angle * pi / 319) * 30);
        xb = angle;
        glVertex2f((xb + 280 + s - 1000) / 300, (yb + 285 + ss - 200) / 300);
    }

    glColor3ub(200, 200, 200);
    glVertex2f((xb + 280 + s - 1000) / 300, (yb + 265 + ss - 200) / 300);
    for (angle = 298; angle > 35; angle -= 2)
    {
        xb = angle;
        yb = -(sin(angle * pi / 319) * 20);
        glVertex2f((xb + 280 + s - 1000) / 300, (yb + 265 + ss - 200) / 300);
    }

    glVertex2f((300 + s - 1000) / 300, (265 + ss - 200) / 300);
    glEnd();

    glColor3ub(138, 3, 3);
    glBegin(GL_POLYGON);
    glVertex2f((302 + s - 1000) / 300, (263 + ss - 200) / 300);
    glVertex2f((330 + s - 1000) / 300, (276 + ss - 200) / 300);
    glVertex2f((297 + s - 1000) / 300, (268 + ss - 200) / 300);
    glEnd();

    // For Shark Tail
    glColor3ub(115, 116, 117);
    glBegin(GL_POLYGON);
    glVertex2f((598 + s - 1000) / 300, (285.6 + ss - 200) / 300);
    glVertex2f((640 + s - 1000) / 300, (330 + ss - 200) / 300);
    glColor3ub(22 + 190, 22 + 190, 22 + 190);
    glVertex2f((628 + s - 1000) / 300, (275 + ss - 200) / 300);
    glVertex2f((640 + s - 1000) / 300, (220 + ss - 200) / 300);
    glVertex2f((598 + s - 1000) / 300, (265 + ss - 200) / 300);
    glEnd();

    glColor3ub(100, 106, 107);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f((410 + s - 1000) / 300, (313 + ss - 200) / 300);
    glColor3ub(150, 150, 150);
    glVertex2f((460 + s - 1000) / 300, (360 + ss - 200) / 300);
    glVertex2f((475 + s - 1000) / 300, (313 + ss - 200) / 300);
    glEnd();

    glColor3ub(115, 116, 117);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f((420 + s - 1000) / 300, (260 + ss - 200) / 300);
    glVertex2f((450 + s - 1000) / 300, (210 + ss - 200) / 300);
    glColor3ub(22 + 190, 22 + 190, 22 + 190);
    glVertex2f((460 + s - 1000) / 300, (260 + ss - 200) / 300);
    glEnd();

    glColor3ub(115, 116, 117);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f((555 + s - 1000) / 300, (297 + ss - 200) / 300);
    glVertex2f((580 + s - 1000) / 300, (305 + ss - 200) / 300);
    glVertex2f((580 + s - 1000) / 300, (290 + ss - 200) / 300);
    glEnd();

    glColor3ub(115, 116, 117);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f((555 + s - 1000) / 300, (257 + ss - 200) / 300);
    glVertex2f((580 + s - 1000) / 300, (247 + ss - 200) / 300);
    glColor3ub(22 + 190, 22 + 190, 22 + 190);
    glVertex2f((580 + s - 1000) / 300, (261 + ss - 200) / 300);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (angle = 0; angle < 360.0; angle += .1)
    {
        glColor3ub(0, 0, 0);
        yb = (sin(angle * pi / 180) * 5);
        xb = (cos(angle * pi / 180) * 5);
        glVertex2f((xb + 332 + s - 1000) / 300, (yb + 287 + ss - 200) / 300);
    }
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f((331.8 + s - 1000) / 300, (287 + ss - 200) / 300);
    glEnd();
}

void drawFish2()
{

    //Body
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(c[k]-0.7f, d[k]-0.05f);
    glVertex2f(c[k]-0.75f, d[k]-0.1f);
    glVertex2f(c[k]-0.85f, d[k]-0.05f);
    glVertex2f(c[k]-0.75f, d[k]-0.0f);
    glEnd();

    //Tail
    glBegin(GL_TRIANGLES);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(c[k]-0.83f, d[k]-0.05f);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(c[k]-0.9f, d[k]-0.09f);
    glVertex2f(c[k]-0.9f, d[k]-0.01f);
    glEnd();

    //upperfin
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(c[k]-0.75f, d[k]-0.095f);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(c[k]-0.79f, d[k]-0.125f);
    glVertex2f(c[k]-0.77f, d[k]-0.07f);
    glEnd();

    //lowerfin
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(c[k]-0.75f, d[k]-0.007f);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(c[k]-0.795f, d[k]-0.035f);
    glVertex2f(c[k]-0.77f, d[k]-0.02f);
    glEnd();

    //eye
    glColor3f(0.0,0.0,0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(c[k]-0.73f, d[k]-0.035f);
    glEnd();
}

void circleFunc(float yc, int d, int x1, int y1, int isLeft)
{
    for (angle = 0; angle < 360.0; angle += .1)
    {
        yb = yc + (sin(angle * pi / 180) * d);
        xb = (cos(angle * pi / 180) * d);
        if (isLeft == 0)
        {
            glVertex2f((xb - x1 - 300) / 250, (yb - y1 - 130) / 250);
        }
        else
        {
            glVertex2f((xb - x1 + 380) / 300, (yb - y1 + 100) / 300);
        }
    }
}

float checkBubPos(float y, float c)
{
    if (y < 200)
    {
        return (y + (c / 10));
    }
    else
    {
        return c;
    }
}

void circle(int x, int isLeft)
{
    // to draw circles
    glBegin(GL_POINTS);
    circleFunc(y21, 15, x + 10, 30, isLeft);
    circleFunc(y31, 5, x, 60, isLeft);
    circleFunc(y41, 7, x + 10, 90, isLeft);
    circleFunc(y51, 12, x, 120, isLeft);
    circleFunc(y61, 15, x + 10, 150, isLeft);
    circleFunc(y71, 5, x, 180, isLeft);
    circleFunc(y81, 3, x + 10, 210, isLeft);
    circleFunc(y81, 15, x, 240, isLeft);
    circleFunc(y91, 12, x + 10, 270, isLeft);
    circleFunc(y10, 10, x, 300, isLeft);
    circleFunc(y12, 16, x + 10, 330, isLeft);
    circleFunc(y13, 15, x, 360, isLeft);
    circleFunc(y14, 10, x + 10, 400, isLeft);
    glEnd();

    y11 = checkBubPos(y11, 2.0);
    y21 = checkBubPos(y21, 3.0);
    y31 = checkBubPos(y31, 4.5);
    y41 = checkBubPos(y41, 7.0);
    y51 = checkBubPos(y51, 6.5);
    y61 = checkBubPos(y61, 18.0);
    y71 = checkBubPos(y71, 17.5);
    y81 = checkBubPos(y81, 8.0);
    y91 = checkBubPos(y91, 7.5);
    y10 = checkBubPos(y10, 10.0);
    y12 = checkBubPos(y12, 11.0);
    y14 = checkBubPos(y14, 8.0);
    y12 = checkBubPos(y12, 9.0);
    y13 = checkBubPos(y13, 1.0);
    glutPostRedisplay();
}

float mousex,mousey;

void animate(int value)
{
    float dx = destX - fishx;
    float dy = destY - fishy;

    float distance = sqrt(dx*dx + dy*dy);
    if(distance>0.01f)
    {
        dx /= distance;
        dy /= distance;

        fishx += dx * animSpeed;
        fishy += dy * animSpeed;

        glutPostRedisplay();

        glutTimerFunc(16,animate,0);
    }
}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
    {
        destX = (float)x / winWidth * 2.0f - 1.0f;
        destY = 1.0f - (float)y / winHeight * 2.0f;
        if(destX<fishx)
        {
            flip = false;
        }
        else flip = true;
        glutTimerFunc(16,animate,0);
    }
}

void idle()
{
    animateTime += 0.005f;
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    background();

    for(int i=0; i<sizeof(zones)/sizeof(int); i++)
    {
        if(i%2!=0)
        {
            coontailStem(zones[i],-1.1);
            coontailLeafNodesR(zones[i],-1.1);
        }
        else
        {
            coontailStem(zones[i]);
            coontailLeafNodesR(zones[i]);
        }
    }

    glMatrixMode(GL_MODELVIEW);              // To operate on Model-View matrix
    glLoadIdentity();                        // Reset the model-view matrix

    //fish that moves
    glPushMatrix();
    if(flip==true)
    {
        glTranslatef(fishx,fishy,0.0f);
        glScalef(-1.0f,1.0f,1.0f);
        glTranslatef(-fishx,-fishy,0.0f);
    }
    movefish();
    glPopMatrix();

    // Gold fish movement
    for (j = 0; j < 2; j++)
    {
        glPushMatrix();
        glTranslatef(a[j] - 1.0, b[j], 0.0f);
        goldFish();
        glPopMatrix();
        a[j] += translateX[j];

        if (a[j] > 2.0f)
        {
            a[j] = -1.0f;
        }
    }

    // green fish movement
    for (k = 0; k < 3; k++)
    {
        glPushMatrix();
        glTranslatef(c[k], d[k], 0.0f);
        drawFish2();
        glPopMatrix(); // Restore the model-view matrix
        c[k] += translateX[k];

        if (c[k] > 2.0f)
        {
            c[k] = -1.0f;
        }
    }

    // Group of small fish move in sine wave
    for ( i = 0; i < 9; ++i)
    {
        glPushMatrix();

        GLfloat newY = initial_y[i] + sin(frequency * initial_x[i] + animateTime) * amplitude;
        smallFish(initial_x[i] - 1.0, newY);
        glPopMatrix();
        initial_x[i] += translateX[i];

        if (initial_x[i] > 3.9f)
        {
            initial_x[i] = -1.0f;
        }
        else if (initial_x[i] < -1.0f)
        {
            initial_x[i] = 1.0f;
        }
    }

    // Bubble animation
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(0.3);
    circle(0, 0);
    circle(0, 1);

    // shark animation
    glPushMatrix();
    Shark();
    glPopMatrix();

    s -= 0.5f;
    if (s <= -70)
    {
        s = 1100;
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height)
    {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

//----------------------------------------------------------------------------------
// first part (text display window)

void displayText()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 1.0, 0.08);
    std::string heading1 = "UNIVERSITY OF INFORMATION TECHNOLOGY";
    std::string heading2 = "An Animated Underwater Scene";

    std::string text1 = "Project Members:";
    std::string text2 = "   1. Naing Soe Htut";
    std::string text3 = "   2. Htay Lwin";
    std::string text4 = "   3. Yin Yin Kyaw";
    std::string text5 = "   4. Khin Kaung Nge";

    std::string text6 = "Press any key to start the animation...";

    std::string text7 = "Supervised by:";
    std::string text8 = "Dr.Ei Moh Moh Aung";

    // Position of the text
    glRasterPos2f(-0.8f, 0.83f);
    for (char c : heading1)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos2f(-0.5f, 0.63f);
    for (char c : heading2)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos2f(-0.9f, 0.35f);
    for (char c : text1)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.9f, 0.2f);
    for (char c : text2)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.9f, 0.05f);
    for (char c : text3)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.9f, -0.1f);
    for (char c : text4)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.9f, -0.25f);
    for (char c : text5)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(-0.5, -0.7);
    for (const char &c : text6)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos2f(0.35f, 0.25f);
    for (char c : text7)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glRasterPos2f(0.35f, 0.1f);
    for (char c : text8)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glFlush();
}
// -------------------------------------------------------------------------------------
// second part (fish animation window)

void startAnimation()
{
    display();
    reshape(winWidth,winHeight);
    idle();

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Aquatopia");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
}
// -------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    if (!animationStarted)
    {
        animationStarted = true;
        startAnimation();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Aquatopia");
    glutDisplayFunc(displayText);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

