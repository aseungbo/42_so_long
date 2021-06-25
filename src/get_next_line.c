// 헤더 추가
#include "so_long.h"

int		check_newline(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_backup(char *backup)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!backup)
		return (0);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (0);
	}
	if (!(rtn = malloc(sizeof(char) * ((ft_gnl_strlen(backup) - i) + 1))))
		return (0);
	i++;
	while (backup[i])
		rtn[j++] = backup[i++];
	rtn[j] = '\0';
	free(backup);
	return (rtn);
}

char	*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*backup[OPEN_MAX];
	int				reader;

	reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!check_newline(backup[fd]) && reader != 0)
	{
		if ((reader = read(fd, buff, BUFFER_SIZE)) == -1)
			return (-1);
		buff[reader] = '\0';
		backup[fd] = ft_gnl_strjoin(backup[fd], buff);
	}
	free(buff);
	*line = get_line(backup[fd]);
	backup[fd] = get_backup(backup[fd]);
	if (reader == 0)
		return (0);
	return (1);
}
