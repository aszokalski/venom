cmake_minimum_required(VERSION 3.15)
project(juce_initializer LANGUAGES CXX)

add_library(juceinit STATIC Initialzier.cpp)
set_property(TARGET juceinit PROPERTY POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(juceinit
        PRIVATE
        juce_shared
        spdlog::spdlog
)
target_include_directories(juceinit
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/initializer>
        $<INSTALL_INTERFACE:include>
)
target_compile_definitions(juceinit
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

add_library(creation_manager STATIC MessageManagerHelper.cpp)
set_property(TARGET creation_manager PROPERTY POSITION_INDEPENDENT_CODE TRUE)

target_link_libraries(creation_manager
        PRIVATE
        juce_shared
        juceinit
        spdlog::spdlog
)
target_include_directories(creation_manager
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/creation>
        $<INSTALL_INTERFACE:include>
)
target_compile_definitions(creation_manager
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)