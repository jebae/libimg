#include "libimg.test.h"

int		main(void)
{
	UNITY_BEGIN();
	RUN_TEST_GROUP(for_each_pixel);
	RUN_TEST_GROUP(filter);
	test_rgb();
	UNITY_END();
	return (0);
}
