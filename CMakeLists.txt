project(lsbuffer)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

aux_source_directory(src/ls SRC)

aux_source_directory(sample SRC_SAMPLE)

include_directories(include)

add_executable(testcase ${SRC} ${SRC_SAMPLE})

add_library(lsbuffer SHARED ${SRC})

install(TARGETS lsbuffer DESTINATION lib)
install(DIRECTORY include/ls DESTINATION include)

