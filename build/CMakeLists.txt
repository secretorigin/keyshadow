cmake_minimum_required(VERSION 3.8)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# expected behaviour
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++lastest")

project(KEYSHADOW)

set(TEST_FILES ../tests/main.cpp)

set(KEYSHADOW_FILES ../src/keyshadow/core/mainloop.cpp
                    ../src/keyshadow/core/keyshadow.cpp)

set(NOTEPROCESSOR_FILES ../src/noteprocessor/writable.cpp
                        ../src/noteprocessor/writablearray.cpp
                        ../src/noteprocessor/writableloginnote.cpp
                        ../src/noteprocessor/factory.cpp)

set(ENCPROCESSOR_FILES ../src/encprocessor/crypto/aes.cpp
                       ../src/encprocessor/core/encdata.cpp
                       ../src/encprocessor/core/encfile.cpp)

# add your .cpp files here
add_executable(keyshadow ${KEYSHADOW_FILES}
                        ${ENCPROCESSOR_FILES} 
                        ${NOTEPROCESSOR_FILES})

target_include_directories(keyshadow PUBLIC ../src/encprocessor)

target_link_libraries(keyshadow)