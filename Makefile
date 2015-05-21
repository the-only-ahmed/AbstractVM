#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caupetit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 15:46:59 by caupetit          #+#    #+#              #
#    Updated: 2015/05/21 16:24:10 by ael-kadh         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = AbstractVM
CLASS = Parse.cpp Factory.cpp Emulator.cpp
SRC = main.cpp
SRC += $(CLASS)
CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++11 -Ofast
OBJ = $(SRC:%.cpp=$(ODIR)/%.o)
HEADERS =
HEADERSPATH = $(HEADERS:%.hpp=$(IDIR)/%.hpp)
HEADERSPATH += $(CLASS:%.cpp=$(IDIR)/%.hpp)
SRCDIR = srcs
IDIR = includes
ODIR = objs

all: $(ODIR) $(NAME)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "\033[32m->\033[0m Directory \033[36m$(ODIR)\033[0m created"

$(NAME): $(OBJ)
	@echo "\033[32m=>\033[0m Compiling \033[33m$(NAME)\033[0m"
	$(CC) $(FLAGS) -o $@ $(OBJ) -I$(IDIR)
	@echo ""
	@echo "Compilation \033[32mSuccess\033[0m"

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(HEADERSPATH)
	@echo "\033[32m->\033[0m Compiling \033[33m$<\033[0m"
	$(CC) $(FLAGS) -o $@ -c $< -I $(IDIR)
	@echo ""

clean:
	@rm -f $(OBJ)
	@echo "\033[31m->\033[0m Deleted \033[33m.o\033[0m"

fclean: clear clean
	@rm -rf $(ODIR)
	@echo "\033[31m->\033[0m Directory \033[36m$(ODIR)\033[0m deleted"
	@rm -f $(NAME)
	@echo "\033[31m->\033[0m Deleted \033[33m$(NAME)\033[0m"

re: fclean all

clear:
	@rm -f *~
	@rm -f **/*~
	@echo "\033[31m->\033[0m cleared ~ files"

list: clear
	@ls -G1 `find . -name .git -prune -o -print`
#	@ls -RA1 --color -I .git       list for linux.
