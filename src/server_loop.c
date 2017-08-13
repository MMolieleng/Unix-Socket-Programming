/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 12:13:09 by mmoliele          #+#    #+#             */
/*   Updated: 2017/07/16 18:35:00 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "server.h"

const char		*g_pwd_args[3] = {"/bin/pwd", "-L", NULL};

static void		handle_cd(char **args, const int client_sockfd)
{
	if (args[1] == NULL)
	{
		if (chdir("./") == -1)
			send(client_sockfd, "ERROR: CD\n", 10, 0);
		else
			send(client_sockfd, "SUCCESS: CD\n", 12, 0);
	}
	else
	{
		if (chdir(args[1]) == -1)
			send(client_sockfd, "ERROR: CD\n", 10, 0);
		else
			send(client_sockfd, "SUCCESS: CD\n", 12, 0);
	}
}

static void		handle_pwd(const int client_sockfd)
{
	int			status;

	status = fork();
	if (status == 0)
	{
		dup2(client_sockfd, 1);
		dup2(client_sockfd, 2);
		execl(g_pwd_args[0], g_pwd_args[1], (char*)0);
		send(client_sockfd, "ERROR: PWD\n", 11, 0);
	}
	dup2(1, 1);
	dup2(2, 2);
	wait(&status);
}

static	void	handle_ls(char **args, const int client_sockfd)
{
	int			status;

	ft_strcpy(args[0], "/bin/ls\0");
	status = fork();
	if (status == 0)
	{
		dup2(client_sockfd, 1);
		dup2(client_sockfd, 2);
		execv(args[0], args);
		send(client_sockfd, "ERROR: LS\n", 10, 0);
	}
	dup2(1, 1);
	dup2(2, 2);
	wait(&status);
}

void			handle_request(char *input, const int client_sockfd)
{
	char	**input_arr;

	input_arr = ft_strsplit(input, ' ');
	if (input_arr[0])
	{
		if (ft_strcmp(input_arr[0], "ls") == 0)
			handle_ls(input_arr, client_sockfd);
		else if (ft_strcmp(input_arr[0], "pwd") == 0)
			handle_pwd(client_sockfd);
		else if (ft_strcmp(input_arr[0], "cd") == 0)
			handle_cd(input_arr, client_sockfd);
		else if (ft_strcmp(ft_strtrim(input_arr[0]), "put") == 0)
			get_file(ft_strtrim(input_arr[1]), client_sockfd);
		else
			send(client_sockfd, "GET\n", 4, 0);
	}
	ft_memdel((void*)&input_arr);
}
