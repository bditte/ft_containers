NAME =	a.out

SRC =			src/main.cpp 

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

OBJS =			$(SRCS:.cpp=.o)

HEADERS =	-I $(DIR_HEADERS)

DIR_HEADERS = 		./include/

DIR_SRCS =		

DIR_OBJS = 		./objs/

DIR_LIBFT =		./libs/libft/

LIBS = 	




BONUS_NAME = 	

BONUS_SRC =		

BONUS_SRCS =	$(addprefix $(DIR_BONUS), $(BONUS_SRC))

BONUS_OBJS =	$(BONUS_SRCS:.cpp=.o)

BONUS_HEADERS = $(HEADERS) -I $(DIR_BONUS)include/

DIR_BONUS = 	./bonus/




RM =			rm -rf

CC =			clang++

FLAGS =			-Wall -Werror -Wextra -std=c++98



all:			$(NAME) $(BONUS)

$(NAME) :		$(OBJS)
			$(CC)  $(HEADERS) $(SRCS) -o $(NAME) $(LIBS) 


%.o: %.cpp
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
				@echo "Compiled "$<" successfully!"
norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all, clean, fclean, re, bonus
