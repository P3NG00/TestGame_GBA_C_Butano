#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_player.h"

using namespace bn;

// method declarations
void handle_input();

// global variables
sprite_ptr* player_sprite_ptr;

int main()
{
    // init butano
    core::init();

    // create game assets
    sprite_ptr player_sprite = sprite_items::player.create_sprite(0, 0);
    player_sprite_ptr = &player_sprite;

    // game loop
    while(true)
    {
        // handle input
        handle_input();

        // update butano last
        core::update();
    }
}

void handle_input()
{
    // player movement
    if (keypad::up_held())
        player_sprite_ptr->set_y(player_sprite_ptr->y() - 1);
    if (keypad::down_held())
        player_sprite_ptr->set_y(player_sprite_ptr->y() + 1);
    if (keypad::left_held())
        player_sprite_ptr->set_x(player_sprite_ptr->x() - 1);
    if (keypad::right_held())
        player_sprite_ptr->set_x(player_sprite_ptr->x() + 1);
}
