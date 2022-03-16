set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp parent.cpp parent.h)

find_package(QT NAMES Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS DBus)
find_package(Qt5DBus REQUIRED)

include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5DBus_INCLUDE_DIRS}
)

qt5_add_dbus_interface(INTERFACE_SOURCES
        child.xml
        child_interface
        )

add_executable(parent ${PROJECT_SOURCES} ${INTERFACE_SOURCES})

target_link_libraries(parent Qt5::Core Qt5::Widgets Qt5::DBus)