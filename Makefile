NAME 		= miniRT

CC			= gcc -g
FLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

ifdef DEBUG
	FLAGS += -g
endif

SRC_DIR 	= src/

OBJ_DIR		= obj/

_SRC 		=	main.c\
				vec3/div.c\
				vec3/mult.c\
				vec3/sub.c\
				vec3/sum.c\
				vec3/utils.c\
				engine/colors.c\
				parser/colors.c\
				parser/coordinates.c\
				parser/o_ambient_lights.c\
				parser/o_camera.c\
				parser/o_cylinder.c\
				parser/o_sphere.c\
				parser/o_plane.c\
				parser/o_light.c\
				parser/parser_errors.c\
				parser/parser_utils.c\
				parser/parser_frees.c\
				parser/parser_scene.c\
				parser/pruebas.c

SRC_FOLDERS =	obj/parser\
				obj/engine\
				obj/vec3


SRC 		= ${addprefix ${SRC_DIR}, ${_SRC}}
OBJ			= ${patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRC}}

LIBS		= ${LIBFT_DIR}/libft.a ${MLX_DIR}/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR	= libft
MLX_DIR		= MLX42

INCLUDES	= -I ./include -I ./${LIBFT_DIR}/include -I ./${MLX_DIR}/include/MLX42

SYS	= $(shell uname -s)

ifeq ($(SYS), Darwin)
	INCLUDES +=	-I /opt/vagrant/embedded/include
	LIBS	+= -L/opt/vagrant/embedded/lib
endif

${NAME}:	 ${OBJ}
			@echo "Compiling $(NAME)..."
			@echo "Compiling dependencies..."
			@$(MAKE) -s all -C $(LIBFT_DIR)
			@$(MAKE) -s all -C $(MLX_DIR)
			@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

${OBJ_DIR}%.o: ${SRC_DIR}%.c
			@git submodule update --init
			@mkdir -p ${OBJ_DIR}
			@mkdir -p ${SRC_FOLDERS}
			@${CC} ${FLAGS} ${INCLUDES} -c $^ -o $@

all:		${NAME} ${LIBFT} ${MLX}

clean:
			@echo "Removing files..."
			@echo "Removing dependencies..."
			@$(MAKE) -s clean -C $(LIBFT_DIR)
			@$(MAKE) -s clean -C $(MLX_DIR)
			@${RM} ${OBJ}

fclean: 	clean
			@${RM} ${NAME}
			@$(MAKE) -s fclean -C  $(LIBFT_DIR)
			@$(MAKE) -s fclean -C $(MLX_DIR)

re:		fclean all

.PHONY:	all clean fclean re bonus