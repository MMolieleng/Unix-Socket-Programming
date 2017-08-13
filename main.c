#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	usage()
{
	write(0, "./exec filename\n", 16);
}

void	read_file(char *filename)
{
	int		fd; // File descriptor
	int		bsize;		//buff size
	char	buff[5]; //buffer size

	bsize = sizeof(buff);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(1, "File not found\n", 15);
	}
	else
	{
		while( read(fd, buff, 5) > 0)
			printf("\n%s, \n", buff);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		usage();
		return (-1);
	}
	read_file(argv[1]);
	return (0);
}
