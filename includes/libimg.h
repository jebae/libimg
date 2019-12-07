#ifndef LIBIMG_H
# define LIBIMG_H

# include "libft.h"
# include <stdio.h>
# include <pthread.h>

# define IM_NUM_THREADS		1024
# define IM_SUCCESS			0
# define IM_FAIL			1
# define IM_TRUE			1
# define IM_FALSE			0

typedef struct	s_im_rgb
{
	unsigned int	arr[3];
}				t_im_rgb;

typedef struct	s_im_buffer_info
{
	int				width;
	int				height;
	unsigned int	line_per_th;
	unsigned int	line_rest;
	unsigned char	*buf[2];
}				t_im_buffer_info;

typedef struct	s_im_arg_th
{
	unsigned int	width;
	unsigned int	worksize;
	unsigned int	offset;
	unsigned char	*buf[2];
}				t_im_arg_th;

typedef void	(*func_th)(void *arg_void);

int				im_handle_err(const char *msg);

/*
** img buffer
*/
int				im_for_each_pixel(t_im_buffer_info *buf_info, func_th func);
void			im_set_buffer_info(
	int width,
	int height,
	t_im_buffer_info *buf_info
);
int				im_img2buffer_info(
	const char *filename,
	t_im_buffer_info *buf_info
);
int				im_buffer2bmp(
	const char *output_name,
	t_im_buffer_info *buf_info
);
int				im_buffer2jpg(
	const char *output_name,
	t_im_buffer_info *buf_info
);

/*
** rgb
*/
t_im_rgb		im_hex2rgb(unsigned int hex);
unsigned int	im_rgb2hex(t_im_rgb *rgb);
unsigned int	im_reverse_hex_color(unsigned int hex);
void			im_reverse_color_pixels(void *arg_void);

/*
** filter
*/
int				im_gaussian_blur(
	unsigned int *buffer,
	int width,
	int height
);
int				im_sephia(
	unsigned int *buffer,
	int width,
	int height
);
int				im_negative(
	unsigned int *buffer,
	int width,
	int height
);

#endif
