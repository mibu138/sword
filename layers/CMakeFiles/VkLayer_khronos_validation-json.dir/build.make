# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build

# Utility rule file for VkLayer_khronos_validation-json.

# Include the progress variables for this target.
include layers/CMakeFiles/VkLayer_khronos_validation-json.dir/progress.make

layers/CMakeFiles/VkLayer_khronos_validation-json:
	cd /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers && /usr/bin/cmake -DINPUT_FILE="/home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/layers/json/VkLayer_khronos_validation.json.in" -DVK_VERSION=1.1.126 -DOUTPUT_FILE="/home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers/VkLayer_khronos_validation.json" -DRELATIVE_LAYER_BINARY="./libVkLayer_khronos_validation.so" -P /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers/generator.cmake

VkLayer_khronos_validation-json: layers/CMakeFiles/VkLayer_khronos_validation-json
VkLayer_khronos_validation-json: layers/CMakeFiles/VkLayer_khronos_validation-json.dir/build.make

.PHONY : VkLayer_khronos_validation-json

# Rule to build all files generated by this target.
layers/CMakeFiles/VkLayer_khronos_validation-json.dir/build: VkLayer_khronos_validation-json

.PHONY : layers/CMakeFiles/VkLayer_khronos_validation-json.dir/build

layers/CMakeFiles/VkLayer_khronos_validation-json.dir/clean:
	cd /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers && $(CMAKE_COMMAND) -P CMakeFiles/VkLayer_khronos_validation-json.dir/cmake_clean.cmake
.PHONY : layers/CMakeFiles/VkLayer_khronos_validation-json.dir/clean

layers/CMakeFiles/VkLayer_khronos_validation-json.dir/depend:
	cd /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/layers /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers /home/michaelb/Dev/Vulkan/1.1.126.0/source/Vulkan-ValidationLayers/build/layers/CMakeFiles/VkLayer_khronos_validation-json.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : layers/CMakeFiles/VkLayer_khronos_validation-json.dir/depend
