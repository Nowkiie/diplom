#include <gtest/gtest.h>

#include "../radio_track/calculate/calculateTile.h"

using namespace track;

std::unique_ptr<workWithTile> wwt_ = std::make_unique<workWithTile>();

TEST(sfda, ajgh) {
    QPoint test = wwt_->calcCoordTileInCombinedImage(2, 2);

    ASSERT_TRUE(test.x() == 0);
    ASSERT_TRUE(test.y() == 256);
}