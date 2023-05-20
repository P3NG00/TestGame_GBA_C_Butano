#include "bn_sprite_text_generator.h"
#include "bn_string_view.h"
#include "bn_vector.h"

#include "common_variable_8x16_sprite_font.h"

class text_handler
{
    bn::sprite_text_generator _text_generator = bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 16> _text_sprites = bn::vector<bn::sprite_ptr, 16>();

public:

    text_handler();
    void create_text(int x, int y, bn::string_view str);
    void clear_texts();
};
