# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/etryfly/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/etryfly/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/etryfly/Документы/Labs/4sem/fundal/2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fuck.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fuck.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fuck.dir/flags.make

CMakeFiles/fuck.dir/fuck.c.o: CMakeFiles/fuck.dir/flags.make
CMakeFiles/fuck.dir/fuck.c.o: ../fuck.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fuck.dir/fuck.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fuck.dir/fuck.c.o   -c /home/etryfly/Документы/Labs/4sem/fundal/2/fuck.c

CMakeFiles/fuck.dir/fuck.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fuck.dir/fuck.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/etryfly/Документы/Labs/4sem/fundal/2/fuck.c > CMakeFiles/fuck.dir/fuck.c.i

CMakeFiles/fuck.dir/fuck.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fuck.dir/fuck.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/etryfly/Документы/Labs/4sem/fundal/2/fuck.c -o CMakeFiles/fuck.dir/fuck.c.s

# Object files for target fuck
fuck_OBJECTS = \
"CMakeFiles/fuck.dir/fuck.c.o"

# External object files for target fuck
fuck_EXTERNAL_OBJECTS =

fuck: CMakeFiles/fuck.dir/fuck.c.o
fuck: CMakeFiles/fuck.dir/build.make
fuck: CMakeFiles/fuck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fuck"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fuck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fuck.dir/build: fuck

.PHONY : CMakeFiles/fuck.dir/build

CMakeFiles/fuck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fuck.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fuck.dir/clean

CMakeFiles/fuck.dir/depend:
	cd /home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/etryfly/Документы/Labs/4sem/fundal/2 /home/etryfly/Документы/Labs/4sem/fundal/2 /home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug /home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug /home/etryfly/Документы/Labs/4sem/fundal/2/cmake-build-debug/CMakeFiles/fuck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fuck.dir/depend

