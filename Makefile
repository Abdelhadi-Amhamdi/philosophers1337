# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:14:30 by aamhamdi          #+#    #+#              #
#    Updated: 2023/03/20 14:22:12 by aamhamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# vars
CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = philo

# paths
SRCS_DIR = srcs/
BUILD_DIR = build/

# headers
S_HEADER = philo.h

# files
SRC = philo.c actions.c utils.c
SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(BUILD_DIR), $(OBJ))

all: $(NAME)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(SRCS_DIR)$(S_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
