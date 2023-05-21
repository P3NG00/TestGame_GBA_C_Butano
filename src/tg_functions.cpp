#include "bn_fixed.h"

#define FRAMES_PER_SECOND 60

int seconds_to_frames(bn::fixed seconds)
{
    return (seconds * FRAMES_PER_SECOND).integer();
}
