cmake_minimum_required(VERSION 2.6)

project(Tarot)


set(ENABLE_DEBUG ON)
if(ENABLE_DEBUG)
  set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
  message("-- DEBUG MODE ON")
else()
  set(CMAKE_C_FLAGS "-std=c99 -O3")
  message("-- DEBUG MODE OFF")
endif(ENABLE_DEBUG)


# Sets the CMP0037 policy to the old one which accept "test" as an executable name
cmake_policy(SET CMP0037 OLD)

include(CTest)
enable_testing()


# -------- SDL + undead_graphic -------- #
# pkg-config --list-all  | grep -i sdl2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

include_directories(${SDL2_ALL_INC})
add_executable(tarot_sdl tarot_graphic.c TI.c game.c)
target_link_libraries(tarot_sdl ${SDL2_ALL_LIBS} m)
# -------------------------------------- #



add_library(game tarot.c)
# Allows the game library to be generate with .o files
set_target_properties(game PROPERTIES LINKER_LANGUAGE C)

add_executable(tarot tarot.c)
target_link_libraries(tarot game)
