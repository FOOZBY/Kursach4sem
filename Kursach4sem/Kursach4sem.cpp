#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    int n, m;
    cout << "Input n: ";
    cin >> n;
    cout << "Input m: ";
    cin >> m;
    Texture texture;
    Sprite sprite;
    struct cell
    {
        bool is_X = 0;
        bool busy = 0;
        int x, y;
    };
    cell** field = new cell* [n];
    for (int i = 0; i < n; i++)
    {
        field[i] = new cell[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            field[i][j].x = 10 + i * 100;
            field[i][j].y = 10 + j * 100;
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!field[i][j].busy)
                    texture.loadFromFile("void.png");
                else if (field[i][j].is_X)
                    texture.loadFromFile("X.png");
                else
                    texture.loadFromFile("O.png");
                sprite.setTexture(texture);
                window.draw(sprite);
            }
        }
        
        window.display();
    }

    return 0;
}