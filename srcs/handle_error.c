#include "libimg.h"

int		im_handle_err(const char *msg)
{
	ft_putstr("Error : ");
	ft_putendl(msg);
	return (IM_FAIL);
}
