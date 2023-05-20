#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "tg_text_handler.hpp"

text_handler::text_handler()
{
    _text_generator.set_center_alignment();
}

void text_handler::create_text(int x, int y, bn::string_view str)
{
    _text_generator.generate(x, y, str, _text_sprites);
}

void text_handler::clear_texts()
{
    _text_sprites.clear();
}
