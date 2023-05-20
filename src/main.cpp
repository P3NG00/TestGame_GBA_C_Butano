#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string_view.h"
#include "bn_vector.h"

// include assets
#include "tg_player.hpp"
#include "bn_sprite_items_player.h"
#include "common_variable_8x16_sprite_font.h"

// method declarations
void create_text(int x, int y, bn::string_view str);

// global variables
bn::sprite_text_generator text_generator = bn::sprite_text_generator(common::variable_8x16_sprite_font);
bn::vector<bn::sprite_ptr, 16> text_sprites = bn::vector<bn::sprite_ptr, 16>();

int main()
{
    // init butano
    bn::core::init();

    // initialize game assets
    text_generator.set_center_alignment();
    create_text(0, 0, "Hello, world!");
    player player(bn::sprite_items::player);

    // game loop
    while(true)
    {
        // handle input
        player.handle_input();

        // update butano last
        bn::core::update();
    }
}

void create_text(int x, int y, bn::string_view str)
{
    text_generator.generate(x, y, str, text_sprites);
}
