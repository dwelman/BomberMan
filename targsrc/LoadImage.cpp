
#include <main.hpp>

SDL_Texture *LoadImageToTexture(std::string file, SDL_Renderer *renderer)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = IMG_Load(file.c_str());

	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return texture;
}

SDL_Surface *LoadImageToSurface(std::string file, SDL_Renderer *renderer)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = IMG_Load(file.c_str());

	if (loadedImage != nullptr)
	{
		return loadedImage;
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return (nullptr);
}

GLuint		*LoadImageGL(std::string file, SDL_Renderer *renderer, GLuint &texture)
{
	SDL_Surface *loadedImage = LoadImageToSurface(file, renderer);
	int mode = loadedImage->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, loadedImage->w, loadedImage->h, 0, mode, GL_UNSIGNED_BYTE, loadedImage->pixels);
	//glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(loadedImage);
	return (&texture);
}
