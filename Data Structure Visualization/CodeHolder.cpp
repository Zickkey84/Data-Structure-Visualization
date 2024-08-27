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

std::string INSERT_HASH =
			  std::string("while (!hashTable[index].empty()) {\n") +
						  "		index++;\n" +
						  "		if (index == hashTableSize) \n			index = 0;\n" +
						  "		if (index == hashCode(x))   \n			return false;\n}\n"	
						  "hashTable[index] = x;\n" +
						  "return true;\n ";

std::string DELETE_HASH = 
			  std::string("while (hashTable[index] != x) {\n") +
						  "		index++;\n" +
						  "		if (index == hashTableSize)\n			index = 0;\n" +
						  "		if (index == hashCode(x))  \n			return false;\n}\n" +
						  "delete hashTable[index];\n" +
						  "return true;\n";

std::string SEARCH_HASH =
			  std::string("while (this->hashArr[index] != x) {\n") +
						  "		index++;\n" +
						  "		if (index == this->size) \n			index = 0;\n" +
						  "		if (index == hashCode(x))\n			return NULL;\n}\n" +
						  "return index;";

std::string MST_GRAPH = "for (int cnt = 0; cnt < V - 1; cnt++) {\n" +
	        std::string("   int u = minKey(key, mstSet);\n") +
			       	    "   mstSet[u] = true;\n" + 
				        "   for (int v = 0; v < V; v++) {\n"
						"	    if (graph[u][v] && !mstSet[v]\n" +
				        "		    && graph[u][v] < key[v]){\n" +
				        "			  parent[v] = u;\n" +
			            "			  key[v] = graph[u][v];\n" +
				        "       }\n" +
						"   }\n}";

extern std::string CC_GRAPH = "for (int v = 0; v < V; v++)\n" +
			std::string("   visited[v] = false;\n") + 
						"for (int v = 0; v < V; v++) {\n" +
						"   if (visited[v] == false) {\n" +
						"      DFSUtil(v, visited);\n" +
						"      count += 1;\n   }\n}\n" +
						"return count;";
