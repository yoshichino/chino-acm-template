project(segmentTreeDivide-codeforces-813F)

aux_source_directory("./" segmentTreeDivide-codeforces-813FSrc)

add_executable(segmentTreeDivide-codeforces-813F ${segmentTreeDivide-codeforces-813FSrc})

target_link_libraries(segmentTreeDivide-codeforces-813F PRIVATE dataStructre)
