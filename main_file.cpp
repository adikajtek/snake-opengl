/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"

#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
//#include "objloader.h"
//#include "libs.h"

#include "myapple.h"
#include "mySnake.h"
#include "mycylinder.h"


float speed_x=0;
float speed_y=0;
float aspectRatio=1;

//float* c1 = myCubeC1;
//float* c2 = myCubeC2;
//float* c3 = myCubeC3;

//float* c1 = myTeapotC1;
//float* c2 = myTeapotC2;
//float* c3 = myTeapotC3;


ShaderProgram *sp;





int myFloorVertexCount = 6;

float myFloorVertices[] = {
	1.0f,-1.0f,-1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,1.0f,

	1.0f,-1.0f,-1.0f,1.0f,
	1.0f, 1.0f,-1.0f,1.0f,
	-1.0f, 1.0f,-1.0f,1.0f,
};

float myFloorColors[] = {
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
};
float myFloorC1[] = {
	//Ściana 1
					1.000000f,-0.000000f,0.000000f,0.000000f,
					1.000000f,-0.000000f,0.000000f,0.000000f,
					1.000000f,-0.000000f,0.000000f,0.000000f,
					1.000000f,-0.000000f,0.000000f,0.000000f,
					1.000000f,-0.000000f,0.000000f,0.000000f,
					1.000000f,-0.000000f,0.000000f,0.000000f,
};
float myFloorC2[] = {
	//Ściana 1
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
	-0.000000f,-1.000000f,-0.000000f,0.000000f,
};
float myFloorC3[] = {
	//Ściana 1
	0.000000f,0.000000f,-1.000000f,0.000000f,
	0.000000f,0.000000f,-1.000000f,0.000000f,
	0.000000f,0.000000f,-1.000000f,0.000000f,
	0.000000f,-0.000000f,-1.000000f,0.000000f,
	0.000000f,-0.000000f,-1.000000f,0.000000f,
	0.000000f,-0.000000f,-1.000000f,0.000000f,
};

float myFloorNormals[] = {
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
};

float myFloorVertexNormals[] = {
	1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	-1.0f,-1.0f,-1.0f,0.0f,

	1.0f,-1.0f,-1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
};

float myFloorTexCoords[] = {
	1.0f, 1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f, 1.0f, 1.0f,0.0f, 0.0f,0.0f,
};


//tylko podoga ma wstawione tekstury narazie

//Odkomentuj, żeby rysować podlog

float* c1 = myFloorC1;
float* c2 = myFloorC2;
float* c3 = myFloorC3;

float* vertices = myFloorVertices;
float* normals = myFloorVertexNormals;
float* texCoords = myFloorTexCoords;
float* colors = myFloorColors;
int vertexCount = myFloorVertexCount;

/*
//Odkomentuj, żeby rysować jablko
float* c1 = myappleC1;
float* c2 = myappleC2;
float* c3 = myappleC3;

float* vertices = myappleVertices;
float* normals = myappleNormals;
float* texCoords = myappleTexCoords;
int vertexCount = myappleVertexCount;
*/
//Odkomentuj, żeby rysować snakw
/*
float* c1 = mySnakeC1;
float* c2 = mySnakeC2;
float* c3 = mySnakeC3;

float* vertices = mySnakeVertices;
float* normals = mySnakeNormals;
float* texCoords = mySnakeTexCoords;
int vertexCount = mySnakeVertexCount;
*/
//Odkomentuj, żeby rysować czajnik
//float* vertices1 = myTeapotVertices;
//float* normals1 = myTeapotVertexNormals;
//float* texCoords1 = myTeapotTexCoords;
//float* colors1 = myTeapotColors;
//int vertexCount1 = myTeapotVertexCount;

GLuint tex0;
GLuint tex1;





//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}


GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
    tex0 = readTexture("planks.png");
    tex1 = readTexture("planksNormal.png");

 

}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V=glm::lookAt(
         glm::vec3(0, 0, -4),
         glm::vec3(0,0,0),
         glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz widoku

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

    glm::mat4 M=glm::mat4(1.0f);
	M=glm::rotate(M,angle_y,glm::vec3(1.0f,0.0f,0.0f)); //Wylicz macierz modelu
	M=glm::rotate(M,angle_x,glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz modelu

    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	//glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("c1"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("c1"), 4, GL_FLOAT, false, 0, c1); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("c2"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("c2"), 4, GL_FLOAT, false, 0, c2); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("c3"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("c3"), 4, GL_FLOAT, false, 0, c3); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt

    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	//glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("c1"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("c2"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("c3"));  //Wyłącz przesyłanie danych do atrybutu normal

	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{

	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1500, 1500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla

	float angle_x=0; //Aktualny kąt obrotu obiektu
	float angle_y=0; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle_x+=speed_x*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        angle_y+=speed_y*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        glfwSetTime(0); //Zeruj timer
		drawScene(window,angle_x,angle_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
