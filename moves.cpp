#include "allitems.h"

bool loseWhite(vector<vector<int>>& f) {
    int cntWhite = 0;
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            if (f[i][j] == checker::WHITE || f[i][j] == checker::WHITE_KING) {
                cntWhite++;
            }
        }
    }
    return cntWhite == 0;
}

bool loseBlack(vector<vector<int>>& f) {
    int cntBlack = 0;
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            if (f[i][j] == checker::BLACK || f[i][j] == checker::BLACK_KING) {
                cntBlack++;
            }
        }
    }
    return cntBlack == 0;
}

bool whiteKingCanEat(vector<vector<int>>&f, set<pair<int, int>>& redRect, int& x, int& y) {
    bool canEat = false;

    int xx = x + 1, yy = y + 1;
    while (xx < SZ - 1 && yy < SZ - 1) {

        if (f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)
            break;

        if ((f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)) {
            if (f[yy + 1][xx + 1] != checker::NONE)
                break;

            xx++;
            yy++;

            while (xx < SZ && yy < SZ && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx++;
                yy++;
            }

            canEat = true;
            break;
        }
        xx++;
        yy++;
    }

    xx = x + 1, yy = y - 1;
    while (xx < SZ - 1 && yy > 0) {

        if (f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)
            break;

        if ((f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)) {
            if (f[yy - 1][xx + 1] != checker::NONE)
                break;

            xx++;
            yy--;

            while (xx < SZ && yy >= 0 && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx++;
                yy--;
            }

            canEat = true;
            break;
        }
        xx++;
        yy--;
    }

    xx = x - 1, yy = y - 1;
    while (xx > 0 && yy > 0) {

        if (f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)
            break;

        if ((f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)) {
            if (f[yy - 1][xx - 1] != checker::NONE)
                break;

            xx--;
            yy--;

            while (xx >= 0 && yy >= 0 && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx--;
                yy--;
            }

            canEat = true;
            break;
        }
        xx--;
        yy--;
    }

    xx = x - 1, yy = y + 1;
    while (xx > 0 && yy < SZ - 1) {

        if (f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)
            break;

        if ((f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)) {
            if (f[yy + 1][xx - 1] != checker::NONE)
                break;

            xx--;
            yy++;

            while (xx >= 0 && yy < SZ && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx--;
                yy++;
            }

            canEat = true;
            break;
        }
        xx--;
        yy++;
    }
    return canEat;
}

void whiteKingChoose(vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect, int& x, int& y) {
    bool canEat = whiteKingCanEat(f, redRect, x, y);
    int xx, yy;

    if (canEat == false) {
        xx = x - 1, yy = y - 1;
        while (xx >= 0 && yy >= 0 && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx--;
            yy--;
        }
        xx = x + 1, yy = y + 1;
        while (xx < SZ && yy < SZ && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx++;
            yy++;
        }
        xx = x + 1, yy = y - 1;
        while (xx < SZ && yy >= 0 && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx++;
            yy--;
        }
        xx = x - 1, yy = y + 1;
        while (xx >= 0 && yy < SZ && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx--;
            yy++;
        }
    }
}

bool blackKingCanEat(vector<vector<int>>& f, set<pair<int, int>>& redRect, int& x, int& y) {
    bool canEat = false;

    int xx = x + 1, yy = y + 1;
    while (xx < SZ - 1 && yy < SZ - 1) {

        if (f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)
            break;

        if ((f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)) {
            if (f[yy + 1][xx + 1] != checker::NONE)
                break;

            xx++;
            yy++;

            while (xx < SZ && yy < SZ && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx++;
                yy++;
            }

            canEat = true;
            break;
        }
        xx++;
        yy++;
    }

    xx = x + 1, yy = y - 1;
    while (xx < SZ - 1 && yy > 0) {

        if (f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)
            break;

        if ((f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)) {
            if (f[yy - 1][xx + 1] != checker::NONE)
                break;

            xx++;
            yy--;

            while (xx < SZ && yy >= 0 && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx++;
                yy--;
            }

            canEat = true;
            break;
        }
        xx++;
        yy--;
    }

    xx = x - 1, yy = y - 1;
    while (xx > 0 && yy > 0) {

        if (f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)
            break;

        if ((f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)) {
            if (f[yy - 1][xx - 1] != checker::NONE)
                break;

            xx--;
            yy--;

            while (xx >= 0 && yy >= 0 && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx--;
                yy--;
            }

            canEat = true;
            break;
        }
        xx--;
        yy--;
    }

    xx = x - 1, yy = y + 1;
    while (xx > 0 && yy < SZ - 1) {

        if (f[yy][xx] == checker::BLACK || f[yy][xx] == checker::BLACK_KING)
            break;

        if ((f[yy][xx] == checker::WHITE || f[yy][xx] == checker::WHITE_KING)) {
            if (f[yy + 1][xx - 1] != checker::NONE)
                break;

            xx--;
            yy++;

            while (xx >= 0 && yy < SZ && f[yy][xx] == checker::NONE) {
                redRect.insert(make_pair(xx, yy));
                xx--;
                yy++;
            }

            canEat = true;
            break;
        }
        xx--;
        yy++;
    }
    return canEat;
}

