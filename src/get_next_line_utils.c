#include "so_long.h"

size_t		ft_gnl_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_gnl_strjoin(char const *backup, char const *buff)
{
	char	*rst;
	size_t	backup_len;
	size_t	buff_len;
	size_t	all_len;

	if (!backup && !buff)
		return (0);
	backup_len = ft_gnl_strlen((char *)backup);
	buff_len = ft_gnl_strlen((char *)buff);
	all_len = backup_len + buff_len + 1;
	rst = malloc(sizeof(char) * all_len);
	if (!rst)
		return (0);
	ft_gnl_memcpy(rst, backup, backup_len);
	ft_gnl_memcpy(rst + backup_len, buff, buff_len);
	*(rst + backup_len + buff_len) = '\0';
	free((char *)(backup));
	return (rst);
}

void *ft_gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	const unsigned char *s;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}