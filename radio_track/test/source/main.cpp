#ifdef _WIN32
#    include <clocale>
#endif
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
#ifdef _WIN32
    setlocale(LC_ALL, ".utf-8");
#endif

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
