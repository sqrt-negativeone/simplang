cmake_minimum_required(VERSION 3.16.3)

project(SimpLang 
        VERSION 1.0
        LANGUAGES C
)


find_package(FLEX REQUIRED)
flex_target(Lex src/lex.l ${CMAKE_CURRENT_BINARY_DIR}/lex.c)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.c src/parser.c src/error.c src/ast.c ${FLEX_Lex_OUTPUTS})

target_include_directories(${PROJECT_NAME}
        PUBLIC include/
)