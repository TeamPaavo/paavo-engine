#include "Window.h"
#include "Rect.h"
#include "Triangle.h"
#include "Camera.h"

#include <GL\glew.h>
#include "..\FreeImage\Dist\FreeImage.h"

int main()
{
	pv::Window win("Otsikko", 800, 600);
	

	//pv::Rect sprite(-0.5f, 0.5f, 1.0f, 1.0f, win);
	pv::Rect sprite2(200, 100, 100, 100, win);
	//pv::Triangle sprite3(300, 100, 100, 100, 100, win);
	
	pv::Camera camera(win.getShader());

	GLfloat cameraX, cameraY;
	cameraX = 0.0f;
	cameraY = 0.0f;


	while (win.update()){
		win.clearColor(0.2f, 0.2f, 0.2f, 1.0f);
		sprite2.draw();
		//sprite3.draw();

		camera.moveCamera(cameraX, cameraY);


		//window.getInput(input);
		//if (input == enum_aerrow_dowm)
		//	blockinson.move(left);

		cameraY += 0.2f;
		cameraX += 0.3f;

		win.swap();
	}

	return 0;
}
