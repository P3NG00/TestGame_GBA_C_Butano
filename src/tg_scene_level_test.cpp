#include "tg_scene_level_test.hpp"

#define PROJECTILE_AMOUNT 8
#define BACKGROUND_AMOUNT 2
#define WINDOW_WIDTH 84
#define ENEMY_AMOUNT 8
#define CAMERA_OFFSET_DISTANCE 20
// used as 1 / CAMERA_OFFSET_DIV_LERP to smoothly move camera towards desired position
#define CAMERA_OFFSET_DIV_LERP 20
#define TARGET_DISTANCE 60

const int WindowCameraOffset = ((WINDOW_WIDTH + ((bn::display::width() - WINDOW_WIDTH) / 2)) - (bn::display::width() / 2));

void scene_level_test::execute()
{
    // setup variables
    bn::sprite_text_generator text_generator = bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 16> text_sprites = bn::vector<bn::sprite_ptr, 16>();
    bn::fixed_point camera_offset;
    bn::fixed_point last_camera_offset;
    unsigned int i;
    unsigned short int bg_index = 0;
    bool spawn_enemy;
    bool shoot_projectile;
    // setup cameras
    bn::camera_ptr camera_obj = bn::camera_ptr::create(0, 0);
    bn::camera_ptr camera_bg = bn::camera_ptr::create(0, 0);
    // setup objects
    bn::array<projectile, PROJECTILE_AMOUNT> projectile_obj_array;
    for (i = 0; i < PROJECTILE_AMOUNT; i++)
        projectile_obj_array[i].sprite.set_camera(camera_obj);
    bn::array<enemy, ENEMY_AMOUNT> enemy_obj_array; // TODO implement collision
    for (i = 0; i < ENEMY_AMOUNT; i++)
        enemy_obj_array[i].set_camera(camera_obj);
    // setup backgrounds
    bn::array<bn::regular_bg_ptr, BACKGROUND_AMOUNT> bg_obj_array = {
        bn::regular_bg_items::bg_1.create_bg(0, 0),
        bn::regular_bg_items::bg_2.create_bg(0, 0)
    };
    for (i = 0; i < BACKGROUND_AMOUNT; i++)
        bg_obj_array[i].set_blending_enabled(true);
    bg_obj_array[0].set_camera(camera_obj);
    bg_obj_array[1].set_camera(camera_bg);
    // setup sprites
    bn::regular_bg_ptr select_window = bn::regular_bg_items::select_window.create_bg(0, 0);
    select_window.set_visible(false);
    player player_obj = player(camera_obj);
    bn::sprite_ptr target_sprite = bn::sprite_items::target.create_sprite(0, 0);
    target_sprite.set_camera(camera_obj);
    target_sprite.set_visible(false);

    // setup fade in
    bn::blending::set_fade_color(bn::blending::fade_color_type::WHITE);
    bn::blending::set_fade_alpha(1);
    bn::blending_fade_alpha_to_action fade_in(seconds_to_frames(1), 0);

    // handle fade in
    while (!fade_in.done())
    {
        fade_in.update();
        bn::core::update();
    }

    // setup background fading
    bn::blending::set_fade_color(bn::blending::fade_color_type::BLACK);
    // change fade alpha temporarily to setup fade actions
    bn::blending::set_fade_alpha(0);
    bn::blending_fade_alpha_to_action fade_out(seconds_to_frames(3), 0.9);
    bn::blending::set_fade_alpha(0.9);
    fade_in = bn::blending_fade_alpha_to_action(seconds_to_frames(1), 0);
    // reset fade alpha
    bn::blending::set_fade_alpha(0);
    // disable blending for bg 2
    bg_obj_array[1].set_blending_enabled(false);
    // enable target sprite
    target_sprite.set_visible(true);

    // loop
    while (true)
    {
        // update background fading
        if (!fade_out.done())
        {
            fade_out.update();
            if (fade_out.done())
                fade_in.reset();
        }
        else
        {
            fade_in.update();
            if (fade_in.done())
            {
                bg_obj_array[bg_index].set_blending_enabled(false);
                bg_index = (bg_index + 1) % 2;
                bg_obj_array[bg_index].set_blending_enabled(true);
                fade_out.reset();
            }
        }

        // handle player input
        player_obj.update();

        // update select window
        // TODO add purchasable upgrades and move camera offset to allow space for window
        if (bn::keypad::select_pressed())
            select_window.set_visible(!select_window.visible());

        // spawn enemy
        // TODO handle enemy random spawning
        spawn_enemy = bn::keypad::b_pressed();
        for (i = 0; i < ENEMY_AMOUNT; i++)
        {
            if (enemy_obj_array[i].active())
                enemy_obj_array[i].update(player_obj.position());
            else if (spawn_enemy)
            {
                enemy_obj_array[i].set(player_obj.position());
                spawn_enemy = false;
            }
        }

        // check player shooting
        shoot_projectile = bn::keypad::r_pressed();

        // update projectiles
        for (i = 0; i < PROJECTILE_AMOUNT; i++)
        {
            if (projectile_obj_array[i].sprite.visible())
                projectile_obj_array[i].update();
            else if (shoot_projectile)
            {
                // TODO if holdling left shoulder, lock onto closest enemy direction
                bn::fixed_point direction = player_obj.direction_facing() * 3;
                projectile_obj_array[i].set(player_obj.position() + direction, direction);
                shoot_projectile = false;
            }
        }

        // update camera
        camera_offset = player_obj.direction_moving() * CAMERA_OFFSET_DISTANCE;
        // add window offset if open
        if (select_window.visible())
            camera_offset.set_x(camera_offset.x() - WindowCameraOffset);
        // linearly interpolate towards desired position
        camera_offset = last_camera_offset + ((camera_offset - last_camera_offset) / CAMERA_OFFSET_DIV_LERP);
        // update last true camera offset before rounding
        last_camera_offset = camera_offset;
        // round camera offset if player is not moving on an axis to avoid bumpiness
        camera_offset.set_x(camera_offset.x().round_integer());
        camera_offset.set_y(camera_offset.y().round_integer());
        // update camera position
        camera_obj.set_position(player_obj.position() + camera_offset);
        camera_bg.set_position(camera_obj.position() / 2);

        // update target sprite position
        target_sprite.set_x(player_obj.position().x() + (player_obj.direction_facing().x() * TARGET_DISTANCE).round_integer());
        target_sprite.set_y(player_obj.position().y() + (player_obj.direction_facing().y() * TARGET_DISTANCE).round_integer());

        // update text
        text_sprites.clear();
        // TODO remove debug text
        text_generator.generate(-119, -76, "magnitude: " + to_string<20>(magnitude(player_obj.direction_moving())), text_sprites);
        text_generator.generate(-119, -66, "x: " + to_string<20>(player_obj.position().x()), text_sprites);
        text_generator.generate(-119, -56, "y: " + to_string<20>(player_obj.position().y()), text_sprites);
        // TODO add debug text showing things from bn_memory like usage and free space

        // update engine last
        bn::core::update();
    }
}
