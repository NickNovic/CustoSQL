# Add source files for PrimitiveTypes
file(GLOB PRIMITIVETYPES_SOURCES "*.cpp")

# Create a library for PrimitiveTypes
add_library(Helpers ${PRIMITIVETYPES_SOURCES})
