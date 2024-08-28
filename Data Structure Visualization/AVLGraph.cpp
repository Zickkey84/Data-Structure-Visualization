#include "AVLGraph.h"

AVLTreeNode::AVLTreeNode(int value, sf::Vector2f position, float radius, int thickness, sf::Color fillColor, sf::Color textColor, sf::Font* font) : value(value) {
    count = 1;
    height = 1;
    left = nullptr;
    right = nullptr;
    vertex = new TreeNode(position, radius, thickness, fillColor, textColor, value, font);
}

void AVLTreeNode::updateValues() {
    count = (left != nullptr ? left->count : 0) + (right != nullptr ? right->count : 0) + 1;

    height = std::max(left != nullptr ? left->height : 0,
        right != nullptr ? right->height : 0) + 1;
}

int AVLTreeNode::balanceFactor() {
    return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
}


AVLTreeNode* AVLTreeNode::left_rotate() {
    AVLTreeNode* R = right;
    right = right->left;
    R->left = this;

    this->updateValues(); 
    R->updateValues();

    return R;
}


AVLTreeNode* AVLTreeNode::right_rotate() {
    AVLTreeNode* L = left;
    left = left->right;
    L->right = this;

    this->updateValues(); 
    L->updateValues();

    return L;
}



AVLGraph::AVLGraph(sf::Vector2f startPosition, float radius, int thickness, colorTheme theme, sf::Font* font)
{
    this->startposition = startPosition;
    this->radius = radius;
    this->thickness = thickness;
    this->fillColor = HASH::color[theme][HASH::Normal].fillColor;
    this->textColor = HASH::color[theme][HASH::Normal].outlineColor;
    this->font = font;
    this->_size = 0;
    this->root = NULL;
}

AVLGraph::~AVLGraph()
{
    clear();
}

