set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp child.cpp child.h)

find_package(QT NAMES Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS DBus)
find_package(Qt5DBus REQUIRED)

include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5DBus_INCLUDE_DIRS}
)

qt5_add_dbus_adaptor(ADAPTOR_SOURCES child.xml
        child.h
        Child
        child_adaptor
        )

add_executable(child ${PROJECT_SOURCES} ${ADAPTOR_SOURCES})

target_link_libraries(child Qt5::Core Qt5::Widgets Qt5::DBus)