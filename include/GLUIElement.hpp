#pragma once
#include "UIElement.hpp"
class GLUIElement :
	public UIElement
{
private:
	float 						vertices[16];
	Uint32						glTexture;
	GLuint						texcoord;
	GLuint						location;
	GLuint						vao;
	GLuint						vbo;
	GLuint						ebo;
	GLuint						uvBuffer;



public:
	bool						glTextureSet;
	static GLuint				shader;

	GLUIElement( int _x, int _y, int w, int h);
	GLUIElement();
	~GLUIElement();

	float				*GetVertices();
	void				SetGLTexture(GLuint shader, SDL_Renderer * ren, std::string path_to_texture);
	GLuint				GetGLTexture();
	void				draw(GLuint shader);
};

