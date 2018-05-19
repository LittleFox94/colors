#include "../include/resizableimage.h"

ResizableImage::ResizableImage(string file, unsigned int drawWidth, unsigned int drawHeight)
{
    sf::Image image;
    image.loadFromFile(file);

    if(
        (image.getSize().x != drawWidth  && image.getSize().x % 2 != 1) ||
        (image.getSize().y != drawHeight && image.getSize().y % 2 != 1))
    {
        cout << "Not a resizable image!" << endl;
    }

    sf::Image tmpImage;
    tmpImage.create(drawWidth, drawHeight);

    _image = new sf::Texture();
    _image->create(drawWidth, drawHeight);

    bool resizeX = image.getSize().x != drawWidth;
    bool resizeY = image.getSize().y != drawHeight;

    if(resizeX)
    {
        for(unsigned int y = 0; y < image.getSize().y; y++)
        {
            for(unsigned int x = 0; x < (image.getSize().x - 1) / 2; x++)
            {
                tmpImage.setPixel(x, y, image.getPixel(x, y));
            }

            for(unsigned int x = (image.getSize().x - 1) / 2; x < drawWidth - (image.getSize().x - 1) / 2; x++)
            {
                tmpImage.setPixel(x, y, image.getPixel(((image.getSize().x - 1) / 2) + 1, y));
            }

            int difference = drawWidth - image.getSize().x;
            for(unsigned int x = drawWidth - (image.getSize().x - 1) / 2; x < drawWidth; x++)
            {
                tmpImage.setPixel(x, y, image.getPixel(x - difference, y));
            }
        }
    }

    _image->update(tmpImage.getPixelsPtr());

    _image->setSmooth(false);
    _sprite = new sf::Sprite();
    _sprite->setTexture(*_image);
}

ResizableImage::~ResizableImage()
{
    delete _sprite;
    delete _image;
}

void ResizableImage::Draw(sf::RenderTarget *target, int x, int y)
{
    _sprite->setPosition(x, y);
    target->draw(*_sprite);
}
