cmake_minimum_required(VERSION 3.1)

project(Concurreny)


add_definitions(-D DBG_LEVEL=100)
add_definitions(-Werror)
add_definitions(-Wno-deprecated-declarations)
add_definitions(-Wreturn-type)  # int main()
add_definitions(-Wunused-value)
add_definitions(-Wunused-variable)
add_definitions(-Wuninitialized)
add_definitions(-Wreturn-local-addr)

# complier options
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fPIC")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")

set(sub_dirs 
    1_Thread 
    2_Lambda 
    3_Barrier
    4_Bug
    5_FunctionObject
    6_PassArgs
    6_shared_memory_with_no_race
    6_shared_memory_with_race
    6_shared_memory_with_race_but_std_move_to_recuse
    7_Future
    7_Future_ref_promise
    8_Except
    9_Async
    9_Async_with_void_function
    10_BadPass
    10_Launch
    10_Launch_thread_reuse
    11_BadConst
    #12_FileList
    #13_FileMonitor
    14_BankAccount
    #15_BankTransfer
    #16_BankDeadlock
    #17_FilePolling
    #18_Condition
    19_MessageQueue
    20_AtomicityBug
)
foreach(sub_dir ${sub_dirs})
  aux_source_directory(${PROJECT_SOURCE_DIR}/${sub_dir} SRCS)
  message(${sub_dir},${SRCS})
  add_executable(${sub_dir} ${SRCS})
  target_link_libraries(${sub_dir} pthread)
  set_target_properties(${sub_dir} PROPERTIES 
    compile_flags "-pthread"
    link_flags "-pthread"
  )
  set(SRCS "")
endforeach(sub_dir)
  
