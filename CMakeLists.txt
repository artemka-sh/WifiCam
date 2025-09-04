cmake_minimum_required(VERSION 3.16)

project(WifiCamProj VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Quick HttpServer Core Gui Qml Multimedia QuickControls2 Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(WifiCam MANUAL_FINALIZATION
    src/main.cpp
    qml/qml.qrc
)

qt_add_qml_module(WifiCam
    URI WifiCamProj
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/MainContent.qml
        qml/Canvas.qml
        qml/Header.qml
        qml/ConnectInfo.qml
        qml/PermissionReq.qml
        qml/Permission-denied.qml
        qml/ChooseCameraPop.qml
    SOURCES
        src/clienthttpserver.h
        src/networkinfo.h
        src/clienthttpserver.cpp
        src/mjpegserver.h
        src/mjpegserver.cpp
        src/cameracontroller.h
        src/cameracontroller.cpp
        src/camera_list_model.h
        src/camera_list_model.cpp
    RESOURCES qml/qml.qrc


)

add_subdirectory(deps/MobileUI/)

set_target_properties(WifiCam PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(WifiCam
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::HttpServer
    Qt6::Multimedia
    Qt6::QuickControls2
    Qt6::Network
    MobileUI::MobileUI

)

qt_finalize_target(WifiCam)

include(GNUInstallDirs)
install(TARGETS WifiCam
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


