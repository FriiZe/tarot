# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wil/Bureau/Info/Projet_Tarot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wil/Bureau/Info/Projet_Tarot

# Include any dependencies generated for this target.
include CMakeFiles/game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.dir/flags.make

CMakeFiles/game.dir/tarot.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/tarot.c.o: tarot.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wil/Bureau/Info/Projet_Tarot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/game.dir/tarot.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/tarot.c.o   -c /home/wil/Bureau/Info/Projet_Tarot/tarot.c

CMakeFiles/game.dir/tarot.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/tarot.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wil/Bureau/Info/Projet_Tarot/tarot.c > CMakeFiles/game.dir/tarot.c.i

CMakeFiles/game.dir/tarot.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/tarot.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wil/Bureau/Info/Projet_Tarot/tarot.c -o CMakeFiles/game.dir/tarot.c.s

CMakeFiles/game.dir/tarot.c.o.requires:

.PHONY : CMakeFiles/game.dir/tarot.c.o.requires

CMakeFiles/game.dir/tarot.c.o.provides: CMakeFiles/game.dir/tarot.c.o.requires
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/tarot.c.o.provides.build
.PHONY : CMakeFiles/game.dir/tarot.c.o.provides

CMakeFiles/game.dir/tarot.c.o.provides.build: CMakeFiles/game.dir/tarot.c.o


# Object files for target game
game_OBJECTS = \
"CMakeFiles/game.dir/tarot.c.o"

# External object files for target game
game_EXTERNAL_OBJECTS =

libgame.a: CMakeFiles/game.dir/tarot.c.o
libgame.a: CMakeFiles/game.dir/build.make
libgame.a: CMakeFiles/game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wil/Bureau/Info/Projet_Tarot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libgame.a"
	$(CMAKE_COMMAND) -P CMakeFiles/game.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.dir/build: libgame.a

.PHONY : CMakeFiles/game.dir/build

CMakeFiles/game.dir/requires: CMakeFiles/game.dir/tarot.c.o.requires

.PHONY : CMakeFiles/game.dir/requires

CMakeFiles/game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game.dir/clean

CMakeFiles/game.dir/depend:
	cd /home/wil/Bureau/Info/Projet_Tarot && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wil/Bureau/Info/Projet_Tarot /home/wil/Bureau/Info/Projet_Tarot /home/wil/Bureau/Info/Projet_Tarot /home/wil/Bureau/Info/Projet_Tarot /home/wil/Bureau/Info/Projet_Tarot/CMakeFiles/game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game.dir/depend

