#!/bin/bash

TEMPLATE_FILE="CMakeTemplates/template.module.txt"
TEST_TEMPLATE_FILE="CMakeTemplates/template.module.test.txt"

for dir in */; do
    [ -d "$dir" ] || continue
    cd "$dir" || continue

    MODULE_NAME=${dir%/}
    SRC_FILE=$(find . -maxdepth 1 -name "*.cpp" | grep -v "test" | head -n 1)
    HEADER_FILE=$(find . -maxdepth 1 -name "*.h" | head -n 1)

    if [[ -z "$SRC_FILE" ]]; then
        echo "Skipping $MODULE_NAME: Missing .cpp"
        cd ..
        continue
    fi

    HEADER_FILE_OPTIONAL=""
    INCLUDE_DIRECTORIES_OPTIONAL=""
    if [[ -n "$HEADER_FILE" ]]; then
        HEADER_FILE_OPTIONAL="$HEADER_FILE"
        INCLUDE_DIRECTORIES_OPTIONAL="target_include_directories($MODULE_NAME PUBLIC \${CMAKE_CURRENT_SOURCE_DIR})"
    fi

    TEST_FILE=$(find . -maxdepth 1 -name "*test*.cpp" | head -n 1)
    if [[ -n "$TEST_FILE" ]]; then
        TEST_BLOCK=$(<"../$TEST_TEMPLATE_FILE")
        TEST_BLOCK="${TEST_BLOCK//\{\{MODULE_NAME\}\}/$MODULE_NAME}"
        TEST_BLOCK="${TEST_BLOCK//\{\{TEST_FILE\}\}/$TEST_FILE}"
    else
        TEST_BLOCK=""
    fi

    TEMPLATE=$(<"../$TEMPLATE_FILE")
    TEMPLATE="${TEMPLATE//\{\{MODULE_NAME\}\}/$MODULE_NAME}"
    TEMPLATE="${TEMPLATE//\{\{SRC_FILE\}\}/$SRC_FILE}"
    TEMPLATE="${TEMPLATE//\{\{HEADER_FILE_OPTIONAL\}\}/$HEADER_FILE_OPTIONAL}"
    TEMPLATE="${TEMPLATE//\{\{INCLUDE_DIRECTORIES_OPTIONAL\}\}/$INCLUDE_DIRECTORIES_OPTIONAL}"
    TEMPLATE="${TEMPLATE//\{\{TEST_BLOCK\}\}/$TEST_BLOCK}"

    echo "$TEMPLATE" >CMakeLists.txt

    echo "✅ Generated CMakeLists.txt for $MODULE_NAME"
    cd ..
done
