cmake_minimum_required(VERSION 3.16)

project(UBST2508_Sheduler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appUBST2508_Sheduler
    main.cpp

)

set_source_files_properties("ui/theme/Theme.qml" PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appUBST2508_Sheduler
    URI UBST2508_Sheduler
    QML_FILES
        Main.qml
        ui/theme/Theme.qml
        ui/components/LessonCard.qml
        ui/components/SegmentedToggle.qml
        ui/components/DayBoard.qml
        ui/components/DeadlineCard.qml
        ui/components/CalendarView.qml
        ui/components/NavigationButton.qml
        ui/pages/SchedulePage.qml
        ui/pages/DeadlinesPage.qml
    RESOURCES
        "assets/fonts/Inter_24pt-Medium.ttf"
        "assets/icons/pdf.svg"
        "assets/icons/docx.svg"
        "assets/icons/xls.svg"
        "assets/icons/pptx.svg"
        "assets/icons/file.svg"
        "assets/icons/settings.svg"
        "assets/icons/changeTheme.svg"
        "assets/icons/back.svg"
        "assets/icons/arrow.svg"
        "assets/icons/download.svg"
        "assets/images/noDeadline.gif"
    SOURCES
        src/entities/commonTypes.h
        src/entities/subject.h src/entities/subject.cpp
        src/entities/deadline.h src/entities/deadline.cpp
        src/entities/lesson.h src/entities/lesson.cpp
        src/core/appcore.h src/core/appcore.cpp
        src/models/schedulelistmodel.h src/models/schedulelistmodel.cpp
        src/models/daylistmodel.h src/models/daylistmodel.cpp
        src/entities/day.h src/entities/day.cpp
        src/models/deadlinelistmodel.h src/models/deadlinelistmodel.cpp
        QML_FILES ui/components/SubjectPopup.qml
        QML_FILES ui/components/FileCard.qml
        SOURCES src/models/filelistmodel.h src/models/filelistmodel.cpp
        QML_FILES ui/components/DeadlinePopup.qml
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
