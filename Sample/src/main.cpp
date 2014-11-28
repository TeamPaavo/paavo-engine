#include "Window.h"
#include "Rect.h"
#include "Triangle.h"
#include "Camera.h"
#include "Square.h"

#include <GL\glew.h>
#include "..\FreeImage\Dist\FreeImage.h"

int main()
{
	pv::Window win("Otsikko", 800, 600);
	GLfloat cameraX, cameraY, moveX;
	GLfloat rotate;

	GLfloat cameraXpostion = 100;
	GLfloat cameraYposition = 500;

	cameraX = 0.0f;
	cameraY = 0.0f;

	//pv::Rect sprite(-0.5f, 0.5f, 1.0f, 1.0f, win);

	//pv::Triangle sprite3(300, 100, 100, 100, 100, win);
	
	pv::Camera camera(win.getShader());

	camera.setCameraPosition(cameraXpostion, cameraYposition);

	pv::Rect sprite2(100, 0, 100, 100, win);







	rotate = 0.0f;

	while (win.update()){
		if (win.isKeyDown(pv::KEYBOARD::ESC))
			return 0;

		win.clearColor(0.2f, 0.2f, 0.2f, 1.0f);

		sprite2.draw();
		//sprite3.draw();



		camera.moveCamera(cameraX, cameraY);
		camera.rotateCamera(rotate);


		if (win.isKeyDown(pv::KEYBOARD::S))
			cameraY += 1.0f;

		if (win.isKeyDown(pv::KEYBOARD::W))
			cameraY -= 1.0f;

		if (win.isKeyDown(pv::KEYBOARD::A))
			cameraX -= 2.0f;

		if (win.isKeyDown(pv::KEYBOARD::D))
			cameraX += 2.0f;

		if (win.isKeyDown(pv::KEYBOARD::LEFT))
			rotate++;

		if (win.isKeyDown(pv::KEYBOARD::RIGHT))
			rotate--;

		
		win.swap();
	}

	return 0;
}
