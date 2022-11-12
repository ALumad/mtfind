set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_library(${LIB_NAME} 
    alg.cpp
    parser.cpp
    textprocessor.cpp
)


target_link_libraries(${LIB_NAME}  Threads::Threads)