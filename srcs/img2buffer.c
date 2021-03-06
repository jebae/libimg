#include "libimg.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int				im_img2buffer_info(
	const char *filename,
	t_im_buffer_info *buf_info
)
{
	buf_info->buf[0] = stbi_load(
		filename, &buf_info->width, &buf_info->height, NULL, STBI_rgb_alpha);
	if (buf_info->buf[0] == NULL)
		return (im_handle_err("Fail to load image"));
	im_set_buffer_info(buf_info->width, buf_info->height, buf_info);
	if (im_for_each_pixel(buf_info, &im_reverse_color_pixels) == IM_FAIL)
		return (IM_FAIL);
	return (IM_SUCCESS);
}
