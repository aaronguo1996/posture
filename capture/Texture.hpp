#pragma once

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <gl/glew.h>

class Texture
{
	GLuint m_id;
	GLuint m_attachment;
	GLenum internalFormat;
public:
	GLenum type;
	GLenum format;
	GLsizei width;
	GLsizei height;

	Texture(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type) {
		glGenTextures(1, &m_id);

		this->width = width;
		this->height = height;
		this->internalFormat = internalFormat;
		this->format = format;
		this->type = type;
	}

	~Texture() {
		glDeleteTextures(1, &m_id);
	}

	Texture* Create(GLuint unit = 0, const GLvoid* data = nullptr)
	{
		m_attachment = unit;

		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//if(glClearTexImage) {
		//	GLuint clearColor = 0;
		//	glClearTexImage(GL_TEXTURE_2D, 0, format, type, &clearColor);
		//}
		//else {

		//}

		return this;
	}

	void Update(const GLvoid* data) {
		if (!data) return;
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, type, data);
	}

	GLuint id() const { return m_id; };
	GLuint attachment() const { return m_attachment; };
};

#endif