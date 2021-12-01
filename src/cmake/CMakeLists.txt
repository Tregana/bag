set(target bag)
add_library(${target} STATIC
  ${PROJECT_SOURCE_DIR}/src/bag.cpp
)
install(TARGETS ${target} DESTINATION lib)
