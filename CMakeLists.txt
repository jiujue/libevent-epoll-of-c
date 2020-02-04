cmake_minimum_required(VERSION 2.8.9)
project(test C)


#For the shared library:
set ( PROJECT_LINK_LIBS libtestStudent.so )
link_directories( ~/exploringBB/extras/cmake/studentlib_shared/build )

#For the static library:
#set ( PROJECT_LINK_LIBS libtestStudent.a )
#link_directories( ~/exploringBB/extras/cmake/studentlib_static/build )



set ( PROJECT_LINK_LIBS libevent-2.0.so )
link_directories( ./another )

#Bring the headers, such as Student.h into the project
include_directories(include)


#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

add_executable(s_v2 ${SOURCES})
target_link_libraries(s_v2 ${PROJECT_LINK_LIBS} )