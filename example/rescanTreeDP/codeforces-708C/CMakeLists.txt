project(rescanTreeDP-codeforces-708C)


aux_source_directory("./" rescanTreeDP-codeforces-708CSrc)

add_executable(rescanTreeDP-codeforces-708C ${rescanTreeDP-codeforces-708CSrc})

target_link_libraries(rescanTreeDP-codeforces-708C PRIVATE dynamicProgramming)
