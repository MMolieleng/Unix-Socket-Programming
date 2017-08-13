# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/08 13:12:05 by mmoliele          #+#    #+#              #
#*   Updated: 2017/07/16 01:24:59 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

FLAGS = -Wall -Werror -Wextra

CLIENTSRC = src/client.c\
	    src/client_loop.c\
		src/client_handle_file.c\

SERVERSRC = src/server.c\
			src/server_loop.c\
			src/server_handle_file.c\

LIB	= -L libft/ -lft

INC	= -I libft/
INC	+= -I inc/

CLIENT_OBJ = client.o\
			 client_handle_file.o\
	client_loop.o#$(CLIENTSRC:.c=.o)

SERVER_OBJ = server.o\
			 server_handle_file.o\
			 server_loop.o#$(SERVERSRC:.c=.o)

all:server client
	make re -C libft

client:
	$(CC) $(FLAGS) -c $(CLIENTSRC) $(INC)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIB) $(INC)

server:
	$(CC) $(FLAGS) -c $(SERVERSRC) $(INC)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_OBJ) $(LIB)

clean:
	rm -f server*
	rm -f client*

#	rm -f server*#$(SERVER_OBJ)
#	rm -f client*#$(CLIENT_OBJ)

fclean: clean
	rm -f $(CLIENT)
	rm -f $(SERVER)

re:fclean all
