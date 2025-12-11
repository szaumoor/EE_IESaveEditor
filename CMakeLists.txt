cmake_minimum_required(VERSION 3.20)

if (POLICY CMP0135)
 cmake_policy(SET CMP0135 NEW)
endif()

project(EE_SaveEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
#     add_link_options(-fsanitize=address,undefined)
# endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

enable_testing()

add_compile_definitions(TEST_RES_DIR="${CMAKE_SOURCE_DIR}/tests/res")

set(TS_FILES EE_SaveEditor_en_001.ts)

set(BACKEND_SOURCES
    src/backend/biff_file.h
    src/backend/tlk_file.h
    src/backend/tlk_file.cpp
    src/backend/gam_file.h
    src/backend/gam_file.cpp
    src/backend/cre_file.h
    src/backend/utils/helper_structs.h
    src/backend/utils/aliases.h
    src/backend/ie_files.h
    src/backend/cre_file.cpp
    src/backend/key_file.h
    src/backend/key_file.cpp
    src/backend/biff_file.cpp
    src/backend/binary_layouts/cre.h
    src/backend/binary_layouts/gam.h
    src/backend/binary_layouts/key_biff.h
    src/backend/binary_layouts/tlk.h
    src/backend/utils/errors.h
    src/backend/utils/errors.cpp
    src/backend/utils/io.h
)

set(TEST_COMMON
    src/backend/utils/errors.h
    src/backend/utils/errors.cpp
    tests/utils/tests_helper.h
    tests/utils/tests_helper.cpp
    src/backend/utils/helper_structs.h
)

set(GAM_TEST_SOURCES
    ${TEST_COMMON}
    tests/gam_file_tests.cpp
    src/backend/gam_file.cpp
    src/backend/gam_file.h
    src/backend/cre_file.cpp
)

set(TLK_TEST_SOURCES
    ${TEST_COMMON}
    tests/tlk_file_tests.cpp
    src/backend/tlk_file.cpp
    src/backend/tlk_file.h
)

set(STRING_TEST_SOURCES
    ${TEST_COMMON}
    tests/string_tests.cpp
)

set(KEY_TEST_SOURCES
    ${TEST_COMMON}
    tests/key_file_tests.cpp
    src/backend/key_file.cpp
    src/backend/key_file.h
)

set(BIFF_TEST_SOURCES
    ${TEST_COMMON}
    tests/biff_file_tests.cpp
    src/backend/biff_file.cpp
    src/backend/biff_file.h
)

set(ALL_TEST_SOURCES
    ${TLK_TEST_SOURCES}
    ${KEY_TEST_SOURCES}
    ${GAM_TEST_SOURCES}
    ${STRING_TEST_SOURCES}
    ${BIFF_TEST_SOURCES}
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ${TS_FILES}
)


add_library (backend ${BACKEND_SOURCES})

set(FRONTEND_SOURCES
    ${BACKEND_SOURCES}
    src/main.cpp
    src/frontend/mainwindow.cpp
    src/frontend/mainwindow.h
    src/frontend/mainwindow.ui)

add_executable(tlk_file_test
    tests/tlk_file_tests.cpp
    ${TLK_TEST_SOURCES}
)

add_executable(key_file_test
    tests/key_file_tests.cpp
    ${KEY_TEST_SOURCES}
)

 add_executable(gam_file_test
    tests/gam_file_tests.cpp
    ${GAM_TEST_SOURCES}
 )

add_executable(biff_file_test
    tests/biff_file_tests.cpp
    ${BIFF_TEST_SOURCES}
)

add_executable(string_tests
    tests/string_tests.cpp
    ${STRING_TEST_SOURCES}
)

add_executable(all_tests
    ${ALL_TEST_SOURCES}
)

 target_link_libraries(tlk_file_test
    PRIVATE
    GTest::gtest_main
)

 target_link_libraries(gam_file_test
    PRIVATE
    GTest::gtest_main
)

 target_link_libraries(key_file_test
    PRIVATE
    GTest::gtest_main
)

target_link_libraries(string_tests
    PRIVATE
    GTest::gtest_main
)

target_link_libraries(biff_file_test
    PRIVATE
    GTest::gtest_main
)

target_link_libraries(all_tests
   PRIVATE
   GTest::gtest_main
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EE_SaveEditor
        MANUAL_FINALIZATION
        ${FRONTEND_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EE_SaveEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(EE_SaveEditor SHARED
            ${BACKEND_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EE_SaveEditor
            ${BACKEND_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(EE_SaveEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EE_SaveEditor)
endif()
set_target_properties(EE_SaveEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EE_SaveEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EE_SaveEditor)
endif()

# Google Test setup
include(GoogleTest)
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
