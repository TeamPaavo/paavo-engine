#pragma once

#include <Windows.h>
#include <iostream>

class Mouse
{
public:
	Mouse();
	~Mouse();
	POINT checkpos();

private:
	POINT p;
};

