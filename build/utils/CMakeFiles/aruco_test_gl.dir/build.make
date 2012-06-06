# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/deepak/development/aruco-1.2.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/deepak/development/aruco-1.2.2/build

# Include any dependencies generated for this target.
include utils/CMakeFiles/aruco_test_gl.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/aruco_test_gl.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/aruco_test_gl.dir/flags.make

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o: utils/CMakeFiles/aruco_test_gl.dir/flags.make
utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o: ../utils/aruco_test_gl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o -c /home/deepak/development/aruco-1.2.2/utils/aruco_test_gl.cpp

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/utils/aruco_test_gl.cpp > CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.i

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/utils/aruco_test_gl.cpp -o CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.s

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.requires:
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.requires

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.provides: utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/aruco_test_gl.dir/build.make utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.provides.build
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.provides

utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.provides.build: utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.provides.build

# Object files for target aruco_test_gl
aruco_test_gl_OBJECTS = \
"CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o"

# External object files for target aruco_test_gl
aruco_test_gl_EXTERNAL_OBJECTS =

utils/aruco_test_gl: utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o
utils/aruco_test_gl: src/libaruco.so.1.2.2
utils/aruco_test_gl: /usr/lib/libGL.so
utils/aruco_test_gl: /usr/lib/libGLU.so
utils/aruco_test_gl: /usr/lib/libglut.so
utils/aruco_test_gl: utils/CMakeFiles/aruco_test_gl.dir/build.make
utils/aruco_test_gl: utils/CMakeFiles/aruco_test_gl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable aruco_test_gl"
	cd /home/deepak/development/aruco-1.2.2/build/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aruco_test_gl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/aruco_test_gl.dir/build: utils/aruco_test_gl
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/build

utils/CMakeFiles/aruco_test_gl.dir/requires: utils/CMakeFiles/aruco_test_gl.dir/aruco_test_gl.cpp.o.requires
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/requires

utils/CMakeFiles/aruco_test_gl.dir/clean:
	cd /home/deepak/development/aruco-1.2.2/build/utils && $(CMAKE_COMMAND) -P CMakeFiles/aruco_test_gl.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/clean

utils/CMakeFiles/aruco_test_gl.dir/depend:
	cd /home/deepak/development/aruco-1.2.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/deepak/development/aruco-1.2.2 /home/deepak/development/aruco-1.2.2/utils /home/deepak/development/aruco-1.2.2/build /home/deepak/development/aruco-1.2.2/build/utils /home/deepak/development/aruco-1.2.2/build/utils/CMakeFiles/aruco_test_gl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/aruco_test_gl.dir/depend

