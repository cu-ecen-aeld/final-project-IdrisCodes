cmake_minimum_required(VERSION 3.14)

project(DoorUnlockerServer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(DoorUnlockerServer
  main.cpp
  Resources.qrc
  secureserver.h secureserver.cpp
  abstractaction.h
  debugaction.h debugaction.cpp
  gpiotoggleaction.h gpiotoggleaction.cpp
)
target_link_libraries(DoorUnlockerServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(DoorUnlockerServer gpiodcxx)

include(GNUInstallDirs)
install(TARGETS DoorUnlockerServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
