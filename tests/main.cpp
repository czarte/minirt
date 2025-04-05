//
// Created by Vojtech Parkan on 04/05/25.
//

#include "../googletest/googletest/include/gtest/gtest.h"
extern "C" {
#include "../include/minirt.h"
#include "../include/vec.h"
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}