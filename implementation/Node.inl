Node::Node(std::string name, Node* child, Node* nextBrother, Node* parent): data(name), child(child), nextBrother(nextBrother), parent(parent){}

Node::Node(){
    this->data = "";
    this->child = nullptr;
    this->nextBrother = nullptr;
    this->parent = nullptr;
}

Node::~Node(){
    if(this->child)
        delete this->child;
    if(this->nextBrother)
        delete this->nextBrother;
}


Node& Node::operator= (const Node& other){
    if(this != &other){
        this->data = other.data;
        this->nextBrother = other.nextBrother;
        this->child = other.child;
        this->parent = other.parent;
    }
    return *this;
}

Node* Node::getChild(){
    return this->child;
}
Node* Node::getBrother(){
    return this->nextBrother;
}

std::string Node::getData(){
    return this->data;
}

Node* Node::getParent(){
    return this->parent;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

void Node::setNextBrother(Node* next){
    this->nextBrother = next;
}
void Node::setChild(Node* child){
    this->child = child;
}
void Node::setData(std::string data){
    this->data = data;
}
