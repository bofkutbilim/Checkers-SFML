#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <set>

using namespace std;
using namespace sf;

#define SZ 8
#define PADDING 50
#define WIDTH 1000
#define HEIGHT 800

enum checker {
    NONE = 0,
    WHITE = 1,
    BLACK = 2,
    WHITE_KING = 3,
    BLACK_KING = 4
};

enum Position {
    WHITE_CHOOSE = 0,
    WHITE_MOVE = 1,
    BLACK_CHOOSE = 2,
    BLACK_MOVE = 3
};

void initTexture(Texture&, Texture&, Texture&, Texture&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, Texture&);
void setup(vector<vector<int>>&);

int toGraph(int n);
int toNum(int n);

void control(RenderWindow&, vector<vector<int>>&, Event&, Position&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&);

void Draw(RenderWindow&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, RectangleShape&, vector<vector<int>>&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&);

bool loseWhite(vector<vector<int>>&);
bool loseBlack(vector<vector<int>>&);

void kingCheck(vector<vector<int>>&);

bool whiteKingCanEat(vector<vector<int>>&, set<pair<int, int>>&, int&, int&);
void whiteKingChoose(vector<vector<int>>&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&, int&, int&);
void whiteChoose(vector<vector<int>>&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&, int&, int&);

void blackKingChoose(vector<vector<int>>&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&, int&, int&);
void blackChoose(vector<vector<int>>&, set<pair<int, int>>&, set<pair<int, int>>&, set<pair<int, int>>&, int&, int&);
