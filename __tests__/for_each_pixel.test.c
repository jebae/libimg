#include "libimg.test.h"

static unsigned int			*buffer;
static int					width;
static int					height;
static int					size;
static int					res;
static t_im_buffer_info		buf_info;

static void		func(void *arg_void)
{
	unsigned int	i;
	unsigned int	*buf;
	t_im_arg_th		*arg;

	arg = (t_im_arg_th *)arg_void;
	buf = (unsigned int *)arg->buf[0] + arg->offset;
	i = 0;
	while (i < arg->worksize)
	{
		buf[i] = 0xff;
		i++;
	}
}

TEST_GROUP(for_each_pixel);

TEST_SETUP(for_each_pixel) {}

TEST_TEAR_DOWN(for_each_pixel)
{
	ft_memdel((void **)&buffer);
}

TEST(for_each_pixel, case_one_line_per_thread)
{
	width = 21;
	height = IM_NUM_THREADS - 10;
	size = width * height;
	buffer = ft_memalloc(sizeof(unsigned int) * size);
	im_set_buffer_info(width, height, &buf_info);
	buf_info.buf[0] = (unsigned char *)buffer;

	res = im_for_each_pixel(&buf_info, (void *)&func);
	TEST_ASSERT_EQUAL_INT_MESSAGE(IM_SUCCESS, res, "res");
	for (int i=0; i < size; i++)
		TEST_ASSERT_EQUAL_INT_MESSAGE(0xff, buffer[i], "buffer value");
}

TEST(for_each_pixel, case_multi_line_per_thread)
{
	width = 21;
	height = IM_NUM_THREADS * 2 + 10;
	size = width * height;
	buffer = ft_memalloc(sizeof(unsigned int) * size);
	im_set_buffer_info(width, height, &buf_info);
	buf_info.buf[0] = (unsigned char *)buffer;

	res = im_for_each_pixel(&buf_info, (void *)&func);
	TEST_ASSERT_EQUAL_INT_MESSAGE(IM_SUCCESS, res, "res");
	for (int i=0; i < size; i++)
		TEST_ASSERT_EQUAL_INT_MESSAGE(0xff, buffer[i], "buffer value");
}

TEST_GROUP_RUNNER(for_each_pixel)
{
	RUN_TEST_CASE(for_each_pixel, case_one_line_per_thread);
	RUN_TEST_CASE(for_each_pixel, case_multi_line_per_thread);
}

void	test_for_each_pixel(void)
{
	RUN_TEST_GROUP(for_each_pixel);
}
