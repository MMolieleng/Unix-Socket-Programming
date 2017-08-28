/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handle_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 14:53:53 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/28 15:56:01 by mmoliele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "client.h"

static	void	*get_binary_bytes(int fd, size_t size)
{
	void	*mapped;

	mapped = mmap(0, size, PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0);
	if (mapped == MAP_FAILED)
	{
		fprintf(stderr, "ERROR: Mapping of file failed: ");
		fprintf(stderr, "%d - %s\n", errno, strerror(errno));
		return (NULL);
	}
	return (mapped);
}

void			put_file(char *args, const int sock_fd)
{
	size_t			size;
	int				fd;
	char			*buff;
	char			*filename;
	struct stat		s;

	filename = ft_strsplit(args, ' ')[1];
	printf("filename ->%s\n", filename);
	if ((fd = open(ft_strtrim(filename), O_RDONLY)))
	{
		fstat(fd, &s);
		size = s.st_size;
		buff = ft_strjoin(
				ft_strjoin("put ", ft_itoa(size)), ft_strjoin(" ", filename));
		send(sock_fd, buff, ft_strlen(buff), 0);
		bzero(buff, size);
		buff = (char *)get_binary_bytes(fd, size);
		if ((size_t)(send(sock_fd, buff, size, 0)) == size)
			printf("Success sending file\n\n");
		else
			printf("Sending failed");
		close(fd);
	}
	free(filename);
}