void AVLGraph::insert(int value)
{
    AVLTreeNode** indirect = &root;  
    std::vector<AVLTreeNode**> path; 

    while (*indirect != nullptr) {
        path.push_back(indirect);

        if ((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }

    *indirect = new AVLTreeNode(value, startposition, radius, thickness, fillColor, textColor, font);
    path.push_back(indirect);
    balance(path);
    _size++;
}

bool AVLGraph::Delete(int value)
{
    AVLTreeNode** indirect = &root; 
    std::vector<AVLTreeNode**> path;  

    while (*indirect != nullptr and (*indirect)->value != value) {
        path.push_back(indirect);
        if ((*indirect)->value > value) indirect = &((*indirect)->left);
        else indirect = &((*indirect)->right);
    }

    if (*indirect == nullptr) return false; 
    else path.push_back(indirect);

    std::size_t index = path.size();

    if ((*indirect)->left == nullptr and (*indirect)->right == nullptr) {
        delete* indirect;
        *indirect = nullptr;
        path.pop_back();
    }
    else if ((*indirect)->right == nullptr) {
        AVLTreeNode* toRemove = *indirect;
        (*indirect) = (*indirect)->left;
        delete toRemove;
        path.pop_back();
    }
    else { 
        AVLTreeNode** successor = &((*indirect)->right);
        while ((*successor)->left != nullptr) {
            path.push_back(successor);
            successor = &((*successor)->left);
        }
        if (*successor == (*indirect)->right) {
            (*successor)->left = (*indirect)->left;
            AVLTreeNode* toRemove = *indirect;
            *indirect = *successor;
            delete toRemove;
        }
        else {
            AVLTreeNode* tmp = *path.back(), * suc = *successor;
            tmp->left = (*successor)->right;
            suc->left = (*indirect)->left;
            suc->right = (*indirect)->right;
            delete* indirect;
            *indirect = suc;
            path[index] = &(suc->right);
        }
    }
    return true;
    balance(path);
    _size--;
}

void AVLGraph::clear()
{
    this->Edgeslist.clear();
    std::vector<AVLTreeNode*> stack;

    if (root != nullptr)
        stack.push_back(root);

    while (!stack.empty()) {
        AVLTreeNode* node = stack.back();
        stack.pop_back();

        if (node->left != nullptr)
            stack.push_back(node->left);

        if (node->right != nullptr)
            stack.push_back(node->right);

        _size--;
        delete node->vertex;
        delete node;
    }
    root = nullptr;
}

bool AVLGraph::empty() const
{
    return _size == 0;
}

int AVLGraph::size() const
{
    return _size;
}

void AVLGraph::balance(std::vector<AVLTreeNode**> path)
{
    std::reverse(path.begin(), path.end());

    for (auto indirect : path) {
        (*indirect)->updateValues();

        if ((*indirect)->balanceFactor() >= 2 and (*indirect)->left->balanceFactor() >= 0)   // left - left
            *indirect = (*indirect)->right_rotate();

        else if ((*indirect)->balanceFactor() >= 2) { 
            (*indirect)->left = (*indirect)->left->left_rotate();
            *indirect = (*indirect)->right_rotate();
        }

        else if ((*indirect)->balanceFactor() <= -2 and (*indirect)->right->balanceFactor() <= 0)  // right - right
            *indirect = (*indirect)->left_rotate();

        else if ((*indirect)->balanceFactor() <= -2) { 
            (*indirect)->right = ((*indirect)->right)->right_rotate();
            *indirect = (*indirect)->left_rotate();
        }
    }
}

sf::RectangleShape AVLGraph::getEdgeLine(sf::Vector2f startPosition, sf::Vector2f endPosition) {
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

sf::RectangleShape AVLGraph::getEdgeLine2(sf::Vector2f startPosition, sf::Vector2f endPosition) {
    sf::Vector2f diff = endPosition - startPosition;
    float lengthDiff = sqrt(diff.x * diff.x + diff.y * diff.y);
    if (lengthDiff < 2.f * (this->radius + this->thickness)) {
        return sf::RectangleShape();
    }
    sf::RectangleShape line(sf::Vector2f((lengthDiff - 1.65f * (this->radius + (float)this->thickness)), this->thickness));
    line.setOrigin(0, (float)this->thickness / 2.f);
    line.setRotation(atan2(diff.y, diff.x) * 180.f / 3.14159265);
    line.setPosition(startPosition + sf::Vector2f(diff.x / lengthDiff, diff.y / lengthDiff) * (this->radius + (float)this->thickness));
    line.setFillColor(this->textColor);
    return line;
}

void AVLGraph::updatePosition(AVLTreeNode*& root, int level)
{
    if (root == NULL) return;
    root->vertex->setHighlight(this->textColor, this->thickness);
    if (root->left != NULL) {
        if (level < 4) {
            root->left->vertex->setSize(root->vertex->getRadius() / root->left->vertex->getRadius());
            root->left->vertex->setPosition(root->vertex->getPosition() + sf::Vector2f(-200.f / pow(2, level), 100.f));
            this->Edgeslist.push_back(getEdgeLine(root->vertex->getPosition(), root->left->vertex->getPosition()));
        }
        if (level == 4) {
            root->left->vertex->setSize(root->vertex->getRadius() / root->left->vertex->getRadius());
            root->left->vertex->setSize(0.65);
            root->left->vertex->setPosition(root->vertex->getPosition() + sf::Vector2f(-200.f / pow(2, level), 100.f));
            this->Edgeslist.push_back(getEdgeLine2(root->vertex->getPosition(), root->left->vertex->getPosition()));
        }
        updatePosition(root->left, level + 1);
    }
    if (root->right != NULL) {
        if (level < 4) {
            root->right->vertex->setSize(root->vertex->getRadius() / root->right->vertex->getRadius());
            root->right->vertex->setPosition(root->vertex->getPosition() + sf::Vector2f(200.f / pow(2, level), 100.f));
            this->Edgeslist.push_back(getEdgeLine(root->vertex->getPosition(), root->right->vertex->getPosition()));

        }
        if (level == 4) {
            root->right->vertex->setSize(root->vertex->getRadius() / root->right->vertex->getRadius());
            root->right->vertex->setSize(0.65);
            root->right->vertex->setPosition(root->vertex->getPosition() + sf::Vector2f(200.f / pow(2, level), 100.f));
            this->Edgeslist.push_back(getEdgeLine2(root->vertex->getPosition(), root->right->vertex->getPosition()));
        }
        updatePosition(root->right, level + 1);
    }
}

void AVLGraph::update() {
    this->Edgeslist.clear();
    if (root == NULL) return;
    this->root->vertex->setPosition(startposition);
    updatePosition(root, 0);
}

void AVLGraph::render(sf::RenderTarget& target)
{
    for (auto it : Edgeslist) target.draw(it);
    std::vector<AVLTreeNode*> stack;
    if (root != nullptr)
        stack.push_back(root);

    while (!stack.empty()) {
        AVLTreeNode* node = stack.back();
        stack.pop_back();

        if (node->left != nullptr)
            stack.push_back(node->left);

        if (node->right != nullptr)
            stack.push_back(node->right);

        node->vertex->render(target);
    }
}

