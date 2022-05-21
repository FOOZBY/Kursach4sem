#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    int n, m;
    bool first_player_move = 1;
    cout << "Input n: ";
    cin >> n;
    cout << "Input m: ";
    cin >> m;
    cout << "Input 'X' if you want to play as X, or 'O' if as O: ";
    bool first_player_is_X = 1;
    char first_player_char;
    cin >> first_player_char;
    if (first_player_char == 'O')
        first_player_is_X = 0;
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
            field[i][j].x = 100*i;
            field[i][j].y = 100*j;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << field[i][j].x<<"\t";
            cout << field[i][j].y<<endl;
        }
    }


    while (window.isOpen())
    {
        Vector2i mousepos = Mouse::getPosition(window);
        int mouse_x = mousepos.x / 100;
        int mouse_y = mousepos.y / 100;
        cout << mouse_x << "\t" << mouse_y << endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                {
                    if (mouse_x <= n && mouse_y <= m && mouse_y >-1 && mouse_x>-1 && !field[mouse_x][mouse_y].busy)
                    {
                        if (first_player_move)
                        {
                            if (first_player_is_X)
                                field[mouse_x][mouse_y].is_X = 1;
                            else
                                field[mouse_x][mouse_y].is_X = 0;
                            field[mouse_x][mouse_y].busy = 1;
                        }
                        else
                        {
                            if (first_player_is_X)
                                field[mouse_x][mouse_y].is_X = 0;
                            else
                                field[mouse_x][mouse_y].is_X = 1;
                            field[mouse_x][mouse_y].busy = 1;
                        }
                        first_player_move = !first_player_move;
                    }
                }
                else if (event.key.code == Mouse::Right)
                {
                    if (mouse_x <= n && mouse_y <= m && mouse_y > -1 && mouse_x > -1)
                        field[mouse_x][mouse_y].busy = 0;
                }

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
                sprite.setPosition(field[i][j].x, field[i][j].y);
                window.draw(sprite);
            }
        }
        
        window.display();
    }

    return 0;
}