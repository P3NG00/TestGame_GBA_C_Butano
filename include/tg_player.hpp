#include "bn_sprite_ptr.h"

class player
{
    bn::sprite_ptr* _player_sprite_ptr;
    int _player_dx = 0;
    int _player_dy = 0;
    int _last_sprite_index = 0;
    int _new_sprite_index = 0;

public:

    player();
    void handle_input();
};
