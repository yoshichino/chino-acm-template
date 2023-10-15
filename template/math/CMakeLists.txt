project(math)

aux_source_directory("./" mathSrc)

add_library(math INTERFACE ${mathSrc})

target_include_directories(math INTERFACE "./")