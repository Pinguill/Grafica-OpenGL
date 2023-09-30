//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLMmodel* objmodel_ptr2;
   GLMmodel* objmodel_ptr3;
   GLMmodel* objmodel_ptr4;
   GLMmodel* objmodel_ptr5;
   GLMmodel* objmodel_ptr6;
   GLMmodel* objmodel_ptr7;

   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura

   float movX, movY, movZ;
   bool xDer, xIzq, yUp, yDown, zoomIn, zoomOut;


public:
	myWindow(){}

	//*** Para Textura: aqui adiciono un método que abre la textura en JPG
	void initialize_textures(void)
	{
		int w, h;
		GLubyte* data = 0;
		//data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		//std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./Mallas/Diffuse.jpg", 0),
			"./Mallas/Diffuse.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);
	}


	virtual void OnRender(void)
	{
	  movX = 0;
	  movY = 0;
	  movZ = 0;
	  if (xIzq) {
		  movX = movX + 0.05;
	  }
	  else if (xDer)
	  {
		  movX = movX - 0.05;
	  }
	  else if (yUp) {
		  movY = movY - 0.05;
	  }
	  else if (yDown) {
		  movY = movY + 0.05;
	  }
	  else if (zoomIn) {
		  movZ = movZ + 0.05;
	  }
	  else if (zoomOut) {
		  movZ = movZ - 0.05;
	  }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      //glPushMatrix();
	  //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);

	  glTranslatef(movX, movY, movZ);



	  //Mount 
	  if (shader) shader->begin();

		  glPushMatrix();
		  glTranslatef(0.0f, 0.0f, 0.0f);
		  glScalef(10.0f, 10.0f, 10.0f);
		  glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader) shader->end();

	  // Arbol
	  if (shader) shader->begin();

		  glPushMatrix();
		  glTranslatef(0.0f, 4.0f, 1.0f);
		  glScalef(6.0f, 6.0f, 6.0f);
		  glmDraw(objmodel_ptr4, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader) shader->end();

	  // Ciclope
	  if (shader) shader->begin();

		  glPushMatrix();
		  glTranslatef(-2.5f, -0.5f, 8.0f);
		  glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		  glmDraw(objmodel_ptr3, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader) shader->end();


	  // Goat
	  if (shader) shader->begin();

		  glPushMatrix();
		  glTranslatef(-1.0f, -0.8f, 8.0f); 
		  glScalef(0.2f, 0.2f, 0.2f);
		  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		  glRotatef(70.0f, .0f, 0.0f, 1.0f);
		  glmDraw(objmodel_ptr5, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader) shader->end();

	  // Casa
	  if (shader1) shader1->begin();

		  glPushMatrix();
		  glTranslatef(3.4f, 1.5f, 4.5f);
		  //glScalef(0.2f, 0.2f, 0.2f);
		  glBindTexture(GL_TEXTURE_2D, texid);
		  glmDraw(objmodel_ptr6, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader1) shader1->end();

	  // Arbusto
	  if (shader) shader->begin();

		  glPushMatrix();
		  glTranslatef(-0.5f, -0.8f, 8.0f);
		  glScalef(0.3f, 0.3f, 0.3f);
		  //glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		  glmDraw(objmodel_ptr7, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
		  //glutSolidTeapot(1.0);
	  if (shader) shader->end();

	  /*
      if (shader) shader->begin();
		  
		  glPushMatrix();
		  glTranslatef(-1.5f, 0.0f, 0.0f);
		  glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
	      //glutSolidTeapot(1.0);
      if (shader) shader->end();

	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (shader1) shader1->begin();

		  glPushMatrix();
		  glTranslatef(1.5f, 0.0f, 0.0f);
		  glBindTexture(GL_TEXTURE_2D, texid);
		  glmDraw(objmodel_ptr1, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		  glPopMatrix();
	  //glutSolidTeapot(1.0);
	  if (shader1) shader1->end();
	  */
	  

      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		movX = 0;
		movY = 0;
		movZ = 0;
		xIzq = false;
		xDer = false;
		yUp = false;
		yDown = false;
		zoomIn = false;
		zoomOut = false;

		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

	 //*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

	  //Abrir mallas
	  objmodel_ptr = NULL;

	  if (!objmodel_ptr)
	  {
		  objmodel_ptr = glmReadOBJ("./Mallas/bunny.obj");
		  if (!objmodel_ptr)
			  exit(0);

		  glmUnitize(objmodel_ptr);
		  glmFacetNormals(objmodel_ptr);
		  glmVertexNormals(objmodel_ptr, 90.0);
	  }


	  //*** Para Textura: abrir malla de objeto a texturizar
	  objmodel_ptr1 = NULL;

	  if (!objmodel_ptr1)
	  {
		  objmodel_ptr1 = glmReadOBJ("./Mallas/bola.obj");
		  if (!objmodel_ptr1)
			  exit(0);

		  glmUnitize(objmodel_ptr1);
		  glmFacetNormals(objmodel_ptr1);
		  glmVertexNormals(objmodel_ptr1, 90.0);
	  }

	  objmodel_ptr2 = NULL;

	  if (!objmodel_ptr2)
	  {
		  objmodel_ptr2 = glmReadOBJ("./Mallas/mount.obj");
		  if (!objmodel_ptr2)
			  exit(0);

		  glmUnitize(objmodel_ptr2);
		  glmFacetNormals(objmodel_ptr2);
		  glmVertexNormals(objmodel_ptr2, 90.0);
	  }

	  objmodel_ptr3 = NULL;

	  if (!objmodel_ptr3)
	  {
		  objmodel_ptr3 = glmReadOBJ("./Mallas/ciclope.obj");
		  if (!objmodel_ptr3)
			  exit(0);

		  glmUnitize(objmodel_ptr3);
		  glmFacetNormals(objmodel_ptr3);
		  glmVertexNormals(objmodel_ptr3, 90.0);
	  }

	  objmodel_ptr4 = NULL;

	  if (!objmodel_ptr4)
	  {
		  objmodel_ptr4 = glmReadOBJ("./Mallas/arbolGrande.obj");
		  if (!objmodel_ptr4)
			  exit(0);

		  glmUnitize(objmodel_ptr4);
		  glmFacetNormals(objmodel_ptr4);
		  glmVertexNormals(objmodel_ptr4, 90.0);
	  }

	  objmodel_ptr5 = NULL;

	  if (!objmodel_ptr5)
	  {
		  objmodel_ptr5 = glmReadOBJ("./Mallas/16432_goat_v3_NEW.obj");
		  if (!objmodel_ptr5)
			  exit(0);

		  glmUnitize(objmodel_ptr5);
		  glmFacetNormals(objmodel_ptr5);
		  glmVertexNormals(objmodel_ptr5, 90.0);
	  }
 
	  objmodel_ptr6 = NULL;

	  if (!objmodel_ptr6)
	  {
		  objmodel_ptr6 = glmReadOBJ("./Mallas/WoodHouse.obj");
		  if (!objmodel_ptr6)
			  exit(0);

		  glmUnitize(objmodel_ptr6);
		  glmFacetNormals(objmodel_ptr6);
		  glmVertexNormals(objmodel_ptr6, 90.0);
	  }

	  objmodel_ptr7 = NULL;

	  if (!objmodel_ptr7)
	  {
		  objmodel_ptr7 = glmReadOBJ("./Mallas/arbusto.obj");
		  if (!objmodel_ptr7)
			  exit(0);

		  glmUnitize(objmodel_ptr7);
		  glmFacetNormals(objmodel_ptr7);
		  glmVertexNormals(objmodel_ptr7, 90.0);
	  }

	  //*** Para Textura: abrir archivo de textura
	  initialize_textures();
      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		switch (cAscii)
		{
		case (27):
			this->Close(); // Close Window!
		case ('a'):
			xIzq = true;
			break;
		case ('d'):
			xDer = true;
			break;
		case ('w'):
			yUp = true;
			break;
		case ('s'):
			yDown = true;
			break;
		case ('q'):
			zoomIn = true;
			break;
		case ('e'):
			zoomOut = true;
			break;
		default:
			break;
		}

	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		switch (cAscii)
		{
		case ('a'):
			xIzq = false;
			break;
		case ('d'):
			xDer = false;
			break;
		case ('w'):
			yUp = false;
			break;
		case ('s'):
			yDown = false;
			break;
		case ('q'):
			zoomIn = false;
			break;
		case ('e'):
			zoomOut = false;
			break;

		default:
			shader->disable();
		}
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     /*
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
	 */
     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
	 
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

