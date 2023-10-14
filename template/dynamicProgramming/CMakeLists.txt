project(dynamicProgramming)

aux_source_directory("./" dynamicProgrammingSrc)

add_library(dynamicProgramming INTERFACE ${dynamicProgrammingSrc})

target_include_directories(dynamicProgramming INTERFACE "./")