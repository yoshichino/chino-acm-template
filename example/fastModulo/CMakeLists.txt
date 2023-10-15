project(fastModulo-example)

aux_source_directory("./" fastModulo-exampleSrc)

add_executable(fastModulo-example ${fastModulo-exampleSrc})

target_link_libraries(fastModulo-example PRIVATE math)
