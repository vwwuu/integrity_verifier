set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest inclusion
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/56efe3983185e3f37e43415d1afa97e3860f187f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

function(add_test_exe test_name)
	add_executable(${test_name} ${ARGN})

	target_link_libraries(${test_name}
		PRIVATE
		Integrity
		GTest::gtest_main
	)

	include(GoogleTest)
	gtest_discover_tests(${test_name})
endfunction()

add_test_exe(IntegrityCoreTest
    IntegrityCoreTest.cc
    TestHelpers.cc
)

add_test_exe(WriteModeTest
    WriteModeTest.cc
)
