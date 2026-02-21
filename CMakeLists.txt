cmake_minimum_required(VERSION 3.16)

project(UBST2508_Sheduler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appUBST2508_Sheduler
    main.cpp
)

qt_add_qml_module(appUBST2508_Sheduler
    URI UBST2508_Sheduler
    QML_FILES
        Main.qml
        SOURCES src/entities/commonTypes.h
        RESOURCES resources.qrc
        SOURCES src/entities/subject.h src/entities/subject.cpp
        SOURCES src/entities/deadline.h src/entities/deadline.cpp
        SOURCES src/entities/lesson.h src/entities/lesson.cpp
        SOURCES src/core/appcore.h src/core/appcore.cpp
        SOURCES src/models/schedulelistmodel.h src/models/schedulelistmodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appUBST2508_Sheduler PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appUBST2508_Sheduler
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appUBST2508_Sheduler
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appUBST2508_Sheduler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
