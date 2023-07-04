NAME	= execution
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

SRCS =	builtins/cd.c\
		builtins/echo.c\
		builtins/pwd.c\
		builtins/exit.c\
		builtins/unset.c\
		env/env.c\
		env/utils.c\
		utils/utils0.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "make it"

clean:
	@rm -f $(OBJS)
	@echo "clean execution"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean execution"

re: fclean $(NAME)

.PHONY: clean fclean re all