#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

//int main() {
//  TestRunner tr;
//  tr.RunTest([] {
//    ostringstream output;
//    PRINT_VALUES(output, 5, "red belt");
//    ASSERT_EQUAL(output.str(), "5\nred belt\n");
//  }, "PRINT_VALUES usage example");
//  tr.RunTest([]{
//      ostringstream output;
//      if(true) PRINT_VALUES(output, 2, "true story");
//      else PRINT_VALUES(output,3,"false story");
//      ASSERT_EQUAL(output.str(), "2\ntrue story\n");
//  }, "PRINT_VALUES usage if");
//  tr.RunTest([]{
//      ostringstream output;
//      for(auto i : {1,2,3,4,5})
//           PRINT_VALUES(output, i, "");
//      ASSERT_EQUAL(output.str(), "1\n\n2\n\n3\n\n4\n\n5\n\n")
//  }, "PRINT_VALUES usage loop");
//}
