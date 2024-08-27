#include "GGraph.h"

GGraph::GGraph(std::set<GEdge*> edges, sf::FloatRect viewRect, colorTheme theme, float radius, int thickness, sf::Font* font)  {
    this->font = font;
    this->radius = radius;
    this->thickness = thickness;
    this->viewRect = viewRect;
    this->fillColor = HEAP::color[theme][HEAP::Normal].fillColor;
    this->textColor = HEAP::color[theme][HEAP::Normal].outlineColor;
    setEdges(edges);
}

GGraph::~GGraph()
{
    auto it = this->nodes.begin();
    for (it; it != nodes.end(); it++) delete it->second;
    auto it2 = this->EdgesList.begin();
    for (it2; it2 != EdgesList.end(); it2++) delete it2->second;
    auto it3 = this->WeightList.begin();
    for (it3; it3 != WeightList.end(); it3++) delete it3->second;
}

void GGraph::setEdges(std::set<GEdge*> edges, int maxSize) {
    this->edges.clear();
    for (auto x : edges) {
        this->edges.insert(x);
        maxSize = std::max(maxSize, std::max(x->from, x->to));
    }
    nodes.clear();
    for (int i = 1; i <= maxSize; i++) {
        nodes[i] = new TreeNode(sf::Vector2f(0, 0), radius, thickness, fillColor, textColor, i, font);
    }
    int numNode = nodes.size();
    float angle = 2 * PI / numNode;
    std::vector <int> idList;
    for (auto x = nodes.begin(); x != nodes.end(); x++) {
        idList.push_back(x->first);
    }
    if (idList.size() == 1) {
        nodes[idList[0]]->setPosition(sf::Vector2f(viewRect.left + viewRect.width / 2, viewRect.top + viewRect.height / 2));
        return;
    }
    if (idList.size() == 2) {
        nodes[idList[0]]->setPosition(sf::Vector2f(viewRect.left + viewRect.width / 2 - viewRect.width / 4, viewRect.top + viewRect.height / 2));
        nodes[idList[1]]->setPosition(sf::Vector2f(viewRect.left + viewRect.width / 2 + viewRect.width / 4, viewRect.top + viewRect.height / 2));
        return;
    }
    for (int i = 0; i < idList.size(); i++) {
        int x = idList[i];
        nodes[x]->setPosition(sf::Vector2f(viewRect.left + viewRect.width / 2 + viewRect.width * 0.5f * cos(angle * i), viewRect.top + viewRect.height / 2 + viewRect.height * 0.5f * sin(angle * i)));
    }
    if (maxSize <= 6 || edges.size() <= maxSize * 2) {
        arrangeGraph();
    }
}

sf::Vector2f GGraph::springForce(sf::Vector2f stablePosition, sf::Vector2f mobilePosition, float idealLength) {
    sf::Vector2f delta = mobilePosition - stablePosition;
    float diff = length(delta) - idealLength;
    return -springConstant * diff * normalize(delta);
}

sf::Vector2f GGraph::repelForce(sf::Vector2f stablePosition, sf::Vector2f mobilePosition, float idealLength) {
    sf::Vector2f delta = mobilePosition - stablePosition;
    float diff = length(delta) - idealLength;
    if (diff > 0) {
        return sf::Vector2f(0, 0);
    }
    return -springConstant * diff * normalize(delta);
}


