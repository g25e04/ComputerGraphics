//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "U10716012.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GLCtrl"
#pragma resource "*.dfm"
TForm1 *Form1;
typedef float point[3];

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

GLfloat vertices[][3]={{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},
{-0.5,0.5,-0.5},{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5}};

GLfloat color[][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},
{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}};

point v[]={{0.0,0.0,1.0}, {0.0,0.942809,-0.33333}, {-0.816497,-0.471405,-0.333333}, {0.816497,-0.471405,-0.333333}};
static GLfloat theta[]={0.0,0.0,0.0};

int xSize=100,ySize=100,zSize=100,tempx;
int xTheta,yTheta,zTheta;
int xMove,yMove,zMove;
float L=4.0;
bool Blue=false,Red=false,Green=false;
GLfloat global_ambient[]={0.2f, 0.2f, 0.2f, 1.0f};
GLfloat light_ambient[][4]={{1.0f,0.0f,0.0f,1.0f},{0.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{0.2f,0.2f,0.2f,1.0f}};
GLfloat light_diffuse[][4]={{0.7f,0.3f,0.3f,1.0f}};
GLfloat light_specular[][4]={{0.7f,0.3f,0.3f,1.0f}};
GLfloat emission[]={0.0,0.3,0.3,1.0};
GLfloat m_ambient[][4]={{0.24725,0.1995,0.0745,1.0},{0.105882,0.058824,0.113725,1.0},{0.23125,0.23125,0.23125,1.0}};
GLfloat m_diffuse[][4]={{0.75164,0.60648,0.22648,1.0},{0.427451,0.470588,0.541176,1.0},{0.2775,0.2775,0.2775,1.0}};
GLfloat m_specular[][4]={{0.628281,0.555802,0.366065,1.0},{0.333333,0.333333,0.521569,1.0},{0.773911,0.773911,0.773911,1.0}};

int ma=0;

static bool state = true;
static int count = 0;

void triangle(point a, point b, point c){
 {
        glBegin(GL_POLYGON);
        glNormal3fv(a);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glEnd();
 }
}

void tetrahedron(point a, point b, point c, point d){
        glBegin(GL_TRIANGLES);
                glColor3f(1.0,0.0,0.0);
                triangle(a,b,c);
                glColor3f(0.0,1.0,0.0);
                triangle(a,d,b);
                glColor3f(1.0,1.0,1.0);
                triangle(b,d,c);
                glColor3f(0.0,0.0,1.0);
                triangle(a,c,d);
        glEnd();
}

void line(){
glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(4,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,4,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,4);
glEnd();
}

void divide(point a, point b, point c, point d,int n){
point middle[6];
int i=0;
if(n>0){
        for(i=0;i<3;i++)middle[0][i]=(a[i]+b[i])/2;
        for(i=0;i<3;i++)middle[1][i]=(a[i]+c[i])/2;
        for(i=0;i<3;i++)middle[2][i]=(a[i]+d[i])/2;
        for(i=0;i<3;i++)middle[3][i]=(b[i]+c[i])/2;
        for(i=0;i<3;i++)middle[4][i]=(c[i]+d[i])/2;
        for(i=0;i<3;i++)middle[5][i]=(b[i]+d[i])/2;

        divide(a, middle[0], middle[1], middle[2], n-1);
        divide(middle[0], b, middle[3], middle[5], n-1);
        divide(middle[1], middle[3], c, middle[4], n-1);
        divide(middle[2], middle[5], middle[4], d, n-1);
        }
else(tetrahedron(a,b,c,d));
}

void polygon(int a, int b, int c, int d){
           glBegin(GL_POLYGON);
                glColor3fv(color[a]);
                glVertex3fv(vertices[a]);
                glColor3fv(color[b]);
                glVertex3fv(vertices[b]);
                glColor3fv(color[c]);
                glVertex3fv(vertices[c]);
                glColor3fv(color[d]);
                glVertex3fv(vertices[d]);
           glEnd();
}


void colorcube(){
        polygon(0,3,2,1); //0 to a, 3 to b...
        polygon(2,3,7,6);
        polygon(0,4,7,3);
        polygon(1,2,6,5);
        polygon(4,5,6,7);
        polygon(0,1,5,4);
}

void JustLine(int a, int b, int c, int d){
     glBegin(GL_LINE_LOOP);
                glColor3fv(color[a]);
                glVertex3fv(vertices[a]);
                glColor3fv(color[b]);
                glVertex3fv(vertices[b]);
                glColor3fv(color[c]);
                glVertex3fv(vertices[c]);
                glColor3fv(color[d]);
                glVertex3fv(vertices[d]);
           glEnd();
}

void Linecube(){
        JustLine(0,3,2,1); //0 to a, 3 to b...
        JustLine(2,3,7,6);
        JustLine(0,4,7,3);
        JustLine(1,2,6,5);
        JustLine(4,5,6,7);
        JustLine(0,1,5,4);
}

void light(){
GLfloat lightPosition[][4]={{L*1,L*(-1),0.0f,1.0f},{L*1,0.0f,L*1,1.0f},{0.0f,L*(-1),L*1,1.0f}};
        if(Blue){
                glLightfv(GL_LIGHT2,GL_AMBIENT,light_ambient[2]);
                glLightfv(GL_LIGHT2,GL_DIFFUSE,light_diffuse[0]);
                glLightfv(GL_LIGHT2,GL_SPECULAR,light_specular[0]);
                glLightfv(GL_LIGHT2,GL_POSITION,lightPosition[2]);
                glEnable(GL_LIGHT2);
        }
        else{glDisable(GL_LIGHT2);}

        if(Green){
                glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient[1]);
                glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse[0]);
                glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular[0]);
                glLightfv(GL_LIGHT1,GL_POSITION,lightPosition[1]);
                glEnable(GL_LIGHT1);
        }
        else{glDisable(GL_LIGHT1);}

        if(Red){
                glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient[0]);
                glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse[0]);
                glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular[0]);
                glLightfv(GL_LIGHT0,GL_POSITION,lightPosition[0]);
                glEnable(GL_LIGHT0);
        }
        else{glDisable(GL_LIGHT2);}
}

