NAME	= execution
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror -fsanitize=address
# LIBFT	= ../execution/libft/libft.a

SRCS =	builtins/cd.c\
		builtins/echo.c\
		env/env.c\
		env/utils.c\
		utils/utils0.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "make it"

# $(LIBFT):
# 	@make -C libft
# 	@make -C libft bonus

clean:
	@rm -f $(OBJS)
	# @make -C libft clean
	@echo "clean execution"

fclean: clean
	@rm -f $(NAME)
	# @make -C libft fclean
	@echo "fclean execution"

re: fclean $(NAME)

.PHONY: clean fclean re all