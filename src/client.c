/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 11:33:00 by mmoliele          #+#    #+#             */
/*   Updated: 2017/07/16 11:41:20 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../inc/client.h"

void	init(char **argv, int sockfd)
{
	int					len;
	int					result;
	struct sockaddr_in	address;

	len = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(argv[1]);
	address.sin_port = ft_atoi(argv[2]);
	result = connect(sockfd, (struct sockaddr*)&address, len);
	if (result == -1)
	{
		ft_putendl("Connection Failed");
	}
	else
	{
		ft_putendl("Connection Established :)");
		handle_user_input(sockfd);
	}
}

void	usage(void)
{
	ft_putendl("usage: ./client <address> <port>");
}

int		main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	address;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (argc != 3)
	{
		usage();
		return (1);
	}
	init(&*argv, sockfd);
	close(sockfd);
	return (0);
}
