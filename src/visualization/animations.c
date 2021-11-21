#include "animations.h"
#include "../../include/debugmalloc.h"
#include "../util.h"
#include <SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Instantiates an animation struct
 * 
 * @param animation_duration The duration of the animation
 * @return Animation* 
 */
Animation *init_animation(double animation_duration) {
    Animation *anim = malloc(sizeof(Animation));
    check_malloc(anim);

    anim->is_finished = false;
    anim->ANIM_DURATION = animation_duration;
    anim->delta_time = 0;
    anim->START_TIME = SDL_GetPerformanceCounter();

    return anim;
}

/**
 * @brief Updates delta_time and is_finished status
 * of animation
 * 
 * @param anim 
 */
void update_animation(Animation *anim) {
    anim->delta_time = (double)((SDL_GetPerformanceCounter() - anim->START_TIME) * 1000 / (double)SDL_GetPerformanceFrequency());
    anim->is_finished = anim->delta_time > anim->ANIM_DURATION;
}

/**
 * @brief Resets all values to default of animation
 * 
 * @param anim 
 */
void restart_animation(Animation *anim) {
    anim->is_finished = false;
    anim->delta_time = 0;
    anim->START_TIME = SDL_GetPerformanceCounter();
}

/**
 * @brief Frees the memory allocated by the animation struct
 * 
 * @param anim 
 */
void free_animation(Animation *anim) {
    free(anim);
}

/**
 * @brief This is a cubic bezier function
 * With P0(0, 0) and P3(1, 1) already defined in it
 * 
 * @param x1 X coord of P1
 * @param x2 X coord of P2
 * @param t The functions parameter
 * @return It returns x(t) given x1, x2, t 
 */
double cubic_bezier(double x1, double x2, double t) {
    assert(1 >= t && t >= 0);
    return (((1.0 - 3.0 * x2 + 3.0 * x1) * t + 3.0 * x2 - 6.0 * x1) * t + 3.0 * x1) * t;
}
