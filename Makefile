# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 15:23:49 by amdedieu          #+#    #+#              #
#    Updated: 2021/03/23 22:34:55 by amdedieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = parsing.c \
		main.c    \
		utils.c    \
		parse_utils.c
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
INCLUDES = -I includes/ -I libft/
LIB = -Llibft -lft
CFLAGS = -Wall -Wextra -Werror
#MLX = -lmlx -framework OpenGL -framework AppKit

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(LIB) $(OBJS)
	@(gcc $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "cub3D created")

$(LIB) :
	@(make -C libft)

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(gcc $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))
	@(rm -f image.bmp)
	@(rm -rf cub3d.dSYM)

fclean : clean
	@(rm -rf $(OBJSDIR))
re : fclean all

fg : $(LIB) $(OBJS)
	@(gcc $(CFLAGS) -g3 -fsanitize=address $(OBJS) $(LIB) $(INCLUDES)  -o $(NAME) )
	@(echo "cub3D created")

