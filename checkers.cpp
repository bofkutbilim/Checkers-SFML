#include "allitems.h"

int main() {
    setlocale(LC_ALL, "Russian");
    RenderWindow window(VideoMode(WIDTH + 2 * PADDING + 50, HEIGHT + 2 * PADDING + 20), "Checkers");

    RectangleShape blackCell(Vector2f(100, 100)), whiteCell(Vector2f(100, 100));
    Texture textureWhite, textureBlack, textureWhiteKing, textureBlackKing;
    RectangleShape blackChecker(Vector2f(100, 100)), whiteChecker(Vector2f(100, 100)), whiteCkeckerKing(Vector2f(100, 100)), blackCheckerKing(Vector2f(100, 100));
    
    vector<vector<int>> f(SZ, vector<int>(SZ));
    
    set<pair<int, int>> yellowRect, greenRect, redRect;
    Position _turn = Position::WHITE_CHOOSE;

    Texture texture, textureExit, textureBack;
    initTexture(textureWhite, textureBlack, textureWhiteKing, textureBlackKing, whiteCell, blackCell, whiteChecker, blackChecker, whiteCkeckerKing, blackCheckerKing, texture, textureExit, textureBack);
    setup(f);

    vector<vector<vector<int>>> positions;
    positions.push_back(f);

    while (window.isOpen()) {
        Event _event;
        if (window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                window.close();
            control(window, whiteCell, blackCell, whiteChecker, blackChecker, whiteCkeckerKing, blackCheckerKing, texture, textureExit, textureBack, f, positions,  _event, _turn, yellowRect, greenRect, redRect);
        }

        window.clear(Color::White);
        Draw(window, whiteCell, blackCell, whiteChecker, blackChecker, whiteCkeckerKing, blackCheckerKing, texture, textureExit, textureBack, f, yellowRect, greenRect, redRect);

        if (loseWhite(f)) {
            Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cout << "Не удалось загрузить шрифт!" << endl;
                return -1;
            }

            Text text;
            text.setFont(font);
            text.setString("BLACK WINS!");
            text.setStyle(3);
            text.setCharacterSize(70);
            text.setFillColor(Color::Black);

            FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition((WIDTH + 2 * PADDING) / 2.0f , (HEIGHT + 2 * PADDING) / 2.0f);
            window.draw(text);
        }
        if (loseBlack(f)) {
            Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cout << "Не удалось загрузить шрифт!" << endl;
                return -1;
            }

            Text text;
            text.setFont(font);
            text.setString("WHITE WINS!");
            text.setCharacterSize(70);
            text.setStyle(3);
            text.setFillColor(Color(202, 207, 196));

            FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition((WIDTH + 2*PADDING) / 2.0f, (HEIGHT + 2*PADDING) / 2.0f);
            window.draw(text);
        }
        window.display();
    }
    return 0;
}