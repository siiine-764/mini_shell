NAME = execution.a
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
SRCS =	\
	./randomUtils.c			\
	./redirection_utils.c	\
	./cd.c					\
	./builtInUtils.c		\
	./heredoc.c				\
	./before_heredoc.c		\
	./export_utils.c		\
	./heredoc_utils.c		\
	./redirection.c			\
	./pipe_utils.c			\
	./exec_utils.c			\
	./env.c					\
	./echo.c				\
	./Unset.c				\
	./free.c				\
	./pipe.c				\
	./execSimpleCommand.c	\
	./export.c				\
	./ft_exit.c				\
	./ft_pwd.c				\
	./combine.c				\
	./error_files.c			\
	./echo_utils.c			\
	./exit_utils.c			

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