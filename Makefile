NAME 		= miniRT

CC			= gcc 
FLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

ifdef DEBUG
	FLAGS += -g
endif

SRC_DIR 	= src/

_SRC 		=	main.c\
				vec3/div.c\
				vec3/mult.c\
				vec3/reflection.c\
				vec3/sub.c\
				vec3/sum.c\
				vec3/utils.c\
				engine/rays.c\
				engine/camera_geometry.c\
				engine/colors.c\
				engine/light_model.c\
				engine/maths.c\
				engine/hooks.c\
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
				parser/pruebas.c\
				objects/o_cylinder.c\
				objects/o_sphere.c\
				objects/o_plane.c

SRC 		= ${addprefix ${SRC_DIR}, ${_SRC}}

LIBS		= ${LIBFT_DIR}/libft.a ${MLX_DIR}/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR	= libft
MLX_DIR		= MLX42

INCLUDES	= -I ./include -I ./${LIBFT_DIR}/include -I ./${MLX_DIR}/include/MLX42

SYS	= $(shell uname -s)

ifeq ($(SYS), Darwin)
#	INCLUDES +=	-I /opt/vagrant/embedded/include
#	LIBS	+= -L/opt/vagrant/embedded/lib
	LIBS	+= -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

${NAME}:	minirt

minirt:		
			@echo "Compiling $(NAME)..."
			@echo "Compiling dependencies..."
			@$(MAKE) -s all -C $(LIBFT_DIR)
			@$(MAKE) -s all -C $(MLX_DIR)
			@$(CC) $(INCLUDES) $(SRC) -o $(NAME) $(LIBS)
			@echo "$(NAME) compiled!"

change:
			$(eval CC += -D BONUS=1)
			$(eval NAME=$(NAME)_bonus)

bonus: 		change all

all:		${NAME} ${LIBFT} ${MLX}

clean:
			@echo "Removing files..."
			@echo "Removing dependencies..."
			@$(MAKE) -s clean -C $(LIBFT_DIR)
			@$(MAKE) -s clean -C $(MLX_DIR)

fclean: 	clean
			@${RM} ${NAME} ${NAME}_bonus
			@$(MAKE) -s fclean -C  $(LIBFT_DIR)
			@$(MAKE) -s fclean -C $(MLX_DIR)

re:		fclean all

.PHONY:	all clean fclean re bonus
