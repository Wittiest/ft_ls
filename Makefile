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

NAME		=	ft_ls

LIBS		=	./libs

LIBFT_DIR	=	$(LIBS)/libft

INCLUDES	=	./includes

CFLAGS		+=	-Wall -Wextra -Werror
CFLAGS		+=	-I $(LIBFT_DIR)/ -I $(INCLUDES)

FILENAMES	=	ft_ls.c list.c

SRC = $(addprefix srcs/, $(FILENAMES))

LIBFT		=	$(LIBFT_DIR)/libft.a


all: $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)
$(NAME): $(LIBFT)
		@gcc $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
clean:
		@make -C $(LIBFT_DIR) clean
fclean: clean
		@rm -rf $(NAME)
		@make -C $(LIBFT_DIR) fclean
re: fclean all