#include "libimg.test.h"

static t_im_buffer_info		buf_info;

void		test_gaussian_blur(void)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_gaussian_blur((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/gaussian_blur_test.jpg", &buf_info);
}

void		test_sephia(void)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_sephia((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/sephia_test.jpg", &buf_info);
}

void		test_negative(void)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_negative((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_buffer2jpg("./__tests__/outputs/negative_test.jpg", &buf_info);
}
