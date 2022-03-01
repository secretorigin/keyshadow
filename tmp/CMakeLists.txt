cmake_minimum_required(VERSION 3.8)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# expected behaviour
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++lastest")

project(KEY_SHADOW)

# add your .cpp files here
add_executable(test.out ../src/tests/test_read_write.cpp
                        #../src/mainloop/command_processor.cpp
                        ../src/mainloop/database/encrypted_file.cpp
                        ../src/crypto/ciphers/aes_ecb.cpp
                        ../src/crypto/core/aes.cpp
                        ../src/crypto/core/pbkdf2.cpp
                        ../src/crypto/hash_functions/pbkdf2_hmac_sha512.cpp)
# ../src/allocators.cpp

target_link_libraries(test.out -L/usr/lib -lssl -lcrypto)
