#include "allitems.h"

int toGraph(int n)
{
    return n * 100 + PADDING;
}
int toNum(int n)
{
    return (n - PADDING) / 100;
}

void Draw(RenderWindow& window, RectangleShape& whiteCell, RectangleShape& blackCell, RectangleShape& whiteChecker, RectangleShape& blackChecker, RectangleShape& whiteCheckerKing, RectangleShape& blackCheckerKing, Texture& texture, Texture& textureExit, Texture& textureBack, vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect) {
    
    Texture backFon;
    if (!backFon.loadFromFile("background.png")) {
        cout << "Не удалось загрузить изображение!" << endl;
        assert(false);
    }
    Sprite spriteFon;
    spriteFon.setTexture(backFon);
    spriteFon.setPosition(0, 0);
    window.draw(spriteFon);

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition((WIDTH-5), HEIGHT / 2 - PADDING);
    window.draw(sprite);

    Sprite spriteExit;
    spriteExit.setTexture(textureExit);
    spriteExit.setPosition((WIDTH-5), HEIGHT / 2 - PADDING + 150);
    window.draw(spriteExit);

    Sprite spriteBack;
    spriteBack.setTexture(textureBack);
    spriteBack.setPosition((WIDTH-5), HEIGHT / 2 - PADDING - 150);
    window.draw(spriteBack);

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
        whiteChecker.setPosition(HEIGHT + PADDING * 2, i * HEIGHT / 8 / 4);
        window.draw(whiteChecker);
    }

    for (int i = cntBlack; i >= 1; i--) {
        blackChecker.setPosition(HEIGHT + PADDING * 2, HEIGHT - i * HEIGHT / 8 / 4);
        window.draw(blackChecker);
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

    Font fontCheckers;
    if (!fontCheckers.loadFromFile("arial.ttf")) {
        cout << "Не удалось загрузить шрифт!" << endl;
        assert(false);
    }

    Text checkers;
    checkers.setFont(fontCheckers);
    checkers.setString(L"ШАШКИ");
    checkers.setCharacterSize(43);
    checkers.setFillColor(Color(252, 237, 216));

    FloatRect textChecker = checkers.getLocalBounds();
    checkers.setOrigin(textChecker.left + textChecker.width / 2.0f, textChecker.top + textChecker.height / 2.0f);
    checkers.setPosition((WIDTH / 2 - PADDING), (PADDING / 2));
    window.draw(checkers);

    Font _font;
    if (!_font.loadFromFile("arial.ttf")) {
        cout << "Не удалось загрузить шрифт!" << endl;
        assert(false);
    }

    Text _text;
    _text.setFont(_font);
    _text.setString("A      B      C      D      E      F      G      H");
    _text.setCharacterSize(43);
    _text.setFillColor(Color(252, 237, 216));

    FloatRect textRect = _text.getLocalBounds();
    _text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    _text.setPosition((WIDTH / 2-PADDING), (HEIGHT+PADDING*2-20));
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
        text.setFillColor(Color(252, 237, 216));

        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition((20), (PADDING * i * 2));
        window.draw(text);
    }
}

void initTexture(Texture& textureWhite, Texture& textureBlack, Texture& textureWhiteKing, Texture& textureBlackKing, RectangleShape& whiteCell, RectangleShape& blackCell, RectangleShape& whiteChecker, RectangleShape& blackChecker, RectangleShape& whiteCheckerKing, RectangleShape& blackCheckerKing, Texture& texture, Texture& textureExit, Texture& textureBack) {
    blackCell.setFillColor(Color(54, 45, 50));
    whiteCell.setFillColor(Color(230, 179, 132));

    auto operation = textureWhite.loadFromFile("whitechecker.png");
    operation = textureBlack.loadFromFile("blackchecker.png");
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

    if (!texture.loadFromFile("restart.png")) {
        cout << "Не удалось загрузить изображение!" << endl;
        assert(false);
    }
    if (!textureExit.loadFromFile("exit.png")) {
        cout << "Не удалось загрузить изображение!" << endl;
        assert(false);
    }
    if (!textureBack.loadFromFile("back.png")) {
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