
#include "Game.hpp"

int main()
{
    Game game(std::string(HOME_DIR) + "/resources/config.json");
    game.Init();
    game.Run();

    return 0;
}
