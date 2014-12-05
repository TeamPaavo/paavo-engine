#include "Window.h"
#include "Rect.h"
#include "Triangle.h"
#include "Camera.h"
#include "Square.h"
#include "Shader.h"
#include "Sprite.h"
#include "Mouse.h"

#include <GL\glew.h>
#include "..\FreeImage\Dist\FreeImage.h"

int main()
{
	pv::Window win("Otsikko", 800, 600);
	GLfloat cameraX, cameraY, moveX;
	GLfloat rotate;

	GLfloat scaleX, scaleY, scaleZ;

	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;

	GLfloat cameraXpostion = 100;
	GLfloat cameraYposition = 500;

	cameraX = 0.0f;
	cameraY = 0.0f;

	//pv::Rect sprite(-0.5f, 0.5f, 1.0f, 1.0f, win);

	//pv::Triangle sprite3(300, 100, 100, 100, 100, win);
	
	pv::Camera camera(win.getShader("colorshader"));

	camera.setCameraPosition(cameraXpostion, cameraYposition);

	//pv::Sprite sprite2(100, 0, 100, 100, win);







	rotate = 0.0f;

	while (win.update()){
		if (win.isKeyDown(pv::KEYBOARD::ESC))
			return 0;

		win.clearColor(0.2f, 0.2f, 0.2f, 1.0f);

		//sprite2.draw();
		//sprite3.draw();



		camera.moveCamera(cameraX, cameraY);
		camera.rotateCamera(rotate);
		camera.scaleCamera(scaleX, scaleY, scaleZ);

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

		if (win.isKeyDown(pv::KEYBOARD::UP))
		{
			scaleX += 0.1f;
			scaleY += 0.05f;
			scaleZ += 0.025f;
		}

		if (win.isKeyDown(pv::KEYBOARD::DOWN))
		{
			scaleX -= 0.05f;
			scaleY -= 0.075f;
			scaleZ -= 0.025f;
		}
		
		win.swap();
	}

	return 0;
}
