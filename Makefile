# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoliele <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/08 13:12:05 by mmoliele          #+#    #+#              #
#    Updated: 2017/07/08 13:23:06 by mmoliele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

CLIENTSRC = client.c\

SERVERSRC = server.c\

LIB	= -L libft/ -lft

INC	= -I libft/
INC	+= -I inc/

CLIENT_OBJ = $(CLIENTSRC:.c=.o)

SERVER_OBJ = $(SERVERSRC:.c=.o)

all:server client

client:
	$(CC) $(FLAGS) -c $(CLIENTSRC) $(INC)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIB) $(INC)

server:
	$(CC) $(FLAGS) -c $(SERVERSRC) $(INC)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_OBJ) $(LIB)

clean:
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean: clean
	rm -f $(CLIENT)
	rm -f $(SERVER)

re:fclean all
