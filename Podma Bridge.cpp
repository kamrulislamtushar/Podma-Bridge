#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<glut.h>

double cameraAngle;
double move_X, move_Y, move_Z;
double angle, angle1;
int canDrawGrid, canDrawAxis;
double speed=30,ang_speed=.1;
double cameraRadius, cameraHeight, cameraAngleDelta;
double moveX, moveCar, moveCar1, moveCar2, moveCar3,moveCar4, moveCar5;
int num_texture  = -1;
GLuint waterimg, skyimg, grassimg, spanimg, roadimg, singleroadimg, cylimg, trainimg, trainfrontimg, railwayimg;


/***************************** Texture Functions *******************************/

int LoadBitmapImage(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
		{
				fread(&rgb, sizeof(rgb), 1, l_file);

				l_texture[j+0] = rgb.rgbtRed;
				l_texture[j+1] = rgb.rgbtGreen;
				l_texture[j+2] = rgb.rgbtBlue;
				l_texture[j+3] = 255;
				j += 4;
		}
    fclose(l_file);

    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);

}

void loadImage()
{
	waterimg = LoadBitmapImage("image/water.bmp");
	skyimg = LoadBitmapImage("image/sky.bmp");
	grassimg = LoadBitmapImage("image/grass.bmp");
	//spanimg = LoadBitmapImage("image/span.bmp");
	roadimg = LoadBitmapImage("image/road.bmp");
	singleroadimg = LoadBitmapImage("image/singleroad.bmp");
	cylimg = LoadBitmapImage("image/cyl.bmp");
	trainimg = LoadBitmapImage("image/train.bmp");
	trainfrontimg = LoadBitmapImage("image/trainfront.bmp");
	railwayimg = LoadBitmapImage("image/railway.bmp");
	//if(grassimg != -1)
		//printf("Load successful!!\n");
	//else printf("Image loading Failed!!\n");
}



void train(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, trainimg);


	for(int i=0; i<4; i++){
		glTranslatef(0,170,0);

	glPushMatrix();{                               //right side
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1,1);
		glVertex3f(50,120,23);
		glTexCoord2f(0,1);
		glVertex3f(50,-50,23);
		glTexCoord2f(0,0);
		glVertex3f(50,-50,0);
		glTexCoord2f(1,0);
		glVertex3f(50,120,0);
	}
		glEnd();
		}glPopMatrix();


	glPushMatrix();{                //left side
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1);
		glVertex3f(30,120,23);
		glTexCoord2f(1,1);
		glVertex3f(30,-50,23);
		glTexCoord2f(1,0);
		glVertex3f(30,-50,0);
		glTexCoord2f(0,0);
		glVertex3f(30,120,0);
	}
		glEnd();
		}glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();{
	for(int i=0; i<4; i++){
		glTranslatef(0,-170,0);
	glPushMatrix();{                     //upper side
	glColor3f(0,.5,.5);
	glTranslatef(0,170,23);
	glBegin(GL_QUADS);
	{

		glVertex3f(50,120,0);
		glVertex3f(50,-50,0);
		glVertex3f(30,-50,0);
		glVertex3f(30,120,0);
	}
		glEnd();
		}glPopMatrix();

	}
	}glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, trainfrontimg);


	glPushMatrix();{                               //back side
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1,1);
		glVertex3f(50,120,23);
		glTexCoord2f(0,1);
		glVertex3f(30,120,23);
		glTexCoord2f(0,0);
		glVertex3f(30,120,0);
		glTexCoord2f(1,0);
		glVertex3f(50,120,0);
	}
		glEnd();
		}glPopMatrix();


	glPushMatrix();{                               //front side
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1,1);
		glVertex3f(50,-560,23);
		glTexCoord2f(0,1);
		glVertex3f(30,-560,23);
		glTexCoord2f(0,0);
		glVertex3f(30,-560,0);
		glTexCoord2f(1,0);
		glVertex3f(50,-560,0);
	}
		glEnd();
		}glPopMatrix();

	glDisable(GL_TEXTURE_2D);


	}glPopMatrix();

}


