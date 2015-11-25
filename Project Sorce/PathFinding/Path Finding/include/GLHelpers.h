#pragma once



namespace reng {

class Texture
{
public:
	int width;
	int height;
	int format;
};


class GLHelpers
{
public:
	static void TurnOnDebugLogging();

private:
	GLHelpers() {}; // Abstract class
};

}