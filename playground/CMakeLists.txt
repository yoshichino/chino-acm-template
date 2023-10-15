project(playground)

aux_source_directory("./" playgroundSrc)

add_executable(playground ${playgroundSrc})

target_link_libraries(playground PRIVATE math dynamicProgramming dataStructre)
