#include "libimg.h"

static int		handle_thread_err(pthread_t *tid)
{
	unsigned int	i;

	i = 0;
	while (i < IM_NUM_THREADS)
	{
		pthread_cancel(tid[i]);
		i++;
	}
	return (IM_FAIL);
}

static void		set_arg_th(
	t_im_buffer_info *buf_info,
	unsigned int offset,
	unsigned int worksize,
	t_im_arg_th *arg
)
{
	ft_memcpy(arg->buf, buf_info->buf, sizeof(unsigned char *) * 2);
	arg->offset = offset;
	arg->worksize = worksize;
	arg->width = buf_info->width;
}

static int		distribute_work(
	t_im_buffer_info *buf_info,
	t_im_arg_th *arg,
	pthread_t *tid,
	void *(*func)(void *arg)
)
{
	unsigned int	i;
	unsigned int	offset;
	unsigned int	worksize;

	offset = 0;
	worksize = buf_info->width * (buf_info->line_per_th + 1);
	i = 0 - 1;
	while (++i < buf_info->line_rest)
	{
		set_arg_th(buf_info, offset, worksize, arg + i);
		if (pthread_create(tid + i, NULL, func, arg + i) != 0)
			return (im_handle_err("Fail to create pthread"));
		offset += worksize;
	}
	if ((worksize = worksize - buf_info->width) == 0)
		return (IM_SUCCESS);
	while (i < IM_NUM_THREADS)
	{
		set_arg_th(buf_info, offset, worksize, arg + i);
		if (pthread_create(tid + i, NULL, func, arg + i) != 0)
			return (im_handle_err("Fail to create pthread"));
		offset += worksize;
		i++;
	}
	return (IM_SUCCESS);
}

int				im_for_each_pixel(t_im_buffer_info *buf_info, func_th func)
{
	int				num_thread;
	t_im_arg_th		arg[IM_NUM_THREADS];
	pthread_t		tid[IM_NUM_THREADS];

	if (buf_info->line_per_th == 0)
		num_thread = buf_info->height;
	else
		num_thread = IM_NUM_THREADS;
	if (distribute_work(buf_info, arg, tid, (void *)func) == IM_FAIL)
		return (handle_thread_err(tid));
	while (num_thread--)
	{
		if (pthread_join(tid[num_thread], NULL) != 0)
			return (handle_thread_err(tid));
	}
	return (IM_SUCCESS);
}

void			im_set_buffer_info(
	int width,
	int height,
	t_im_buffer_info *buf_info
)
{
	buf_info->width = width;
	buf_info->height = height;
	buf_info->line_per_th = height / IM_NUM_THREADS;
	buf_info->line_rest = height % IM_NUM_THREADS;
}
