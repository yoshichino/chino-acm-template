project(segmentTree-luogu-P3372)

aux_source_directory("./" segmentTree-luogu-P3372Src)

add_executable(segmentTree-luogu-P3372 ${segmentTree-luogu-P3372Src})

target_link_libraries(segmentTree-luogu-P3372 PRIVATE dataStructre)
