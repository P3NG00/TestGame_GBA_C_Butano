#include "bn_keypad.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

#include "tg_player.hpp"

player::player()
{
    _player_sprite_ptr = new bn::sprite_ptr(bn::sprite_items::player.create_sprite(0, 0));
}

void player::handle_input()
{
    // player movement
    _player_dx = 0;
    _player_dy = 0;
    if (bn::keypad::up_held())
        _player_dy--;
    if (bn::keypad::down_held())
        _player_dy++;
    if (bn::keypad::left_held())
        _player_dx--;
    if (bn::keypad::right_held())
        _player_dx++;

    // update position
    if (!bn::keypad::l_held())
    {
        _player_sprite_ptr->set_x(_player_sprite_ptr->x() + _player_dx);
        _player_sprite_ptr->set_y(_player_sprite_ptr->y() + _player_dy);
    }

    // find sprite index
    _new_sprite_index = -1;
    if      (_player_dx ==  0 && _player_dy == -1)
        _new_sprite_index = 0;
    else if (_player_dx ==  1 && _player_dy == -1)
        _new_sprite_index = 1;
    else if (_player_dx ==  1 && _player_dy ==  0)
        _new_sprite_index = 2;
    else if (_player_dx ==  1 && _player_dy ==  1)
        _new_sprite_index = 3;
    else if (_player_dx ==  0 && _player_dy ==  1)
        _new_sprite_index = 4;
    else if (_player_dx == -1 && _player_dy ==  1)
        _new_sprite_index = 5;
    else if (_player_dx == -1 && _player_dy ==  0)
        _new_sprite_index = 6;
    else if (_player_dx == -1 && _player_dy == -1)
        _new_sprite_index = 7;

    // update sprite check
    if (_new_sprite_index != -1 && _new_sprite_index != _last_sprite_index)
    {
        _player_sprite_ptr->set_tiles(bn::sprite_items::player.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
    }
}
