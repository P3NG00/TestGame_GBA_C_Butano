#ifndef TG_CONSTANTS_HPP
#define TG_CONSTANTS_HPP

#include "bn_fixed.h"

#define FRAMES_PER_SECOND 60
#define NORMALIZED bn::fixed(0.71) // rounded up from 1/sqrt(2)
#define ENTITY_DISTANCE_CHECK bn::fixed(12) // distance from enemies or player to check collision

#endif
