#include "Tree234Graph.h"


void Tree234Graph::insert(int value)
{
	if (this->nodes.empty()) {
		int idNode = getMexNodeID();
		int idGroup = getMexGroupID();
		this->nodes[idNode] = new Node234(startPosition, value, font, fillColor, textColor, size, thickness);
		this->groups[idGroup] = new Group234(std::vector<int>(), size, thickness);
		root = idGroup;
		insertNode(idGroup, idNode);
		return;
	}
	int idGroup = root, par = -1;
	while (true) {
		if (groups[idGroup]->nodes.size() < 3 && idGroup != par) {
			int nextIDGroup = findEdge(idGroup, value);
			if (nextIDGroup == -1) {
				int idNode = getMexNodeID();
				this->nodes[idNode] = new Node234(startPosition, value, font, fillColor, textColor, size, thickness);
				insertNode(idGroup, idNode);
				break;
			}
			else {
				par = idGroup;
				idGroup = nextIDGroup;
			}
		}
		else if (par == -1) {
			std::vector <int> newGroupID = getMexGroupIDs(2);
			int idLeftGroup = newGroupID[0], idRightGroup = newGroupID[1];
			std::vector <int> edges = getEdges(idGroup);
			this->groups[idLeftGroup] = new Group234(std::vector<int>(), size, thickness);
			this->groups[idRightGroup] = new Group234(std::vector<int>(), size, thickness);
			insertNode(idLeftGroup, groups[idGroup]->nodes[0]);
			insertNode(idRightGroup, groups[idGroup]->nodes[2]);
			deleteNode(idGroup, groups[idGroup]->nodes[0]);
			deleteNode(idGroup, groups[idGroup]->nodes[1]);
			setEdge(idGroup, 0, idLeftGroup);
			setEdge(idGroup, 1, idRightGroup);
			setEdge(idLeftGroup, 0, edges[0]);
			setEdge(idLeftGroup, 1, edges[1]);
			setEdge(idRightGroup, 0, edges[2]);
			setEdge(idRightGroup, 1, edges[3]);
		}
		else if (idGroup != par) {
			std::vector <int> newGroupID = getMexGroupIDs(2);
			int idLeftGroup = newGroupID[0], idRightGroup = newGroupID[1];
			std::vector <int> edges = getEdges(idGroup);
			std::vector <int> parEdges = getEdges(par);
			int idEdgePos = findEdgePos(par, value);
			this->groups[idLeftGroup] = new Group234(std::vector<int>(), size, thickness);
			this->groups[idRightGroup] = new Group234(std::vector<int>(), size, thickness);
			insertNode(par, groups[idGroup]->nodes[1]);
			insertNode(idRightGroup, groups[idGroup]->nodes[2]);
			insertNode(idLeftGroup, groups[idGroup]->nodes[0]);
			delete this->groups[idGroup];
			this->groups.erase(idGroup);
			parEdges[idEdgePos] = idLeftGroup;
			parEdges.insert(parEdges.begin() + idEdgePos + 1, idRightGroup);
			for (int i = 0; i < parEdges.size(); i++) {
				setEdge(par, i, parEdges[i]);
			}
			setEdge(idLeftGroup, 0, edges[0]);
			setEdge(idLeftGroup, 1, edges[1]);
			setEdge(idRightGroup, 0, edges[2]);
			setEdge(idRightGroup, 1, edges[3]);
			idGroup = par;
		}
		else {
			int nextIDGroup = findEdge(idGroup, value);
			par = idGroup;
			idGroup = nextIDGroup;
		}
	}
}