void carWheel(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	glPushMatrix();{                 //Wheel
	glRotatef(90,0,1,0);
	glColor3f(.1,.1,.1);
	glutSolidTorus(1,2,5,40);
	}glPopMatrix();


	glPushMatrix();{
	glRotatef(angle1,1,0,0);
	glColor3f(.7,.7,.7);
	glScalef(.3,2,0.5);
	glutSolidCube(1);
	}glPopMatrix();



	glPushMatrix();{
	glRotatef(angle,1,0,0);
	glColor3f(.7,.7,.7);
	glScalef(.3,2,0.5);
	glutSolidCube(1);
	}glPopMatrix();

	}glPopMatrix();

}

void car(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	glPushMatrix();{
	glColor3f(.2,.4,.6);
	glTranslatef(67,-90,118);
	glScalef(12,30,5);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.2,.2,.2);
	glTranslatef(67,-82.5,124);
	glScalef(12,15,6);
	glutSolidCube(1);
	}glPopMatrix();

	carWheel(60,-81,115);           //right back Wheel
	carWheel(60,-99,115);          //Wheel
	carWheel(74,-99,115);			//left front Wheel
	carWheel(74,-81,115);			//left back Wheel

	}glPopMatrix();

}


void car1(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	glPushMatrix();{
	glColor3f(.8,0,0);
	glTranslatef(25,-90,118);
	glScalef(12,30,5);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.58,.58,.58);
	glTranslatef(25,-97.5,124);
	glScalef(12,15,6);
	glutSolidCube(1);
	}glPopMatrix();

	carWheel(18,-81,115);           //right back Wheel
	carWheel(18,-99,115);          //Wheel
	carWheel(32,-99,115);			//left front Wheel
	carWheel(32,-81,115);			//left back Wheel

	}glPopMatrix();

}


void car2(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	glPushMatrix();{
	glColor3f(1,.8,0);
	glTranslatef(25,-90,118);
	glScalef(12,30,5);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.75,.75,.75);
	glTranslatef(25,-90,122);
	glScalef(12,15,4);
	glutSolidCube(1);
	}glPopMatrix();

	carWheel(18,-81,115);           //right back Wheel
	carWheel(18,-99,115);          //Wheel
	carWheel(32,-99,115);			//left front Wheel
	carWheel(32,-81,115);			//left back Wheel

	}glPopMatrix();

}


void approachRoad(double tx, double ty, double tz, double angle, double rx, double ry, double rz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);
	glRotatef(angle,rx,ry,rz);

	glEnable(GL_TEXTURE_2D);                      //pitch road
	glBindTexture(GL_TEXTURE_2D, singleroadimg);
	glPushMatrix();{
	glColor3f(1,1,1);
	glTranslatef(0,0,46);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1);
		glVertex3f(42,81,0);
		glTexCoord2f(0,0);
		glVertex3f(42,-50,0);
		glTexCoord2f(1,0);
		glVertex3f(83,-50,0);
		glTexCoord2f(1,1);
		glVertex3f(83,81,0);
	}
		glEnd();
		}glPopMatrix();

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();{                  //Down portion  of Road
				glColor3f(.47,.47,.47);
				glTranslatef(63,0,44.5);
				glRotatef(90,1,0,0);
				glScalef(41,1,131);
				glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{                  //right side line
	glColor3f(.7,.7,.7);
	glRotatef(90,1,0,0);
	glTranslatef(84,46,-13);
	glScalef(3,8,127);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{                  //left side line
	glColor3f(.7,.7,.7);
	glRotatef(90,1,0,0);
	glTranslatef(41,46,-13);
	glScalef(3,8,127);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{
	GLUquadricObj *obj = gluNewQuadric();            //left light post
	glColor3f(.2,.2,.2);
	glTranslatef(41,-100,45);

	for(int i=0; i<2; i++){

	glTranslatef(0,66,0);
	gluCylinder(obj, 0.5,0.5,46,20,20);

	}
	}glPopMatrix();



	glPushMatrix();{
	for(int i=0; i<2; i++){
		glTranslatef(0,66,0);

	glPushMatrix();{
	glTranslatef(44.5,-100,91);
	glRotatef(90,0,1,0);
	glScalef(0.5,0.5,8);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{             // light
	//glColor3f(.9,.9,.9);
	glTranslatef(51,-100,91);
	glRotatef(90,0,1,0);
	glScalef(1,2,5);
	glutSolidCube(1);
	}glPopMatrix();

	}
	}glPopMatrix();


	glPushMatrix();{
	GLUquadricObj *obj = gluNewQuadric();            //right light post
	glColor3f(.2,.2,.2);
	glTranslatef(84,-100,45);

	for(int i=0; i<2; i++){

	glTranslatef(0,66,0);
	gluCylinder(obj, 0.5,0.5,46,20,20);

	}
	}glPopMatrix();



	glPushMatrix();{
	for(int i=0; i<2; i++){
		glTranslatef(0,66,0);

	glPushMatrix();{
	glTranslatef(80.5,-100,91);
	glRotatef(90,0,1,0);
	glScalef(0.5,0.5,8);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{             // light
	//glColor3f(.9,.9,.9);
	glTranslatef(74,-100,91);
	glRotatef(90,0,1,0);
	glScalef(1,2,5);
	glutSolidCube(1);
	}glPopMatrix();

	}
	}glPopMatrix();

}glPopMatrix();

}



void pillar(double tx, double ty, double tz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	glPushMatrix();{
	glTranslatef(40,10,1);
	glColor3f(.7,.7,.7);
	glutSolidTorus(18,19,2,40);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.75,.75,.75);
	glTranslatef(40,10,19);
	glScalef(45,15,38);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{             // side of trapezium
	glColor3f(.7,.7,.7);
	glTranslatef(11,10,44);
	glRotatef(-45,0,1,0);
	glScalef(0.5,15,18);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.7,.7,.7);
	glTranslatef(68,10,44);
	glRotatef(45,0,1,0);
	glScalef(0.5,15,18);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.75,.75,.75);
	glTranslatef(39.5,10,56);
	glScalef(71,15,10);
	glutSolidCube(1);
	}glPopMatrix();



	}glPopMatrix();
}



