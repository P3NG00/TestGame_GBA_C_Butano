#include "bn_fixed.h"

bn::fixed seconds_to_frames(bn::fixed seconds)
{
    return seconds * 60;
}
