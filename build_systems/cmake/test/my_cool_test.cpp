//TODO: make the DYN_LINK change depending on the targeted architecture.  some need it, others don't.
//if used, this BOOST_TEST_DYN_LINK appear before #include <boost/test/unit_test.hpp>
#define BOOST_TEST_DYN_LINK

//this #define MUST appear before #include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE "My Cool Library and Program Testing"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(num_traits_checking)


BOOST_AUTO_TEST_CASE(test_case_1)
{
	BOOST_CHECK_EQUAL(1+1,2); // dear god, please let this be true
}

BOOST_AUTO_TEST_CASE(test_case_2)
{
	BOOST_CHECK_EQUAL(1+3,5); // this had better not be true.  this test deliberately fails.  fix it!
}

BOOST_AUTO_TEST_SUITE_END()
