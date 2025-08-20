#include <cstring> // for memset ?
#include <iostream>

#include "myassert.h"
#include "resource.h"
#include "gameconf.h"

namespace res {
	namespace texture {
		GLenum normalWrap{GL_REPEAT};
		GLenum normalFilter{GL_NEAREST};

		void set_normal_load(GLenum _normalWrap, GLenum _normalFilter) {
			normalWrap = _normalWrap;
			normalFilter = _normalFilter;
		}

		void load(const char* textureFileName, GLuint* _textureID, GLenum wrap, GLenum filter) {
			sf::Image loadTexture;
			std::string currentPath = GetTexturesPath() + textureFileName;
			assert(loadTexture.loadFromFile(currentPath.c_str()));

			glGenTextures(1, _textureID);
			glBindTexture(GL_TEXTURE_2D, *_textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadTexture.getSize().x, loadTexture.getSize().y,
										0, GL_RGBA, GL_UNSIGNED_BYTE, loadTexture.getPixelsPtr());
			
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		void normal_load(const char* textureFileName, GLuint* _textureID) {
			load(textureFileName, _textureID, normalWrap, normalFilter);
		}
	};
};