void GGraph::arrangeGraph() {
    std::vector <int> idList;
    for (auto x : nodes) {
        idList.push_back(x.first);
    }
    if (idList.empty()) {
        return;
    }
    int maxNode = nodes.rbegin()->first;
    std::vector <sf::Vector2f> pos, nextPos, prePos;
    pos.resize(maxNode + 1);
    nextPos.resize(maxNode + 1);
    for (int i = 0; i < idList.size(); i++) {
        pos[idList[i]] = nodes[idList[i]]->getVertexPosition();
    }
    prePos = pos;
    float maximumDisp = 0;
    for (auto u : idList) {
        for (auto v : idList) {
            if (u == v) continue;
            sf::Vector2f delta = pos[u] - pos[v];
            maximumDisp = std::max(maximumDisp, length(delta));
        }
    }
    maximumDisp /= 2;
    for (int t = 0; t < 1000; t++) {
        std::vector <sf::Vector2f> disp;
        disp.resize(maxNode + 1);
        for (int u : idList) {
            nextPos[u] = pos[u];
        }

        for (auto edge : edges) {
            int u = edge->from;
            int v = edge->to;
            sf::Vector2f middle = (pos[u] + pos[v]) / 2.0f;
            disp[u] += springForce(middle, pos[u], idealLength);
            disp[v] += springForce(middle, pos[v], idealLength);
        }
        std::vector <std::vector <bool>> adjacencyMatrix(maxNode + 1, std::vector <bool>(maxNode + 1, false));
        for (auto edge : edges) {
            int u = edge->from;
            int v = edge->to;
            adjacencyMatrix[u][v] = true;
        }
        for (int u : idList) {
            for (int v : idList) {
                if (!adjacencyMatrix[u][v]) {
                    sf::Vector2f middle = (pos[u] + pos[v]) / 2.0f;
                    disp[u] += repelForce(middle, pos[u], idealLength);
                    disp[v] += repelForce(middle, pos[v], idealLength);
                }
            }
        }
        for (auto edge : edges) {
            int u = edge->from;
            int v = edge->to;
            sf::Vector2f middle = (pos[u] + pos[v]) / 2.0f;
            for (int x : idList) {
                if (x == u || x == v) continue;
                disp[x] += repelForce(middle, pos[x], idealLength);
            }
            for (auto otherEdge : edges) {
                int x = otherEdge->from;
                int y = otherEdge->to;
                if (x == u && y == v) continue;
                sf::Vector2f otherMiddle = (pos[x] + pos[y]) / 2.0f;
                disp[x] += repelForce(middle, otherMiddle, idealLength);
                disp[y] += repelForce(middle, otherMiddle, idealLength);
            }
        }
        for (int x : idList) {
            for (auto edge : edges) {
                int u = edge->from;
                int v = edge->to;
                if (u == x || v == x) continue;
                sf::Vector2f middle = (pos[u] + pos[v]) / 2.0f;
                disp[u] += repelForce(pos[x], middle, idealLength);
                disp[v] += repelForce(pos[x], middle, idealLength);
            }
        }
        sf::Vector2f screenCenter = sf::Vector2f(viewRect.left + viewRect.width / 2, viewRect.top + viewRect.height / 2);
        sf::Vector2f totalPos = sf::Vector2f(0, 0);
        for (int u : idList) {
            totalPos += pos[u];
        }
        totalPos *= 1.f / maxNode;
        for (int u : idList) {
            disp[u] += springForce(screenCenter, totalPos, 0);
        }

        bool flag = false;
        for (int v : idList) {
            nextPos[v] += normalize(disp[v]) * std::min(length(disp[v]), maximumDisp);
            if (length(disp[v]) > 0.000001f) {
                flag = true;
            }
            nextPos[v].x = std::max(viewRect.left, std::min(viewRect.left + viewRect.width, nextPos[v].x));
            nextPos[v].y = std::max(viewRect.top, std::min(viewRect.top + viewRect.height, nextPos[v].y));
        }
        maximumDisp *= 0.99;
        pos = nextPos;
        if (!flag) {
            break;
        }
    }
    bool goodGraph = true;
    for (int u : idList) {
        for (int v : idList) {
            if (u == v) continue;
            if (pos[u] == pos[v]) {
                goodGraph = false;
                break;
            }
        }
        if (!goodGraph) {
            break;
        }
    }
    if (!goodGraph) {
        pos = prePos;
    }
    for (auto& x : nodes) {
        x.second->setPosition(pos[x.first]);
    }
}

sf::RectangleShape GGraph::getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition)
{
    sf::Vector2f diff = endPosition - startPosition;
    float lengthDiff = sqrt(diff.x * diff.x + diff.y * diff.y);
    if (lengthDiff < 2.f * (this->radius + this->thickness)) {
        return sf::RectangleShape();
    }
    sf::RectangleShape line(sf::Vector2f((lengthDiff - 2.f * (this->radius + (float)this->thickness)), this->thickness));
    line.setOrigin(0, (float)this->thickness / 2.f);
    line.setRotation(atan2(diff.y, diff.x) * 180.f / 3.14159265);
    line.setPosition(startPosition + sf::Vector2f(diff.x / lengthDiff, diff.y / lengthDiff) * (this->radius + (float)this->thickness));
    line.setFillColor(this->textColor);
    return line;
}

