cmake_minimum_required(VERSION 3.16)

project(UBST2508_Sheduler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Quick)

qt_standard_project_setup(REQUIRES 6.8)

if(WIN32)
    set(APP_ICON_FILE "assets/icons/app_icon.ico")
elseif(APPLE)
    set(APP_ICON_FILE "assets/icons/app_icon.icns")
else()
    set(APP_ICON_FILE "assets/icons/app_icon.png")
endif()

qt_add_executable(appUBST2508_Sheduler
    main.cpp
    "assets/icons/app_icon.rc"
    ${APP_ICON_FILE}
)

set_source_files_properties("ui/theme/Theme.qml" PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appUBST2508_Sheduler
    URI UBST2508_Sheduler
    QML_FILES
        Main.qml
        ui/theme/Theme.qml
        ui/pages/SchedulePage.qml
        ui/pages/DeadlinesPage.qml
        ui/components/LessonCard.qml
        ui/components/SegmentedToggle.qml
        ui/components/DayBoard.qml
        ui/components/DeadlineCard.qml
        ui/components/CalendarView.qml
        ui/components/NavigationButton.qml
        ui/components/SubjectPopup.qml
        ui/components/FileCard.qml
        ui/components/DeadlinePopup.qml
        ui/components/SubjectDeadlinesPopup.qml
        ui/components/BasePopup.qml
        ui/components/SettingsPopup.qml
        ui/components/HeaderButton.qml
        ui/components/SettingsButton.qml
        ui/components/SettingsDescription.qml
    RESOURCES
        "assets/icons/app_icon.png"
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
        "assets/icons/openFile.svg"
        "assets/images/noDeadline.gif"
    SOURCES
        src/core/appcore.h src/core/appcore.cpp
        src/core/constants.h
        src/core/networkservice.h src/core/networkservice.cpp
        src/core/typedefs.h
        src/core/entityfactory.h
        src/core/entityfactory.cpp
        src/tests/testdatagenerator.h src/tests/testdatagenerator.cpp
        src/entities/commonTypes.h
        src/entities/subject.h src/entities/subject.cpp
        src/entities/deadline.h src/entities/deadline.cpp
        src/entities/lesson.h src/entities/lesson.cpp
        src/entities/day.h src/entities/day.cpp
        src/models/schedulelistmodel.h src/models/schedulelistmodel.cpp
        src/models/daylistmodel.h src/models/daylistmodel.cpp
        src/models/deadlinelistmodel.h src/models/deadlinelistmodel.cpp
        src/models/filelistmodel.h src/models/filelistmodel.cpp
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
    MACOSX_BUNDLE_ICON_FILE "app_icon.icns"
    #OUTPUT_NAME "UBST2508_Scheduler"
)

# Указываем CMake, где лежат Android-настройки и Манифест
if(ANDROID)
    # 1. Подключаем Манифест
    set_property(TARGET appUBST2508_Sheduler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

    # 2. Подключаем библиотеки OpenSSL 3
    set(OPENSSL_LIB_DIR "/home/altast/Android/Sdk/android_openssl/ssl_3/arm64-v8a")

    set_property(TARGET appUBST2508_Sheduler APPEND PROPERTY QT_ANDROID_EXTRA_LIBS
        "${OPENSSL_LIB_DIR}/libcrypto_3.so"
        "${OPENSSL_LIB_DIR}/libssl_3.so"
    )
endif()

target_link_libraries(appUBST2508_Sheduler PRIVATE
    Qt6::Quick
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appUBST2508_Sheduler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
