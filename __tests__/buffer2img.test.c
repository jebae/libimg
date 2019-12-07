#include "libimg.test.h"

static t_im_buffer_info		buf_info;

void		test_buffer2bmp(void)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_buffer2bmp("./__tests__/outputs/buffer2bmp_test.bmp", &buf_info);
}

void		test_buffer2jpg(void)
{
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_buffer2jpg("./__tests__/outputs/buffer2jpg_test.jpg", &buf_info);
}
