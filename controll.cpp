#include "allitems.h"

void control(RenderWindow& window, RectangleShape& whiteCell, RectangleShape& blackCell, RectangleShape& whiteChecker, RectangleShape& blackChecker, RectangleShape& whiteCheckerKing, RectangleShape& blackCheckerKing, vector<vector<int>>& f, Event& event, Position& _turn, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect) {
    static int xChoose, yChoose;

    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            int x = toNum(event.mouseButton.x);
            int y = toNum(event.mouseButton.y);

            if (event.mouseButton.x >= WIDTH - 2 * PADDING && event.mouseButton.x <= WIDTH - 2 * PADDING + 170 && event.mouseButton.y >= HEIGHT / 2 - PADDING && event.mouseButton.y <= HEIGHT / 2 - PADDING + 170) {
                setup(f);
                yellowRect.clear();
                greenRect.clear();
                redRect.clear();
                _turn = Position::WHITE_CHOOSE;
            }

            if (x >= 0 && x < SZ && y >= 0 && y < SZ) {
                if (_turn == Position::WHITE_CHOOSE) {
                    if (f[y][x] != checker::WHITE && f[y][x] != checker::WHITE_KING) return;

                    yellowRect.insert(make_pair(x, y));

                    if (f[y][x] == checker::WHITE_KING) {
                        whiteKingChoose(f, yellowRect, greenRect, redRect, x, y);
                    }
                    else {
                        whiteChoose(f, yellowRect, greenRect, redRect, x, y);
                    }

                    set<pair<int, int>> redRect_new;
                    if (whiteHasEatMoves(f, redRect_new)) greenRect.clear();
                    redRect_new.clear();

                    xChoose = x;
                    yChoose = y;

                    _turn = Position::WHITE_MOVE;
                }
                else if (_turn == Position::WHITE_MOVE) {
                    if (greenRect.count(make_pair(x, y)) == 0 && redRect.count(make_pair(x, y)) == 0) return;

                    bool eating = redRect.count(make_pair(x, y)) == 1;

                    yellowRect.clear();
                    greenRect.clear();
                    redRect.clear();

                    
                    if (eating) {
                        while (true) {

                            if (f[yChoose][xChoose] == checker::WHITE) {
                                if (y == 0) f[y][x] = checker::WHITE_KING;
                                else f[y][x] = checker::WHITE;
                            }
                            else if (f[yChoose][xChoose] == checker::WHITE_KING) {
                                f[y][x] = checker::WHITE_KING;
                            }

                            f[yChoose][xChoose] = checker::NONE;
                            
                            while (xChoose != x && yChoose != y) {

                                f[yChoose][xChoose] = checker::NONE;

                                if (xChoose < x) xChoose++; else xChoose--;
                                if (yChoose < y) yChoose++; else yChoose--;
                            }

                            yellowRect.clear();

                            if ((f[y][x] == checker::WHITE && !whiteCanEat(f, redRect, x, y))) break;
                            else if ((f[y][x] == checker::WHITE_KING && !whiteKingCanEat(f, redRect, x, y))) break;

                            yellowRect.insert({ x, y });
                            
                            window.clear(Color::White);
                            Draw(window, whiteCell, blackCell, whiteChecker, blackChecker, whiteCheckerKing, blackCheckerKing, f, yellowRect, greenRect, redRect);
                            window.display();

                            while (window.isOpen()) {

                                Event event;
                                if (window.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed)
                                        window.close();

                                    if (event.type == Event::MouseButtonPressed)
                                    {
                                        if (event.mouseButton.button == Mouse::Left)
                                        {
                                            if (redRect.count({ toNum(event.mouseButton.x), toNum(event.mouseButton.y) })) {
                                                x = toNum(event.mouseButton.x);
                                                y = toNum(event.mouseButton.y);
                                                redRect.clear();
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        if (f[yChoose][xChoose] == checker::WHITE) {
                            if (y == 0) f[y][x] = checker::WHITE_KING;
                            else f[y][x] = checker::WHITE;
                        }
                        else if (f[yChoose][xChoose] == checker::WHITE_KING) {
                            f[y][x] = checker::WHITE_KING;
                        }

                        f[yChoose][xChoose] = checker::NONE;
                    }

                    _turn = Position::BLACK_CHOOSE;
                }
                else if (_turn == Position::BLACK_CHOOSE) {
                    if (f[y][x] != checker::BLACK && f[y][x] != checker::BLACK_KING) return;

                    yellowRect.insert(make_pair(x, y));

                    if (f[y][x] == checker::BLACK_KING) {
                        blackKingChoose(f, yellowRect, greenRect, redRect, x, y);
                    }
                    else {
                        blackChoose(f, yellowRect, greenRect, redRect, x, y);
                    }

                    set<pair<int, int>> redRect_new;
                    if (blackHasEatMoves(f, redRect_new)) greenRect.clear();
                    redRect_new.clear();

                    xChoose = x;
                    yChoose = y;

                    _turn = Position::BLACK_MOVE;
                }
                else if (_turn == Position::BLACK_MOVE) {
                    if (greenRect.count(make_pair(x, y)) == 0 && redRect.count(make_pair(x, y)) == 0) return;

                    bool eating = redRect.count(make_pair(x, y)) == 1;

                    yellowRect.clear();
                    greenRect.clear();
                    redRect.clear();

                    if (eating) {
                        while (true) {

                            if (f[yChoose][xChoose] == checker::BLACK) {
                                if (y == SZ-1) f[y][x] = checker::BLACK_KING;
                                else f[y][x] = checker::BLACK;
                            }
                            else if (f[yChoose][xChoose] == checker::BLACK_KING) {
                                f[y][x] = checker::BLACK_KING;
                            }

                            f[yChoose][xChoose] = checker::NONE;

                            while (xChoose != x && yChoose != y) {

                                f[yChoose][xChoose] = checker::NONE;

                                if (xChoose < x) xChoose++; else xChoose--;
                                if (yChoose < y) yChoose++; else yChoose--;
                            }

                            yellowRect.clear();

                            if ((f[y][x] == checker::BLACK && !blackCanEat(f, redRect, x, y))) break;
                            else if ((f[y][x] == checker::BLACK_KING && !blackKingCanEat(f, redRect, x, y))) break;

                            yellowRect.insert({ x, y });

                            window.clear(Color::White);
                            Draw(window, whiteCell, blackCell, whiteChecker, blackChecker, whiteCheckerKing, blackCheckerKing, f, yellowRect, greenRect, redRect);
                            window.display();

                            while (window.isOpen()) {

                                Event event;
                                if (window.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed)
                                        window.close();

                                    if (event.type == Event::MouseButtonPressed)
                                    {
                                        if (event.mouseButton.button == Mouse::Left)
                                        {
                                            if (redRect.count({ toNum(event.mouseButton.x), toNum(event.mouseButton.y) })) {
                                                x = toNum(event.mouseButton.x);
                                                y = toNum(event.mouseButton.y);
                                                redRect.clear();
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        if (f[yChoose][xChoose] == checker::BLACK) {
                            if (y == SZ-1) f[y][x] = checker::BLACK_KING;
                            else f[y][x] = checker::BLACK;
                        }
                        else if (f[yChoose][xChoose] == checker::BLACK_KING) {
                            f[y][x] = checker::BLACK_KING;
                        }

                        f[yChoose][xChoose] = checker::NONE;
                    }

                    _turn = Position::WHITE_CHOOSE;
                }
            }
        }
        else if (event.mouseButton.button == Mouse::Right) {
            if (_turn == Position::WHITE_MOVE) {
                yellowRect.clear();
                greenRect.clear();
                redRect.clear();
                _turn = Position::WHITE_CHOOSE;
            }
            if (_turn == Position::BLACK_MOVE) {
                yellowRect.clear();
                greenRect.clear();
                redRect.clear();
                _turn = Position::BLACK_CHOOSE;
            }
        }
    }
}

void kingCheck(vector<vector<int>>& f) {
    for (int i = 0; i < SZ; i++) {
        if (f[0][i] == checker::WHITE) {
            f[0][i] = checker::WHITE_KING;
        }
        if (f[SZ - 1][i] == checker::BLACK) {
            f[SZ - 1][i] = checker::BLACK_KING;
        }
    }
}