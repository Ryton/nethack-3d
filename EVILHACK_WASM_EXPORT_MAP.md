# EvilHack WASM Export Mapping

This table documents the mapping between JavaScript property names (used in the EvilHack JS glue code), the actual WASM export keys, and the internal WASM function index/name for EvilHack's WASM build. This mapping is used to ensure the JS glue code can reliably access the correct WASM exports, even if the export names change or are obfuscated.

| JS Name (Module property)         | WASM Export Key                | Internal WASM Function (index <name>) |
|-----------------------------------|-------------------------------|---------------------------------------|
| memory                           | memory                        | -                                     |
| _malloc                          | malloc                        | func[2567] <malloc>                   |
| _free                            | free                          | func[2568] <free>                     |
| _shim_graphics_set_callback      | shim_graphics_set_callback    | func[1403] <shim_graphics_set_callback> |
| _main                            | __main_argc_argv              | func[2341] <__main_argc_argv>         |
| _memset                          | memset                        | func[2418] <memset>                   |
| _memcpy                          | memcpy                        | func[2429] <memcpy>                   |
| _realloc                         | realloc                       | func[2569] <realloc>                  |
| __emscripten_stack_restore       | _emscripten_stack_restore     | func[2586] <_emscripten_stack_restore> |
| __emscripten_stack_alloc         | _emscripten_stack_alloc       | func[2587] <_emscripten_stack_alloc>   |
| _emscripten_stack_get_current    | emscripten_stack_get_current  | func[2588] <emscripten_stack_get_current> |
| dynCall_vi                       | dynCall_vi                    | func[2589] <dynCall_vi>               |
| dynCall_iii                      | dynCall_iii                   | func[2590] <dynCall_iii>              |
| dynCall_iiii                     | dynCall_iiii                  | func[2591] <dynCall_iiii>             |
| dynCall_ii                       | dynCall_ii                    | func[2592] <dynCall_ii>               |
| dynCall_i                        | dynCall_i                     | func[2593] <dynCall_i>                |
| dynCall_vii                      | dynCall_vii                   | func[2594] <dynCall_vii>              |
| dynCall_viii                     | dynCall_viii                  | func[2595] <dynCall_viii>             |
| dynCall_iiiii                    | dynCall_iiiii                 | func[2596] <dynCall_iiiii>            |
| dynCall_v                        | dynCall_v                     | func[2597] <dynCall_v>                |
| dynCall_viiiiiiii                | dynCall_viiiiiiii             | func[2598] <dynCall_viiiiiiii>        |
| dynCall_viiiii                   | dynCall_viiiii                | func[2599] <dynCall_viiiii>           |
| dynCall_viij                     | dynCall_viij                  | func[2600] <dynCall_viij>             |
| dynCall_viiii                    | dynCall_viiii                 | func[2601] <dynCall_viiii>            |
| dynCall_viiiiii                  | dynCall_viiiiii               | func[2602] <dynCall_viiiiii>          |
| dynCall_jiji                     | dynCall_jiji                  | func[2603] <dynCall_jiji>             |
| dynCall_iidiiii                  | dynCall_iidiiii               | func[2604] <dynCall_iidiiii>          |
| _asyncify_start_unwind           | asyncify_start_unwind         | func[2605] <asyncify_start_unwind>    |
| _asyncify_stop_unwind            | asyncify_stop_unwind          | func[2606] <asyncify_stop_unwind>     |
| _asyncify_start_rewind           | asyncify_start_rewind         | func[2607] <asyncify_start_rewind>    |
| _asyncify_stop_rewind            | asyncify_stop_rewind          | func[2608] <asyncify_stop_rewind>     |
| __indirect_function_table        | __indirect_function_table     | -                                     |

This mapping is used in the EvilHack WASM build script to patch the JS glue code after each build.
