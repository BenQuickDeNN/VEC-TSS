#include <cstdio>

#include "tile-factor-selection.h"

void test1();

/**
 * @brief main function
 * @param argc count of arguments
 * @param argv values of arguments, including vector width (V), array height (H) and data width (W)
 * @return exit status
 */
int main(int argc, char** argv)
{
    test1();
    return 0;
}

void test1()
{
    std::printf("J = %d\r\n", getBestTileFactor(4, 13, 13));
}