#include "libimg.test.h"

int		main(void)
{
	UNITY_BEGIN();
	RUN_TEST_GROUP(for_each_pixel);
	test_rgb();
	test_buffer2bmp();
	test_buffer2jpg();
	test_gaussian_blur();
	test_sephia();
	test_negative();
	UNITY_END();
	return (0);
}
