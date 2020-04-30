cmake_minimum_required(VERSION 3.15)
project(catalog C)

set(CMAKE_C_STANDARD 11)

add_executable(catalog main.c CatalogTree.c CatalogTree.h findFile.h findFile.c quantity.c quantity.h findLargeFiles.c findLargeFile.h strrem.c strrem.h)