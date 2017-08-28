/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handle_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 14:53:53 by mmoliele          #+#    #+#             */
/*   Updated: 2017/08/28 03:04:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "client.h"

char	*file_length(int fd, size_t size)
{
	int		r;
	int		i;
	char	buff[2];
	char	*my_arr;

	i = 0;
	ft_bzero(buff, 2);
	my_arr = (char*)malloc(sizeof(char) * size);
	if (my_arr)
	{
		r = read(fd, my_arr, size);
		//while ((r = read(fd, buff, 1)))
		//{
		//	my_arr[i] = buff[0];
		//	i++;
		//}
		return (my_arr);
	}
	else
		exit(EXIT_FAILURE);
}

static void *get_binary_bytes(int fd, size_t size)
{
	void        *mapped;

	mapped = mmap(0, size, PROT_READ|PROT_EXEC, MAP_SHARED, fd, 0);
	if (mapped == MAP_FAILED)
	{
		fprintf(stderr, "ERROR: Mapping of file failed: ");
		fprintf(stderr, "%d - %s\n", errno, strerror(errno));
		return (NULL);
	}
	return (mapped);
}

void	put_file(char *filename, const int sock_fd)
{
	size_t			size;
	int				fd;
	int				status;
	char			*buff;
	struct stat		s;

	printf("filename ->%s\n", filename);
	if ((fd = open(ft_strtrim(filename), O_RDONLY)))
	{
		status = fstat(fd, &s);
		size = s.st_size;
		
		buff = ft_strjoin(
				ft_strjoin("put ", ft_itoa(size)),ft_strjoin(" ", filename));
		
		/*buff = ft_strjoin(
				ft_strjoin("put ",  filename),
				ft_strjoin(" ", ft_itoa(size)));
	*/

		printf("to send = %s\n\n", buff);
		send(sock_fd, buff, ft_strlen(buff), 0);
		bzero(buff, size);
		//buff = file_length(fd, size);
		buff = (char *)get_binary_bytes(fd, size);
		//printf("\n%d, \n%s\n", sock_fd, buff);	
		if ((size_t)(send(sock_fd, buff, size, 0)) == size)
			printf("Success sending file\n\n");
		else
			printf("Sending failed");
		close(fd);
	}
}
