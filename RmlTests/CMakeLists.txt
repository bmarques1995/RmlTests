# CMakeList.txt: projeto de CMake para RmlTests, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
add_executable (RmlTests "RmlTests.cpp" "RmlTests.h")

set_property(TARGET RmlTests PROPERTY CXX_STANDARD 23)


# TODO: Adicione testes e instale destinos, se necessário.
