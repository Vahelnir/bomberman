#include "game.h"

int main() {
    Game game("Bomberman | ", 800, 600);
    game.createWindow();

    if (game.isReady()) {
        game.loop();
    }
    game.destroy();
    return 0;
}