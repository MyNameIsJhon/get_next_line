/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:30:38 by jriga             #+#    #+#             */
/*   Updated: 2025/04/12 17:30:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>

static char	*append_line(char *line, char *buf, char *nl)
{
	char	*temp;
	char	*newl;

	if (!line)
	{
		if (nl)
			newl = ft_substr(buf, 0, nl - buf + 1);
		else
			newl = ft_strdup(buf);
	}
	else
	{
		if (nl)
			temp = ft_substr(buf, 0, nl - buf + 1);
		else
			temp = ft_strdup(buf);
		newl = ft_strjoin(line, temp);
		free(line);
		free(temp);
	}
	return (newl);
}

static void	shift_buffer(char *buf)
{
	char	*nl;
	int		i;
	int		j;

	nl = ft_strchr(buf, '\n');
	if (!nl)
		return ;
	i = nl - buf + 1;
	j = 0;
	while (buf[i + j])
	{
		buf[j] = buf[i + j];
		j++;
	}
	buf[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*nl;
	char		*line;
	ssize_t		bytes;

	line = NULL;
	while (1)
	{
		nl = ft_strchr(buf, '\n');
		if (!nl)
		{
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
				break ;
			buf[bytes] = '\0';
			nl = ft_strchr(buf, '\n');
		}
		line = append_line(line, buf, nl);
		shift_buffer(buf);
		if (nl)
			break ;
	}
	return (line);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* 	char fd; */
/* 	char *get; */
/**/
/* 	fd = open("./README.md", O_RDONLY); */
/**/
/* 	for(int i; i < 3 ; i++) */
/* 	{ */
/* 		get = get_next_line(fd); */
/* 		printf("%s", get); */
/* 		free(get); */
/* 	} */
/* } */
