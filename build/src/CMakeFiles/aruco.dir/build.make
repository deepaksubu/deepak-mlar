# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/deepak/development/aruco-1.2.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/deepak/development/aruco-1.2.2/build

# Include any dependencies generated for this target.
include src/CMakeFiles/aruco.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/aruco.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/aruco.dir/flags.make

src/CMakeFiles/aruco.dir/markerdetector.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/markerdetector.cpp.o: ../src/markerdetector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/markerdetector.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/markerdetector.cpp.o -c /home/deepak/development/aruco-1.2.2/src/markerdetector.cpp

src/CMakeFiles/aruco.dir/markerdetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/markerdetector.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/markerdetector.cpp > CMakeFiles/aruco.dir/markerdetector.cpp.i

src/CMakeFiles/aruco.dir/markerdetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/markerdetector.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/markerdetector.cpp -o CMakeFiles/aruco.dir/markerdetector.cpp.s

src/CMakeFiles/aruco.dir/markerdetector.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/markerdetector.cpp.o.requires

src/CMakeFiles/aruco.dir/markerdetector.cpp.o.provides: src/CMakeFiles/aruco.dir/markerdetector.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/markerdetector.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/markerdetector.cpp.o.provides

src/CMakeFiles/aruco.dir/markerdetector.cpp.o.provides.build: src/CMakeFiles/aruco.dir/markerdetector.cpp.o

src/CMakeFiles/aruco.dir/boarddetector.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/boarddetector.cpp.o: ../src/boarddetector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/boarddetector.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/boarddetector.cpp.o -c /home/deepak/development/aruco-1.2.2/src/boarddetector.cpp

src/CMakeFiles/aruco.dir/boarddetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/boarddetector.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/boarddetector.cpp > CMakeFiles/aruco.dir/boarddetector.cpp.i

src/CMakeFiles/aruco.dir/boarddetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/boarddetector.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/boarddetector.cpp -o CMakeFiles/aruco.dir/boarddetector.cpp.s

src/CMakeFiles/aruco.dir/boarddetector.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/boarddetector.cpp.o.requires

src/CMakeFiles/aruco.dir/boarddetector.cpp.o.provides: src/CMakeFiles/aruco.dir/boarddetector.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/boarddetector.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/boarddetector.cpp.o.provides

src/CMakeFiles/aruco.dir/boarddetector.cpp.o.provides.build: src/CMakeFiles/aruco.dir/boarddetector.cpp.o

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o: ../src/cvdrawingutils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/cvdrawingutils.cpp.o -c /home/deepak/development/aruco-1.2.2/src/cvdrawingutils.cpp

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/cvdrawingutils.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/cvdrawingutils.cpp > CMakeFiles/aruco.dir/cvdrawingutils.cpp.i

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/cvdrawingutils.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/cvdrawingutils.cpp -o CMakeFiles/aruco.dir/cvdrawingutils.cpp.s

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.requires

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.provides: src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.provides

src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.provides.build: src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o: ../src/arucofidmarkers.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/arucofidmarkers.cpp.o -c /home/deepak/development/aruco-1.2.2/src/arucofidmarkers.cpp

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/arucofidmarkers.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/arucofidmarkers.cpp > CMakeFiles/aruco.dir/arucofidmarkers.cpp.i

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/arucofidmarkers.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/arucofidmarkers.cpp -o CMakeFiles/aruco.dir/arucofidmarkers.cpp.s

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.requires

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.provides: src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.provides

src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.provides.build: src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o

src/CMakeFiles/aruco.dir/board.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/board.cpp.o: ../src/board.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/board.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/board.cpp.o -c /home/deepak/development/aruco-1.2.2/src/board.cpp

src/CMakeFiles/aruco.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/board.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/board.cpp > CMakeFiles/aruco.dir/board.cpp.i

src/CMakeFiles/aruco.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/board.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/board.cpp -o CMakeFiles/aruco.dir/board.cpp.s

src/CMakeFiles/aruco.dir/board.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/board.cpp.o.requires

src/CMakeFiles/aruco.dir/board.cpp.o.provides: src/CMakeFiles/aruco.dir/board.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/board.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/board.cpp.o.provides

src/CMakeFiles/aruco.dir/board.cpp.o.provides.build: src/CMakeFiles/aruco.dir/board.cpp.o

src/CMakeFiles/aruco.dir/cameraparameters.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/cameraparameters.cpp.o: ../src/cameraparameters.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/cameraparameters.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/cameraparameters.cpp.o -c /home/deepak/development/aruco-1.2.2/src/cameraparameters.cpp

