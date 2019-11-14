# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asolopov <asolopov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 11:44:13 by asolopov          #+#    #+#              #
#    Updated: 2019/11/14 16:56:11 by asolopov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  fdf

CFLAGS = -Wall -Werror -Wextra

FTS =	main.c\
		input_processor.c\
		line_algorithm.c\
		color_manager.c\
		map_controls.c

LMXLIB = /usr/local/lib/ -lmlx

LIBFT = ./libft/libft.a

FTO = $(FTS:.c=.o)

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME):
		gcc -O3 -o $(NAME) $(CFLAGS) $(FTS) -L $(LMXLIB) $(LIBFT) -framework OpenGL -framework AppKit

clean:
	/bin/rm -f $(FTO)
	
fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
