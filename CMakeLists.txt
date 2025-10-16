cmake_minimum_required(VERSION 3.16)

project(QT_try1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ✅ ملفات المشروع
set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    filters.cpp
    filters.h
    Image_Class.cpp
    Image_Class.h
)

# ✅ لا تضيف ملفات .h الخاصة بـ stb هنا لأنها ليست ملفات تنفيذية
# لأننا بنضمها داخل Image_Class.cpp بالفعل

# ✅ إنشاء الـ target
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_try1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(QT_try1 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(QT_try1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ✅ ربط المشروع بمكتبات Qt
target_link_libraries(QT_try1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# إعداد خصائص التطبيق
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QT_try1)
endif()

set_target_properties(QT_try1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QT_try1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT_try1)
endif()