void approachPillar(double tx, double ty, double tz, double sx, double sy, double sz)

{
	glPushMatrix();{
	glTranslatef(tx,ty,tz);
	glScalef(sx,sy,sz);

	glPushMatrix();{
	glColor3f(.75,.75,.75);
	glTranslatef(40,10,19);
	glScalef(45,15,38);
	glutSolidCube(1);
	}glPopMatrix();

	//trapezium(39.5,16,32,-90,1,0,0);
	//trapezium(39.5,2,32,-90,1,0,0);

	glPushMatrix();{             // side of trapezium
	glColor3f(.7,.7,.7);
	glTranslatef(11,10,44);
	glRotatef(-45,0,1,0);
	glScalef(0.5,15,18);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.7,.7,.7);
	glTranslatef(68,10,44);
	glRotatef(45,0,1,0);
	glScalef(0.5,15,18);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(.75,.75,.75);
	glTranslatef(39.5,10,56);
	glScalef(71,15,10);
	glutSolidCube(1);
	}glPopMatrix();


	}glPopMatrix();
}



void SpanPart1(double tx, double ty, double tz){

	glPushMatrix();{
	glTranslatef(tx,ty,tz);

 	glPushMatrix();{
	glColor3f(1,.8,.4);
	glRotatef(45,1,0,0);
	glTranslatef(0,0,14);
	glScalef(7,7,50);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(1,.8,.4);
	glTranslatef(0,-40,10);
	glRotatef(-45,1,0,0);
	glScalef(7,7,50);
	glutSolidCube(1);
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(1,.8,.5);
	glRotatef(90,1,0,0);
	glTranslatef(0,-10,25);
	glScalef(7,7,70);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{
	glColor3f(1,.8,.5);
	glRotatef(90,1,0,0);
	glTranslatef(0,30,25);
	glScalef(7,7,70);
	glutSolidCube(1);
	}glPopMatrix();


	}glPopMatrix();
}

void Span(double tx, double ty, double tz){

	glPushMatrix();{
	glTranslatef(tx,ty,tz);

	SpanPart1(10,10,10);
	SpanPart1(10,70,10);
	SpanPart1(70,10,10);
	SpanPart1(70,70,10);

	glPushMatrix();{                  //Down portion  of Road
	glColor3f(.7,.7,.7);
	glTranslatef(40,15,44);
	glRotatef(90,1,0,0);
	glScalef(90,1,129);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{
	GLUquadricObj *obj = gluNewQuadric();            //left light post
	glColor3f(.2,.2,.2);
	glTranslatef(-5,-100,45);

	for(int i=0; i<2; i++){

	glTranslatef(0,66,0);
	gluCylinder(obj, 0.5,0.5,46,20,20);

	}
	}glPopMatrix();



	glPushMatrix();{
	for(int i=0; i<2; i++){
		glTranslatef(0,66,0);

	glPushMatrix();{
	glTranslatef(2,-100,91);
	glRotatef(90,0,1,0);
	glScalef(0.5,0.5,15);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{             // light
	//glColor3f(.9,.9,.9);
	glTranslatef(12,-100,91);
	glRotatef(90,0,1,0);
	glScalef(1,2,5);
	glutSolidCube(1);
	}glPopMatrix();

	}
	}glPopMatrix();


	glPushMatrix();{
	GLUquadricObj *obj = gluNewQuadric();            //right light post
	glColor3f(.2,.2,.2);
	glTranslatef(84,-100,45);

	for(int i=0; i<2; i++){

	glTranslatef(0,66,0);
	gluCylinder(obj, 0.5,0.5,46,20,20);

	}
	}glPopMatrix();



	glPushMatrix();{
	for(int i=0; i<2; i++){
		glTranslatef(0,66,0);

	glPushMatrix();{
	glTranslatef(77,-100,91);
	glRotatef(90,0,1,0);
	glScalef(0.5,0.5,15);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{             // light
	//glColor3f(.9,.9,.9);
	glTranslatef(67,-100,91);
	glRotatef(90,0,1,0);
	glScalef(1,2,5);
	glutSolidCube(1);
	}glPopMatrix();

	}
	}glPopMatrix();


	glPushMatrix();{                  //right side line
	glColor3f(.7,.7,.7);
	glRotatef(90,1,0,0);
	glTranslatef(84,46,-13);
	glScalef(3,8,127);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{                  //left side line
	glColor3f(.7,.7,.7);
	glRotatef(90,1,0,0);
	glTranslatef(-5,46,-13);
	glScalef(3,8,127);
	glutSolidCube(1);
	}glPopMatrix();



	glEnable(GL_TEXTURE_2D);                      //pitch road
	glBindTexture(GL_TEXTURE_2D, roadimg);
	glPushMatrix();{
	glColor3f(1,1,1);
	glTranslatef(0,0,46);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1,1);
		glVertex3f(-5,81,0);
		glTexCoord2f(1,0);
		glVertex3f(-5,-50,0);
		glTexCoord2f(0,0);
		glVertex3f(85,-50,0);
		glTexCoord2f(0,1);
		glVertex3f(85,81,0);
	}
		glEnd();
		}glPopMatrix();





	glBindTexture(GL_TEXTURE_2D, cylimg);          //rail line floor
	glPushMatrix();{
	glColor3f(1,1,1);
	glTranslatef(0,0,5);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1);
		glVertex3f(22,81,0);
		glTexCoord2f(0,0);
		glVertex3f(22,-50,0);
		glTexCoord2f(1,0);
		glVertex3f(58,-50,0);
		glTexCoord2f(1,1);
		glVertex3f(58,81,0);
	}
		glEnd();
		}glPopMatrix();

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();{                  //rail line
	glColor3f(.2,.2,.2);
	glRotatef(90,1,0,0);
	glTranslatef(48,7.5,-13);
	glScalef(2,1,130);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{                  //rail line
	glColor3f(.2,.2,.2);
	glRotatef(90,1,0,0);
	glTranslatef(32,7.5,-13);
	glScalef(2,1,130);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{              // Diagonal rod
	glColor3f(1,.8,.4);
	glRotatef(90,0,1,0);
	glTranslatef(-2,77,40);
	glScalef(7,7,60);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{
	glColor3f(1,.8,.4);
	glRotatef(90,0,1,0);
	glTranslatef(-2,15,40);
	glScalef(7,7,60);
	glutSolidCube(1);
	}glPopMatrix();


	glPushMatrix();{
	glColor3f(1,.8,.4);
	glRotatef(90,0,1,0);
	glTranslatef(-2,-47,40);
	glScalef(7,7,60);
	glutSolidCube(1);
	}glPopMatrix();



	}glPopMatrix();

}


void singlePart(double tx, double ty, double tz){

	glPushMatrix();{
	glTranslatef(tx,ty,tz);


	pillar(0,0,1);
	Span(0,50,65);
	Span(0,170,65);


	pillar(0,240,1);
	Span(0,290,65);
	Span(0,410,65);


	}glPopMatrix();

}




/***************************** VECTOR structure **********************************/

struct V;

V operator+(V a,V b);
V operator*(V a,V b);
V operator*(V b,double a);
V operator*(double a,V b);

struct V{
	double x,y,z;

	V(){}
	V(double _x,double _y){x=_x;y=_y;z=0;}
	V(double _x,double _y,double _z){x=_x;y=_y;z=_z;}


	double	mag(){	return sqrt(x*x+y*y+z*z);	}

	void 	norm(){	double d = mag();x/=d;y/=d;	z/=d;}
	V 		unit(){	V ret = *this;	ret.norm(); return ret;}

	double	dot(V b){		return x*b.x + y*b.y + z*b.z;}
	V		cross(V b){		return V( y*b.z - z*b.y , z*b.x - x*b.z , x*b.y - y*b.x );}


	double	projL(V on){	on.norm();	return this->dot(on);}
	V		projV(V on){	on.norm();	return on * projL(on);}

	V rot(V axis, double angle){
		return this->rot(axis, cos(angle), sin(angle));
	}

	V rot(V axis, double ca, double sa){
		V rotatee = *this;
		axis.norm();
		V normal = (axis * rotatee).unit();
		V mid = (normal * axis).unit();
		double r = rotatee.projL(mid);
		V ret=r*mid*ca + r*normal*sa + rotatee.projV(axis);
		return ret.unit();
	}
};

V operator+(V a,V b){		return V(a.x+b.x, a.y+b.y, a.z+b.z);	}
V operator-(V a){			return V (-a.x, -a.y, -a.z);			}
V operator-(V a,V b){		return V(a.x-b.x, a.y-b.y, a.z-b.z);	}
V operator*(V a,V b){		return a.cross(b);						}
V operator*(double a,V b){	return V(a*b.x, a*b.y, a*b.z);			}
V operator*(V b,double a){	return V(a*b.x, a*b.y, a*b.z);			}
V operator/(V b,double a){	return V(b.x/a, b.y/a, b.z/a);			}




V loc,dir,perp;


V  _L(1500,0,200);
V  _D(-1,0,0);
V  _P(0,0,1);



/****************************** GridLines and Axes ***********************************/

void gridAndAxis(){
	// draw the three major AXES
	if(canDrawAxis==1){
		glBegin(GL_LINES);
			//X axis
			glColor3f(0, 1, 0);	//100% Green
			glVertex3f(-150, 0, 0);
			glVertex3f( 150, 0, 0);

			//Y axis
			glColor3f(0, 0, 1);	//100% Blue
			glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
			glVertex3f(0,  150, 0);

			//Z axis
			glColor3f(1, 1, 1);	//100% White
			glVertex3f( 0, 0, -150);
			glVertex3f(0, 0, 150);
		glEnd();
	}

	if(canDrawGrid == 1){
	//some gridlines along the field
		int i;

		glColor3f(0.5, 0.5, 0.5);	//grey
		glBegin(GL_LINES);
			for(i=-10;i<=10;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		glEnd();

	}
}

/********************************************************************************/

void display(){
	//codes for Models, Camera

	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers to preset values

	/***************************
	/ set-up camera (view) here
	****************************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);		//specify which matrix is the current matrix

	//initialize the matrix
	glLoadIdentity();				//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	//gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

	V to=loc+dir;
	gluLookAt(loc.x, loc.y, loc.z,		to.x,to.y,to.z,		perp.x,perp.y,perp.z);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/

	//gridAndAxis();


	/****************************
	/ Add your objects from here
	****************************/


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, waterimg);

	glPushMatrix();{
	glColor3f(.9,.9,.9);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(-2500,2000,0);
		glTexCoord2f(1,0);
		glVertex3f(-2500,-2000,0);
		glTexCoord2f(0,0);
		glVertex3f(2500,-2000,0);
		glTexCoord2f(0,1);
		glVertex3f(2500,2000,0);
	glEnd();
	}glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, skyimg);
	glColor3f(1,1,1);
	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, 2500, 25, 25);


	glPushMatrix();{
	glBindTexture(GL_TEXTURE_2D, grassimg);
	glColor3f(1,1,1);
	glTranslatef(0,0,68);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(-2500,-1440,0);
		glTexCoord2f(0,0);
		glVertex3f(-2500,-2500,0);
		glTexCoord2f(1,0);
		glVertex3f(2500,-2500,0);
		glTexCoord2f(1,1);
		glVertex3f(2500,-1440,0);
	glEnd();
	}glPopMatrix();


	glPushMatrix();{
	glBindTexture(GL_TEXTURE_2D, grassimg);
	glColor3f(1,1,1);
	glTranslatef(0,0,68);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(-2500,1450,0);
		glTexCoord2f(0,0);
		glVertex3f(-2500,2500,0);
		glTexCoord2f(1,0);
		glVertex3f(2500,2500,0);
		glTexCoord2f(1,1);
		glVertex3f(2500,1450,0);
	glEnd();
	}glPopMatrix();

	glDisable(GL_TEXTURE_2D);




	glPushMatrix();{
	for(int i=0; i<16; i++){
		glTranslatef(0,60,0);
	glPushMatrix();{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, railwayimg);          //rail line floor




	glColor3f(1,1,1);
	glTranslatef(0,1440,71);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1);
		glVertex3f(12,81,0);
		glTexCoord2f(0,0);
		glVertex3f(12,-50,0);
		glTexCoord2f(1,0);
		glVertex3f(68,-50,0);
		glTexCoord2f(1,1);
		glVertex3f(68,81,0);
	}
		glEnd();

	glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	}

	}glPopMatrix();



	glPushMatrix();{
	for(int i=0; i<16; i++){
		glTranslatef(0,-60,0);
	glPushMatrix();{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, railwayimg);          //rail line floor




	glColor3f(1,1,1);
	glTranslatef(0,-1455,71);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1);
		glVertex3f(12,81,0);
		glTexCoord2f(0,0);
		glVertex3f(12,-50,0);
		glTexCoord2f(1,0);
		glVertex3f(68,-50,0);
		glTexCoord2f(1,1);
		glVertex3f(68,81,0);
	}
		glEnd();

	glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
	}

	}glPopMatrix();





	singlePart(0,0,1);
	singlePart(0,480,1);
	singlePart(0,960,1);
	singlePart(0,-480,1);           // 480 meter doirgho
	singlePart(0,-960,1);
	singlePart(0,-1440,1);
	pillar(0,1440,1);




	glPushMatrix();{

		approachRoad(17,-1525, 65, 12, 0,0,1);

		for(int i=0; i<7; i++){
		glTranslatef(26,-121,0);
			glPushMatrix();{

			approachRoad(17,-1525, 65, 12, 0,0,1);
			approachPillar(59,-1525,69,.5,.8,.65);


			}glPopMatrix();
		}
	}glPopMatrix();


	glPushMatrix();{
		approachRoad(-60,-1500, 65, -12, 0,0,1);

		for(int i=0; i<7; i++){
			glTranslatef(-26,-121,0);
			glPushMatrix();{

				approachRoad(-60,-1500, 65, -12, 0,0,1);
				approachPillar(-14,-1500,69,.5,.8,.65);


			}glPopMatrix();
		}

	}glPopMatrix();



	glPushMatrix();{                                //Opposite direction (opposite of train)

		approachRoad(11,1507, 65, -12, 0,0,1);

		for(int i=0; i<7; i++){
		glTranslatef(26,121,0);
			glPushMatrix();{

			approachRoad(11,1507, 65, -12, 0,0,1);
			approachPillar(59,1507,69,.5,.8,.65);

			}glPopMatrix();
		}
	}glPopMatrix();


	glPushMatrix();{
		approachRoad(-55,1481, 65, 12, 0,0,1);

		for(int i=0; i<7; i++){
			glTranslatef(-26,121,0);
			glPushMatrix();{

				approachRoad(-55,1481, 65, 12, 0,0,1);
				approachPillar(-14,1481,69,.5,.8,.65);


			}glPopMatrix();
		}

	}glPopMatrix();

	train(0,moveX,73);

	glPushMatrix();{
	glTranslatef(0,moveCar,0);
	car(0,1500,1);
	}glPopMatrix();

	glPushMatrix();{
	glTranslatef(0,moveCar1,0);
	car(0,1100,1);
	}glPopMatrix();


	glPushMatrix();{
	glTranslatef(0,moveCar5,0);
	car2(42,700,1);
	}glPopMatrix();

	glPushMatrix();{
	glTranslatef(0,moveCar2,0);
	car1(0,-1300,1);
	}glPopMatrix();


	glPushMatrix();{
	glTranslatef(0,moveCar3,0);
	car1(0,-900,1);
	}glPopMatrix();


	glPushMatrix();{
	glTranslatef(0,moveCar4,0);
	car2(0,-500,1);
	}glPopMatrix();






	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glFlush();
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Models, Camera

	if(moveCar > -2800)
	{
	moveCar -= 3;
	}
	else
	{
	moveCar = 0;
	}


	if(moveCar1 > -2400)
	{
	moveCar1 -= 3;
	}
	else
	{
	moveCar1 = 0;
	}


	if(moveCar5 > -2000)
	{
	moveCar5 -= 3;
	}
	else
	{
	moveCar5 = 0;
	}


	if(moveCar2 < 2800)
	{
	moveCar2 += 3;
	}
	else
	{
	moveCar2 = 0;
	}


	if(moveCar3 < 2400)
	{
	moveCar3 += 3;
	}
	else
	{
	moveCar3 = 0;
	}


	if(moveCar4 < 2000)
	{
	moveCar4 += 3;
	}
	else
	{
	moveCar4 = 0;
	}

    if(moveX <1200)
    {
        moveX+=5;
    }
    else
    {
        moveX=-1200;
    }
	angle += 5;
	angle1 += 5;

	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.

	//codes for any changes in Models

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void init(){
	//codes for initialization
	loadImage();

	cameraAngle = 0;	//angle in radian
	move_X = 0;
	move_Y = 0;
	move_Z = 0;
	canDrawGrid = 1;
	canDrawAxis = 1;
	moveX = -1400;
	moveCar = 0;
	moveCar1 = 0;
	moveCar2 = 0;
	moveCar3 = 0;
	moveCar4 = 0;
	moveCar5 = 0;
	angle1 = 90;
	angle = 0;

	cameraAngleDelta = .001;

	cameraRadius = 150;
	cameraHeight = 50;


	loc=_L,dir=_D,perp=_P;
	//clear the screen
	glClearColor(0,0,0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*
		gluPerspective() — set up a perspective projection matrix

		fovy -         Specifies the field of view angle, in degrees, in the y direction.
        aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
        zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
        zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
    */

	gluPerspective(70,	1,	0.1,	10000.0);

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

	case 'w':case 'W':
		loc=loc+speed*dir;
		break;

	case 'a':case 'A':
		loc=loc+speed*((perp*dir).unit());
		break;

	case 's':case 'S':
		loc=loc-speed*dir;
		break;

	case 'd':case 'D':
		loc=loc+speed*((dir*perp).unit());
		break;
	default:
		break;
	}
}

