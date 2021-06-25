// 헤더 추가
#include "so_long.h"

int					num_counter(int n)
{
	int				cnt;

	cnt = 1;
	if (-2147483648 < n && n < 0)
		n *= -1;
	else if (n == -2147483648)
	{
		cnt++;
		n = 147483648;
	}
	while (n >= 10)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

char				*positive_num(int n, int n_cnt)
{
	char			*str;

	str = (char *)malloc(sizeof(char) * (n_cnt + 1));
	if (!str)
		return (NULL);
	str[n_cnt] = '\0';
	while (n_cnt--)
	{
		str[n_cnt] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char				*ft_itoa(int n)
{
	int				n_cnt;
	unsigned int	num;
	char			*str;

	n_cnt = num_counter(n);
	if (n < 0)
	{
		str = (char *)malloc(sizeof(char) * (n_cnt + 2));
		if (!str)
			return (NULL);
		num = n * -1;
		str[n_cnt + 1] = '\0';
		while (n_cnt)
		{
			str[n_cnt] = (num % 10) + '0';
			num /= 10;
			n_cnt--;
		}
		str[0] = '-';
		return (str);
	}
	return (positive_num(n, n_cnt));
}

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
			c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *nptr)
{
	long	nbr;
	long	minus;
	int		idx;

	nbr = 0;
	minus = 1;
	idx = 0;
	while (ft_isspace(nptr[idx]) && nptr[idx] != '\0')
		idx++;
	if (nptr[idx] == '-')
		minus = -1;
	if (nptr[idx] == '+' || nptr[idx] == '-')
		idx++;
	while (nptr[idx] != '\0' && ('0' <= nptr[idx] && nptr[idx] <= '9'))
	{
		nbr = (nbr * 10) + (nptr[idx] - '0');
		if (nbr > 2147483647 && minus == 1)
			return (-1);
		if (nbr > 2147483648 && minus == -1)
			return (0);
		idx++;
	}
	return (minus * nbr);
}