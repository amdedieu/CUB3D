# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 15:23:49 by amdedieu          #+#    #+#              #
#    Updated: 2021/08/24 14:39:47 by amdedieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
SRCSDIR = srcs
OBJSDIR = .objs
SRCS =  error.c\
		main.c\
		utils.c\
		check.c\
		key.c	\
		draw.c	\
		rotate.c \
		textures.c\
		parsing.c\
		raycast.c \
		movement.c \
		parsing_map.c\
		parse_utils.c\
		parsing_color.c\
		addr_collector.c\
		check_map_outline.c
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
INCLUDES = -I includes/ -I libft/ -I mlx/
LIB = -Llibft -lft
CFLAGS = -Wall -Wextra -Werror -flto -O2 -march=native
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(LIB) $(OBJS) 
	@(gcc $(MLX) $(CFLAGS) $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
	@(echo "cub3D created")

fg : $(LIB) $(OBJS) 
	@(gcc $(MLX) $(CFLAGS) -g3 -fsanitize=address $(OBJS) $(LIB) $(INCLUDES) -o $(NAME))
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
	@(gcc $(MLX) $(CFLAGS) -g3 -fsanitize=address $(OBJS) $(LIB) $(INCLUDES)  -o $(NAME) )
	@(echo "cub3D created")

