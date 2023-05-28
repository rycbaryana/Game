cmake_minimum_required(VERSION 3.24)
project(Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:/Qt/6.4.2/mingw_64/lib/cmake")


find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        LinguistTools)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

qt_add_big_resources(SRC resources.qrc)

add_executable(Game ${SRC} ${HEADERS})
include_directories(Game include include/Graphics include/Objects include/Upgrades)
qt_add_translations(Game TS_FILES assets/translations/en.ts assets/translations/ru.ts RESOURCE_PREFIX "/translations")

target_link_libraries(Game
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )


