#include "CodeHolder.h"

std::string INSERT_HEAP = "if (capacity == number_of_value)\n    return;\n" + 
			  std::string("int i = number_of_value;\n") +
						  "arr.push_back(key);\n" + 
						  "number_of_value++;\n" +
						  "heapify_up(i);\n";

std::string DELETE_HEAP = "for (i = 0; i < n; i++)\n    if(this->arr[i] == key) break;\n" +
			  std::string("if (i == n) return;\n") +
						  "swap(arr[i], arr[n - 1]);\n" +
						  "arr.pop_back()\n" +
						  "heapify_down(i);\n";

std::string GETTOP_HEAP = "if (number_of_value == 0)\n    return -1;\n" +
			  std::string("int top = arr[0];\n") +
						  "arr[0] = arr[n - 1];\n" +
						  "arr.pop_back();\nnumber_of_value--;\n" +
						  "heapify_down(0);\n" +
						  "return top;\n";

std::string SIZE_HEAP = "return number_of_value;";