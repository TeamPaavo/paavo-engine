#include "../include/TextureManager.h"

using namespace pv;

TextureManager* TextureManager::_instance = 0;

TextureManager* TextureManager::getInstance()
{
	if (!_instance) {
		_instance = new TextureManager();
	}
	return _instance;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	unloadAll();
	_instance = 0;
}

GLuint TextureManager::load(const std::string& filename)
{
	if (_textureMap.find(filename) == _textureMap.end())
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP* image(0);
		BYTE* imagedata(0);
		unsigned int width(0), height(0);
		GLuint texId;

		fif = FreeImage_GetFileType(filename.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename.c_str());
		if (fif == FIF_UNKNOWN) {
			printf("fif unknown\n");
			exit(1);
		}

		if (FreeImage_FIFSupportsReading(fif))
			image = FreeImage_Load(fif, filename.c_str());

		if (!image) {
			printf("kuvan lataus ei onnistunut\n");
			exit(1);
		}

		imagedata = FreeImage_GetBits(image);
		width = FreeImage_GetWidth(image);
		height = FreeImage_GetHeight(image);

		if ((imagedata == 0) || (width == 0) || (height == 0)) {
			printf("imagedata mattaa\n");
			exit(1);
		}

		//printf("%d, %d\n", width, height);

		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, imagedata);
		FreeImage_Unload(image);

		_textureMap[filename] = texId;

		return texId;
	} else {
		return _textureMap[filename];
	}
}

bool TextureManager::unload(const std::string& filename)
{
	if (_textureMap.find(filename) != _textureMap.end()) {
		glDeleteTextures(1, &(_textureMap[filename]));
		_textureMap.erase(filename);
		return true;
	}
	else {
		return false;
	}
}

bool TextureManager::bind(const std::string& filename)
{
	if (_textureMap.find(filename) != _textureMap.end()) {
		glBindTexture(GL_TEXTURE_2D, _textureMap[filename]);
		return true;
	}
	else {
		return false;
	}
}

void TextureManager::unloadAll()
{
	std::map<std::string, GLuint>::iterator it = _textureMap.begin();

	while (it != _textureMap.end()) {
		unload(it->first);
	}

	_textureMap.clear();
}