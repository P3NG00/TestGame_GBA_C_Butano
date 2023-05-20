#include "bn_core.h"

// include assets
#include "tg_player.hpp"
#include "tg_text_handler.hpp"

int main()
{
    // init butano
    bn::core::init();

    // initialize game assets
    text_handler text_handler_obj = text_handler();
    text_handler_obj.create_text(0, 0, "Hello, world!");
    player player_obj = player();

    // game loop
    while(true)
    {
        // handle input
        player_obj.handle_input();

        // update butano last
        bn::core::update();
    }
}
