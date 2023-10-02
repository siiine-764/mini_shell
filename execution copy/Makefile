NAME = cpy
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRCS = before_heredoc.c\
		builtInUtils.c\
		combine.c\
		echo.c\
		env.c\
		error_files.c\
		exec_utils.c\
		execSimpleCommand.c\
		exit_utils.c\
		export_utils.c\
		export.c\
		free.c\
		ft_exit.c\
		ft_pwd.c\
		heredoc_utils.c\
		heredoc.c\
		pipe_utils.c\
		pipe.c\
		randomUtils.c\
		redirection_utils.c\
		redirection.c\
		Unset.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all