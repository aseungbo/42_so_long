#include "so_long.h"

void				ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void				ft_putstr_fd(char *s, int fd)
{
	size_t			idx;

	idx = 0;
	if (!s)
		return ;
	while (s[idx])
	{
		ft_putchar_fd(s[idx], fd);
		idx++;
	}
}

