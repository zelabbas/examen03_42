#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif


int	ft_strlen(char *str)
{
	int i = -1;

	while (str[++i])
		;
	return (i);
}

char *ft_substr(char *str, unsigned int start, size_t len)
{
	size_t size;
	size_t	len_s;
	char *res;
	size_t i;

	if (!str)
		return (NULL);
	len_s = ft_strlen(str);
	if (start >= len_s)
		size = 0;
	else if (len_s - start < len)
		size = len_s - start;
	else
		size = len;
	res = malloc (size + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = str[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_strdup(char *str)
{
	char *res;
	int i;
	int len_s;

	if (!str)
		return (NULL);
	len_s = ft_strlen(str);
	res = malloc(len_s + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_strcher(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (!(char)c)
		return (str);
	return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *ptr;
	char *origin;

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	origin = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (origin);
}

char *help_get(int fd, char *buff, char *backup)
{
	char *tmp;
	int read_line;

	read_line = 1;
	while (read_line)
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break;
		buff[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(tmp , buff);
		free(tmp);
		if (!backup)
			return (NULL);
		if (ft_strcher(backup, '\n'))
			break;
	}
	return (backup);
}

char *ft_extract_line(char *line)
{
	int count;
	char *backup;

	count = 0;
	while (line[count] && line[count] != 'n')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (!backup)
	{
		if (line)
			free(line);
		line = NULL;
		return (NULL);
	}
	if (*backup == '\0')
	{
		free(backup);
		backup = (NULL);
	}
	line[count + 1] = '\0';
	return (backup);
}

char *get_next_line(int fd)
{
	static char *backup;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
	{
		if (backup)
			free(backup);
		backup = NULL;
		return (NULL);
	}
	line = help_get(fd, buff, backup);
	free(buff);
	if (!line)
	{
		if (backup)
			free (backup);
		backup = NULL;
		return (NULL);
	}
	backup = ft_extract_line(line);
	return (line);
}