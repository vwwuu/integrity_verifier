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

add_executable(IntegrityCoreTest
	IntegrityCoreTest.cc
	TestHelpers.cc
)

target_link_libraries(IntegrityCoreTest
	PRIVATE
	IntegrityCore
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(IntegrityCoreTest)
