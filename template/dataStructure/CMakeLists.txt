project(dataStructre)

aux_source_directory("./" dataStructreSrc)

add_library(dataStructre INTERFACE ${dataStructreSrc})

target_include_directories(dataStructre INTERFACE "./")