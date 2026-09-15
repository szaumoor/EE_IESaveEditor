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

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)

if (ENABLE_SANITIZERS)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address,undefined)
    else()
        message(WARNING "ENABLE_SANITIZERS is only supported with Clang or GCC")
    endif()
endif()

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wsign-conversion;-Wshadow;-Wold-style-cast;-Wnull-dereference>"
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Concurrent)

enable_testing()

include(GoogleTest)
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_compile_definitions(TEST_RES_DIR="${CMAKE_SOURCE_DIR}/tests/res")

set(TS_FILES
    translations/EE_SaveEditor_es.ts
    translations/EE_SaveEditor_zh_CN.ts
)

SET(RES_FILES
  resources/resource.qrc
)

set(BACKEND_SOURCES
        src/backend/biff_file.hpp
        src/backend/tlk_file.hpp
        src/backend/tlk_file.cpp
        src/backend/gam_file.hpp
        src/backend/gam_file.cpp
        src/backend/cre_file.hpp
        src/backend/utils/helper_structs.hpp
        src/backend/utils/aliases.hpp
        src/backend/ie_files.hpp
        src/backend/cre_file.cpp
        src/backend/key_file.hpp
        src/backend/key_file.cpp
        src/backend/biff_file.cpp
        src/backend/binary_layouts/cre.hpp
        src/backend/binary_layouts/gam.hpp
        src/backend/binary_layouts/key_biff.hpp
        src/backend/binary_layouts/tlk.hpp
        src/backend/utils/errors.hpp
        src/backend/utils/errors.cpp
        src/backend/utils/io.hpp
        src/backend/binary_layouts/spl.hpp
        src/backend/binary_layouts/bam.hpp
        src/backend/utils/ie_string.hpp
        src/backend/utils/abstract_structs.hpp
)

set(TEST_COMMON
        src/backend/utils/errors.hpp
        src/backend/utils/errors.cpp
    tests/utils/tests_helper.hpp
        tests/utils/tests_helper.cpp
        src/backend/utils/helper_structs.hpp
)

set(GAM_TEST_SOURCES
    ${TEST_COMMON}
    tests/gam_file_tests.cpp
        src/backend/gam_file.cpp
        src/backend/gam_file.hpp
        src/backend/cre_file.cpp
)

set(TLK_TEST_SOURCES
    ${TEST_COMMON}
    tests/tlk_file_tests.cpp
        src/backend/tlk_file.cpp
        src/backend/tlk_file.hpp
)

set(STRING_TEST_SOURCES
    ${TEST_COMMON}
    tests/string_tests.cpp
)

set(QT_STRING_TEST_SOURCES
    ${TEST_COMMON}
    tests/qt_string_tests.cpp
        src/backend/tlk_file.cpp
        src/backend/tlk_file.hpp
)

set(KEY_TEST_SOURCES
    ${TEST_COMMON}
    tests/key_file_tests.cpp
        src/backend/key_file.cpp
        src/backend/key_file.hpp
)

set(BIFF_TEST_SOURCES
    ${TEST_COMMON}
    tests/biff_file_tests.cpp
        src/backend/biff_file.cpp
        src/backend/biff_file.hpp
)

set(ALL_TEST_SOURCES
    ${TLK_TEST_SOURCES}
    ${KEY_TEST_SOURCES}
    ${GAM_TEST_SOURCES}
    ${STRING_TEST_SOURCES}
    ${QT_STRING_TEST_SOURCES}
    ${BIFF_TEST_SOURCES}
        src/backend/binary_layouts/bmp.hpp
    tests/bitmap_tests.cpp
        src/backend/binary_layouts/itm.hpp
        src/backend/utils/ie_string.hpp
        src/frontend/profiles/games.hpp
        src/frontend/profiles/constants.hpp
        src/frontend/helpers/qt_strings.hpp
        src/backend/utils/ie_class.hpp
        src/frontend/resources/resource_repository.cpp
        src/frontend/resources/resource_repository.hpp
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    ${TS_FILES}
)


add_library (backend ${BACKEND_SOURCES}
        src/backend/binary_layouts/itm.hpp)
target_link_libraries(backend PRIVATE project_warnings)

set(FRONTEND_SOURCES
    ${BACKEND_SOURCES}
    src/main.cpp
        src/frontend/mainwindow.cpp
        src/frontend/mainwindow.hpp
    src/frontend/mainwindow.ui
    ${RES_FILES}
        src/frontend/helpers/gui_helpers.hpp
        src/frontend/helpers/disable_guard.hpp
        src/frontend/helpers/qt_io.hpp
        src/frontend/helpers/dialogs.hpp
        src/frontend/profiles/settings.cpp
        src/frontend/profiles/games.hpp
        src/frontend/profiles/constants.hpp
        src/frontend/views/variable_table_model.cpp
        src/frontend/views/variable_table_model.hpp
        src/frontend/views/css.hpp
        src/frontend/helpers/qt_strings.hpp
        src/frontend/resources/resource_repository.cpp
        src/frontend/resources/resource_repository.hpp
)

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

add_executable(qt_string_tests
    ${QT_STRING_TEST_SOURCES}
)

add_executable(all_tests
    ${ALL_TEST_SOURCES}
)

set(TEST_TARGETS
    tlk_file_test
    key_file_test
    gam_file_test
    biff_file_test
    string_tests
    qt_string_tests
    all_tests
)

foreach(test_target IN LISTS TEST_TARGETS)
    target_link_libraries(${test_target} PRIVATE GTest::gtest_main project_warnings)
endforeach()

target_link_libraries(qt_string_tests PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(all_tests PRIVATE Qt${QT_VERSION_MAJOR}::Core)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EE_SaveEditor
        MANUAL_FINALIZATION
        ${FRONTEND_SOURCES}
            src/frontend/views/savegamewidget.hpp src/frontend/views/savegamewidget.cpp src/frontend/views/savegamewidget.ui
    )

    qt_add_translations(EE_SaveEditor
        SOURCE_TARGETS EE_SaveEditor
        TS_FILES ${TS_FILES}
        RESOURCE_PREFIX "/translations"
    )
else()
    if(ANDROID)
        add_library(EE_SaveEditor SHARED
            ${BACKEND_SOURCES}
        )
    else()
        add_executable(EE_SaveEditor
            ${BACKEND_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(EE_SaveEditor PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::Concurrent
    project_warnings
)
target_include_directories(EE_SaveEditor
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/frontend/views
)

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
