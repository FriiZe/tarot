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

add_library(game tarot.c)
# Allows the game library to be generate with .o files
set_target_properties(game PROPERTIES LINKER_LANGUAGE C)

add_executable(tarot tarot.c)
target_link_libraries(tarot game)
