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
CMAKE_SOURCE_DIR = /home/etryfly/Документы/Labs/3sem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/etryfly/Документы/Labs/3sem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/chown.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chown.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chown.dir/flags.make

CMakeFiles/chown.dir/OS/ch/chown.c.o: CMakeFiles/chown.dir/flags.make
CMakeFiles/chown.dir/OS/ch/chown.c.o: ../OS/ch/chown.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/etryfly/Документы/Labs/3sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/chown.dir/OS/ch/chown.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chown.dir/OS/ch/chown.c.o   -c /home/etryfly/Документы/Labs/3sem/OS/ch/chown.c

CMakeFiles/chown.dir/OS/ch/chown.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chown.dir/OS/ch/chown.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/etryfly/Документы/Labs/3sem/OS/ch/chown.c > CMakeFiles/chown.dir/OS/ch/chown.c.i

CMakeFiles/chown.dir/OS/ch/chown.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chown.dir/OS/ch/chown.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/etryfly/Документы/Labs/3sem/OS/ch/chown.c -o CMakeFiles/chown.dir/OS/ch/chown.c.s

# Object files for target chown
chown_OBJECTS = \
"CMakeFiles/chown.dir/OS/ch/chown.c.o"

# External object files for target chown
chown_EXTERNAL_OBJECTS =

chown: CMakeFiles/chown.dir/OS/ch/chown.c.o
chown: CMakeFiles/chown.dir/build.make
chown: CMakeFiles/chown.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/etryfly/Документы/Labs/3sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable chown"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chown.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chown.dir/build: chown

.PHONY : CMakeFiles/chown.dir/build

CMakeFiles/chown.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chown.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chown.dir/clean

CMakeFiles/chown.dir/depend:
	cd /home/etryfly/Документы/Labs/3sem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/etryfly/Документы/Labs/3sem /home/etryfly/Документы/Labs/3sem /home/etryfly/Документы/Labs/3sem/cmake-build-debug /home/etryfly/Документы/Labs/3sem/cmake-build-debug /home/etryfly/Документы/Labs/3sem/cmake-build-debug/CMakeFiles/chown.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chown.dir/depend

