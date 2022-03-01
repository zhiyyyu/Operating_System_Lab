cmake_minimum_required(VERSION 3.5)

project(FileCopier LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES FileCopier_zh_CN.ts)

if(ANDROID)
  add_library(FileCopier SHARED
    main.cpp
    filecopier.cpp
    filecopier.h
    filecopier.ui
    conwin.cpp
    conwin.h
    conwin.ui
    ${TS_FILES}
  )
else()
  add_executable(FileCopier
    main.cpp
    filecopier.cpp
    filecopier.h
    filecopier.ui
    conwin.cpp
    conwin.h
    conwin.ui
    ${TS_FILES}
  )

add_executable(sub1
  sub1.cpp
  conwin.cpp
  conwin.h
  conwin.ui
  ${TS_FILES}
)
add_executable(sub2
  sub2.cpp
  conwin.cpp
  conwin.h
  conwin.ui
  ${TS_FILES}
)
add_executable(sub3
  sub3.cpp
  conwin.cpp
  conwin.h
  conwin.ui
  ${TS_FILES}
)

endif()

target_link_libraries(FileCopier
    PRIVATE Qt5::Widgets
)

target_link_libraries(sub1
    PRIVATE Qt5::Widgets
)

target_link_libraries(sub2
    PRIVATE Qt5::Widgets
)

target_link_libraries(sub3
    PRIVATE Qt5::Widgets
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
