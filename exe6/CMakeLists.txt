add_executable(exe6
        main.c
)

target_link_libraries(exe6 pico_stdlib)
pico_add_extra_outputs(exe6)
