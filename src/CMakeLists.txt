cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(mrlcp_naive_source_files
	naive.cpp
)
add_executable(mrlcp-naive ${mrlcp_naive_source_files})
target_link_libraries(mrlcp-naive ${Boost_LIBRARIES})

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(mrlcp_irreducible_source_files
	irreducible.cpp
)
add_executable(mrlcp-irreducible ${mrlcp_irreducible_source_files})
target_link_libraries(mrlcp-irreducible ${Boost_LIBRARIES})

set(mrlcp_posorder_source_files
	posorder.cpp
)
add_executable(mrlcp-posorder ${mrlcp_posorder_source_files})
target_link_libraries(mrlcp-posorder ${Boost_LIBRARIES})
