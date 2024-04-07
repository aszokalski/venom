Include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0)  #v1.14
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    # Note: We add this directory to prevent installing Google Test
    # into the user's system and only use it for this project
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    add_subdirectory("${googletest_SOURCE_DIR}" "${googletest_BINARY_DIR}")
endif()

enable_testing()
include(GoogleTest)
set(STUBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stubs" CACHE STRING "Dir for stubs ")
add_subdirectory(juce_audio_processors)

