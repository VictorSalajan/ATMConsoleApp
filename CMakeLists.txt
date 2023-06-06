cmake_minimum_required(VERSION 3.25)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab5 main.cpp Collection.h Console.h Pair.h Transaction.h List.h Node.h TestList.cpp TestList.h ATM.h)
