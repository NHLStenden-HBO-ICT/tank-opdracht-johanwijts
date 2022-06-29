#include "precomp.h"
#include "game_object.h"


namespace Tmpl8
{
    Game_Object::Game_Object(vec2 position, vec2 direction, float collision_radius, allignments allignment, Sprite* rocket_sprite)
        : position(position), speed(direction), collision_radius(collision_radius), allignment(allignment), current_frame(0), rocket_sprite(rocket_sprite), active(true)
    {
    }

    Game_Object::~Game_Object()
    {
    }

    void Game_Object::tick()
    {
        position += speed;
        if (++current_frame > 8) current_frame = 0;
    }

    //Draw the sprite with the facing based on this rockets movement direction
    void Game_Object::draw(Surface* screen)
    {
        rocket_sprite->set_frame(((abs(speed.x) > abs(speed.y)) ? ((speed.x < 0) ? 3 : 0) : ((speed.y < 0) ? 9 : 6)) + (current_frame / 3));
        rocket_sprite->draw(screen, (int)position.x - 12 + HEALTHBAR_OFFSET, (int)position.y - 12);
    }

    //Does the given circle collide with this rockets collision circle?
    bool Game_Object::intersects(vec2 position_other, float radius_other) const
    {
        //Note: Uses squared lengths to remove expensive square roots
        float distance_sqr = (position_other - position).sqr_length();

        if (distance_sqr <= ((collision_radius + radius_other) * (collision_radius + radius_other)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace Tmpl8
