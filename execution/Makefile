NAME	= execution
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror -fsanitize=address -g

SRCS =	builtins/cd.c\
		builtins/pwd.c\
		builtins/exit.c\
		builtins/echo.c\
		builtins/unset.c\
		builtins/export.c\
		env/env.c\
		env/utils.c\
		utils/utils0.c\
		utils/utils1.c\
		utils/utils2.c\
		utils/utils3.c\
		utils/utils_pipe0.c\
		utils/utils_pipe1.c\
		exec/pipe.c\
		exec/execute.c\
		exec/redir.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline
	@echo "make minishell"

# $(NAME) : $(OBJS)
# 	@ar rcs $(NAME) $(OBJS)
# 	@echo "make execution"

clean:
	@rm -f $(OBJS)
	@echo "clean execution"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean execution"

re: fclean $(NAME)
	@echo "re execution"

.PHONY: clean fclean re all	