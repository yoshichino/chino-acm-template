project(segmentTreeDivide-luogu-P787)


aux_source_directory("./" segmentTreeDivide-luogu-P787Src)

add_executable(segmentTreeDivide-luogu-P787 ${segmentTreeDivide-luogu-P787Src})

target_link_libraries(segmentTreeDivide-luogu-P787 PRIVATE dataStructre)
