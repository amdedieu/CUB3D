# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 19:58:34 by amdedieu          #+#    #+#              #
#    Updated: 2021/03/23 15:18:49 by amdedieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME                =   libft.a

CC                  =   gcc -Wall -Wextra -Werror

SRC            =        ft_atoi.c               \
						ft_exit.c 				\
						ft_bzero.c              \
						ft_calloc.c             \
						ft_isalnum.c            \
						ft_isalpha.c            \
						ft_isascii.c            \
						ft_isdigit.c            \
						ft_isprint.c            \
						ft_itoa.c               \
						ft_itoa_base.c 			\
						ft_itoa_address.c 		\
						ft_memccpy.c            \
						ft_memmove.c            \
						ft_memchr.c             \
						ft_memcmp.c             \
						ft_memdel.c 			\
						ft_memcpy.c             \
						ft_memset.c             \
						ft_putchar_fd.c         \
						ft_putendl_fd.c         \
						ft_putnbr_fd.c          \
						ft_putstr_fd.c          \
						ft_split.c              \
						ft_strchr.c             \
						ft_strjoin_free.c 		\
						ft_strjoin_free1.c 		\
						ft_strjoin_free2.c 		\
						ft_str_toupper.c 		\
						ft_itoa_unsigned.c 		\
						ft_strdup.c             \
						ft_strjoin.c            \
						ft_strlcat.c            \
						ft_strlcpy.c            \
						ft_strndup.c            \
						ft_strlen.c             \
						ft_strmapi.c            \
						ft_strncmp.c            \
						ft_strnstr.c            \
						ft_strrchr.c            \
						ft_strtrim.c            \
						ft_substr.c             \
						ft_tolower.c            \
						ft_toupper.c            \
						get_next_line.c         \
						ft_lstnew.c       \
						ft_lstadd_front.c \
						ft_lstadd_back.c  \
						ft_lstclear.c     \
						ft_lstiter.c      \
						ft_lstdelone.c    \
						ft_lstlast.c      \
						ft_lstmap.c       \
						ft_lstsize.c      \
						ft_swap.c         \

OBJ                 = $(SRC:.c=.o)
INCLUDE             =   libft.h

all: $(NAME)
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
clean :
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -rf $(NAME)
re : fclean all

.PHONY: all clean fclean re
