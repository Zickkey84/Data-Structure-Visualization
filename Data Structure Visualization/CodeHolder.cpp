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

std::string CC_GRAPH = "for (int v = 0; v < V; v++)\n" +
			std::string("   visited[v] = false;\n") + 
						"for (int v = 0; v < V; v++) {\n" +
						"   if (visited[v] == false) {\n" +
						"      DFSUtil(v, visited);\n" +
						"      count += 1;\n   }\n}\n" +
						"return count;";

std::string INSERT_TRIE = "TrieNode* temp = root;\n" +
			  std::string("for (int i = 0; word[i] != '\\0'; i++) {\n") + 
					      "  int idx = word[i] - 'a';\n" +
						  "  if (temp->children[idx] == NULL)\n" +
						  "    temp->children[idx] = makenode(word[i]);\n" +
						  "  temp = temp->children[idx];\n}\n" +
						  "temp->is_leaf = 1;";

std::string DELETE_TRIE = "If root is NULL or word is empty:\n" +
			  std::string("   Return root\n") + 
					      "If not a leaf node :\n" +
						  "   Return root\n" +
						  "Find the longest prefix that is not `word`\n" +
						  "Traverse the prefix :\n" +
						  "   Move down to the corresponding child node\n" +
						  "Delete nodes corresponding to `word`\n" +
						  "   Return root\n";

std::string SEARCH_TRIE = "TrieNode* temp = root;\n" +
			  std::string("for (int i = 0; word[i] != '\\0'; i++) {\n") + 
					      "	  int position = word[i] - 'a';\n" +
						  "   if (temp->children[position] == NULL)\n" +
						  "      return false;\n" +
						  "   temp = temp->children[position];\n}\n" +
						  "if (temp != NULL && temp->is_leaf == 1)\n" +
						  "   return true;\nreturn false;";

std::string INSERT_AVL = "if (root == NULL) {\n" +
			 std::string("   root = makeNode(key);\n") + 
					     "   return;\n}\n" +
						 "Node* cur = root;\n" +
						 "while (cur != NULL) {\n" +
						 "   if (key <= cur->key) cur = cur->left;\n" +
						 "   if (key > cur->key) cur = cur->right;\n}\n" +
						 "cur = makeNode(key);\nrebalanceTree()\n";

std::string DELETE_AVL= "if root is NULL: return NULL\n" +
			std::string("if key < root.key:\n") + 
					    "	root.left = deleteNode(root.left, key)\n" +
						"else if key > root.key:\n" +
						"   root.right = deleteNode(root.right, key)\n" +
					    "else:\n" +
						"   if root.left is NULL: return root.right\n" +
						"   if root.right is NULL: return root.left\n" +
						"   temp = minValueNode(root.right)\n" +
						"   root.key = temp.key\n" +
						"   root.right = deleteNode(root.right, temp.key)\n" +
						"UpdateHeight() and rebalanceTree()";

std::string SEARCH_AVL = "if (!root || root->key == key)\n" +
			 std::string("   return root\n") + 
					     "if (key < root->key)\n" +
						 "   return search(root->left, key)\n" +
						 "else\n" +
						 "   return search(root.left, key)\n";

std::string INSERT_234TREE = "if root is full :\n" +
				 std::string("   root = splitRoot(root)\n") + 
							 "insertNonFull(root, key)\n" +
							 "return root\n" +
							 "function insertNonFull(node, key) :\n" +
							 " if node.isLeaf : insertKey(node, key)\n" +
							 " else :\n" +
							 "    i = findChildIndex(node, key)\n" +
							 "    if node.children[i].isFull() :\n" +
							 "    splitChild(node, i)\n" +
							 " if key > node.keys[i]: i++\n"+
							 " insertNonFull(node.children[i], key)";

std::string DELETE_234TREE = "if root is leaf :\n" +
				 std::string("   deleteKey(root, key)\n") + 
							 "else :\n" +
							 "   i = findChildIndex(root, key)\n" +
							 "   if key in root.keys :\n" +
							 "     if root.children[i].numKeys > 1:\n" +
							 "       deletePredecessor(root.children[i])\n" +
							 "     else :\n" +
							 "       mergeChildren(root, i)\n" +
							 "       delete(root.children[i], key)\n" +
							 "	 else:\n"+
							 "     if root.children[i].numKeys == 1 :\n" +
							 "       fixChild(root, i)\n" + 
							 "		 delete(root.children[i], key)";

std::string SEARCH_234TREE = "i = 0\n" +
				 std::string("while i < node.numKeys and key > node.keys[i] :\n") + 
							 "    i += 1\n" +
							 "if i < node.numKeys and key == node.keys[i] :\n" +
							 "    return node\n" +
							 "if node.isLeaf :\n" +
							 "    return NULL\n" +
							 "else :\n" +
							 "    return search(node.children[i], key)\n";

	

	




	
		
		
			
			

		
		
			

			
				
				
		
	
	

	
		
	
		
		
			
			

