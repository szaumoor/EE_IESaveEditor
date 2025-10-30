cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("EESaveEditorBackend")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

file(GLOB CHOC_SRC
    "src/choc/containers/*.h"
    "src/choc/math/*.h"
    "src/choc/platform/*.h"
    "src/choc/text/*.h"
    "src/choc/threading/*.h"
    "src/choc/memory/*.h"
)

add_library (EESaveEditorBackend
    ${CHOC_SRC}
    "src/backend/biff_files.h"
    "src/backend/tlk_file.h"
    "src/backend/tlk_file.cpp"
    "src/backend/gam_file.h"
    "src/backend/gam_file.cpp"
    "src/backend/cre_file.h"
    "src/backend/helper_structs.h"
        "src/backend/aliases.h"
    "src/backend/ie_files.h"
    "src/backend/cre_file.cpp"
    "src/backend/key_file.h"
    "src/backend/key_file.cpp"
 "src/backend/biff_files.cpp"
        src/backend/binary_layouts.h)

 add_executable(tlk_file_test
    tests/tlk_file_tests.cpp
         src/backend/tlk_file.cpp
         src/backend/tlk_file.h
 )

  add_executable(key_file_test
          src/backend/key_file.cpp
          src/backend/key_file.h
    tests/key_file_tests.cpp
 )

  add_executable(gam_file_test
    tests/gam_file_tests.cpp
          src/backend/gam_file.cpp
          src/backend/gam_file.h
          src/backend/cre_file.cpp
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

include(GoogleTest)
gtest_discover_tests(tlk_file_test)


include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)