#include "libimg.test.h"

static t_im_buffer_info		buf_info;

TEST_GROUP(filter);

TEST_SETUP(filter) {}

TEST_TEAR_DOWN(filter)
{
	ft_memdel((void **)&buf_info.buf[0]);
}

TEST(filter, gaussian_blur)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	for (int i=0; i < 2; i++)
		im_gaussian_blur((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/gaussian_blur_test.jpg", &buf_info);
}

TEST(filter, sephia)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_sephia((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/sephia_test.jpg", &buf_info);
}

TEST(filter, negative)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_negative((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/negative_test.jpg", &buf_info);
}

TEST(filter, gray_scale)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_gray_scale((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/gray_scale_test.jpg", &buf_info);
}

TEST_GROUP_RUNNER(filter)
{
	RUN_TEST_CASE(filter, gaussian_blur);
	RUN_TEST_CASE(filter, sephia);
	RUN_TEST_CASE(filter, negative);
	RUN_TEST_CASE(filter, gray_scale);
}
