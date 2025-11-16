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

find_package(Qt6 REQUIRED COMPONENTS Widgets)

enable_testing()

set(BACKEND_SOURCES
   src/backend/biff_files.h
   src/backend/tlk_file.h
   src/backend/tlk_file.cpp
   src/backend/gam_file.h
   src/backend/gam_file.cpp
   src/backend/cre_file.h
   src/backend/helper_structs.h
   src/backend/aliases.h
   src/backend/ie_files.h
   src/backend/cre_file.cpp
   src/backend/key_file.h
   src/backend/key_file.cpp
   src/backend/biff_files.cpp
   src/backend/binary_layouts.h
)

set(GAM_TEST_SOURCES
   src/backend/gam_file.cpp
   src/backend/gam_file.h
   src/backend/cre_file.cpp
)

set(TLK_TEST_SOURCES
  src/backend/tlk_file.cpp
  src/backend/tlk_file.h
)

set(KEY_TEST_SOURCES
  src/backend/key_file.cpp
  src/backend/key_file.h
)

set(ALL_TEST_SOURCES
   ${TLK_TEST_SOURCES}
   ${KEY_TEST_SOURCES}
   ${GAM_TEST_SOURCES}
        src/backend/choc/string_utilities.h
        src/backend/choc/choc_assert.h
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

add_executable(all_tests
  tests/gam_file_tests.cpp
  tests/key_file_tests.cpp
  tests/tlk_file_tests.cpp
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

target_link_libraries(all_tests
   PRIVATE
   GTest::gtest_main
)

target_link_libraries(EESaveEditor PRIVATE Qt6::Widgets)

include(GoogleTest)
gtest_discover_tests(tlk_file_test)


include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)