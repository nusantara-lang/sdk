# Recursively find all .cc source files in the current directory and subdirectories
file(GLOB_RECURSE NUSANTARA_SUPPORT_SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" # Match .cc files in the current source directory
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cc" # Match .cc files in all subdirectories
)

# Create a library target 'nusantaraSupport' using the collected source files
add_library(nusantaraSupport ${NUSANTARA_SUPPORT_SRC_FILES})

# Link the "nusantaraSupport" library with the specified LLVM libraries
target_link_libraries(nusantaraSupport PRIVATE
    ${LLVMSupport} # Link with LLVM Support static library
)