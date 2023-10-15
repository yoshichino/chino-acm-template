project(modInt-example)

aux_source_directory("./" modIntSrc)

add_executable(modInt ${modIntSrc})

target_link_libraries(modInt PRIVATE math)
