/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 08:32:11 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/28 08:34:32 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	usage(void)
{
	ft_putendl("usage: ./server <port>");
}

void	handle_client(int client_sockfd, char *cwd)
{
	char	buff[BUFF_SIZE];
	char	*str;

	str = NULL;
	ft_bzero(buff, BUFF_SIZE);
	while ((recv(client_sockfd, buff, BUFF_SIZE, 0)) > 0)
	{
		str = ft_strtrim(buff);
		handle_request(str, client_sockfd, cwd);
		ft_bzero(buff, ft_strlen(buff));
	}
}

void	init(char **argv, int server_sockfd, char *cwd)
{
	int					client_sockfd;
	unsigned int		client_len;
	unsigned int		server_len;
	struct sockaddr_in	server_address;
	struct sockaddr_in	client_address;

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(ft_atoi(argv[1]));
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
	listen(server_sockfd, 5);
	signal(SIGCHLD, SIG_IGN);
	while (1)
	{
		ft_putendl("server waiting");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
				(struct sockaddr*)&client_address, &client_len);
		if (client_sockfd)
			ft_putendl("New connection established");
		if (fork() == 0)
			handle_client(client_sockfd, cwd);
	}
	close(client_sockfd);
}

int		main(int argc, char **argv)
{
	int		server_sockfd;
	char	*cwd;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (argc != 2)
	{
		usage();
		return (1);
	}
	cwd = getcwd(NULL, 0);
	init(&*argv, server_sockfd, cwd);
	return (0);
}
