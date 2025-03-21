#pragma once

// (c) Copyright Dmitriy Shikhov 2016

#define UTILS_CHECK_CLOSE_COLLECTIONS(L, L_END, R, R_END, T)                   \
    do                                                                         \
    {                                                                          \
        auto left = L;                                                         \
        auto left_end = L_END;                                                 \
        auto right = R;                                                        \
        auto right_end = R_END;                                                \
        auto tolerance = T;                                                    \
                                                                               \
        size_t pos = 0;                                                        \
        for (; left != left_end && right != right_end; ++left, ++right, ++pos) \
        {                                                                      \
            BOOST_TEST_INFO("Check close at position " << pos);                \
            BOOST_CHECK_CLOSE(*left, *right, tolerance);                       \
        }                                                                      \
                                                                               \
        if (left != left_end)                                                  \
        {                                                                      \
            auto r_size = pos;                                                 \
            while (left != left_end)                                           \
            {                                                                  \
                ++pos;                                                         \
                ++left;                                                        \
            }                                                                  \
            BOOST_TEST_INFO("Collections size mismatch");                      \
            BOOST_CHECK_EQUAL(pos, r_size);                                    \
        }                                                                      \
                                                                               \
        if (right != right_end)                                                \
        {                                                                      \
            auto l_size = pos;                                                 \
            while (right != right_end)                                         \
            {                                                                  \
                ++pos;                                                         \
                ++right;                                                       \
            }                                                                  \
            BOOST_TEST_INFO("Collections size mismatch");                      \
            BOOST_CHECK_EQUAL(l_size, pos);                                    \
        }                                                                      \
    } while (false);                                                           \
    /**/
