# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mattellegrino/Scaricati/clion-2021.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mattellegrino/Scaricati/clion-2021.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mattellegrino/progetto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mattellegrino/progetto/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/progetto.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/progetto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/progetto.dir/flags.make

CMakeFiles/progetto.dir/main.cpp.o: CMakeFiles/progetto.dir/flags.make
CMakeFiles/progetto.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mattellegrino/progetto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/progetto.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/progetto.dir/main.cpp.o -c /home/mattellegrino/progetto/main.cpp

CMakeFiles/progetto.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progetto.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mattellegrino/progetto/main.cpp > CMakeFiles/progetto.dir/main.cpp.i

CMakeFiles/progetto.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progetto.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mattellegrino/progetto/main.cpp -o CMakeFiles/progetto.dir/main.cpp.s

CMakeFiles/progetto.dir/ScreenRecorder.cpp.o: CMakeFiles/progetto.dir/flags.make
CMakeFiles/progetto.dir/ScreenRecorder.cpp.o: ../ScreenRecorder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mattellegrino/progetto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/progetto.dir/ScreenRecorder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/progetto.dir/ScreenRecorder.cpp.o -c /home/mattellegrino/progetto/ScreenRecorder.cpp

CMakeFiles/progetto.dir/ScreenRecorder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progetto.dir/ScreenRecorder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mattellegrino/progetto/ScreenRecorder.cpp > CMakeFiles/progetto.dir/ScreenRecorder.cpp.i

CMakeFiles/progetto.dir/ScreenRecorder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progetto.dir/ScreenRecorder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mattellegrino/progetto/ScreenRecorder.cpp -o CMakeFiles/progetto.dir/ScreenRecorder.cpp.s

# Object files for target progetto
progetto_OBJECTS = \
"CMakeFiles/progetto.dir/main.cpp.o" \
"CMakeFiles/progetto.dir/ScreenRecorder.cpp.o"

# External object files for target progetto
progetto_EXTERNAL_OBJECTS =

progetto: CMakeFiles/progetto.dir/main.cpp.o
progetto: CMakeFiles/progetto.dir/ScreenRecorder.cpp.o
progetto: CMakeFiles/progetto.dir/build.make
progetto: libScreenModule.a
progetto: CMakeFiles/progetto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mattellegrino/progetto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable progetto"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/progetto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/progetto.dir/build: progetto
.PHONY : CMakeFiles/progetto.dir/build

CMakeFiles/progetto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/progetto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/progetto.dir/clean

CMakeFiles/progetto.dir/depend:
	cd /home/mattellegrino/progetto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mattellegrino/progetto /home/mattellegrino/progetto /home/mattellegrino/progetto/cmake-build-debug /home/mattellegrino/progetto/cmake-build-debug /home/mattellegrino/progetto/cmake-build-debug/CMakeFiles/progetto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/progetto.dir/depend
