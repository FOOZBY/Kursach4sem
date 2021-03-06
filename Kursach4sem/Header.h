#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int getnum()
{
    int value;
    while (!(cin >> value))
    { //Since value is a int, (cin >> value) will be true only if the user enters a valid value that can be put inside a int
        cout << "Please enter a valid value:" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    cin.ignore(32767, '\n');
    return value;
}

struct cell
{
    bool is_X = 0, is_O = 0;
    bool busy = 0;
    int x, y;
};

string won(cell** field, int n, int m, int x, int y)
{
    if (x >= 1 && y >= 1 && x < n - 1 && y < m - 1)
    {
        if (field[x - 1][y - 1].is_X && field[x][y].is_X && field[x + 1][y + 1].is_X)
            return "X";
        if (field[x - 1][y - 1].is_O && field[x][y].is_O && field[x + 1][y + 1].is_O)
            return "O";
        if (field[x + 1][y - 1].is_X && field[x][y].is_X && field[x - 1][y + 1].is_X)
            return "X";
        if (field[x + 1][y - 1].is_O && field[x][y].is_O && field[x - 1][y + 1].is_O)
            return "O";
    }
    if (y >= 1 && y < m - 1)
    {
        if (field[x][y - 1].is_X && field[x][y].is_X && field[x][y + 1].is_X)
            return "X";
        if (field[x][y - 1].is_O && field[x][y].is_O && field[x][y + 1].is_O)
            return "O";
    }
    if (x >= 1 && x < n - 1)
    {
        if (field[x - 1][y].is_X && field[x][y].is_X && field[x + 1][y].is_X)
            return "X";
        if (field[x - 1][y].is_O && field[x][y].is_O && field[x + 1][y].is_O)
            return "O";
    }

    if (x >= 2 && y >= 2)
    {
        if (field[x - 2][y - 2].is_X && field[x - 1][y - 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x - 2][y - 2].is_O && field[x - 1][y - 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (y >= 2)
    {
        if (field[x][y - 2].is_X && field[x][y - 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x][y - 2].is_O && field[x][y - 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (x < n - 2 && y >= 2)
    {
        if (field[x + 2][y - 2].is_X && field[x + 1][y - 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x + 2][y - 2].is_O && field[x + 1][y - 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (x < n - 2)
    {
        if (field[x + 2][y].is_X && field[x + 1][y].is_X && field[x][y].is_X)
            return "X";
        if (field[x + 2][y].is_O && field[x + 1][y].is_O && field[x][y].is_O)
            return "O";
    }
    if (x < n - 2 && y < m - 2)
    {
        if (field[x + 2][y + 2].is_X && field[x + 1][y + 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x + 2][y + 2].is_O && field[x + 1][y + 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (y < m - 2)
    {
        if (field[x][y + 2].is_X && field[x][y + 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x][y + 2].is_O && field[x][y + 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (x >= 2 && y < m - 2)
    {
        if (field[x - 2][y + 2].is_X && field[x - 1][y + 1].is_X && field[x][y].is_X)
            return "X";
        if (field[x - 2][y + 2].is_O && field[x - 1][y + 1].is_O && field[x][y].is_O)
            return "O";
    }
    if (x >= 2)
    {
        if (field[x - 2][y].is_X && field[x - 1][y].is_X && field[x][y].is_X)
            return "X";
        if (field[x - 2][y].is_O && field[x - 1][y].is_O && field[x][y].is_O)
            return "O";
    }
    return "no";
};

bool game_is_life()
{
    system("cls");
    int winXSize = 1000, winYSize = 800;
    int cellSize = 100;
    int n = 3, m = 3, moves = 0;
    char first_player_char;
    while (true)
    {
        cout << "n*m must be equal or move than 5.\n";
        cout << "Input n (1 - " << winYSize / cellSize << "): ";
        n = getnum();
        cout << "Input m (1 - " << winXSize / cellSize << "): ";
        m = getnum();
        if ((n > 0) && (n <= (winYSize / cellSize)) && (m > 0) && (m <= (winXSize / cellSize)) && ((n * m) >= 5))
            break;
        cout << "Error values of n and m! Repeat enter.\n";
    }
    cout << "Input First player char('X' if first is X and any other if O): ";
    cin >> first_player_char;


    sf::RenderWindow window(sf::VideoMode(winXSize, winYSize), "X0 Game!");
    
    bool first_player_move = 1;
    bool first_player_is_X = 1;
    if (first_player_char != 'X')
        first_player_is_X = 0;
    bool game = 1;
    string winner;

    Texture texture, wintexture;
    Sprite sprite, winsprite;

    cell** field = new cell * [n];
    for (int i = 0; i < n; i++)
    {
        field[i] = new cell[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            field[i][j].x = cellSize * j;
            field[i][j].y = cellSize * i;
        }
    }

    while (window.isOpen())
    {
        Vector2i mousepos = Mouse::getPosition(window);
        int mouse_i = mousepos.y / cellSize;
        int mouse_j = mousepos.x / cellSize;
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                window.close();
                break;
            }
            case Event::MouseButtonPressed:
            {
                if (game)
                {
                    if (event.key.code == Mouse::Left)
                    {
                        if (mouse_i < n && mouse_j < m && mouse_j > -1 && mouse_i > -1 && !field[mouse_i][mouse_j].busy)
                        {
                            if (first_player_move)
                            {
                                if (first_player_is_X)
                                    field[mouse_i][mouse_j].is_X = 1;
                                else
                                    field[mouse_i][mouse_j].is_O = 1;
                                field[mouse_i][mouse_j].busy = 1;
                            }
                            else
                            {
                                if (first_player_is_X)
                                    field[mouse_i][mouse_j].is_O = 1;
                                else
                                    field[mouse_i][mouse_j].is_X = 1;
                                field[mouse_i][mouse_j].busy = 1;
                            }
                            first_player_move = !first_player_move;
                            moves++;

                            if (won(field, n, m, mouse_i, mouse_j) == "X")
                            {
                                winner = "X";
                                game = 0;
                                break;
                            }
                            if (won(field, n, m, mouse_i, mouse_j) == "O")
                            {
                                winner = "O";
                                game = 0;
                                break;
                            }
                            if (moves == n * m)
                            {
                                winner = "draw";
                                game = 0;
                                break;
                            }
                        }
                    }
                }
                break;
            }
            default:
                break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//???? ???, ?? ????????????? ????
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//???? ??????, ?? ??????? ?? ????

        window.clear();
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!field[i][j].busy)
                    texture.loadFromFile("void.png");
                else if (field[i][j].is_X)
                    texture.loadFromFile("X.png");
                else if (field[i][j].is_O)
                    texture.loadFromFile("O.png");
                sprite.setTexture(texture);
                sprite.setPosition(field[i][j].x, field[i][j].y);
                window.draw(sprite);
            }
        }
        if (!game)
        {
            if ((winner == "X" && first_player_is_X) || (winner == "O" && !first_player_is_X))
                wintexture.loadFromFile("firstplayerwon.png");
            if ((winner == "O" && first_player_is_X) || (winner == "X" && !first_player_is_X))
                wintexture.loadFromFile("secondplayerwon.png");
            if (winner == "draw")
                wintexture.loadFromFile("draw.png");
            winsprite.setTexture(wintexture);
            winsprite.setPosition(200, 250);
            window.draw(winsprite);
        }
        window.display();
    }
    for (int i = 0; i < n; i++)
    {
        delete[] field[n];
    }
    delete[] field;
}

void game_running()
{
    if (game_is_life())
        game_running();
}