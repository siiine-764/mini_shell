NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
EXECUTION = execution/execution.a

SRCS = main.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(EXECUTION)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(EXECUTION) -lreadline -lncurses
	@echo "make minishell"

$(EXECUTION):
	make -C execution

clean:
	@rm -f $(OBJS)
	@make -C execution clean
	@echo "clean minishell"

fclean: clean
	@rm -f $(NAME)
	@make -C execution fclean
	@echo "fclean minishell"

re: fclean all
	@echo "re minishell"

.PHONY: clean fclean re all
