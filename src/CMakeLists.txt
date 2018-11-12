link_libraries(cppkafka ${RDKAFKA_LIBRARY} ${Boost_LIBRARIES} pthread z)
include_directories(SYSTEM ${RDKAFKA_INCLUDE_DIR})
add_executable(engine "engine.cpp")
