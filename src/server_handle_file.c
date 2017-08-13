/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handle_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:32:44 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/13 12:43:34 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "server.h"
int		len_tokens(char **tokens)
{
	int c;

	c = 0;
	while (*tokens)
	{
		c++;
		tokens++;
	}
	return (c);
}

void	sock_iter(int sock_fd, int fd)
{
	size_t	read_size;
	size_t	file_size;
	char	buff[SEND_BUFF];
	int		i;
	int		sents;

	file_size = 0;
	i = 0;
	ft_bzero(buff, SEND_BUFF);
	read(sock_fd, buff, SEND_BUFF);
	sents = ft_atoi(buff);
	ft_bzero(buff, SEND_BUFF);
	while (i < sents)
	{
		read_size = recv(sock_fd, buff, SEND_BUFF, 0);
		if (write(fd, buff, read_size) < 0)
		{
			ft_putendl("error writing to file");
			return ;
		}
		file_size += read_size;
		ft_bzero(buff, SEND_BUFF);
		i++;
	}
}

int		file_valid(sock_fd, fd)
{
	if (fd < 0)
	{
		ft_putendl("error creating file");
		write(sock_fd, "ERR", 3);
		return (0);
	}
	return (1);
}

void	get_file(char *file, const int sock_fd)
{
	int		fd;
	char	**tokens;
	int		len;
	char	buff[SEND_BUFF];

	tokens = ft_strsplit(file, '/');
	len = len_tokens(tokens);
	ft_bzero(buff, SEND_BUFF);
	read(sock_fd, buff, SEND_BUFF);
	if (ft_strcmp(buff, "ERR") == 0)
	{
		write(sock_fd, "ERROR", 5);
		return ;
	}
	fd = open(tokens[len - 1], O_WRONLY | O_CREAT, 0644);
	if (!file_valid(sock_fd, fd))
		return ;
	write(sock_fd, "OK", 2);
	ft_putstr("receiving file ");
	ft_putendl(tokens[len - 1]);
	sock_iter(sock_fd, fd);
	close(fd);
	ft_putendl("finished downloading file");
	write(sock_fd, "Upload complete", 15);
	return ;
}
