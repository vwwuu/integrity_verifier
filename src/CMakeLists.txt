add_executable(${PROJECT_NAME} main.cc)

add_library(IntegrityCore
	IntegrityCore.cc
	status_out.cc
)

target_sources(IntegrityCore
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			${PROJECT_SOURCE_DIR}/include
		FILES
			${PROJECT_SOURCE_DIR}/include/status_out.h
			${PROJECT_SOURCE_DIR}/include/Statuses.h
			${PROJECT_SOURCE_DIR}/include/AcceptedFSType.h
			${PROJECT_SOURCE_DIR}/include/IntegrityCore.h			
)

find_package(OpenSSL REQUIRED)
target_link_libraries(IntegrityCore PUBLIC OpenSSL::Crypto)

target_link_libraries(${PROJECT_NAME} PRIVATE IntegrityCore)
