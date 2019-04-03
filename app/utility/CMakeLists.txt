cmake_minimum_required(VERSION 3.4)
project(IMAGE)

set(EXECUTABLE_NAME "publisher")
set(EXECUTABLE_NAME2 "subscriber")
#set(EXECUTABLE_NAME3 "video")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#message("path is ${OpenCV_LIBS}")

add_executable(${EXECUTABLE_NAME}
    publisher.cpp
)

add_executable(${EXECUTABLE_NAME2}
    subscriber.cpp
)

#add_executable(${EXECUTABLE_NAME3}
##    video.cpp
#)

target_link_libraries(${EXECUTABLE_NAME}
    zmq
)

target_link_libraries(${EXECUTABLE_NAME2}
    zmq
)
  #target_link_libraries(${EXECUTABLE_NAME3}
   # ${OpenCV_LIBS}
 #)