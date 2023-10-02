NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
EXECUTION = execution/execution.a
#PARSING = parsing/parsing.a

SRCS = main.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(EXECUTION) $(PARSING)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(EXECUTION) $(PARSING) -lreadline
	@echo "make minishell"

$(EXECUTION):
	@make -C execution

$(PARSING):
	@make -C parsing

clean:
	@rm -f $(OBJS)
	@make -C execution clean
	@make -C parsing clean
	@echo "clean minishell"

fclean: clean
	@rm -f $(NAME)
	@make -C execution fclean
	@make -C parsing fclean
	@echo "fclean minishell"

re: fclean all
	@echo "re minishell"

.PHONY: clean fclean re all
