/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:43:01 by wkrippne          #+#    #+#             */
/*   Updated: 2023/01/11 14:43:01 by wkrippne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_clean(char *st)
{
	char	*out;
	char	*p;
	int		i;

	p = ft_strchr(st, '\n');
	if (!p)
		return (ft_free(st));
	i = p - st + 1;
	if (!st[i])
		return (ft_free(st));
	out = ft_substr(st, i, ft_strlen(st) - i);
	free(st);
	return (out);
}

char	*ft_line(char *st)
{
	char	*out;
	char	*p;
	int		i;

	p = st;
	while (*p != '\n' && *p)
		p++;
	if (*p == '\n')
		i = p - st + 1;
	else
		i = p - st;
	out = ft_substr(st, 0, i);
	return (out);
}

void	*ft_free(char *st)
{
	free(st);
	return (0);
}

char	*ft_read(int fd, char *st)
{
	char	*p;
	int		i;

	i = 1;
	p = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!p)
		return (0);
	*p = '\0';
	while (i > 0 && !ft_strchr(p, '\n'))
	{
		i = read(fd, p, BUFFER_SIZE);
		if (i > 0)
		{
			p[i] = '\0';
			st = ft_strjoin(st, p);
		}
	}
	free(p);
	if (i == -1)
		return (ft_free(st));
	return (st);
}

char	*get_next_line(int fd)
{
	static char	*st;
	char		*out;

	if (fd < 0)
		return (0);
	st = ft_read(fd, st);
	if (!st)
		return (0);
	out = ft_line(st);
	if (!out)
		return (0);
	st = ft_clean(st);
	return (out);
}

int main(void)
{
	int	i = 0;
	printf("%s/n", get_next_line(0));
	printf("%s/n", get_next_line(0));
	printf("%s/n", get_next_line(0));
	return (0);
}