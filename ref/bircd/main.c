
#include <unistd.h>
#include "bircd.h"

int	main(int ac, char **av)
{
	t_env	e;

	init_env(&e);
	get_opt(&e, ac, av);
	srv_create(&e, e.port);
	main_loop(&e);
	close(3);
	return (0);
}
