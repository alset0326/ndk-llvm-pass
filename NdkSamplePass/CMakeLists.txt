# Modify name here
set(PASS_NAME NdkSamplePass)

add_library(${PASS_NAME} MODULE
        # List your source files here.
        Pass.cpp
        )

# Use C++11 to compile your pass (i.e., supply -std=c++11).
target_compile_features(${PASS_NAME} PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(${PASS_NAME} PROPERTIES COMPILE_FLAGS "-fno-rtti")

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if (APPLE)
    set_target_properties(${PASS_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif (APPLE)