void specialKeyListener(int key, int x,int y){
	V p;

	switch(key){
	case GLUT_KEY_UP:
		p=(dir*perp).unit();
		dir=dir.rot(p,ang_speed);
		perp=perp.rot(p,ang_speed);
		break;
	case GLUT_KEY_DOWN:
		p=(perp*dir).unit();
		dir=dir.rot(p,ang_speed);
		perp=perp.rot(p,ang_speed);
		break;

	case GLUT_KEY_LEFT:
		dir=dir.rot(-perp,ang_speed);
		break;
	case GLUT_KEY_RIGHT:
		dir=dir.rot(perp,ang_speed);
		break;

	case GLUT_KEY_PAGE_UP:
		loc=loc+speed*perp;
		break;
	case GLUT_KEY_PAGE_DOWN:
		loc=loc-speed*perp;
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		loc=_L,dir=_D,perp=_P;
		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

int main(int argc, char **argv){

	glutInit(&argc,argv);							//initialize the GLUT library

	glutInitWindowSize(700, 650);
	glutInitWindowPosition(100, 50);

	/*
		glutInitDisplayMode - inits display mode
		GLUT_DOUBLE - allows for display on the double buffer window
		GLUT_RGBA - shows color (Red, green, blue) and an alpha
		GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Padma Bridge ");

	printf("Camera Control\n");
	printf("______________________________________________\n");
	printf("Roll: UP and DOWN arrow\n");
	//printf("Pitch: Q and E\n");
	printf("Yaw: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("Left-Right: A and D\n");
	printf("Zoom in-out: W and S\n");
	printf("Reset Camera: HOME\n");
	printf("______________________________________________\n");
	printf("Rafid Asrar Protty & Kamrul Islam Tushar\n");
	printf("______________________________________________\n");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
