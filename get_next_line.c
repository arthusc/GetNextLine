#include "get_next_line.h"

int		ft_mycpy(char **dst, char *src)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while (src[i] != '\n')
		i++;
	CHECKMALLOC((tmp = (char*)malloc(sizeof(char) * i + 1)));
	i = -1;
	while (src[++i] != '\n')
		tmp[i] = src[i];
	tmp[i] = '\0';
	*dst = tmp;
	i += 1;
	while (src[i] != '\0')
	{
		src[j] = src[i];
		i++;
		j++;
	}
	src[j] = '\0';
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock[NBFD];
	char		buf[BUFF_SIZE + 1];
	int			r;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) || fd > NBFD)
		return (-1);
	if (stock[fd] == NULL)
		CHECKMALLOC((stock[fd] = malloc(1)));
	if (stock[fd] && (ft_strchr(stock[fd], '\n') != 0))
		return (ft_mycpy(line, stock[fd]));
	while ((r = read(fd, buf, BUFF_SIZE)))
	{
		buf[r] = '\0';
		stock[fd] = ft_joinfree(stock[fd], buf, &stock[fd]);
		if (ft_strchr(stock[fd], '\n') != 0)
			return (ft_mycpy(line, stock[fd]));
	}
	if (stock[fd][0] != '\0')
	{
		CHECKMALLOC((*line = malloc(ft_strlen(stock[fd]))));
		*line = ft_strcpy(*line, stock[fd]);
		bzero(stock[fd], ft_strlen(stock[fd]));
		return (1);
	}
	return (0);
}


/*
int main (int argc,char **argv)
{
	if ( argc < 1)
		return (0);
	char *line;
	int fd;
	fd = open(argv[1], O_RDONLY);
	while ((get_next_line(fd, &line)))
		ft_putendl(line);
	return (0);
}
*/
