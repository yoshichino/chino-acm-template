project(segmentTree-luogu-P1083)

aux_source_directory("./" segmentTree-luogu-P1083Src)

add_executable(segmentTree-luogu-P1083 ${segmentTree-luogu-P1083Src})

target_link_libraries(segmentTree-luogu-P1083 PRIVATE dataStructre)
