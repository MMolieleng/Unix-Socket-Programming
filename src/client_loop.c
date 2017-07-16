/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 11:42:52 by mmoliele          #+#    #+#             */
/*   Updated: 2017/07/16 11:52:49 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../inc/client.h"

/*
** @params cmd is command string
** @return 1 for valid command
** @return 0 for exit command
** @return -1 for invalid command
*/

static	int	handle_command(char *cmd)
{
	char	**cmd_arr;

	cmd_arr = ft_strsplit(cmd, ' ');
	if (ft_strcmp(cmd_arr[0], "quit") == 0)
		return (0);
	else if (ft_strcmp(cmd_arr[0], "get") == 0)
		return (1);
	else if (ft_strcmp(cmd_arr[0], "put") == 0)
		return (1);
	else if (ft_strcmp(cmd_arr[0], "ls") == 0)
		return (1);
	else if (ft_strcmp(cmd_arr[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_arr[0], "pwd") == 0)
		return (1);
	else
		return (-1);
}

static void	send_command(char *cmd, const int sockfd)
{
	int	res;

	res = send(sockfd, cmd, ft_strlen(cmd), 0);
}

static void	server_response(const int sockfd)
{
	int		rec_bytes;
	char	buff[BUFF_SIZE];

	rec_bytes = 0;
	ft_bzero(buff, BUFF_SIZE);
	ft_putchar('\n');
	while ((rec_bytes = recv(sockfd, buff, BUFF_SIZE, 0)) > 0)
	{
		printf("%s", buff);
		ft_bzero(buff, BUFF_SIZE);
		if (rec_bytes < BUFF_SIZE)
			break ;
	}
}

void		handle_user_input(const int sockfd)
{
	int		readlen;
	char	buff[BUFF_SIZE];

	readlen = 0;
	while ((readlen = read(0, buff, BUFF_SIZE)) > 0)
	{
		if (handle_command(ft_strtrim(buff)))
		{
			send_command(ft_strtrim(buff), sockfd);
			server_response(sockfd);
		}
		else if (handle_command(ft_strtrim(buff)) == 0)
		{
			close(sockfd);
			exit(1);
		}
		ft_bzero(buff, BUFF_SIZE);
		ft_putstr("\n> ");
	}
}
