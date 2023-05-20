#include "player.hpp"

#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_player.h"

Player::Player(bn::sprite_ptr* player_sprite_ptr) : _player_sprite_ptr(player_sprite_ptr) {}

void Player::handle_input()
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
    _player_sprite_ptr->set_x(_player_sprite_ptr->x() + _player_dx);
    _player_sprite_ptr->set_y(_player_sprite_ptr->y() + _player_dy);

    // find sprite index
    if      (_player_dx ==  1 && _player_dy == -1)
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
    else
        _new_sprite_index = 0;

    // update sprite check
    if (_new_sprite_index != _last_sprite_index)
    {
        _player_sprite_ptr->set_tiles(bn::sprite_items::player.tiles_item().create_tiles(_new_sprite_index));
        _last_sprite_index = _new_sprite_index;
    }
}
