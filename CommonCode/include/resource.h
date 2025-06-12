#pragma once

#include "glcore.hpp"

namespace res {
	namespace texture {
		void set_normal_load(GLenum _normalWrap, GLenum _normalFilter);
		void load(const char* textureFileName, GLuint* _textureID, GLenum wrap, GLenum filter);
		void normal_load(const char* textureFileName, GLuint* _textureID);
	};
};

