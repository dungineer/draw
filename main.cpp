// Components
#include <game.h>


constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

int main() {
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    return game.exec();
}
