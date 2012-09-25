include ../solutionSettings.mk
#===============================================================================
# Project settings
#===============================================================================
# name of out file
outFile = test
# Compiler flags when compiling objects
oFlags = -c
#Compiler flags used when linking binary
bFlags =

#===============================================================================
# Project dependencies
#===============================================================================
# Space separated list of directories to projects that this project depends on. 
projectPaths = ../output ../concStrings


#===============================================================================
# Libraries
#===============================================================================
# Space separated list of directories where libs that the project uses reside. 
# This list is ONLY for linux libs. Correspodning header files are added to
# 'libIncludePaths'.
_libPaths =
libIncludePaths =

# Specify the file names of the libs that should be used when compiling.
# The file MUST be prefixed with 'lib' and suffiex with '.a'
__libs =
