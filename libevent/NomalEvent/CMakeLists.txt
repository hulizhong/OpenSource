project("NormalEventPractice")

set(SERVER_SRC EventServer.cpp)
set(CLIENT_SRC EventClient.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11")


set(LIBEVENTPATH /home/thinkInEvent/install/)

include_directories(${LIBEVENTPATH}/include)
link_directories(${LIBEVENTPATH}/lib)

add_executable(eventSer ${SERVER_SRC})
target_link_libraries(eventSer event)

add_executable(eventCli ${CLIENT_SRC})
target_link_libraries(eventCli event)

