#include "allitems.h"

void control(RenderWindow& window, vector<vector<int>>& f, Event& event, Position& _turn, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect) {
    static int xChoose, yChoose;
    bool checkWhite = false, checkBlack = false;

    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            int x = toNum(event.mouseButton.x);
            int y = toNum(event.mouseButton.y);

            if (event.mouseButton.x >= 900 && event.mouseButton.x <= 900 + 170 && event.mouseButton.y >= 100 && event.mouseButton.y <= 100 + 170) {
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

                    //if (whiteHasEatMoves(f, redRect)) greenRect.clear();

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

                    if (f[yChoose][xChoose] == checker::WHITE) {
                        f[y][x] = checker::WHITE;
                        f[yChoose][xChoose] = checker::NONE;
                        if (eating) {
                            while (xChoose != x && yChoose != y) {

                                f[yChoose][xChoose] = checker::NONE;

                                if (xChoose < x) xChoose++; else xChoose--;
                                if (yChoose < y) yChoose++; else yChoose--;
                            }
                        }
                    }
                    else if (f[yChoose][xChoose] == checker::WHITE_KING) {
                        f[y][x] = checker::WHITE_KING;
                        f[yChoose][xChoose] = checker::NONE;
                        if (eating) {
                            while (xChoose != x && yChoose != y) {

                                f[yChoose][xChoose] = checker::NONE;

                                if (xChoose < x) xChoose++; else xChoose--;
                                if (yChoose < y) yChoose++; else yChoose--;
                            }
                        }
                    }

                    _turn = Position::BLACK_CHOOSE;
                }
                else if (_turn == Position::BLACK_CHOOSE) {
                    if (f[y][x] != checker::BLACK && f[y][x] != checker::BLACK_KING) return;

                    yellowRect.insert(make_pair(x, y));
                    checkBlack = true;

                    if (f[y][x] == checker::BLACK_KING) {
                        blackKingChoose(f, yellowRect, greenRect, redRect, x, y);
                    }

                    else {
                        blackChoose(f, yellowRect, greenRect, redRect, x, y);
                    }

                    xChoose = x;
                    yChoose = y;

                    _turn = Position::BLACK_MOVE;
                }
                else if (_turn == Position::BLACK_MOVE) {
                    if (f[y][x] == checker::BLACK) return;
                    if (greenRect.count(make_pair(x, y)) == 0 && redRect.count(make_pair(x, y)) == 0) return;

                    yellowRect.clear();
                    greenRect.clear();
                    redRect.clear();

                    f[y][x] = checker::BLACK;
                    f[yChoose][xChoose] = checker::NONE;

                    if (checkBlack == false) {
                        if (y - 2 >= 0 && x - 2 >= 0 && yChoose == y - 2 && xChoose == x - 2) {
                            f[y - 1][x - 1] = checker::NONE;
                        }
                        if (y - 2 >= 0 && x + 2 < SZ && yChoose == y - 2 && xChoose == x + 2) {
                            f[y - 1][x + 1] = checker::NONE;
                        }
                        if (y + 2 < SZ && x + 2 < SZ && yChoose == y + 2 && xChoose == x + 2) {
                            f[y + 1][x + 1] = checker::NONE;
                        }
                        if (y + 2 < SZ && x - 2 >= 0 && yChoose == y + 2 && xChoose == x - 2) {
                            f[y + 1][x - 1] = checker::NONE;
                        }
                    }

                    _turn = Position::WHITE_CHOOSE;
                }
            }
        }
        else if (event.mouseButton.button == Mouse::Right) {
            if (_turn == Position::WHITE_MOVE) { yellowRect.clear(); greenRect.clear(); redRect.clear(); _turn = Position::WHITE_CHOOSE; }
            if (_turn == Position::BLACK_MOVE) { yellowRect.clear(); greenRect.clear(); redRect.clear(); _turn = Position::BLACK_CHOOSE; }
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