src/CMakeFiles/aruco.dir/cameraparameters.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/cameraparameters.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/cameraparameters.cpp > CMakeFiles/aruco.dir/cameraparameters.cpp.i

src/CMakeFiles/aruco.dir/cameraparameters.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/cameraparameters.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/cameraparameters.cpp -o CMakeFiles/aruco.dir/cameraparameters.cpp.s

src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.requires

src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.provides: src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.provides

src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.provides.build: src/CMakeFiles/aruco.dir/cameraparameters.cpp.o

src/CMakeFiles/aruco.dir/marker.cpp.o: src/CMakeFiles/aruco.dir/flags.make
src/CMakeFiles/aruco.dir/marker.cpp.o: ../src/marker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/deepak/development/aruco-1.2.2/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/aruco.dir/marker.cpp.o"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aruco.dir/marker.cpp.o -c /home/deepak/development/aruco-1.2.2/src/marker.cpp

src/CMakeFiles/aruco.dir/marker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aruco.dir/marker.cpp.i"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/deepak/development/aruco-1.2.2/src/marker.cpp > CMakeFiles/aruco.dir/marker.cpp.i

src/CMakeFiles/aruco.dir/marker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aruco.dir/marker.cpp.s"
	cd /home/deepak/development/aruco-1.2.2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/deepak/development/aruco-1.2.2/src/marker.cpp -o CMakeFiles/aruco.dir/marker.cpp.s

src/CMakeFiles/aruco.dir/marker.cpp.o.requires:
.PHONY : src/CMakeFiles/aruco.dir/marker.cpp.o.requires

src/CMakeFiles/aruco.dir/marker.cpp.o.provides: src/CMakeFiles/aruco.dir/marker.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/aruco.dir/build.make src/CMakeFiles/aruco.dir/marker.cpp.o.provides.build
.PHONY : src/CMakeFiles/aruco.dir/marker.cpp.o.provides

src/CMakeFiles/aruco.dir/marker.cpp.o.provides.build: src/CMakeFiles/aruco.dir/marker.cpp.o

# Object files for target aruco
aruco_OBJECTS = \
"CMakeFiles/aruco.dir/markerdetector.cpp.o" \
"CMakeFiles/aruco.dir/boarddetector.cpp.o" \
"CMakeFiles/aruco.dir/cvdrawingutils.cpp.o" \
"CMakeFiles/aruco.dir/arucofidmarkers.cpp.o" \
"CMakeFiles/aruco.dir/board.cpp.o" \
"CMakeFiles/aruco.dir/cameraparameters.cpp.o" \
"CMakeFiles/aruco.dir/marker.cpp.o"

# External object files for target aruco
aruco_EXTERNAL_OBJECTS =

src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/markerdetector.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/boarddetector.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/board.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/cameraparameters.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/marker.cpp.o
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/build.make
src/libaruco.so.1.2.2: src/CMakeFiles/aruco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libaruco.so"
	cd /home/deepak/development/aruco-1.2.2/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aruco.dir/link.txt --verbose=$(VERBOSE)
	cd /home/deepak/development/aruco-1.2.2/build/src && $(CMAKE_COMMAND) -E cmake_symlink_library libaruco.so.1.2.2 libaruco.so.1.2 libaruco.so

src/libaruco.so.1.2: src/libaruco.so.1.2.2

src/libaruco.so: src/libaruco.so.1.2.2

# Rule to build all files generated by this target.
src/CMakeFiles/aruco.dir/build: src/libaruco.so
.PHONY : src/CMakeFiles/aruco.dir/build

src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/markerdetector.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/boarddetector.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/cvdrawingutils.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/arucofidmarkers.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/board.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/cameraparameters.cpp.o.requires
src/CMakeFiles/aruco.dir/requires: src/CMakeFiles/aruco.dir/marker.cpp.o.requires
.PHONY : src/CMakeFiles/aruco.dir/requires

src/CMakeFiles/aruco.dir/clean:
	cd /home/deepak/development/aruco-1.2.2/build/src && $(CMAKE_COMMAND) -P CMakeFiles/aruco.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/aruco.dir/clean

src/CMakeFiles/aruco.dir/depend:
	cd /home/deepak/development/aruco-1.2.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/deepak/development/aruco-1.2.2 /home/deepak/development/aruco-1.2.2/src /home/deepak/development/aruco-1.2.2/build /home/deepak/development/aruco-1.2.2/build/src /home/deepak/development/aruco-1.2.2/build/src/CMakeFiles/aruco.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/aruco.dir/depend

