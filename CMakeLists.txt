cmake_minimum_required(VERSION 3.16)

project(Monopoly VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp

        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Monopoly
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        addsquarewindow.h chance.hpp freeparking.hpp game.hpp gotojail.hpp jail.hpp mainwindow.hpp player.hpp playerselectiondialog.h railroad.hpp square.hpp start.hpp street.hpp utility.hpp
        addsquarewindow.cpp chance.cpp freeparking.cpp game.cpp gotojail.cpp jail.cpp main.cpp mainwindow.cpp player.cpp playerselectiondialog.cpp railroad.cpp square.cpp start.cpp street.cpp utility.cpp
        resources.qrc
        addsquarewindow.ui playerselectiondialog.ui
        tax.hpp tax.cpp
        gotojail.hpp gotojail.cpp
        jail.hpp jail.cpp
        freeparking.hpp freeparking.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Monopoly APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Monopoly SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Monopoly
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Monopoly PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Monopoly)
endif()
set_target_properties(Monopoly PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Monopoly
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Monopoly)
endif()