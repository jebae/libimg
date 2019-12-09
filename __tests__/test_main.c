#include "libimg.test.h"

int		main(int argc, char **args)
{
	UNITY_BEGIN();
	RUN_TEST_GROUP(for_each_pixel);
	RUN_TEST_GROUP(filter);
	RUN_TEST_GROUP(edge_detect);
	test_rgb();
	UNITY_END();
	if (argc >= 2 && ft_strcmp(args[1], "leak") == 0)
		while (1);
	return (0);
}
