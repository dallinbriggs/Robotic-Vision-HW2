project(HW2_P2)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package( OpenCV 3 REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})


#add_executable( task_1 task_1.cpp )
target_link_libraries(HW2_P2 ${OpenCV_LIBS} )
