NAME	= execution
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address -g

SRCS =	builtins/cd.c\
		builtins/pwd.c\
		builtins/exit.c\
		builtins/echo.c\
		builtins/unset.c\
		builtins/export.c\
		env/env.c\
		env/utils.c\
		utils/utils0.c\
		exec/pipe.c\
		# main_ex.c\
		# exec/execute.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "make it"

clean:
	@rm -f $(OBJS)
	@echo "clean execution"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean execution"

re: fclean $(NAME)

.PHONY: clean fclean re all	