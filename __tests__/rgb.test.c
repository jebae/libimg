#include "libimg.test.h"

void	test_hex2rgb(void)
{
	t_im_rgb		expected = (t_im_rgb){0xf2, 0x78, 0xa0};
	unsigned int	hex = 0xf278a0;
	t_im_rgb		rgb;

	rgb = im_hex2rgb(hex);
	(void)expected;
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected, &rgb, sizeof(t_im_rgb), "rgb");
}

void	test_im_rgb2hex(void)
{
	unsigned int	expected = 0xf278a0;
	t_im_rgb		rgb = {0xf2, 0x78, 0xa0};
	unsigned int	hex;

	hex = im_rgb2hex(&rgb);
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected, hex, "hex");
}

void	test_reverse_hex_color(void)
{
	unsigned int	hex = 0xc8bcc0;
	unsigned int	res;

	res = im_reverse_hex_color(hex);
	TEST_ASSERT_EQUAL_INT_MESSAGE(0xc0bcc8, res, "reverse hex color");
}

void	test_rgb(void)
{
	RUN_TEST(test_hex2rgb);
	RUN_TEST(test_im_rgb2hex);
	RUN_TEST(test_reverse_hex_color);
}
