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
    int cntBlack = 12;
    int cntWhite = 12;
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
                cntWhite--;
                whiteChecker.setPosition(toGraph(x), toGraph(y));
                window.draw(whiteChecker);
            }
            else if (f[y][x] == checker::BLACK)
            {
                cntBlack--;
                blackChecker.setPosition(toGraph(x), toGraph(y));
                window.draw(blackChecker);
            }
            else if (f[y][x] == checker::WHITE_KING)
            {
                cntWhite--;
                whiteCheckerKing.setPosition(toGraph(x), toGraph(y));
                window.draw(whiteCheckerKing);
            }
            else if (f[y][x] == checker::BLACK_KING)
            {
                cntBlack--;
                blackCheckerKing.setPosition(toGraph(x), toGraph(y));
                window.draw(blackCheckerKing);
            }
        }
    }

    for (int i = 1; i <= cntWhite; i++) {
        blackChecker.setPosition(HEIGHT + PADDING * 2, i * HEIGHT / 8 / 4);
        window.draw(blackChecker);
    }

    for (int i = 1; i <= cntBlack; i++) {
        whiteChecker.setPosition(HEIGHT + PADDING * 2, HEIGHT - i * HEIGHT / 8 / 4);
        window.draw(whiteChecker);
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

    Font _font;
    if (!_font.loadFromFile("arial.ttf")) {
        cout << "Не удалось загрузить шрифт!" << endl;
        assert(false);
    }

    Text _text;
    _text.setFont(_font);
    _text.setString("A      B      C      D      E      F      G      H");
    _text.setCharacterSize(43);
    _text.setFillColor(Color::Black);

    FloatRect textRect = _text.getLocalBounds();
    _text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    _text.setPosition((WIDTH / 2-PADDING), (PADDING / 2-5));
    window.draw(_text);

    for (int i = 1; i <= SZ; i++) {
        Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cout << "Не удалось загрузить шрифт!" << endl;
            assert(false);
        }

        Text text;
        text.setFont(font);
        text.setString(to_string(SZ+1-i));
        text.setCharacterSize(46);
        text.setFillColor(Color::Black);

        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition((20), (PADDING * i * 2));
        window.draw(text);
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