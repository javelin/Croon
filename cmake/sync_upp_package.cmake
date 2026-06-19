if(NOT DEFINED CROON_SOURCE_DIR)
    message(FATAL_ERROR "CROON_SOURCE_DIR is required")
endif()

if(NOT DEFINED CROON_PACKAGE_DIR)
    message(FATAL_ERROR "CROON_PACKAGE_DIR is required")
endif()

if(IS_SYMLINK "${CROON_PACKAGE_DIR}")
    file(REMOVE "${CROON_PACKAGE_DIR}")
else()
    file(REMOVE_RECURSE "${CROON_PACKAGE_DIR}")
endif()
file(MAKE_DIRECTORY "${CROON_PACKAGE_DIR}")

foreach(pattern IN ITEMS "*.upp" "*.cpp" "*.h" "*.lay" "*.iml")
    file(GLOB files "${CROON_SOURCE_DIR}/${pattern}")
    foreach(file IN LISTS files)
        get_filename_component(name "${file}" NAME)
        configure_file("${file}" "${CROON_PACKAGE_DIR}/${name}" COPYONLY)
    endforeach()
endforeach()

file(WRITE "${CROON_PACKAGE_DIR}/.croon-package-sync" "synced\n")
