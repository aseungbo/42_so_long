#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char *dst;

	if (!(dst = (char *)malloc(ft_strlen(s) + 1)))
		return (0);
	ft_memcpy(dst, s, ft_strlen(s));
	*(dst + ft_strlen(s)) = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *rst;

	if (!(rst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_memcpy(rst, s1, ft_strlen(s1));
	ft_memcpy(rst + ft_strlen(s1), s2, ft_strlen(s2));
	*(rst + ft_strlen(s1) + ft_strlen(s2)) = '\0';
	return (rst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	m_len;
	char	*rst;

	if (!s || ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	if ((start + len) >= ft_strlen(s))
		m_len = ft_strlen(s) - start;
	else
		m_len = len;
	if (!(rst = malloc(sizeof(char) * m_len + 1)))
		return (NULL);
	ft_memcpy(rst, &s[start], m_len);
	rst[m_len] = '\0';
	return (rst);
}