bool GGraph::MST(int& d)
{
    int maxSize = 0;
    for (auto x : this->edges) {
        maxSize = std::max(maxSize, std::max(x->from, x->to));
    }
    std::vector<std::vector<std::pair<int, int>>> adj(maxSize + 1);
    bool used[11] = { 0 };

    for (auto it : this->edges) {
        int f = it->from, t = it->to, w = it->weight;
        if (w != 0) {
            adj[f].push_back({ t,w });
            adj[t].push_back({ f,w });
        }
    }

    std::vector<GEdge> MST;
    used[1] = true;
    while (MST.size() < maxSize - 1) {
        int min_w = INT_MAX;
        int X = -1, Y = -1;
        for (int i = 1; i <= maxSize; i++) {
            if (used[i]) {
                for (std::pair<int, int> it : adj[i]) {
                    int j = it.first, weight = it.second;
                    if (!used[j] && weight < min_w) {
                        min_w = weight;
                        X = j; Y = i;
                    }
                }
            }
        }
        if (X != -1 && Y != -1) {
            MST.push_back({ X,Y,min_w });
            d += min_w;
            used[X] = true;
        }
        else return false;
    }
    for (GEdge e : MST) {
        for (auto it : EdgesList) {
            if (it.first.first == e.from && it.first.second == e.to ||
                it.first.second == e.from && it.first.first == e.to) {
                it.second->setFillColor(NeonPink);
            }
        }
    }
    return true;
}

int GGraph::CC()
{
    int ans = 0;
    int maxSize = 0;
    for (auto x : this->edges) {
        maxSize = std::max(maxSize, std::max(x->from, x->to));
    }
    std::vector<std::vector<int>> res;

    std::vector<std::vector<int>> adj(maxSize + 1);
    for (auto it : this->edges) {
        int f = it->from, t = it->to, w = it->weight;
        if (w != 0) {
            adj[f].push_back(t);
            adj[t].push_back(f);
        }
    }
    bool visited[11] = { 0 };
    for (int i = 1; i <= maxSize; i++) {
        std::vector<int> temp;
        if (!visited[i]) {
            ans++;
            dfs(i, visited, adj, temp);
            res.push_back(temp);
        }
    }
    std::vector<sf::Color> colorTable;
    colorTable.push_back(sf::Color::Green);
    colorTable.push_back(NeonPink);
    colorTable.push_back(sf::Color::Red);
    colorTable.push_back(sf::Color::Yellow);
    colorTable.push_back(sf::Color(132, 66, 245));
    colorTable.push_back(sf::Color(245, 117, 66));
    colorTable.push_back(sf::Color(188, 245, 66));
    colorTable.push_back(sf::Color(176, 66, 245));
    colorTable.push_back(sf::Color(245, 66, 182));
    colorTable.push_back(sf::Color(245, 66, 75));
    int k = 0;
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            this->nodes[res[i][j]]->setFillColor(colorTable[k], DarkBlue);
            for (auto it : EdgesList) {
                if (it.first.first == res[i][j] || it.first.second == res[i][j]) {
                    it.second->setFillColor(colorTable[k]);
                }
            }
        }
        k++;
    }
    return ans;
}

void GGraph::update()
{
    setEdges(this->edges);
    this->EdgesList.clear();
    this->WeightList.clear();
    for (auto i = edges.begin(); i != edges.end(); i++) {
        if ((*i)->weight != 0) {
            int from = (*i)->from, to = (*i)->to;
            sf::RectangleShape* x = new sf::RectangleShape();
            *x = this->getEdgeLine(this->nodes[from]->getVertexPosition(), this->nodes[to]->getVertexPosition());
            this->EdgesList.insert({ { from,to }, x });
            sf::Text* y = new sf::Text();
            y->setString(std::to_string((*i)->weight));
            sf::Vector2f temp = this->nodes[from]->getVertexPosition() + this->nodes[to]->getVertexPosition();
            y->setPosition({ round(temp.x / 2), round(temp.y / 2) });
            y->setFont(*font);
            y->setCharacterSize(round(radius * 2 / 3));
            y->setFillColor(textColor);
            WeightList.insert({ { from,to }, y });
        }
    }
}

void GGraph::render(sf::RenderTarget& target)
{
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        it->second->render(target);
    }
    for (auto it = EdgesList.begin(); it != EdgesList.end(); it++) {
        target.draw(*it->second);
    }
    for (auto it = WeightList.begin(); it != WeightList.end(); it++) {
        target.draw(*it->second);
    }
}

GEdge::GEdge(int from, int to, int weight) {
    this->from = from;
    this->to = to;
    this->weight = weight;
}
