#include "../include/resizableimage.h"

ResizableImage::ResizableImage(string file, unsigned int drawWidth, unsigned int drawHeight)
{
    sf::Image image;
    image.LoadFromFile(file);

    if((image.GetWidth() != drawWidth && image.GetWidth() % 2 != 1) || (image.GetHeight() != drawHeight && image.GetHeight() % 2 != 1))
    {
        cout << "Not a resizable image!" << endl;
    }

    _image = new sf::Image(drawWidth, drawHeight);

    bool resizeX = image.GetWidth() != drawWidth;
    bool resizeY = image.GetHeight() != drawHeight;

    if(resizeX)
    {
        for(unsigned int y = 0; y < image.GetHeight(); y++)
        {
            for(unsigned int x = 0; x < (image.GetWidth() - 1) / 2; x++)
            {
                _image->SetPixel(x, y, image.GetPixel(x, y));
            }

            for(unsigned int x = (image.GetWidth() - 1) / 2; x < drawWidth - (image.GetWidth() - 1) / 2; x++)
            {
                _image->SetPixel(x, y, image.GetPixel(((image.GetWidth() - 1) / 2) + 1, y));
            }

            int difference = drawWidth - image.GetWidth();
            for(unsigned int x = drawWidth - (image.GetWidth() - 1) / 2; x < drawWidth; x++)
            {
                _image->SetPixel(x, y, image.GetPixel(x - difference, y));
            }
        }
    }

    _image->SetSmooth(false);
    _sprite = new sf::Sprite();
    _sprite->SetImage(*_image);
}

ResizableImage::~ResizableImage()
{
    delete _sprite;
    delete _image;
}

void ResizableImage::Draw(sf::RenderTarget *target, int x, int y)
{
    _sprite->SetPosition(x, y);
    target->Draw(*_sprite);
}
