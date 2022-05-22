cmake_minimum_required(VERSION 3.5)

project(Sniffer LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Quick Charts )

message(STATUS "Qt5Gui Version:  ${Qt5Gui_VERSION}")
message(STATUS "Qt5Quick Version:  ${Qt5Quick_VERSION}")
message(STATUS "Qt5Charts version:  ${Qt5Charts_VERSION}")

file(GLOB SOURCES
    ./src/*.hpp
    ./src/*.cpp
    ./src/*.h
    ./src/*.qrc
    ./src/protocols/*.hpp
    ./src/protocols/*.cpp
    ./src/protocols/*.h
)

add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")


include(cmake/FindPCAP.cmake)

#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(${CMAKE_PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${CMAKE_PROJECT_NAME}
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Charts

  ${PCAP_LIBRARY}
)
