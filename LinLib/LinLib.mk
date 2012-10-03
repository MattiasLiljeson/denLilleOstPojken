#===============================================================================
# Project settings
#===============================================================================
# Name of out file
outFile = LinLib

# Compiler flags when compiling objects
cFlags = -c

# Linker flags used when linking binary
lFlags =

# Link when compiling is done. This should not be done for "libraries". "link" 
# should be set to 'true' or 'false'. Everything other than 'true' results in 
# the project not being linked.
link = false

#===============================================================================
# Project dependencies
#===============================================================================
# Space separated list of directories to projects that this project depends on. 
projectPaths = ../CommonLib


#===============================================================================
# Libraries
#===============================================================================
# Space separated list of directories where libs that the project uses reside. 
# This list is ONLY for linux libs. Correspodning header files are added to
# 'libIncludePaths'.
_libPaths = external/glew/lin-lib external/glfw/lin-lib
libIncludePaths = external/glew/include/ external/glfw/include/ external/boost_1_51_0/include/

# Specify the file names of the libs that should be used when compiling.
# The file MUST be prefixed with 'lib' and suffiex with '.a'
__libs = libglfw.a libGLEW.a libGLEWmx.a librt.a

include ../solutionSettings.mk
include ../compileAndLink.mk

