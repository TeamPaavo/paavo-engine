#ifndef TGL_TEXTUREMANAGER_H
#define TGL_TEXTUREMANAGER_H

#include <GL/glew.h>
#include <FreeImage.h>
#include <map>
#include <string>
#include <utility>

namespace pv {

	/**
	 * Singleton class for texture management.
	 * Keeps track of textures in map. Key is filename and value is GLuint id of the texture.
	 * Usable only in internals of the library, no api outside.
	 */

	class TextureManager
	{
	public:
		static TextureManager* getInstance();
		virtual ~TextureManager();

		GLuint load(const std::string& filename);
		bool unload(const std::string& filename);
		bool bind(const std::string& filename);
		void unloadAll();

	protected:
		TextureManager();
		TextureManager(const TextureManager& texturemanager);
		TextureManager& operator=(const TextureManager& texturemanager);

		static TextureManager* _instance;

		std::map<std::string, GLuint> _textureMap;
	};

} // namespace tgl

#endif // TGL_TEXTUREMANAGER_H