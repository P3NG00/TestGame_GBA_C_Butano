#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_string_view.h"
#include "bn_vector.h"

#include "bn_sprite_items_player.h"

#include "common_variable_8x16_sprite_font.h"

using namespace bn;

// method declarations
void handle_input();
void create_text(int x, int y, string_view str);

// global variables
sprite_ptr* player_sprite_ptr;
sprite_text_generator text_generator = sprite_text_generator(common::variable_8x16_sprite_font);
vector<sprite_ptr, 16> text_sprites = vector<sprite_ptr, 16>();
int player_dx = 0;
int player_dy = 0;
int last_sprite_index = 0;
int new_sprite_index = 0;

int main()
{
    // init butano
    core::init();

    // create game assets
    text_generator.set_center_alignment();
    create_text(0, 0, "Hello, world!");
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
    player_dx = 0;
    player_dy = 0;
    if (keypad::up_held())
        player_dy--;
    if (keypad::down_held())
        player_dy++;
    if (keypad::left_held())
        player_dx--;
    if (keypad::right_held())
        player_dx++;

    // update position
    player_sprite_ptr->set_x(player_sprite_ptr->x() + player_dx);
    player_sprite_ptr->set_y(player_sprite_ptr->y() + player_dy);

    // find sprite index
    if      (player_dx ==  1 && player_dy == -1)
        new_sprite_index = 1;
    else if (player_dx ==  1 && player_dy ==  0)
        new_sprite_index = 2;
    else if (player_dx ==  1 && player_dy ==  1)
        new_sprite_index = 3;
    else if (player_dx ==  0 && player_dy ==  1)
        new_sprite_index = 4;
    else if (player_dx == -1 && player_dy ==  1)
        new_sprite_index = 5;
    else if (player_dx == -1 && player_dy ==  0)
        new_sprite_index = 6;
    else if (player_dx == -1 && player_dy == -1)
        new_sprite_index = 7;
    else
        new_sprite_index = 0;

    // update sprite check
    if (new_sprite_index != last_sprite_index)
    {
        player_sprite_ptr->set_tiles(sprite_items::player.tiles_item().create_tiles(new_sprite_index));
        last_sprite_index = new_sprite_index;
    }
}

void create_text(int x, int y, string_view str)
{
    text_generator.generate(x, y, str, text_sprites);
}
