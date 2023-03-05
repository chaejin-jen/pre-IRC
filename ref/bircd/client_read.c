
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{

			if ((e->fds[i].type == FD_CLIENT) &&
				(i != cs)){
					//printf("<><><>\n");
					//printf("(((%s)))", e->fds[cs].buf_read);
					if (*e->fds[cs].buf_read == 0)
					{
						close(3);
						exit(1);
					}
					
					send(i, e->fds[cs].buf_read, r, 0);
				}
			i++;
		}
	}
}
