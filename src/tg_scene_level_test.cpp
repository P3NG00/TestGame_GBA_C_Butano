#include "tg_scene_level_test.hpp"

#define PROJECTILE_AMOUNT 8
#define BACKGROUND_AMOUNT 2
#define WINDOW_WIDTH 84
#define ENEMY_AMOUNT 32
#define CAMERA_OFFSET_DISTANCE 20
// used as 1 / CAMERA_OFFSET_DIV_LERP to smoothly move camera towards desired position
#define CAMERA_OFFSET_DIV_LERP 20
#define TARGET_DISTANCE 60

const int WindowCameraOffset = (WINDOW_WIDTH + ((240 - WINDOW_WIDTH) / 2)) - 120;

struct lock_on_info
{
    bn::fixed distance;
    unsigned int enemy_index;
};

void scene_level_test::execute()
{
    // setup variables
    bn::random random = bn::random();
    bn::sprite_text_generator text_generator = bn::sprite_text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 16> text_score = bn::vector<bn::sprite_ptr, 16>();
    bn::fixed_point camera_offset;
    bn::fixed_point last_camera_offset;
    unsigned int score = 0;
    unsigned int i, j;
    unsigned short int bg_index = 0;
    // TODO make harder by spawning more enemies, harder enemies, or waves
    const bn::fixed spawn_timer = seconds_to_frames(1);
    bn::fixed spawn_timer_counter = spawn_timer;
    const unsigned int shoot_timer = seconds_to_frames(1);
    unsigned int shoot_timer_counter = shoot_timer;
    bool spawn_enemy = true;
    bool shoot_projectile;
    bool update_score = true;
    bool lock_on = true;
    bn::optional<lock_on_info> lock_on_enemy;
    bn::optional<lock_on_info> lock_on_enemy_check;
    // setup cameras
    bn::camera_ptr camera_obj = bn::camera_ptr::create(0, 0);
    bn::camera_ptr camera_bg = bn::camera_ptr::create(0, 0);
    // setup objects
    bn::array<projectile, PROJECTILE_AMOUNT> projectile_obj_array;
    for (i = 0; i < PROJECTILE_AMOUNT; i++)
        projectile_obj_array[i].set_camera(camera_obj);
    bn::array<enemy, ENEMY_AMOUNT> enemy_obj_array;
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
    player player_obj = player();
    player_obj.set_camera(camera_obj);
    bn::sprite_ptr target_sprite = bn::sprite_items::target.create_sprite(0, 0);
    target_sprite.set_camera(camera_obj);
    target_sprite.set_visible(false);
    bn::sprite_ptr fire_bar = bn::sprite_items::fire_bar.create_sprite(89, -101);
    fire_bar.set_blending_enabled(true);

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
    bg_obj_array[1].set_blending_enabled(false);
    fire_bar.set_blending_enabled(false);
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
        if (bn::keypad::l_pressed())
            lock_on = !lock_on;

        // check player shooting
        if (shoot_timer_counter > 0)
            shoot_timer_counter -= 1;
        shoot_projectile = bn::keypad::r_held() && shoot_timer_counter == 0;

        // update projectiles
        for (i = 0; i < PROJECTILE_AMOUNT; i++)
        {
            if (projectile_obj_array[i].active())
                projectile_obj_array[i].update();
            else if (shoot_projectile)
            {
                bn::fixed_point direction;
                if (lock_on && lock_on_enemy.has_value())
                    direction = normalize(enemy_obj_array[lock_on_enemy.value().enemy_index].new_position() - player_obj.position());
                else
                    direction = player_obj.direction_facing();
                direction *= 3;
                projectile_obj_array[i].set(player_obj.position() + direction, direction);
                shoot_timer_counter = shoot_timer;
                shoot_projectile = false;
            }
        }

        // check collision between enemies and projectiles
        for (i = 0; i < ENEMY_AMOUNT; i++)
        {
            // check if enemy is active
            if (!enemy_obj_array[i].active())
                continue;
            // check collision against projectiles
            for (j = 0; j < PROJECTILE_AMOUNT; j++)
            {
                if (!projectile_obj_array[j].active())
                    continue;
                if (enemy_obj_array[i].collides_with(projectile_obj_array[j].position(), projectile_obj_array[j].size()))
                {
                    // TODO implement actual damage values
                    enemy_obj_array[i].damage(0);
                    projectile_obj_array[j].damage(0);
                    if (lock_on_enemy.has_value() && lock_on_enemy.value().enemy_index == i)
                        lock_on_enemy.reset();
                    score++;
                    update_score = true;
                }
            }
        }

        // update enemies
        spawn_timer_counter -= 1;
        if (spawn_timer_counter == 0)
        {
            spawn_timer_counter = spawn_timer;
            spawn_enemy = true;
        }
        for (i = 0; i < ENEMY_AMOUNT; i++)
        {
            if (enemy_obj_array[i].active())
                enemy_obj_array[i].update(player_obj.position());
            // check if enemy should be spawned
            else if (spawn_enemy)
            {
                bn::fixed_point spawn_pos = normalize(bn::fixed_point(
                    random.get_int(-120, 121),
                    random.get_int(-80, 81)));
                enemy_obj_array[i].set(player_obj.position() + (spawn_pos * 300));
                spawn_enemy = false;
            }
        }

        // reset lock on check
        lock_on_enemy_check.reset();
        // check collision between enemies and player
        // TODO test implementing a vector that stores the locations of enemies in a grid (divide by cell size) then test collision only against enemies in the same cell
        for (i = 0; i < ENEMY_AMOUNT; i++)
        {
            // check if enemy is active
            if (enemy_obj_array[i].active())
            {
                bn::fixed distance_check = distance(enemy_obj_array[i].position(), player_obj.position());
                if (lock_on && (!lock_on_enemy_check.has_value() || distance_check < lock_on_enemy_check.value().distance))
                    lock_on_enemy_check = lock_on_info(distance_check, i);
                // check collision against other enemies
                for (j = i + 1; j < ENEMY_AMOUNT; j++)
                {
                    if (enemy_obj_array[j].active())
                        enemy_obj_array[i].handle_collision(enemy_obj_array[j].new_position(), enemy_obj_array[j].size());
                }

                // check collision against player
                enemy_obj_array[i].handle_collision(player_obj.position(), player_obj.size());

                // update enemy position
                enemy_obj_array[i].update_position();
            }
        }
        // update lock on info
        if (lock_on_enemy_check.has_value() && (!lock_on_enemy.has_value() || lock_on_enemy_check.value().enemy_index != lock_on_enemy.value().enemy_index))
            lock_on_enemy = lock_on_enemy_check;

        // update score
        if (update_score)
        {
            text_score.clear();
            text_generator.generate(-119, -76, "Score: " + bn::to_string<20>(score), text_score);
            update_score = false;
        }

        // update select window
        // TODO add purchasable upgrades and move camera offset to allow space for window
        if (bn::keypad::select_pressed())
            select_window.set_visible(!select_window.visible());

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
        if (lock_on && lock_on_enemy.has_value())
            target_sprite.set_position(enemy_obj_array[lock_on_enemy.value().enemy_index].position());
        else
        {
            target_sprite.set_x(player_obj.position().x() + (player_obj.direction_facing().x() * TARGET_DISTANCE).round_integer());
            target_sprite.set_y(player_obj.position().y() + (player_obj.direction_facing().y() * TARGET_DISTANCE).round_integer());
        }

        // update fire bar sprite
        int sprite_index;
        if (shoot_timer_counter == 0)
            sprite_index = 7;
        else
            sprite_index = 8 - bn::fixed(bn::fixed(shoot_timer_counter * 8) / shoot_timer).ceil_integer();
        fire_bar.set_tiles(bn::sprite_items::fire_bar.tiles_item().create_tiles(sprite_index));

        // update engine last
        bn::core::update();
    }
}