void blackKingChoose(vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect, int& x, int& y) {
    bool canEat = blackKingCanEat(f, redRect, x, y);
    int xx, yy;

    if (canEat == false) {
        xx = x - 1, yy = y - 1;
        while (xx >= 0 && yy >= 0 && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx--;
            yy--;
        }
        xx = x + 1, yy = y + 1;
        while (xx < SZ && yy < SZ && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx++;
            yy++;
        }
        xx = x + 1, yy = y - 1;
        while (xx < SZ && yy >= 0 && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx++;
            yy--;
        }
        xx = x - 1, yy = y + 1;
        while (xx >= 0 && yy < SZ && f[yy][xx] == checker::NONE) {
            greenRect.insert(make_pair(xx, yy));
            xx--;
            yy++;
        }
    }
}

bool whiteCanEat(vector<vector<int>>& f, set<pair<int, int>>& redRect,  int& x, int& y) {
    bool canEat = false;
    
    if (y - 1 >= 1 && x - 1 >= 1 && (f[y - 1][x - 1] == checker::BLACK || f[y - 1][x - 1] == checker::BLACK_KING) && f[y - 2][x - 2] == checker::NONE) {
        redRect.insert(make_pair(x - 2, y - 2));
        canEat = true;
    }

    if (y - 1 >= 1 && x + 1 < SZ - 1 && (f[y - 1][x + 1] == checker::BLACK || f[y - 1][x + 1] == checker::BLACK_KING) && f[y - 2][x + 2] == checker::NONE) {
        redRect.insert(make_pair(x + 2, y - 2));
        canEat = true;
    }

    if (y + 1 < SZ - 1 && x + 1 < SZ - 1 && (f[y + 1][x + 1] == checker::BLACK || f[y + 1][x + 1] == checker::BLACK_KING) && f[y + 2][x + 2] == checker::NONE) {
        redRect.insert(make_pair(x + 2, y + 2));
        canEat = true;
    }

    if (y + 1 < SZ - 1 && x - 1 >= 1 && (f[y + 1][x - 1] == checker::BLACK || f[y + 1][x - 1] == checker::BLACK_KING) && f[y + 2][x - 2] == checker::NONE) {
        redRect.insert(make_pair(x - 2, y + 2));
        canEat = true;
    }

    return canEat;
}

void whiteChoose(vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect, int& x, int& y) {
    bool checkWhite = whiteCanEat(f, redRect, x, y);
    if (checkWhite == false) {
        if (y - 1 >= 0 && x - 1 >= 0 && f[y - 1][x - 1] == checker::NONE) {
            greenRect.insert(make_pair(x - 1, y - 1));
        }

        if (y - 1 >= 0 && x + 1 < SZ && f[y - 1][x + 1] == checker::NONE) {
            greenRect.insert(make_pair(x + 1, y - 1));
        }
    }
}

bool blackCanEat(vector<vector<int>>& f, set<pair<int, int>>& redRect, int& x, int& y) {
    bool canEat = false;

    if (y - 1 >= 1 && x - 1 >= 1 && (f[y - 1][x - 1] == checker::WHITE || f[y - 1][x - 1] == checker::WHITE_KING) && f[y - 2][x - 2] == checker::NONE) {
        redRect.insert(make_pair(x - 2, y - 2));
        canEat = true;
    }

    if (y - 1 >= 1 && x + 1 < SZ - 1 && (f[y - 1][x + 1] == checker::WHITE || f[y - 1][x + 1] == checker::WHITE_KING) && f[y - 2][x + 2] == checker::NONE) {
        redRect.insert(make_pair(x + 2, y - 2));
        canEat = true;
    }

    if (y + 1 < SZ - 1 && x + 1 < SZ - 1 && (f[y + 1][x + 1] == checker::WHITE || f[y + 1][x + 1] == checker::WHITE_KING) && f[y + 2][x + 2] == checker::NONE) {
        redRect.insert(make_pair(x + 2, y + 2));
        canEat = true;
    }

    if (y + 1 < SZ - 1 && x - 1 >= 1 && (f[y + 1][x - 1] == checker::WHITE || f[y + 1][x - 1] == checker::WHITE_KING) && f[y + 2][x - 2] == checker::NONE) {
        redRect.insert(make_pair(x - 2, y + 2));
        canEat = true;
    }

    return canEat;
}

void blackChoose(vector<vector<int>>& f, set<pair<int, int>>& yellowRect, set<pair<int, int>>& greenRect, set<pair<int, int>>& redRect, int& x, int& y) {
    bool checkBlack = blackCanEat(f, redRect, x, y);
    if (checkBlack == false) {
        if (y + 1 < SZ && x + 1 < SZ && f[y + 1][x + 1] == checker::NONE) {
            greenRect.insert(make_pair(x + 1, y + 1));
        }

        if (y + 1 < SZ && x - 1 >= 0 && f[y + 1][x - 1] == checker::NONE) {
            greenRect.insert(make_pair(x - 1, y + 1));
        }
    }
}


bool whiteHasEatMoves(vector<vector<int>>& f, set<pair<int, int>>& redRect) {
    for (int y = 0; y < SZ; y++) {
        for (int x = 0; x < SZ; x++) {
            if ((f[y][x] == checker::WHITE_KING && whiteKingCanEat(f, redRect, x, y)) || (f[y][x] == checker::WHITE && whiteCanEat(f, redRect, x, y))) {
                return true;
            }
        }
    }
    return false;
}

bool blackHasEatMoves(vector<vector<int>>& f, set<pair<int, int>>& redRect) {
    for (int y = 0; y < SZ; y++) {
        for (int x = 0; x < SZ; x++) {
            if ((f[y][x] == checker::BLACK_KING && blackKingCanEat(f, redRect, x, y)) || (f[y][x] == checker::BLACK && blackCanEat(f, redRect, x, y))) {
                return true;
            }
        }
    }
    return false;
}