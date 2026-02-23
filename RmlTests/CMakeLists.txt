# CMakeList.txt: projeto de CMake para RmlTests, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
set(TARGET_NAME RmlTests)

trace_dependency(NAME SDL3 INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/sdl.cmake.json")
trace_dependency(NAME glad INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/glad.cmake.json")

file(GLOB_RECURSE RMLT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE RMLT_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")

add_executable(${TARGET_NAME} ${RMLT_SRCS} ${RMLT_HDRS})
target_link_libraries(${TARGET_NAME} PUBLIC SDL3::SDL3 glad::glad)
target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)

# TODO: Adicione testes e instale destinos, se necessário.
