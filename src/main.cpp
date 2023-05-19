#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_player.h"

using namespace bn;

// method declarations
void handle_input(sprite_ptr player_sprite);

int main()
{
    // init butano
    core::init();

    // create game assets
    sprite_ptr player_sprite = sprite_items::player.create_sprite(0, 0);

    // game loop
    while(true)
    {
        // handle input
        handle_input(player_sprite);

        // update butano last
        core::update();
    }
}

void handle_input(sprite_ptr player_sprite)
{
    // player movement
    if (keypad::up_held())
        player_sprite.set_y(player_sprite.y() - 1);
    if (keypad::down_held())
        player_sprite.set_y(player_sprite.y() + 1);
    if (keypad::left_held())
        player_sprite.set_x(player_sprite.x() - 1);
    if (keypad::right_held())
        player_sprite.set_x(player_sprite.x() + 1);
}
