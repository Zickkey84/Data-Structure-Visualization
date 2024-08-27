#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "TreeNode.h"
#include "Miscellaneous.h"
#include "Color.h"

const float idealLength = 120;
const float springConstant = 0.9;
const float PI = 3.14;

struct GEdge {
    int from, to, weight;
    GEdge(int from, int to, int weight);
};

class GGraph{

public:
    float radius; int thickness;
    sf::Color fillColor, textColor;
    sf::Font* font;
    std::map <int, TreeNode*> nodes;
    std::set <GEdge*> edges;
    std::map<std::pair<int, int>, sf::Text*> WeightList;
    std::map<std::pair<int, int>, sf::RectangleShape*> EdgesList;
    sf::FloatRect viewRect;

    GGraph(std::set<GEdge*> edges, sf::FloatRect viewRect, colorTheme theme, float radius, int thickness, sf::Font* font);
    ~GGraph();
    void setEdges(std::set<GEdge*> edges, int maxSize = 0);
    float fAttract(float x);
    float fRepel(float x);
    sf::Vector2f springForce(sf::Vector2f stablePosition, sf::Vector2f mobilePosition, float idealLength);
    sf::Vector2f repelForce(sf::Vector2f stablePosition, sf::Vector2f mobilePosition, float idealLength);
    void arrangeGraph();
    sf::RectangleShape getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition);

	bool MST(int& d);
	int CC();
    void update();
    void render(sf::RenderTarget& target);
};

inline void dfs(int u, bool visited[], std::vector<std::vector<int>> adj, std::vector<int>& ans) {
	visited[u] = true;
	ans.push_back(u);
	for (int x : adj[u]) {
		if (!visited[x]) dfs(x, visited, adj, ans);
	}
}
inline void generateRandomMatrix(int x, std::set<GEdge*> &edges) {
	edges.clear();
	if (x <= 10 && x > 2) {
		int k = rand() % (x * (x - 1) / 2);
		bool** used = new bool* [x+1];
		for (int i = 0; i <= x; i++) used[i] = new bool[x+1];
		for (int i = 0; i <= x; i++) {
			for (int j = 0; j <= x; j++) used[i][j] = 0;
		}
		while (k--) {
			int f, t, w;
			f = rand() % x + 1;
			do {
				t = rand() % x + 1;
			} while (t == f);
			if (used[f][t] == false) {
				used[f][t] = true;
				used[t][f] = true;
				w = rand() % 99;
				edges.insert(new GEdge(f, t, w));
			}
			else {
				k++;
			}
		}
		for (int i = 1; i <= x; i++) {
			bool check = false;
			for (int j = 1; j <= x; j++) {
				if (used[i][j]) check = true;
			}
			if (!check) edges.insert(new GEdge(i, i, 0));
		}
		return;
	}
	if (x == 1) {
		edges.insert(new GEdge(1, 1, 0));
		return;
	}
	if (x == 2) {
		edges.insert(new GEdge(1, 2, rand() % 99));
		return;
	}
}