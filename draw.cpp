#include "allitems.h"

int toGraph(int n)
{
    return n * 100 + PADDING;
}
int toNum(int n)
{
    return (n - PADDING) / 100;
}

void Draw(RenderWindow& window, RectangleShape& whiteCell, RectangleShape& blackCell, RectangleShape& whiteChecker, RectangleShape& blackChecker, RectangleShape& whiteCheckerKing, RectangleShape& blackCheckerKing, vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect) {
    for (int x = 0; x < SZ; x++) {
        for (int y = 0; y < SZ; y++) {
            if (y % 2 != x % 2) {
                blackCell.setPosition(toGraph(x), toGraph(y));
                window.draw(blackCell);
            }
            else {
                whiteCell.setPosition(toGraph(x), toGraph(y));
                window.draw(whiteCell);
            }
            if (f[y][x] == checker::WHITE)
            {
                whiteChecker.setPosition(toGraph(x), toGraph(y));
                window.draw(whiteChecker);
            }

            else if (f[y][x] == checker::BLACK)
            {
                blackChecker.setPosition(toGraph(x), toGraph(y));
                window.draw(blackChecker);
            }
            else if (f[y][x] == checker::WHITE_KING)
            {
                whiteCheckerKing.setPosition(toGraph(x), toGraph(y));
                window.draw(whiteCheckerKing);
            }
            else if (f[y][x] == checker::BLACK_KING)
            {
                blackCheckerKing.setPosition(toGraph(x), toGraph(y));
                window.draw(blackCheckerKing);
            }
        }
    }

    for (auto i : yellowRect) {
        auto x = RectangleShape(Vector2f(100, 100));
        x.setFillColor(Color(120, 120, 0, 60));
        x.setPosition(toGraph(i.first), toGraph(i.second));

        window.draw(x);
    }
    for (auto i : greenRect) {
        auto x = RectangleShape(Vector2f(100, 100));
        x.setFillColor(Color(0, 255, 0, 60));
        x.setPosition(toGraph(i.first), toGraph(i.second));

        window.draw(x);
    }
    for (auto i : redRect) {
        auto x = RectangleShape(Vector2f(100, 100));
        x.setFillColor(Color(255, 0, 0, 60));
        x.setPosition(toGraph(i.first), toGraph(i.second));

        window.draw(x);
    }
}

void initTexture(Texture& textureWhite, Texture& textureBlack, Texture& textureWhiteKing, Texture& textureBlackKing, RectangleShape& whiteCell, RectangleShape& blackCell, RectangleShape& whiteChecker, RectangleShape& blackChecker, RectangleShape& whiteCheckerKing, RectangleShape& blackCheckerKing, Texture& texture) {
    blackCell.setFillColor(Color(98, 154, 204));
    whiteCell.setFillColor(Color(199, 207, 226));

    auto operation = textureWhite.loadFromFile("whitecell.png");
    operation = textureBlack.loadFromFile("blackcell.png");
    operation = textureWhiteKing.loadFromFile("whitedamka.png");
    operation = textureBlackKing.loadFromFile("blackdamka.png");
    whiteChecker.setTexture(&textureWhite);
    blackChecker.setTexture(&textureBlack);
    whiteCheckerKing.setTexture(&textureWhiteKing);
    blackCheckerKing.setTexture(&textureBlackKing);

    blackCell.setOutlineThickness(5);
    whiteCell.setOutlineThickness(5);

    blackCell.setOutlineColor(Color::Black);
    whiteCell.setOutlineColor(Color::Black);

    if (!texture.loadFromFile("restart4.jpg")) {
        cout << "Не удалось загрузить изображение!" << endl;
        assert(false);
    }
}

void setup(vector<vector<int>>& f) {
    for (int x = 0; x < SZ; x++)
    {
        for (int y = 0; y < SZ; y++)
        {
            if (y >= 5 && (y % 2) != (x % 2))
            {
                f[y][x] = checker::WHITE;
            }
            else if (y <= 2 && (y % 2) != (x % 2))
            {
                f[y][x] = checker::BLACK;
            }
            else
            {
                f[y][x] = checker::NONE;
            }
        }
    }
}