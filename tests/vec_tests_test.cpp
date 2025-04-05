#include "../googletest/googletest/include/gtest/gtest.h"
extern "C" {
#include "../include/minirt.h"
#include "../include/vec.h"
}

TEST(Tests, VecTests) {
	t_vec *a = new_vec(3, 0.7, 1);
    t_vec *b = new_vec(1, 0.5, 0);

    double len_a = vec_length(a);
    double len_b = vec_length(b);
   	ASSERT_EQ(len_a, len_b);

}
