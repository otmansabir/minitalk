# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osabir <osabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 15:11:27 by osabir            #+#    #+#              #
#    Updated: 2023/02/28 13:34:18 by osabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER1 = client.c help.c 
OBJ1 = $(SER1:.c=.o)

SER2 = server.c help.c 
OBJ2 = $(SER2:.c=.o)

SER3 = client_bonus.c help.c 
OBJ3 = $(SER3:.c=.o)

SER4 = server_bonus.c help_bonus.c 
OBJ4 = $(SER4:.c=.o)

HD1 = minitalk.h
HD2 = minitalk_bonus.h

NAME = client
NAMES = server

NAMECB = client_bonus
NAMESB = server_bonus

all : $(NAME) $(NAMES)

$(NAME) : $(OBJ1)
	cc -Wall -Wextra -Werror $(OBJ1) -o $(NAME)
$(NAMES) : $(OBJ2)
	cc -Wall -Wextra -Werror $(OBJ2) -o $(NAMES)

bonus : $(NAMECB) $(NAMESB)

$(NAMECB) : $(OBJ3)
	cc -Wall -Wextra -Werror $(OBJ3) -o $(NAMECB)

$(NAMESB) : $(OBJ4)
	cc -Wall -Wextra -Werror $(OBJ4) -o $(NAMESB)

%.o : %.c $(HD1) $(HD2)
	cc -Wall -Wextra -Werror -c $< -o $@

clean :
	rm -rf $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

fclean : clean
	rm -rf $(NAME) $(NAMES) $(NAMECB) $(NAMESB)

re : fclean all