bool Tree234Graph::Delete(int value, int id)
{
	int preID = -1;
	int idGroup = root;
	if (idGroup == -1) return false;
	int k = value;
	while (true) {
		if (groups[idGroup]->isLeaf()) {
			int curNode = findNode(idGroup, k);
			if (curNode != -1) {
				deleteNode(idGroup, curNode);
				delete this->nodes[curNode];
				this->nodes.erase(curNode);
				if (groups[idGroup]->nodes.size() == 0) {
					delete this->groups[idGroup];
					if (idGroup == root) root = -1;
				}
				return true;
			}
			return false;
		}
		int curNode = findNode(idGroup, k);
		int pos = findNodePos(idGroup, k);
		if (curNode != -1) {
			int leftIDGroup = groups[idGroup]->listEdge[pos];
			int rightIDGroup = groups[idGroup]->listEdge[pos + 1];

			if (groups[leftIDGroup]->nodes.size() >= 2) {
				int idGroupPredecessor = leftIDGroup, preID = -1;
				while (true) {
					if (groups[idGroupPredecessor]->isLeaf()) {
						int predecessor = nodes[groups[idGroupPredecessor]->nodes.back()]->getValue();
						this->nodes[curNode]->setValue(predecessor);
						idGroup = leftIDGroup;
						k = predecessor;
						break;
					}
					else {
						preID = idGroupPredecessor;
						idGroupPredecessor = groups[idGroupPredecessor]->listEdge.back();
					}
				}
			}
			else if (groups[rightIDGroup]->nodes.size() > 1) {
				int idGroupSuccessor = rightIDGroup, preID = -1;
				while (true) {
					if (groups[idGroupSuccessor]->isLeaf()) {
						int successor = nodes[groups[idGroupSuccessor]->nodes[0]]->getValue();
						this->nodes[curNode]->setValue(successor);
						idGroup = rightIDGroup;
						k = successor;
						break;
					}
					else {
						preID = idGroupSuccessor;
						idGroupSuccessor = groups[idGroupSuccessor]->listEdge[0];
					}
				}
			}
			else {
				int a = groups[leftIDGroup]->nodes[0];
				int b = groups[rightIDGroup]->nodes[0];

				std::vector <int> preListEdge;
				for (int i = 0; i <= pos; i++) {
					preListEdge.push_back(groups[idGroup]->listEdge[i]);
				}
				for (int i = pos + 2; i < groups[idGroup]->listEdge.size(); i++) {
					preListEdge.push_back(groups[idGroup]->listEdge[i]);
				}
				deleteNode(idGroup, curNode);
				deleteNode(rightIDGroup, b);
				delete this->groups[rightIDGroup];
				insertNode(leftIDGroup, curNode);
				insertNode(leftIDGroup, b);
				int x = groups[leftIDGroup]->listEdge[0];
				int y = groups[leftIDGroup]->listEdge[1];
				int z = groups[rightIDGroup]->listEdge[0];
				int w = groups[rightIDGroup]->listEdge[1];
				setEdge(leftIDGroup, 0, x);
				setEdge(leftIDGroup, 1, y);
				setEdge(leftIDGroup, 2, z);
				setEdge(leftIDGroup, 3, w);
				for (int i = 0; i < preListEdge.size(); i++) {
					setEdge(idGroup, i, preListEdge[i]);
				}
				idGroup = leftIDGroup;
			}
		}
		else {
			int nextIDGroup = findEdge(idGroup, k);
			int nextPos = findEdgePos(idGroup, k);
			if (groups[nextIDGroup]->nodes.size() != 1) {
				preID = idGroup;
				idGroup = nextIDGroup;
			}
			else {
				bool found = false;
				for (int delta = -1; delta <= 1; delta += 2) {
					int siblingPos = nextPos + delta;
					if (siblingPos < 0 || siblingPos > groups[idGroup]->nodes.size()) {
						continue;
					}
					int siblingIDGroup = groups[idGroup]->listEdge[siblingPos];
					if (groups[siblingIDGroup]->nodes.size() >= 2) {
						int idNodeStolen = groups[siblingIDGroup]->nodes[delta == 1 ? 0 : groups[siblingIDGroup]->nodes.size() - 1];
						int curNode = groups[idGroup]->nodes[delta == -1 ? nextPos - 1 : nextPos];
						std::vector <int> preCurListEdge, preSiblingListEdge, preNextListEdge;
						preCurListEdge = groups[idGroup]->listEdge;
						preSiblingListEdge = groups[siblingIDGroup]->listEdge;
						preSiblingListEdge.erase(preSiblingListEdge.begin() + (delta == 1 ? 0 : groups[siblingIDGroup]->listEdge.size() - 1));
						preNextListEdge = groups[nextIDGroup]->listEdge;
						preNextListEdge.insert(preNextListEdge.begin() + (delta == -1 ? 0 : groups[nextIDGroup]->listEdge.size()),
							groups[siblingIDGroup]->listEdge[delta == 1 ? 0 : groups[siblingIDGroup]->nodes.size()]);
						deleteNode(siblingIDGroup, idNodeStolen);
						deleteNode(idGroup, curNode);
						insertNode(idGroup, idNodeStolen);
						insertNode(nextIDGroup, curNode);
						for (int i = 0; i < preCurListEdge.size(); i++) {
							setEdge(idGroup, i, preCurListEdge[i]);
						}
						for (int i = 0; i < preSiblingListEdge.size(); i++) {
							setEdge(siblingIDGroup, i, preSiblingListEdge[i]);
						}
						for (int i = 0; i < preNextListEdge.size(); i++) {
							setEdge(nextIDGroup, i, preNextListEdge[i]);
						}
						found = true;
						break;
					}
				}
				if (!found) {
					int siblingIDGroup = nextPos == 0 ? groups[idGroup]->listEdge[1] : groups[idGroup]->listEdge[nextPos - 1];
					int deleteCurEdgePos = nextPos == 0 ? 1 : nextPos - 1;
					int idCurNode = groups[idGroup]->nodes[nextPos == 0 ? 0 : nextPos - 1];
					int idSiblingNode = groups[siblingIDGroup]->nodes[0];
					std::vector <int> preCurListEdge, preNextListEdge;
					preCurListEdge = groups[idGroup]->listEdge;
					preCurListEdge.erase(preCurListEdge.begin() + deleteCurEdgePos);
					int a, b, c, d;
					if (deleteCurEdgePos < nextPos) {
						a = groups[siblingIDGroup]->listEdge[0];
						b = groups[siblingIDGroup]->listEdge[1];
						c = groups[nextIDGroup]->listEdge[0];
						d = groups[nextIDGroup]->listEdge[1];
					}
					else {
						a = groups[nextIDGroup]->listEdge[0];
						b = groups[nextIDGroup]->listEdge[1];
						c = groups[siblingIDGroup]->listEdge[0];
						d = groups[siblingIDGroup]->listEdge[1];
					}
					preNextListEdge = { a, b, c, d };

					deleteNode(idGroup, idCurNode);
					deleteNode(siblingIDGroup, idSiblingNode);
					delete this->groups[siblingIDGroup];
					insertNode(nextIDGroup, idSiblingNode);
					insertNode(nextIDGroup, idCurNode);
					if (groups[idGroup]->nodes.size() == 1) {
						delete this->groups[idGroup];
						root = nextIDGroup;
						idGroup = -1;
					}
					else {
						for (int i = 0; i < preCurListEdge.size(); i++) {
							setEdge(idGroup, i, preCurListEdge[i]);
						}
					}
					for (int i = 0; i < preNextListEdge.size(); i++) {
						setEdge(nextIDGroup, i, preNextListEdge[i]);
					}
				}
				preID = idGroup;
				idGroup = nextIDGroup;
			}
		}
	}
	return true;
}

bool Tree234Graph::Delete(int value) {
	std::vector<int> v;
	for (auto it : nodes) {
		v.push_back(it.second->value);
	}
	bool exist = false;
	for (auto it : v) if (it == value) exist = true;
	if (exist == false) return false;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == value) v.erase(v.begin() + i);
	}
	clear();
	for (auto it : v) insert(it);
}
