cmake_minimum_required(VERSION 3.28)

project(YARMI VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(YARMI_JUCE_SOURCE_DIR "" CACHE PATH "Use an existing JUCE checkout")
set(YARMI_LIBPD_SOURCE_DIR "" CACHE PATH "Use an existing libpd checkout")
set(YARMI_LINK_SOURCE_DIR "" CACHE PATH "Use an existing Ableton Link checkout")
set(YARMI_LINKKIT_SOURCE_DIR "" CACHE PATH "Directory containing LinkKit.xcframework")

if(YARMI_JUCE_SOURCE_DIR)
    add_subdirectory("${YARMI_JUCE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/_deps/juce-build")
else()
    FetchContent_Declare(juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 9.0.1
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(juce)
endif()

set(LIBPD_STATIC ON CACHE BOOL "" FORCE)
set(LIBPD_SHARED OFF CACHE BOOL "" FORCE)
set(PD_EXTRA OFF CACHE BOOL "" FORCE)
set(PD_UTILS OFF CACHE BOOL "" FORCE)
set(PD_MULTI OFF CACHE BOOL "" FORCE)
set(PD_LOCALE OFF CACHE BOOL "" FORCE)
set(PD_BUILD_C_EXAMPLES OFF CACHE BOOL "" FORCE)

if(YARMI_LIBPD_SOURCE_DIR)
    add_subdirectory("${YARMI_LIBPD_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/_deps/libpd-build")
else()
    FetchContent_Declare(libpd
        GIT_REPOSITORY https://github.com/libpd/libpd.git
        GIT_TAG 0.16.1
        GIT_SHALLOW TRUE
        GIT_SUBMODULES pure-data)
    FetchContent_MakeAvailable(libpd)
endif()

set(YARMI_IOS FALSE)
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(YARMI_IOS TRUE)
    set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH NO)

    if(YARMI_LINKKIT_SOURCE_DIR)
        set(linkkit_SOURCE_DIR "${YARMI_LINKKIT_SOURCE_DIR}")
    else()
        FetchContent_Declare(linkkit
            URL https://github.com/Ableton/LinkKit/releases/download/LinkKit-4.1/LinkKit.zip
            URL_HASH SHA256=25b101597d2c138310237bc21f8483b70aec2b93e4d101f26487d9efe437e613
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
            SOURCE_SUBDIR yarmi-no-cmakelists)
        FetchContent_MakeAvailable(linkkit)
    endif()
else()
    set(LINK_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(LINK_BUILD_JACK OFF CACHE BOOL "" FORCE)
    set(LINK_BUILD_ASIO OFF CACHE BOOL "" FORCE)

    if(YARMI_LINK_SOURCE_DIR)
        set(ableton_link_SOURCE_DIR "${YARMI_LINK_SOURCE_DIR}")
    else()
        FetchContent_Declare(ableton_link
            GIT_REPOSITORY https://github.com/Ableton/link.git
            GIT_TAG 902aef95bf94af49746fdda5369b42cdcfa1e6d2
            GIT_SHALLOW TRUE
            SOURCE_SUBDIR yarmi-no-cmakelists)
        FetchContent_MakeAvailable(ableton_link)
    endif()

    include("${ableton_link_SOURCE_DIR}/AbletonLinkConfig.cmake")
endif()

juce_add_binary_data(YarmiPdResources
    NAMESPACE YarmiBinaryData
    SOURCES
        Resources/Pd/yarmi.pd
        Resources/Pd/yarmi_voice.pd)

set(YARMI_APP_OPTIONS
    PRODUCT_NAME "YARMI"
    COMPANY_NAME "YARMI"
    BUNDLE_ID "art.yarmi.station"
    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE
    MICROPHONE_PERMISSION_ENABLED FALSE
    BACKGROUND_AUDIO_ENABLED TRUE
    LOCAL_NETWORK_PERMISSION_ENABLED TRUE
    LOCAL_NETWORK_PERMISSION_TEXT "YARMI uses the local network to share musical time with nearby Ableton Link peers.")

if(YARMI_IOS)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/cmake/YarmiInfo.plist" YARMI_INFO_PLIST_CONTENT)
    list(APPEND YARMI_APP_OPTIONS
        TARGETED_DEVICE_FAMILY "1,2"
        REQUIRES_FULL_SCREEN FALSE
        STATUS_BAR_HIDDEN TRUE
        PLIST_TO_MERGE "${YARMI_INFO_PLIST_CONTENT}")
endif()

juce_add_gui_app(YarmiStation ${YARMI_APP_OPTIONS})

target_sources(YarmiStation PRIVATE
    Source/Main.cpp
    Source/UI/MainComponent.cpp
    Source/UI/MainComponent.h
    Source/Core/Pattern.cpp
    Source/Core/Pattern.h
    Source/Core/Sequencer.cpp
    Source/Core/Sequencer.h
    Source/Audio/AudioBackend.h
    Source/Audio/AudioDiagnostics.cpp
    Source/Audio/AudioDiagnostics.h
    Source/Audio/LibPdBackend.cpp
    Source/Audio/LibPdBackend.h
    Source/Timing/TimingService.h
    Source/Timing/LinkTimingService.h)

if(YARMI_IOS)
    target_sources(YarmiStation PRIVATE Source/Timing/LinkTimingService_ios.mm)

    set(YARMI_LINKKIT_XCFRAMEWORK "${linkkit_SOURCE_DIR}/LinkKit.xcframework")
    if(NOT EXISTS "${YARMI_LINKKIT_XCFRAMEWORK}")
        message(FATAL_ERROR "LinkKit.xcframework was not found under ${linkkit_SOURCE_DIR}")
    endif()

    target_link_libraries(YarmiStation PRIVATE "${YARMI_LINKKIT_XCFRAMEWORK}")
    target_include_directories(YarmiStation PRIVATE
        "${YARMI_LINKKIT_XCFRAMEWORK}/ios-arm64/Headers"
        "${YARMI_LINKKIT_XCFRAMEWORK}/ios-arm64_x86_64-simulator/Headers")

    set(YARMI_LINKKIT_RESOURCES "${linkkit_SOURCE_DIR}/LinkKitResources.bundle")
    if(EXISTS "${YARMI_LINKKIT_RESOURCES}")
        set_source_files_properties("${YARMI_LINKKIT_RESOURCES}"
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        target_sources(YarmiStation PRIVATE "${YARMI_LINKKIT_RESOURCES}")
    endif()

    set_target_properties(YarmiStation PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Yarmi.entitlements"
        # JUCE's Objective-C++ platform modules use explicit retain/release.
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC NO)
else()
    target_sources(YarmiStation PRIVATE Source/Timing/LinkTimingService_desktop.cpp)
    target_link_libraries(YarmiStation PRIVATE Ableton::Link)
endif()

find_package(Threads REQUIRED)

target_include_directories(YarmiStation PRIVATE Source)
target_compile_definitions(YarmiStation PRIVATE
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:YarmiStation,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:YarmiStation,JUCE_VERSION>"
    JUCE_REPORT_APP_USAGE=0
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0)

target_link_libraries(YarmiStation PRIVATE
    YarmiPdResources
    libpd_static
    Threads::Threads
    juce::juce_audio_devices
    juce::juce_audio_utils
    juce::juce_gui_extra
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags)

if(APPLE)
    target_link_libraries(YarmiStation PRIVATE "-framework Accelerate")
endif()

if(NOT YARMI_IOS)
    include(CTest)
    if(BUILD_TESTING)
        add_executable(YarmiCoreTests
            tests/CoreTests.cpp
            Source/Core/Pattern.cpp
            Source/Core/Sequencer.cpp)
        target_include_directories(YarmiCoreTests PRIVATE Source)
        target_compile_features(YarmiCoreTests PRIVATE cxx_std_20)
        add_test(NAME YarmiCoreTests COMMAND YarmiCoreTests)

        add_executable(YarmiAudioTests
            tests/AudioBackendTests.cpp
            Source/Audio/LibPdBackend.cpp)
        target_include_directories(YarmiAudioTests PRIVATE Source)
        target_compile_definitions(YarmiAudioTests PRIVATE
            JUCE_REPORT_APP_USAGE=0
            JUCE_USE_CURL=0
            JUCE_WEB_BROWSER=0)
        target_link_libraries(YarmiAudioTests PRIVATE
            YarmiPdResources
            libpd_static
            Threads::Threads
            juce::juce_core)
        add_test(NAME YarmiAudioTests COMMAND YarmiAudioTests)
    endif()
endif()
