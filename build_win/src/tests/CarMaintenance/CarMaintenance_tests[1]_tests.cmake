add_test([=[MyTest.MenuTest]=]  E:/DataStructures/ce205-final-eray-burak-cakir-cpp/build_win/build/Release/CarMaintenance_tests.exe [==[--gtest_filter=MyTest.MenuTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MyTest.MenuTest]=]  PROPERTIES WORKING_DIRECTORY E:/DataStructures/ce205-final-eray-burak-cakir-cpp/build_win/src/tests/CarMaintenance SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  CarMaintenance_tests_TESTS MyTest.MenuTest)
