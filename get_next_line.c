#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		size = 0;
	else if (slen - start < len)
		size = (slen - start);
	else
		size = len;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*origin;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = (char *)malloc(((len_s1 + len_s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	origin = ptr;
	while (*s1)
	{
		*ptr++ = *s1++;
	}
	while (*s2)
	{
		*ptr++ = *s2++;
	}
	*ptr = '\0';
	return (origin);
}

static	char	*help_get(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*buf_tmp;

	read_line = 1;
	while (read_line)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		buf_tmp = backup;
		backup = ft_strjoin(buf_tmp, buf);
		free(buf_tmp);
		buf_tmp = NULL;
		if (!backup)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_line(char *line)
{
	size_t		count;
	char		*backup;

	count = 0;
	while (line[count] && line[count] != '\n')
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
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = help_get(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
	{
		if (backup)
			free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract_line(line);
	return (line);
}