#include "visualization.h"
#include <gtest/gtest.h>


int main(int argc, char **argv)
{
    try {
        visualization();
    } catch (const char* msg) {
        std::cerr << msg << "\n";
    }

    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();

    return 0;
}
