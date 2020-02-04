cmake_minimum_required(VERSION 3.10.1)
project(test C)


# For the shared library:
set ( PROJECT_LINK_LIBS libevent-2.0.so )
link_directories( ./another )

# For the static library:
# set ( PROJECT_LINK_LIBS libevent-2.0.a )
# link_directories( ./another)



set ( PROJECT_LINK_LIBS libevent-2.0.so )
link_directories( ./another )

# Bring the headers, such as head.h into the project
include_directories(include)


# Can manually add the sources using the set command as follows:
# set(SOURCES src/sent_file.c src/main.c)

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

add_executable(s_v2 ${SOURCES})
target_link_libraries(s_v2 ${PROJECT_LINK_LIBS} )
