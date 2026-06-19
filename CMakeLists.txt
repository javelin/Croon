cmake_minimum_required(VERSION 3.20)

project(Croon LANGUAGES NONE)

set(CROON_UPP_ROOT "/Users/mdoc/Dev/u++/upp" CACHE PATH "Ultimate++ root containing uppsrc")
set(CROON_UPPSRC "${CROON_UPP_ROOT}/uppsrc" CACHE PATH "Ultimate++ uppsrc nest")
set(CROON_BUILD_METHOD "CLANG" CACHE STRING "U++ build method name or .bm path")

find_program(UPP_UMK NAMES umk DOC "Ultimate++ command-line builder")
find_package(Python3 REQUIRED COMPONENTS Interpreter)

enable_testing()

add_test(
    NAME croon_identity
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_identity.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_core_contracts
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_core_contracts.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_process_contracts
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_process_contracts.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_simple_layouts
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_simple_layouts.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_wizard_layouts
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_wizard_layouts.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_editor_layouts
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_editor_layouts.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_test(
    NAME croon_export_audit
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests/validate_export_audit.py" "${CMAKE_CURRENT_SOURCE_DIR}"
)

set(CROON_NESTS "${CMAKE_CURRENT_SOURCE_DIR};${CROON_UPPSRC}")

if(UPP_UMK)
    add_custom_target(croon
        COMMAND "${UPP_UMK}" "${CROON_NESTS}" Croon "${CROON_BUILD_METHOD}" -br
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Building Croon with Ultimate++ umk"
        VERBATIM
    )
else()
    add_custom_target(croon
        COMMAND "${CMAKE_COMMAND}" -E echo "umk was not found. Reconfigure with -DUPP_UMK=/path/to/umk or add umk to PATH."
        COMMAND "${CMAKE_COMMAND}" -E false
        COMMENT "Cannot build Croon without Ultimate++ umk"
        VERBATIM
    )
endif()
