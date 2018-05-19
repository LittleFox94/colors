#ifndef RESIZABLEIMAGE_H_INCLUDED
#define RESIZABLEIMAGE_H_INCLUDED

#include "main.h"

class ResizableImage
{
    public:
        ResizableImage(string file, unsigned int drawWidth, unsigned int drawHeight);
        virtual ~ResizableImage();

        void Draw(sf::RenderTarget *target, int x, int y);
    protected:
    private:
        sf::Texture *_image;
        sf::Sprite *_sprite;
};

#endif // RESIZABLEIMAGE_H_INCLUDED
