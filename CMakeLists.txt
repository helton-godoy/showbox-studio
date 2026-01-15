cmake_minimum_required(VERSION 3.16)

project(showbox-studio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuração Automática do Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Svg)

# Importar a Biblioteca Showbox UI via subdiretório
# Isso permite que o CMake propague as dependências (QtCharts, etc) corretamente
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../showbox/libs/showbox-ui" "libs/showbox-ui")

# Fontes do Studio
file(GLOB_RECURSE STUDIO_SOURCES 
    "src/*.cpp" 
    "src/*.h"
)

add_executable(showbox-studio 
    ${STUDIO_SOURCES}
)

# Includes
target_include_directories(showbox-studio PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Linkagem
# Agora linkamos o TARGET da biblioteca, o que resolve as dependências do Qt automaticamente
target_link_libraries(showbox-studio PRIVATE 
    Qt6::Widgets 
    Qt6::Charts
    Qt6::Svg
    showbox-ui
)