# CMakeList.txt: projeto de CMake para RmlTests, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
set(TARGET_NAME RmlTests)

trace_dependency(NAME SDL3 INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/sdl.cmake.json")
trace_dependency(NAME glad INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/glad.cmake.json")
trace_dependency(NAME ZLIB INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/zlib.cmake.json")
trace_dependency(NAME PNG INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/png.cmake.json")
trace_dependency(NAME harfbuzz INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/harfbuzz.cmake.json")
trace_dependency(NAME brotli INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/brotli.cmake.json")
trace_dependency(NAME freetype INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/freetype.cmake.json")
trace_dependency(NAME lunasvg INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/lunasvg.cmake.json")
trace_dependency(NAME libjpeg-turbo INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/jpeg_turbo.cmake.json")
trace_dependency(NAME RmlUi INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/rmlui.cmake.json")

file(GLOB_RECURSE RMLT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE RMLT_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")

add_executable(${TARGET_NAME} ${RMLT_SRCS} ${RMLT_HDRS})
target_link_libraries(${TARGET_NAME} PUBLIC SDL3::SDL3 glad::glad PNG::png_shared libjpeg-turbo::jpeg RmlUi::RmlUi)
if(WIN32)
	target_link_libraries(${TARGET_NAME} PUBLIC dxgi dxguid d3d11)
endif()
target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/graphics/shared
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/graphics/platform)
set_cxx_project_standards(${TARGET_NAME} 20 FALSE)

# TODO: Adicione testes e instale destinos, se necessário.
