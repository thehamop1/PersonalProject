add_test( LRU_CACHE.AddToZeroCache /home/thehamop/Github/PersonalProject/build/bin/LRUTEST [==[--gtest_filter=LRU_CACHE.AddToZeroCache]==] --gtest_also_run_disabled_tests)
set_tests_properties( LRU_CACHE.AddToZeroCache PROPERTIES WORKING_DIRECTORY /home/thehamop/Github/PersonalProject/build/test VS_DEBUGGER_WORKING_DIRECTORY)
set( LRUTEST_TESTS LRU_CACHE.AddToZeroCache)