void material(){
        if(ma==0){
                glMaterialf(GL_FRONT,GL_SHININESS,51.2);
        }
        else if(ma==1){
                glMaterialf(GL_FRONT,GL_SHININESS,9.84615);
        }
        else if(ma==2){
                glMaterialf(GL_FRONT,GL_SHININESS,89.6);
        }
        //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_ambient[ma]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_diffuse[ma]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_specular[ma]);
}

void __fastcall TForm1::init(TObject *Sender)
{
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_LIGHTING);

        glClearColor(0.1,0.1,0.1,1.0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::drawing(TObject *Sender)
{

        glClearColor(0.1,0.1,0.1,1.0);


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION); //set to projection
        glLoadIdentity(); //set to identity matrix
        glOrtho(-10,10,-10,10,-10.0,10.0);
        //glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);
        glMatrixMode(GL_MODELVIEW); //set to model view


         if(RadioButton1 -> Checked == true){
          glLoadIdentity();
//glTranslatef(0.0, 0.0, -2);
//glRotatef(35.26, 1.0, 0.0, 0.0);
//glRotatef(-45.0, 0.0, 1.0, 0.0);
        gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glViewport(0,0,GLBox1->Width,GLBox1->Height);

        //light();
        //material();
        line();

        if(samesize -> Checked == false)
        glScalef(1+0.01*xSize,1+0.01*ySize,1+0.01*zSize);
        else
        glScalef(1+0.01*xSize,1+0.01*xSize,1+0.01*xSize);

        glRotatef(xTheta,  1.0,  0.0,  0.0);
        glRotatef(yTheta,  0.0,  1.0,  0.0);
        glRotatef(zTheta,  0.0,  0.0,  1.0);
        glTranslatef(0.01*xMove, 0.0, 0.0);
        glTranslatef(0.0, 0.01*yMove, 0.0);
        glTranslatef(0.0, 0.0, 0.01*zMove);
        //divide(v[0],v[1],v[2],v[3],count);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if(RadioButton6 -> Checked == true)
           glShadeModel(GL_SMOOTH);
        else
           glShadeModel(GL_FLAT);

        if(RadioButton3 -> Checked == true)
        colorcube();
        else{
        Linecube();}

         }

         else{
         glLoadIdentity();
        gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glViewport(0,0,GLBox1->Width/2,GLBox1->Height/2);

        light();
        material();
        line();

        if(samesize -> Checked == false)
        glScalef(1+0.01*xSize,1+0.01*ySize,1+0.01*zSize);
        else
        glScalef(1+0.01*xSize,1+0.01*xSize,1+0.01*xSize);
        glRotatef(xTheta,  1.0,  0.0,  0.0);
        glRotatef(yTheta,  0.0,  1.0,  0.0);
        glRotatef(zTheta,  0.0,  0.0,  1.0);
        glTranslatef(xMove, yMove, zMove);
        //divide(v[0],v[1],v[2],v[3],count);
         if(RadioButton6 -> Checked == true)
           glShadeModel(GL_SMOOTH);
        else
           glShadeModel(GL_FLAT);

        if(RadioButton3 -> Checked == true)
        colorcube();
        else{
        Linecube();}

         glLoadIdentity();
        gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glViewport(GLBox1->Width/2,0,GLBox1->Width/2,GLBox1->Height/2);

        light();
        material();
        line();

        if(samesize -> Checked == false)
        glScalef(1+0.01*xSize,1+0.01*ySize,1+0.01*zSize);
        else
        glScalef(1+0.01*xSize,1+0.01*xSize,1+0.01*xSize);
        glRotatef(xTheta,  1.0,  0.0,  0.0);
        glRotatef(yTheta,  0.0,  1.0,  0.0);
        glRotatef(zTheta,  0.0,  0.0,  1.0);
        glTranslatef(xMove, yMove, zMove);
        //divide(v[0],v[1],v[2],v[3],count);
         if(RadioButton6 -> Checked == true)
           glShadeModel(GL_SMOOTH);
        else
           glShadeModel(GL_FLAT);

        if(RadioButton3 -> Checked == true)
        colorcube();
        else{
        Linecube();}

         glLoadIdentity();
        gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        glViewport(0,GLBox1->Height/2,GLBox1->Width/2,GLBox1->Height/2);

        light();
        material();
        line();

        if(samesize -> Checked == false)
        glScalef(1+0.01*xSize,1+0.01*ySize,1+0.01*zSize);
        else
        glScalef(1+0.01*xSize,1+0.01*xSize,1+0.01*xSize);
        glRotatef(xTheta,  1.0,  0.0,  0.0);
        glRotatef(yTheta,  0.0,  1.0,  0.0);
        glRotatef(zTheta,  0.0,  0.0,  1.0);
        glTranslatef(xMove, yMove, zMove);
        //divide(v[0],v[1],v[2],v[3],count);
         if(RadioButton6 -> Checked == true)
           glShadeModel(GL_SMOOTH);
        else
           glShadeModel(GL_FLAT);

        if(RadioButton3 -> Checked == true)
        colorcube();
        else{
        Linecube();}

         glLoadIdentity();
        gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glViewport(GLBox1->Width/2,GLBox1->Height/2,GLBox1->Width/2,GLBox1->Height/2);

        light();
        material();
        line();

        if(samesize -> Checked == false)
        glScalef(1+0.01*xSize,1+0.01*ySize,1+0.01*zSize);
        else
        glScalef(1+0.01*xSize,1+0.01*xSize,1+0.01*xSize);
        glRotatef(xTheta,  1.0,  0.0,  0.0);
        glRotatef(yTheta,  0.0,  1.0,  0.0);
        glRotatef(zTheta,  0.0,  0.0,  1.0);
        glTranslatef(xMove, yMove, zMove);
        //divide(v[0],v[1],v[2],v[3],count);
         if(RadioButton6 -> Checked == true)
           glShadeModel(GL_SMOOTH);
        else
           glShadeModel(GL_FLAT);

        if(RadioButton3 -> Checked == true)
        colorcube();
        else{
        Linecube();}
         }
        glFlush();  //in this homework is not to important
}
//----------------------------------------------------------------------------
/* void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        GLBox1->Invalidate();

        if(state){
                count++;
                if(count>=5)
                        state=!state;
        }
        else{
                count--;
                if(count<=0)
                        state=!state;
        }

}         */
//---------------------------------------------------------------------------

