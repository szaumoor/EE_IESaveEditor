cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(EE_SaveEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wsign-conversion;-Wshadow;-Wold-style-cast;-Wnull-dereference>"
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>"
)

add_library(project_sanitizers INTERFACE)
if(ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(project_sanitizers INTERFACE
            -fsanitize=address,undefined -fno-omit-frame-pointer
        )
        target_link_options(project_sanitizers INTERFACE -fsanitize=address,undefined)
    else()
        message(WARNING "ENABLE_SANITIZERS is only supported with Clang or GCC")
    endif()
endif()

find_package(Qt6 6.7 REQUIRED COMPONENTS Widgets Concurrent LinguistTools)

add_library(backend STATIC
    src/backend/biff_file.cpp
    src/backend/biff_file.hpp
    src/backend/cre_file.cpp
    src/backend/cre_file.hpp
    src/backend/gam_file.cpp
    src/backend/gam_file.hpp
    src/backend/ie_files.hpp
    src/backend/key_file.cpp
    src/backend/key_file.hpp
    src/backend/tlk_file.cpp
    src/backend/tlk_file.hpp
    src/backend/binary_layouts/bam.hpp
    src/backend/binary_layouts/bmp.hpp
    src/backend/binary_layouts/cre.hpp
    src/backend/binary_layouts/gam.hpp
    src/backend/binary_layouts/itm.hpp
    src/backend/binary_layouts/key_biff.hpp
    src/backend/binary_layouts/spl.hpp
    src/backend/binary_layouts/tlk.hpp
    src/backend/utils/abstract_structs.hpp
    src/backend/utils/aliases.hpp
    src/backend/utils/errors.cpp
    src/backend/utils/errors.hpp
    src/backend/utils/helper_structs.hpp
    src/backend/utils/ie_class.hpp
    src/backend/utils/ie_string.hpp
    src/backend/utils/io.hpp
)
target_compile_features(backend PUBLIC cxx_std_23)
target_link_libraries(backend
    PUBLIC project_sanitizers
    PRIVATE project_warnings
)
set_target_properties(backend PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_precompile_headers(backend PRIVATE pch/backend.hpp)

qt_add_executable(EE_SaveEditor MANUAL_FINALIZATION
    src/main.cpp
    src/frontend/mainwindow.cpp
    src/frontend/mainwindow.hpp
    src/frontend/mainwindow.ui
    src/frontend/helpers/dialogs.hpp
    src/frontend/helpers/disable_guard.hpp
    src/frontend/helpers/gui_helpers.hpp
    src/frontend/helpers/qt_io.hpp
    src/frontend/helpers/qt_strings.hpp
    src/frontend/profiles/constants.hpp
    src/frontend/profiles/games.hpp
    src/frontend/profiles/games.cpp
    src/frontend/profiles/settings.cpp
    src/frontend/profiles/settings.hpp
    src/frontend/resources/resource_repository.cpp
    src/frontend/resources/resource_repository.hpp
    src/frontend/views/css.hpp
    src/frontend/views/savegamewidget.cpp
    src/frontend/views/savegamewidget.hpp
    src/frontend/views/savegamewidget.ui
    src/frontend/views/variable_table_model.cpp
    src/frontend/views/variable_table_model.hpp
    resources/resource.qrc
)
target_link_libraries(EE_SaveEditor PRIVATE
    backend
    Qt6::Widgets
    Qt6::Concurrent
    project_warnings
)
target_include_directories(EE_SaveEditor PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/frontend/views"
)
target_precompile_headers(EE_SaveEditor PRIVATE pch/frontend.hpp)
set_target_properties(EE_SaveEditor PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_add_translations(EE_SaveEditor
    SOURCE_TARGETS EE_SaveEditor
    TS_FILES
        translations/EE_SaveEditor_es.ts
        translations/EE_SaveEditor_zh_CN.ts
    RESOURCE_PREFIX "/translations"
)
qt_finalize_executable(EE_SaveEditor)

include(GNUInstallDirs)
install(TARGETS EE_SaveEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.tar.gz
        URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
    )
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "Use the shared MSVC runtime for GoogleTest" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)

    add_library(test_support STATIC
        tests/utils/tests_helper.cpp
        tests/utils/tests_helper.hpp
    )
    target_link_libraries(test_support PRIVATE project_warnings project_sanitizers)

    function(add_editor_test target)
        add_executable(${target} ${ARGN})
        target_link_libraries(${target} PRIVATE
            backend
            test_support
            GTest::gtest_main
            project_warnings
        )
        target_compile_definitions(${target} PRIVATE
            TEST_RES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/res"
        )
    endfunction()

    add_editor_test(tlk_file_test tests/tlk_file_tests.cpp)
    add_editor_test(key_file_test tests/key_file_tests.cpp)
    add_editor_test(gam_file_test tests/gam_file_tests.cpp)
    add_editor_test(biff_file_test tests/biff_file_tests.cpp)
    add_editor_test(string_tests tests/string_tests.cpp)
    add_editor_test(qt_string_tests tests/qt_string_tests.cpp)
    target_link_libraries(qt_string_tests PRIVATE Qt6::Core)

    add_editor_test(all_tests
        tests/biff_file_tests.cpp
        tests/bitmap_tests.cpp
        tests/gam_file_tests.cpp
        tests/key_file_tests.cpp
        tests/qt_string_tests.cpp
        tests/string_tests.cpp
        tests/tlk_file_tests.cpp
    )
    target_link_libraries(all_tests PRIVATE Qt6::Core)

    target_precompile_headers(all_tests PRIVATE pch/common.hpp <gtest/gtest.h>)
    add_test(NAME all_tests COMMAND all_tests)
endif()
