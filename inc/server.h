/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 11:54:10 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/28 02:43:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <netdb.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/fcntl.h>

# define BUFF_SIZE 256
# define SEND_BUFF 256

void		usage();
void		handle_command(char **cmd, const int sockfd);
void		handle_client(int sockfd, char *cwd);
void		handle_request(char *input, const int client_fd, char *cwd);
void		get_file(char *filename, const int sockfd);
#endif
