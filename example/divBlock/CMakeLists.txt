project(divBlock-example)


aux_source_directory("./" divBlock-exampleSrc)

add_executable(divBlock-example ${divBlock-exampleSrc})

target_link_libraries(divBlock-example PRIVATE math)
