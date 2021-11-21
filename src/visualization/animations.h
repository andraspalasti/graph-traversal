#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <SDL.h>
#include <stdbool.h>

// Should only use this in an SDL context
typedef struct Animation {
    Uint64 START_TIME;    /* the start time of the animation */
    double ANIM_DURATION; /* the duration of the animation in ms */
    double delta_time;    /* the elapsed time since start in ms */
    bool is_finished;
} Animation;

Animation *init_animation(double animation_duration);

void update_animation(Animation *anim);

void restart_animation(Animation *anim);

void free_animation(Animation *anim);

#endif
