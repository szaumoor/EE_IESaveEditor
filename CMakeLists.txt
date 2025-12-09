cmake_minimum_required (VERSION 3.20)

if (POLICY CMP0135)
 cmake_policy(SET CMP0135 NEW)
endif()

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (EESaveEditor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

# set(CMAKE_CXX_COMPILER "/usr/bin/clang")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
#find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

enable_testing()

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

add_library (backend ${BACKEND_SOURCES})

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

add_executable(EESaveEditor
    ${BACKEND_SOURCES}
    src/frontend/mainwindow.cpp
    src/frontend/mainwindow.h
    src/frontend/mainwindow.ui
    src/main.cpp
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

target_link_libraries(EESaveEditor PRIVATE Qt6::Widgets)

#set(TS_FILES
#    src/frontend/translations/app_en.ts
#    src/frontend/translations/app_es.ts
#)
#
#qt_add_translations(EESaveEditor
#    TS_FILES ${TS_FILES}
#    QM_FILES_OUTPUT_VARIABLE QM_FILES
#)
#
#add_custom_target(translations ALL DEPENDS ${QM_FILES})

# Google Test setup
include(GoogleTest)
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)