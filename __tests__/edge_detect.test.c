#include "libimg.test.h"

static t_im_buffer_info		buf_info;
static float				gmax;

static void		get_edge_img(void *arg_void)
{
	t_im_arg_th			*arg;
	unsigned int		*img_buf;
	unsigned int		hex;
	t_im_edge_gradient	*grad_buf;

	arg = (t_im_arg_th *)arg_void;
	img_buf = (unsigned int *)arg->buf[0] + arg->offset;
	grad_buf = (t_im_edge_gradient *)arg->buf[1] + arg->offset;
	for (unsigned int i=0; i < arg->worksize; i++)
	{
		hex = (grad_buf[i].magnitude / gmax) * 0xff;
		img_buf[i] = 0;
		img_buf[i] += hex;
		img_buf[i] <<= 8;
		img_buf[i] += hex;
		img_buf[i] <<= 8;
		img_buf[i] += hex;
	}
}

static void		get_edge_img2(void *arg_void)
{
	t_im_arg_th			*arg;
	unsigned int		*img_buf;
	unsigned int		hex;
	t_im_edge_gradient	*grad_buf;

	arg = (t_im_arg_th *)arg_void;
	img_buf = (unsigned int *)arg->buf[0] + arg->offset;
	grad_buf = (t_im_edge_gradient *)arg->buf[1] + arg->offset;
	for (unsigned int i=0; i < arg->worksize; i++)
	{
		hex = grad_buf[i].magnitude * 0xff;
		img_buf[i] = 0;
		img_buf[i] += hex;
		img_buf[i] <<= 8;
		img_buf[i] += hex;
		img_buf[i] <<= 8;
		img_buf[i] += hex;
	}
}

TEST_GROUP(edge_detect);

TEST_SETUP(edge_detect)
{
	buf_info.buf[0] = NULL;
	buf_info.buf[1] = NULL;
}

TEST_TEAR_DOWN(edge_detect)
{
	ft_memdel((void **)&buf_info.buf[0]);
	ft_memdel((void **)&buf_info.buf[1]);
}

TEST(edge_detect, sobel)
{
	// get image buffer and remove noise
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_gray_scale((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_gaussian_blur((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);

	// prepare gradients buffer and calculate gradient by sobel
	buf_info.buf[1] = ft_memalloc(
		sizeof(t_im_edge_gradient) * buf_info.width * buf_info.height);
	im_sobel(
		(unsigned int *)buf_info.buf[0],
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// get max magnitude
	im_max_gradient(
		(t_im_edge_gradient *)buf_info.buf[1],
		&gmax, buf_info.width, buf_info.height);

	// get example image to test sobel
	im_set_buffer_info(buf_info.width, buf_info.height, &buf_info);
	im_for_each_pixel(&buf_info, &get_edge_img);
	im_buffer2jpg("./__tests__/outputs/sobel_test.jpg", &buf_info);
}

TEST(edge_detect, non_maximum_suppression)
{
	// get image buffer and remove noise
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_gray_scale((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_gaussian_blur((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);

	// prepare gradients buffer and calculate gradient by sobel
	buf_info.buf[1] = ft_memalloc(
		sizeof(t_im_edge_gradient) * buf_info.width * buf_info.height);
	im_sobel(
		(unsigned int *)buf_info.buf[0],
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// non maximum suppression
	im_non_maximum_suppression(
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// get max magnitude
	im_max_gradient(
		(t_im_edge_gradient *)buf_info.buf[1],
		&gmax, buf_info.width, buf_info.height);

	// get example image to test non maximum suppression
	im_set_buffer_info(buf_info.width, buf_info.height, &buf_info);
	im_for_each_pixel(&buf_info, &get_edge_img);
	im_buffer2jpg("./__tests__/outputs/non_maximum_suppression_test.jpg", &buf_info);
}

TEST(edge_detect, hysteresis_thresholding)
{
	// get image buffer and remove noise
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);
	im_gray_scale((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);
	im_gaussian_blur((unsigned int *)buf_info.buf[0], buf_info.width, buf_info.height);

	// prepare gradients buffer and calculate gradient by sobel
	buf_info.buf[1] = ft_memalloc(
		sizeof(t_im_edge_gradient) * buf_info.width * buf_info.height);
	im_sobel(
		(unsigned int *)buf_info.buf[0],
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// non maximum suppression
	im_non_maximum_suppression(
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// hysteresis thresholding
	im_hysteresis_thresholding(
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height, &gmax);

	// get example image to test non maximum suppression
	im_set_buffer_info(buf_info.width, buf_info.height, &buf_info);
	im_for_each_pixel(&buf_info, &get_edge_img);
	im_buffer2jpg("./__tests__/outputs/hysteresis_thresholding_test.jpg", &buf_info);
}

TEST(edge_detect, canny_edge_detect)
{
	// get image buffer
	im_img2buffer_info("./__tests__/samples/sample.png", &buf_info);

	// edge detect
	buf_info.buf[1] = ft_memalloc(
		sizeof(t_im_edge_gradient) * buf_info.width * buf_info.height);
	im_canny_edge_detect(
		(unsigned int *)buf_info.buf[0],
		(t_im_edge_gradient *)buf_info.buf[1],
		buf_info.width, buf_info.height);

	// get example image to test non maximum suppression
	im_set_buffer_info(buf_info.width, buf_info.height, &buf_info);
	im_for_each_pixel(&buf_info, &get_edge_img2);
	im_buffer2jpg("./__tests__/outputs/canny_edge_detect_test.jpg", &buf_info);
}

TEST_GROUP_RUNNER(edge_detect)
{
	RUN_TEST_CASE(edge_detect, sobel);
	RUN_TEST_CASE(edge_detect, non_maximum_suppression);
	RUN_TEST_CASE(edge_detect, hysteresis_thresholding);
	RUN_TEST_CASE(edge_detect, canny_edge_detect);
}
