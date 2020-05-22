#ifndef IMAGES_H
#define IMAGES_H

#include <SFML/Graphics.hpp>

class Images
{
    public:
        Images();
        Images(const char* pointer);
        sf::Sprite sprite;
        sf::Texture texture;
        void loadImage(const char* pointer);
};

#endif // IMAGES_H
