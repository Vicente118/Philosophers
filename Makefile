RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS_DIR = ./sources/
OBJS_DIR = ./objects/

SRCS = sources/main.c sources/parsing.c sources/ft_atoi.c sources/ft_strtrim.c \
	   sources/utils_libft.c sources/init.c sources/simulation.c 

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)


all : $(NAME)

$(NAME) : $(OBJS)
	@printf "                                                  \r"
	@echo "                                                                                                                  "
	@echo "\033[0;31m██████╗  ██╗  ██╗ ██╗ ██╗       ██████╗  ███████╗  ██████╗  ██████╗  ██╗  ██╗ ███████╗ ██████╗  ███████╗"
	@echo "\033[0;31m██╔══██╗ ██║  ██║ ██║ ██║      ██╔═══██╗ ██╔════╝ ██╔═══██╗ ██╔══██╗ ██║  ██║ ██╔════╝ ██╔══██╗ ██╔════╝"
	@echo "\033[0;31m██████╔╝ ███████║ ██║ ██║      ██║   ██║ ███████╗ ██║   ██║ ██████╔╝ ███████║ █████╗   ██████╔╝ ███████╗"		
	@echo "\033[0;31m██╔═══╝  ██╔══██║ ██║ ██║      ██║   ██║ ╚════██║ ██║   ██║ ██╔═══╝  ██╔══██║ ██╔══╝   ██╔══██╗ ╚════██║"
	@echo "\033[0;31m██║      ██║  ██║ ██║ ███████╗ ╚██████╔╝ ███████║ ╚██████╔╝ ██║      ██║  ██║ ███████╗ ██║  ██║ ███████║"
	@echo "\033[0;31m╚═╝      ╚═╝  ╚═╝ ╚═╝ ╚══════╝  ╚═════╝  ╚══════╝  ╚═════╝  ╚═╝      ╚═╝  ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝"
	@echo "                                                                                                                  "                                                                                         
	@$(CC) -pthread $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/sources
	@$(CC) -pthread -o $@ -c $<

clean :
	@$(RM) obj/**/*.o
	@$(RM) obj/philo.o
	@$(RM) -r obj

fclean : clean
	@$(RM) $(NAME)

re : fclean all 