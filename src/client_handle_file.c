/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handle_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 14:53:53 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/14 17:47:52 by mmoliele         ###   ########.fr       */
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

void	put_file(char *filename, const int sock_fd)
{
	int				size;
	int				fd;
	int				status;
	char			*buff;
//	char			rec[10];
	struct stat		s;

	printf("filename %s\n", filename);
	if ((fd = open(ft_strtrim(filename), O_RDONLY)))
	{
		status = fstat(fd, &s);
		size = s.st_size;
		buff = ft_strjoin(
				ft_strjoin("put ", ft_itoa(size)),ft_strjoin(" ", filename));
		printf("%d , %d , nm=%s\n\n", size, fd, buff);
		send(sock_fd, buff, ft_strlen(buff), 0);
		
	/*	int x = read(sock_fd, buff, 10);
		buff[x] = '\0';
		printf("\n\nStatus: %s\n\n", buff);
	*/	free(buff);
		
		buff = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
		printf("\n%d, \n%s\n", sock_fd, buff);
		send(sock_fd, buff, size, 0);
		munmap(buff, size);
		close(fd);
	}
}
