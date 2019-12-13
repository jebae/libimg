#include "libimg.h"

int		im_handle_err(const char *msg)
{
	ft_putstr(KRED);
	ft_putstr("libimg Error : ");
	ft_putendl(msg);
	ft_putstr(KNRM);
	return (IM_FAIL);
}
