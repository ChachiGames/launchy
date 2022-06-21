#include "Texture.h"
#include "SDL_View.h"

#include <SDL_Image.h>
#include <iostream>

//Initializes variables
Texture::Texture(SDLView* view): _view(view)
{

}

//Deallocates memory
Texture::~Texture()
{
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
}

//Loads image at specified path
bool Texture::LoadFromFile( std::string path )
{
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface( _view->GetRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            return false;
        }
        _texture = newTexture;
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    if(SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height) != 0)
    {
        printf( "Unable to detect texture size from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return false;
    }
    return true;
}

//Creates image from font string
bool Texture::LoadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    return false;
}

//Set color modulation
void Texture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{

}

//Set blending
void Texture::SetBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode(_texture, blending);
}

//Set alpha modulation
void Texture::SetAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod(_texture, alpha);
}

//Renders texture at given point
void Texture::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect dest{0,0,_width,_height};
    SDL_RenderCopyEx(_view->GetRenderer(),_texture,clip,&dest,angle,center,flip);
}

//Gets image dimensions
int Texture::GetWidth(){return _width;}
int Texture::GetHeight(){return _height;}

void Texture::SetWidth(int w) {_width = w;}
void Texture::SetHeight(int h) {_height = h;}