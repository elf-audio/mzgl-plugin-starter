function(set_au_appex_info_plist_properties target type sub_type manufacturer name description principal_class version tags)
    # Used in AudioComponents in Info.plist.in
    set(INFO_PLIST_AUDIO_COMPONENT_MANUFACTURER ${manufacturer} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_TYPE ${type} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_SUBTYPE ${sub_type} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_VERSION ${version} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_NAME ${name} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_DESCRIPTION ${description} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_EXTENSION_PRINCIPAL_CLASS ${principal_class} PARENT_SCOPE)
    set(INFO_PLIST_AUDIO_COMPONENT_TAGS ${tags} PARENT_SCOPE)
endfunction()


#set(application_extension_name ${application_name}Extension)
set(appex_bundle_identifier ${bundle_identifier}.${PLUGIN_NAME})
string(TOLOWER ${appex_bundle_identifier} appex_bundle_identifier)


set(appex_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AUV3.mm
)

add_executable(${PLUGIN_NAME} MACOSX_BUNDLE ${appex_src})


set_target_properties(${PLUGIN_NAME} PROPERTIES
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${bundle_short_version_string}
    MACOSX_BUNDLE_BUNDLE_VERSION ${bundle_version}
    MACOSX_BUNDLE_GUI_IDENTIFIER ${appex_bundle_identifier}
    MACOSX_BUNDLE_BUNDLE_NAME ${PLUGIN_NAME}
    INFO_PLIST_APPEX_BUNDLE_EXECUTABLE ${PLUGIN_NAME}
)

set_au_appex_info_plist_properties(${PLUGIN_NAME} ${au_type} ${au_sub_type} ${au_manufacturer} ${au_name} ${au_description} ${au_principal_class} ${au_version} ${au_tags})

set_target_properties(${PLUGIN_NAME} PROPERTIES
        CXX_STANDARD 20
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
        XCODE_PRODUCT_TYPE com.apple.product-type.app-extension
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/auv3/Info.plist
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS ${CMAKE_CURRENT_SOURCE_DIR}/res/auv3/auv3.entitlements
        XCODE_ATTRIBUTE_PRODUCT_NAME ${PLUGIN_NAME}
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${appex_bundle_identifier}
        XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "--deep"
)

target_link_libraries(${PLUGIN_NAME} libmzgl)
