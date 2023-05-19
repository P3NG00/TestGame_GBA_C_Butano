#include "bn_core.h"

using namespace bn;

int main()
{
    // init butano
    core::init();

    // game loop
    while(true)
    {
        // TODO game handling

        // update butano last
        core::update();
    }
}
