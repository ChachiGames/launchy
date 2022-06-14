#pragma once
#include <SDL.h>
#include <string>

class SDLView;
//This texture class will only be used by SDL classes so
//we won't bother with interfaces
class Texture
{
    public:
        //Initializes variables
        Texture(SDLView* view);

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool LoadFromFile( std::string path );
        
        //Creates image from font string
        bool LoadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Set color modulation
        void SetColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void SetBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void SetAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void Render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int GetWidth();
        int GetHeight();

    private:
        //The actual hardware texture
        SDL_Texture* _texture;

        //Image dimensions
        int _width;
        int _height;

        SDLView* _view;
};