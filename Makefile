# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 09:26:28 by cboutier          #+#    #+#              #
#    Updated: 2022/02/16 11:06:32 by cboutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= containers
NAME_FT			= ft_containers
NAME_STD		= std_containers

SRCS_DIR		= .
INCLUDES		= .
OBJS_DIR		= objs
OBJS_DIR_FT		= ft_objs
OBJS_DIR_STD	= std_objs

CXX				= clang++

CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
DEP_FLAGS		= -MMD -MP

SRCS			= ft_main.cpp std_main.cpp
SRCS_FT			= ft_main.cpp
SRCS_STD		= std_main.cpp

OBJS			= $(addprefix ${OBJS_DIR}/,${SRCS:.cpp=.o})
OBJS_FT			= $(addprefix ${OBJS_DIR_FT}/,${SRCS_FT:.cpp=.o})
OBJS_STD		= $(addprefix ${OBJS_DIR_STD}/,${SRCS_STD:.cpp=.o})

DEP				= ${OBJS:.o=.d}

RM				= rm -f

all:			$(NAME_FT) $(NAME_STD)
				@./$(NAME_FT) > $(NAME_FT).txt
				@./$(NAME_STD) > $(NAME_STD).txt
				@diff $(NAME_FT).txt $(NAME_STD).txt > diff.txt || exit 0
				cat diff.txt

$(NAME_FT):		${OBJS_FT}
				${CXX} -I${INCLUDES} ${CXXFLAGS} ${DEP_FLAGS} ${OBJS_FT} -o $@

$(NAME_STD):	${OBJS_STD}
				${CXX} -I${INCLUDES} ${CXXFLAGS} ${DEP_FLAGS} ${OBJS_STD} -o $@

${OBJS_DIR}/%.o:${SRCS_DIR}/%.cpp
				@mkdir -p ${OBJS_DIR}
				${CXX} ${CXXFLAGS} ${DEP_FLAGS} -c $< -o $@

${OBJS_DIR_FT}/%.o:${SRCS_DIR}/%.cpp
				@mkdir -p ${OBJS_DIR_FT}
				${CXX} ${CXXFLAGS} ${DEP_FLAGS} -c $< -o $@

${OBJS_DIR_STD}/%.o:${SRCS_DIR}/%.cpp
				@mkdir -p ${OBJS_DIR_STD}
				${CXX} ${CXXFLAGS} ${DEP_FLAGS} -c $< -o $@

clean:
				rm -rf ${OBJS_DIR} ${OBJS_DIR_FT} ${OBJS_DIR_STD}

fclean:			clean
				${RM} ${NAME} $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re:				fclean all

.PHONY:			all clean fclean re ft std

-include ${DEP}
