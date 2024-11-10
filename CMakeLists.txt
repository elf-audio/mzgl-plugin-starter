set(APP_NAME "MyPlugin")
set(PLUGIN_NAME ${APP_NAME}-auv3)
cmake_minimum_required(VERSION 3.18)
project(${APP_NAME} VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(au_manufacturer ElfA)
set(au_type aumu)
set(au_sub_type MyPl)
set(au_name "${au_manufacturer}: MyPlugin")
set(au_description "MyPlugin")
set(au_principal_class MyPluginAUViewController)
set(au_tags <string>Synthesizer</string>)



set(bundle_copyright_string "(c) 2024 elf audio")

set(bundle_identifier ${au_manufacturer}.${APP_NAME})
string(TOLOWER ${bundle_identifier} bundle_identifier)

set(bundle_short_version_string "1.0")
set(bundle_version "1")
set(au_version 1)
include(auv3.cmake)

set(MZGL_ROOT "../koala/lib/mzgl")

include_directories(src)

set(SOURCES src/main.cpp)

add_executable(${APP_NAME} MACOSX_BUNDLE ${SOURCES})
add_dependencies(${APP_NAME} libmzgl ${PLUGIN_NAME})

### TODO: Can you put all these PROPERTIES into one set_target_properties?
set_target_properties( ${APP_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY    ${PROJECT_SOURCE_DIR}/bin
)

# Application bundle properties
set(EX_MACOSX_BUNDLE_NAME_DISPLAY_NAME ${APP_NAME})
set(EX_MACOSX_BUNDLE_EXECUTABLE ${APP_NAME})

set_target_properties(${APP_NAME} PROPERTIES
    XCODE_EMBED_PLUGINS ${PLUGIN_NAME}
    XCODE_EMBED_PLUGINS_CODE_SIGN_ON_COPY ON
    XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS res/app/app.entitlements
    XCODE_ATTRIBUTE_PRODUCT_NAME ${APP_NAME}
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${bundle_identifier}
)

set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/app/Info.plist
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${bundle_short_version_string}
        MACOSX_BUNDLE_BUNDLE_VERSION ${bundle_version}
        MACOSX_BUNDLE_GUI_IDENTIFIER ${bundle_identifier}
        MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME}
        MACOSX_BUNDLE_COPYRIGHT ${bundle_copyright_string}
        BUNDLE_EXTENSION app
)

add_subdirectory(${MZGL_ROOT} "mzgl-build" )

add_compile_definitions(GL_SILENCE_DEPRECATION MZGL_GL2 MZGL_MAC_GLFW __MACOSX_CORE__)	

# Link and set dependencies
target_link_libraries(${APP_NAME} libmzgl)
