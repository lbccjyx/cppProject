// test/main.cpp

// BOOST_TEST_MODULE 定义了程序名, 将在输出消息中使用。
// 一个测试程序中只允许存在一个定义一个测试模块。 测试模块中存在一个主测试套件，所有未明确包含到测试套件中的测试用例将被包含到主测试套件中。
#define BOOST_TEST_MODULE MyTest

// 一个头文件中包含了整个单元测试框架
#include <boost/test/included/unit_test.hpp>



/*
测试模块中存在一个主测试套件
BOOST_AUTO_TEST_SUITE (tests_suit)->创建一个名为calculator_tests的测试套件，
所有未明确包含到测试套件中的测试用例将被包含到主测试套件中。
BOOST_AUTO_TEST_CASE(my_test1)->创建一个名为“my_test1”的测试用例，并将其加入到测试套件tests_suit中。

BOOST_CHECK ：这种方法将检查到的错误保存起来，测试结束时由测试框架自动显示；
BOOST_REQUIRE ：同样是检查错误，与BOOST_CHECK 不同之处在于如果发生错误时将抛出一个异常，因此后续的测试将不会继续进行；
BOOST_ERROR ：可以用来对错误进行独立描述，测试结束时由测试框架自动显示；
BOOST_FAIL ：同样可以用来对错误进行独立描述，调用时将抛出一个异常；
抛出异常方式：测试框架将捕获该异常并打印出错误信息；
BOOST_CHECK_MESSAGE ：与BOOST_CHECK 类似，可以在第二个参数中加入错误描述信息；
BOOST_CHECK_EQUAL ：与BOOST_CHECKL 类似，用来检查两个参数是否相等。
*/