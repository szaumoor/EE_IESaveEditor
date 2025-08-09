cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("EESaveEditorBackend")

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
    "src/biff_files.h"
    "src/tlk_file.h"
    "src/tlk_file.cpp"
    "src/gam_file.h"
    "src/gam_file.cpp"
    "src/exceptions.h"
    "src/cre_file.h"
    "src/helper_structs.h"
    "src/eff_files.h"
    "src/aliases.h"
    "src/ie_files.h"
)

 add_executable(tlk_file_test
    tests/tlk_file_tests.cpp
    src/tlk_file.cpp
    src/tlk_file.h
    src/exceptions.h
 )

  add_executable(gam_file_test
    tests/gam_file_tests.cpp
    src/gam_file.cpp
    src/gam_file.h
  )

 target_link_libraries(tlk_file_test
    PRIVATE
    GTest::gtest_main
)

 target_link_libraries(gam_file_test
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tlk_file_test)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EESaveEditorBackend PROPERTY CXX_STANDARD 23)
endif()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)