void __fastcall TForm1::XscaleChange(TObject *Sender)
{
         xSize = Xscale ->Position;
         XL -> Caption = xSize;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YscaleChange(TObject *Sender)
{
         ySize = Yscale ->Position;
         YL -> Caption = ySize;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZscaleChange(TObject *Sender)
{
         zSize = Zscale ->Position;
         ZL -> Caption = zSize;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XRoChange(TObject *Sender)
{
         xTheta = XRo ->Position;
         XR -> Caption = xTheta;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YRoChange(TObject *Sender)
{
         yTheta = YRo ->Position;
         YR -> Caption = yTheta;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZRoChange(TObject *Sender)
{
         zTheta = ZRo ->Position;
         ZR -> Caption = zTheta;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XTransChange(TObject *Sender)
{

         xMove = XTrans ->Position;
         XT -> Caption = xMove;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YTransChange(TObject *Sender)
{
         yMove = YTrans ->Position;
         YT -> Caption = yMove;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZTransChange(TObject *Sender)
{
         zMove = ZTrans ->Position;
         ZT -> Caption = zMove;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScaleButtonClick(TObject *Sender)
{
         Xscale ->Position = 0;
         xSize = 0;
         Yscale ->Position = 0;
         ySize = 0;
         Zscale ->Position = 0;
         zSize = 0;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TransButtonClick(TObject *Sender)
{
         XRo ->Position = 0;
         xTheta = 0;
         YRo ->Position = 0;
         yTheta = 0;
         ZRo ->Position = 0;
         zTheta = 0;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
         XTrans ->Position = 0;
         xMove = 0;
         YTrans ->Position = 0;
         yMove = 0;
         ZTrans ->Position = 0;
         zMove = 0;
         GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::samesizeClick(TObject *Sender)
{
          Xscale ->Position = 0;
          xSize=1;

          if(samesize -> Checked == true){
          Yscale -> Enabled = false;
          Zscale -> Enabled = false;
          }
          else{
          Yscale -> Enabled = true;
          Zscale -> Enabled = true;
          }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton5Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton6Click(TObject *Sender)
{
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
          Blue=!Blue;
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
          Red=!Red;
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
          Green=!Green;
          GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton7Click(TObject *Sender)
{
        ma=2;
        GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton8Click(TObject *Sender)
{
        ma=0;
        GLBox1 -> Invalidate();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton9Click(TObject *Sender)
{
        ma=1;
        GLBox1 -> Invalidate();
}
//---------------------------------------------------------------------------

