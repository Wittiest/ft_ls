#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpearson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 03:40:05 by dpearson          #+#    #+#              #
#    Updated: 2017/12/08 03:40:08 by dpearson         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC	= gcc

NAME			=	ft_ls

LIBS			=	./libs

LIBFT_DIR		=	$(LIBS)/libft

INCLUDES_DIR	=	./includes

CFLAGS			+=	-Wall -Wextra -Werror
CFLAGS			+=	-I $(INCLUDES_DIR)

FILENAMES		=	ft_ls.c tree.c flags.c utils.c main.c print.c utils2.c

SRC 			= $(addprefix srcs/, $(FILENAMES))

OBJ				= $(SRC:.c=.o)

LIBFT			=	$(LIBFT_DIR)/libft.a


all: $(NAME)

$(LIBFT):
		make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
clean:
		rm -f $(OBJ)
		make -C $(LIBFT_DIR) clean
fclean: clean
		rm -rf $(NAME)
		make -C $(LIBFT_DIR) fclean
re: fclean all
