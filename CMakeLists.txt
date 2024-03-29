cmake_minimum_required(VERSION 3.12)
project(wolf3d)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)
include_directories(libft)
include_directories(src)
include_directories(resources)

add_executable(wolf3d
        includes/wolf3d.h
        libft/author
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_clear_list.c
        libft/ft_free_arr.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_iswhitespaces.c
        libft/ft_itoa.c
        libft/ft_lstadd.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_size_of_lst.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strsplit.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        libft/Makefile
        libft/powd.c
        src/colorize.c
        src/wolf3d.c
        src/init_sdl_ttf.c
        author
        src/validation.c src/errors.c src/raycasting.c src/keys.c src/load_weapon.c src/doors.c src/stats_showing.c src/menu.c src/weapons.c libft/ft_is_uppercase.c src/exit.c libft/ft_clear_string_array.c src/free.c src/init_hud_and_player.c src/init_weapons.c src/move.c src/check_events.c src/load_hud_menu_walls.c src/stats_weapon.c src/changing_fullscreen.c src/calculate_distance.c src/draw.c src/vert_hor_calc.c src/timers_game_loop.c src/map_processing.c src/parse_map.c)

target_link_libraries(wolf3d "-lmlx")
target_link_libraries(wolf3d "-framework OpenGl")
target_link_libraries(wolf3d "-framework Appkit")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2_image")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2_ttf")


include_directories("libft/includes")
include_directories("/Users/$ENV{USER}/Library/Frameworks/SDL2.framework/Versions/A/Headers/")
include_directories("/Users/$ENV{USER}/Library/Frameworks/SDL2_image.framework/Versions/A/Headers/")
#include_directories("/Users/$ENV{USER}/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers/")
include_directories("/Users/$ENV{USER}/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers/")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2_image")
target_link_libraries(wolf3d "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2_ttf")