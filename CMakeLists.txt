cmake_minimum_required(VERSION 3.4)
project(MQ_TEST)
set(EXECUTABLE_NAME "mq_test")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#Check gcc version
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_COMPILER_IS_GNUCC)
	message("Compile is gcc")
endif()
if(NOT DEFINED ENV{ARCH})
    #message("not cross compiler")
    set(IS_CROSS_COMPILE "FALSE")
else()
    if($ENV{ARCH} MATCHES "arm")
        #message("is cross compiler")
        set(IS_CROSS_COMPILE "TRUE")
    endif()
endif()

# Marcos
#ADD_DEFINITIONS(-DHF800 -DENABLE_MASTER_CERTIFICATE -DENABLE_NOREAD_DEBUG -DNDEBUG)

#zeromq
set(ZeroMQ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libzmq)
include_directories(${ZeroMQ_DIR}/include)
link_directories(${ZeroMQ_DIR}/lib)

add_subdirectory(app/utility)
#add_subdirectory(src/logging)

add_executable(${EXECUTABLE_NAME}
    app/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
    zmq
    pthread
)

