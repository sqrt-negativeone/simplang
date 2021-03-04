cmake_minimum_required(VERSION 3.16.3)

project(SimpLang 
        VERSION 1.0
        LANGUAGES C
)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC include/
)
