# libimg

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/08153e1a101f458a995d61bc500517c1)](https://www.codacy.com/manual/jebae/libimg?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jebae/libimg&amp;utm_campaign=Badge_Grade)

C library libimg is made to handle image buffer.

<br><br>

## Requirements

This library is using [libft](https://github.com/jebae/libft) as alternative of standard lib functions. So at first download or git clone libft and put it in same path with libimg.

```
# download libft
git clone https://github.com/jebae/libft.git

# directory structure of libft and libimg
root/
  libft/
  libimg/
```

Instead of putting libft in same path with libimg, you can modify [Makefile](./Makefile) macro `LIBFT_PATH = ../libft` with your libft path.

<br><br>

## Installation

```
make
```

<br><br>

## Features

### buffer

```c
typedef struct	s_im_buffer_info
{
	int		width;
	int		height;
	unsigned int	line_per_th;
	unsigned int	line_rest;
	unsigned char	*buf[2];
}		t_im_buffer_info;

void im_set_buffer_info(
	int width,
	int height,
	t_im_buffer_info *buf_info
);
```

`t_im_buffer_info` is base struct to save image buffer and information to be used by thread.
`t_im_buffer_info` can be set with `im_set_buffer_info`. 

<br>

```c
int im_img2buffer_info(
	const char *filename,
	t_im_buffer_info *buf_info
);
```

`im_img2buffer_info` read image file with `filename`, save buffer in `buf_info->buf[0]` and set buffer info. It uses `stbi_load` to read all format of image. It returns `IM_FAIL` if read file failed or lack of memory, else `IM_SUCCESS`. 

<br>

```c
int im_buffer2bmp(
	const char *output_name,
	t_im_buffer_info *buf_info
);

int im_buffer2jpg(
	const char *output_name,
	t_im_buffer_info *buf_info
);
```

`im_buffer2bmp` and `im_buffer2jpg` write image file from `buf_info.buf[0]` buffer. It returns `IM_FAIL` if write file failed or thread error or lack of memory, else `IM_SUCCESS`.

<br><br>

### filter

```c
int im_gaussian_blur(
	unsigned int *buffer,
	int width,
	int height
);

int im_sephia(
	unsigned int *buffer,
	int width,
	int height
);

int im_negative(
	unsigned int *buffer,
	int width,
	int height
);

int im_gray_scale(
	unsigned int *buffer,
	int width,
	int height
);
```

Each filter functions returns `IM_FAIL` if thread error or lack of memory, else `IM_SUCCESS`.

<br>

*origin*
<br>
<img src="https://www.dropbox.com/s/7l4l904csunjnwe/sample.png?raw=1" width="50%">

<br>

*gaussian blur*
<br>
<img src="https://www.dropbox.com/s/tcdbrhm5ugpafbo/gaussian_blur_test.jpg?raw=1" width="50%">

<br>

*sephia*
<br>
<img src="https://www.dropbox.com/s/oabqo0ed6na1sny/sephia_test.jpg?raw=1" width="50%">

<br>

*negative*
<br>
<img src="https://www.dropbox.com/s/nl4qr5ef60h5ihq/negative_test.jpg?raw=1" width="50%">

<br>

*gray scale*
<br>
<img src="https://www.dropbox.com/s/o0hnitxgqh7vl7o/gray_scale_test.jpg?raw=1" width="50%">

<br><br>

### edge detect

```c
int im_canny_edge_detect(
	unsigned int *img_buf,
	t_im_edge_gradient *grad_buf,
	int width,
	int height
);
```

`im_canny_edge_detect` uses already malloced buffer `grad_buf` as result buffer. `grad_buf` has to be malloced with proper size regarding width and height before calling function. Each pixel value of `grad_buf` is struct `t_im_edge_gradient`.

```c
typedef struct	s_im_edge_gradient
{
	float	theta;
	float	magnitude;
}		t_im_edge_gradient;
```

`theta` represents direction of edge and `magnitude` represents magnitude literally. `magnitude` value will be assigned between 0.0 and 1.0. More bigger value means more edge like pixel. It returns `IM_FAIL` if thread error or lack of memory, else `IM_SUCCESS`.

<br>

*edge detect*
<br>
<img src="https://www.dropbox.com/s/pu1qdjg4ac913bk/canny_edge_detect_test.jpg?raw=1" width="50%">