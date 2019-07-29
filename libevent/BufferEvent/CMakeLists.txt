project("NormalEventPractice")

set(SERVER_SRC BufferEventServer.cpp)
set(CLIENT_SRC BufferEventClient.cpp)

add_executable(bufferEventSer ${SERVER_SRC})
add_executable(bufferEventCli ${CLIENT_SRC})

