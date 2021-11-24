NAME =	a.out

S =		src/
O = 	obj/
I = 	include/
D =		dep/

SRC =			main.cpp 

OBJ =			$(SRC:$S%.cpp=$O%.o)
DEP = $(SRC:$S%=$D%.d)
HEADERS =	-I $(DIR_HEADERS)
LIBS = 

DIR_HEADERS = 		./include/
DIR_LIBFT =		./libs/libft/
	


BONUS_NAME = 	
BONUS_SRC =		
BONUS_SRCS =	$(addprefix $(DIR_BONUS), $(BONUS_SRC))
BONUS_OBJS =	$(BONUS_SRCS:.cpp=.o)
BONUS_HEADERS = $(HEADERS) -I $(DIR_BONUS)include/
DIR_BONUS = 	./bonus/


RM =			rm -rf

CC =			clang++
FLAGS =			-Wall -Werror -Wextra -std=c++98

$O:
		@mkdir $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$D:
		@ mkdir $@

$(DEP): | $D

$(DEP): $D%.d: $S%
	$(CC) $(FLAGS) -MM -MF $@ -MT "$O$*.o $@" $<


all:		$(NAME) $(BONUS)

$(NAME) :	$(OBJ)
	$(CC) $^ -o $@

cleanobj:
			$(RM) $(wildcard $O)
			$(RM) -r $O

clean:		cleanobj
				$(RM) $(OBJ)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

-include $(DEP)

.PHONY:			all, clean, fclean, re, bonus