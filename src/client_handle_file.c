/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handle_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 14:53:53 by mmoliele          #+#    #+#             */
/*   Updated: 2017/07/16 18:41:32 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "client.h"

int		args_ok(int argc, char *usage, int num, char **argv)
{
	if (argc != num)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putendl(usage);
		return (0);
	}
	return (1);
}

int		sent_count(char *file)
{
	int		sent_count;
	char	buff[SEND_BUFF];
	int		fd;

	fd = open(file, O_RDONLY);
	sent_count = 0;
	ft_bzero(buff, SEND_BUFF);
	while (read(fd, buff, SEND_BUFF) > 0)
	{
		sent_count++;
		ft_bzero(buff, SEND_BUFF);
	}
	return (sent_count);
}

void	file_iter(int sock_fd, int fd)
{
	char	buff[SEND_BUFF];
	size_t	sent_size;
	size_t	file_size;
	size_t	read_size;

	file_size = 0;
	ft_bzero(buff, SEND_BUFF);
	while ((read_size = read(fd, buff, SEND_BUFF)) > 0)
	{
		sent_size = send(sock_fd, buff, read_size, 0);
		if (sent_size < read_size)
		{
			ft_putendl("Error:send error");
			return ;
		}
		file_size += sent_size;
		ft_bzero(buff, SEND_BUFF);
	}
}

void	finish(int sock_fd, int fd, char *file)
{
	ft_putstr("sending file ...");
	ft_putendl(file);
	file_iter(sock_fd, fd);
	close(fd);
	ft_putendl("Sending file complete");
}

void	put_file(char *file, const int sock_fd)
{
	int		fd;
	char	buff[SEND_BUFF];
	int		sents;

	if ((fd = open(ft_strtrim(file), O_RDONLY)) < 0)
	{
		ft_putendl("Error:File not found");
		write(sock_fd, "ERR", 3);
		return;
	}
	write(sock_fd, "OK", 2);
	ft_bzero(buff, SEND_BUFF);
	read(sock_fd, buff, SEND_BUFF);
	if (ft_strcmp(buff, "ERR") == 0)
	{
		ft_putendl("Sending file error");
		return;
	}
	sents = sent_count(file);
	write(sock_fd, ft_itoa(sents), ft_strlen(ft_itoa(sents)));
	finish(sock_fd, fd, file);
}
