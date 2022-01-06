#pragma once
Hierarchy::Hierarchy(Hierarchy&& r) noexcept{
    this->root = new Node("Uspeshnia");
    this->size = 1;
    this->name = r.name;
    eval(r.print());
}
Hierarchy::Hierarchy(const Hierarchy& r){
    this->root = new Node("Uspeshnia");
    this->size = 1;
    this->name = r.name;
    eval(r.print());
}
Hierarchy::Hierarchy(const string& data){
    if(data != "") {
        this->size = 1;
        this->root = new Node("Uspeshnia");
        this->name = "";
        eval(data);
    }
    else{
        this->size = 0;
        this->root = nullptr;
        this->name = "";
    }
}

Hierarchy::Hierarchy() {
    this->root = new Node("Uspeshnia");
    this->size = 1;
    this->name = "";
}

void Hierarchy::eval(string toEval){
    if(toEval == "") return;
    int countLettersToRemove = 0;
    int i=0;

    //<---------find and copy boss-------------->
    while(toEval[i] && (toEval[i]==' ' || toEval[i] == '-' || toEval[i]=='\n')){
        i++;
    }
    countLettersToRemove = i;
    while(toEval[i] && toEval[i] != ' ' && toEval[i] != '-' && toEval[i]!= '\n'){
        i++;
    }
    std::string boss = "";
    for(int j=countLettersToRemove; j<i; j++){
        boss += toEval[j];
    }
    //<---------find and copy boss-------------->

    int countMinus = 0;
    while(toEval[i] && (toEval[i]==' ' || toEval[i] == '-' || toEval[i]=='\n')){
        if(toEval[i] == '-'){
            countMinus++;
        }
        i++;
    }
    if(countMinus == 0) {
        throw std::runtime_error("Wrong Format");
    }

    //<---------find and copy employee-------------->
    countLettersToRemove = i;
    while(toEval[i] && toEval[i] != ' ' && toEval[i] != '-' && toEval[i]!= '\n'){
        i++;
    }
    std::string employee = "";
    for(int j=countLettersToRemove; j<i; j++){
        employee += toEval[j];
    }
    //<---------find and copy employee-------------->


    while(toEval[i] && (toEval[i]==' ' || toEval[i]=='\n')){
        i++;
    }
    countLettersToRemove = i;


    if(!find(employee) && !find(boss)){
        throw std::runtime_error("The boss doesn't exist in the current hierarchy!");
    }
    hire(employee, boss);

    toEval = toEval.substr(i, toEval.length());
    if(!toEval.empty()){
        eval(toEval);
    }
}



Hierarchy::~Hierarchy() noexcept{
    delete this->root;
}

string Hierarchy::print()const{
    return Hierarchy::printHelper(root);
}

void swap(Node **xp, Node **yp)
{
    Node* temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void sortStrArr(std::vector<Node*>& arr){
    int min;
    int sz = arr.size();
    for (int i = 0; i < sz-1; ++i)
    {
        min = i;
        for (int j = i+1; j < sz; ++j) {
            int len1 = arr[j]->getData().length();
            int len2 = arr[min]->getData().length();
            int minlen = len1 < len2 ? len1 : len2;
            for(int k=0; k<minlen; k++) {
                if (arr[j]->getData()[k] < arr[min]->getData()[k]) {
                    min = j;
                    break;
                } else if (arr[j]->getData()[k] > arr[min]->getData()[k]) {
                    break;
                }
                if(k == minlen-1 && len1 < len2){
                    min = j;
                }
            }
        }
        swap(&arr[min], &arr[i]);
    }
}




string Hierarchy::printHelper(Node* current) const{
    std::string result = "";
    if(!current){
        return result;
    }

    std::queue<Node*> q;

    Node* child = current->getChild();
    std::vector<Node*> children;
    children.push_back(child);

    while(child->getBrother()){
        child = child->getBrother();
        children.push_back(child);
    }
    sortStrArr(children);
    int sz = children.size();
    for(int i=0; i<sz; ++i){
        result += current->getData() + "-" + children[i]->getData() + "\n";
        q.push(children[i]);
    }
    children.clear();

    while(!q.empty()){
        current = q.front();
        q.pop();
        child = current->getChild();
        while(child){
            children.push_back(child);
            child = child->getBrother();
        }
        sortStrArr(children);
        sz = children.size();
        for(int i=0; i<sz; ++i){
            result += current->getData() + "-" + children[i]->getData() + "\n";
            q.push(children[i]);
        }
        children.clear();
    }
    return result;
}


int Hierarchy::longest_chain() const{
    int mD = 0;
    return longest_chain_helper(this->root, mD,0);
}

bool Hierarchy::isEmpty() const{
    return size == 0 && root == nullptr;
}


int Hierarchy::longest_chain_helper(Node* current, int& maxDepth, int currDepth) const{
    if(this->isEmpty()) return 0;
    if(!current){
        return maxDepth;
    }
    if(currDepth == 0){
        currDepth = 1;
    }
    if(maxDepth < currDepth){
        maxDepth = currDepth;
    }
    while(current){
        if(current->getChild()) {
            longest_chain_helper(current->getChild(), maxDepth, currDepth+1);
        }
        current = current->getBrother();
    }
    return maxDepth;
}


bool Hierarchy::find(const string& name) const{
    return find(name, this->root) != nullptr;
}

Node* Hierarchy::find(const string& name, Node* current) const{
    if(!current){
        return nullptr;
    }
    while(current){
        if(current->getData() == name){
            return current;
        }
        if(current->getChild()) {
            if(Node* res = find(name, current->getChild())){
                return res;
            }
        }
        current = current->getBrother();
    }
    return nullptr;
}


int Hierarchy::num_employees() const{
    return size;
}
int Hierarchy::num_overloaded(int level) const{
    return num_overloaded_helper(this->root, level);
}

int Hierarchy::num_overloaded_helper(Node* current, int level) const{
    int overloaded = 0;
    int zero = 0;
    while(current) {
        if (num_subordinates_helper(current->getChild(), zero) >= level) {
            overloaded++;
        }
        zero = 0;
        if(current->getChild()){
            overloaded += num_overloaded_helper(current->getChild(), level);
        }
        current = current->getBrother();
    }
    return overloaded;
}

string Hierarchy::manager(const string& name) const{
    Node* current = find(name,root);
    if(current){
        Node* hisParent = current->getParent();
        if(hisParent){
            return hisParent->getData();
        }
    }
    return "";
}

int Hierarchy::num_subordinates(const string& name) const{
    Node* current = find(name, root);
    if(!current){
        return -1;
    }
    if(current && current->getChild()) {
        return num_subordinates_close(current->getChild());
    }
    return 0;
}

int Hierarchy::num_subordinates_helper(Node* current, int& count) const{
    if(!current){
        return 0;
    }

    while(current){
        count++;
        if(current->getChild()){
            num_subordinates_helper(current->getChild(), count);
        }
        current = current->getBrother();
    }
    return count;
}

int Hierarchy::num_subordinates_close(Node* current) const{
    int count = 0;
    if(!current){
        return count;
    }
    count++;
    while(current && current->getBrother()){
        current = current->getBrother();
        count++;
    }
    return count;
}


unsigned long Hierarchy::getSalary(const string& who) const{
    Node* current = find(who,root);
    if(!current){
        return -1;
    }
    int zero = 0;
    int sum = 450* num_subordinates(who);
    sum += 50 * num_subordinates_helper(current->getChild(), zero);
    return sum;
}
unsigned long Hierarchy::getSalary(Node* who) const{
    if(!who){
        return -1;
    }
    int zero = 0;
    int sum = 450* num_subordinates_close(who->getChild());
    zero = 0;
    sum += 50 * num_subordinates_helper(who->getChild(), zero);
    return sum;
}


bool Hierarchy::isLeaf(Node* curr){
    return curr->getChild() == nullptr;
}
bool Hierarchy::hasNoBrothers(Node* curr){
    return curr->getBrother() == nullptr && curr->getParent()->getChild() == curr;
}



bool Hierarchy::fire(const string& who){
    Node* toDelete = find(who,root);
    if(!toDelete) return false;


    //Case 0: is Uspeshnia
    if(!toDelete->getParent()){
        return false;
    }

    //Case 1 : is Leaf, has no brothers
    if(isLeaf(toDelete) && hasNoBrothers(toDelete)){
        toDelete->getParent()->setChild(nullptr);
        delete toDelete;
        size--;
        return true;
    }

    //case 2: is Leaf, has brothers
    else if(isLeaf(toDelete)){
        Node* prevBrother = toDelete->getParent()->getChild();
        while(prevBrother->getBrother() && prevBrother->getBrother() != toDelete){
            prevBrother = prevBrother->getBrother();
        }
        if(prevBrother == toDelete){
            toDelete->getParent()->setChild(toDelete->getBrother());
            toDelete->setNextBrother(nullptr);
            toDelete->setChild(nullptr);
            delete toDelete;
            size--;
            return true;
        }
        if(toDelete->getBrother()){
            prevBrother->setNextBrother(toDelete->getBrother());
        }
        else{
            prevBrother->setNextBrother(nullptr);
        }
        toDelete->setNextBrother(nullptr);
        toDelete->setChild(nullptr);
        delete toDelete;
        size--;
        return true;
    }

    //case 3: is not leaf, has brothers
    else{
        if(toDelete == toDelete->getParent()->getChild()) {
            Node* child = toDelete->getChild();
            toDelete->getParent()->setChild(child);
            while (child->getBrother()) {
                child = child->getBrother();
            }
            child->setNextBrother(toDelete->getBrother());
            toDelete->setNextBrother(nullptr);
            if(toDelete->getChild())
                toDelete->setChild(nullptr);
            delete toDelete;
            size--;
            return true;
        }
        Node* child = toDelete->getChild();
        Node* prevBrother = toDelete->getParent()->getChild();
        while(prevBrother->getBrother() != toDelete){
            prevBrother = prevBrother->getBrother();
        }
        prevBrother->setNextBrother(child);
        while (child->getBrother()) {
            child = child->getBrother();
        }
        child->setNextBrother(toDelete->getBrother());
        toDelete->setNextBrother(nullptr);
        if(toDelete->getChild())
            toDelete->setChild(nullptr);
        delete toDelete;
        size--;
        return true;
    }
}




bool Hierarchy::hire(const string& who, const string& boss){
    Node* newEmployee = find(who, root);
    Node* hisBoss = find(boss, root);


    if(!hisBoss) {
        return false;
    }
    if(newEmployee){
        return hire(newEmployee, hisBoss);
    }

    Node* toHire = new Node(who);
    Node* bossChild = hisBoss->getChild();
    if(bossChild) {
        while (bossChild->getBrother()) {
            bossChild = bossChild->getBrother();
        }
        bossChild->setNextBrother(toHire);
    }
    else {
        hisBoss->setChild(toHire);
    }
    toHire->setParent(hisBoss);
    toHire = nullptr;
    delete toHire;
    size++;
    return true;
}


bool Hierarchy::hire(Node* newEmployee, Node* hisBoss){
    if(newEmployee == root){
        return false;
    }

    if(newEmployee && newEmployee->getParent() != hisBoss){
        //case 1: boss has no children, employee has no brothers
        if(hisBoss->getChild() == nullptr && newEmployee->getParent()->getChild() == newEmployee && newEmployee->getBrother() == nullptr){
            hisBoss->setChild(newEmployee);
            newEmployee->getParent()->setChild(nullptr);
            newEmployee->setParent(hisBoss);
            return true;
        }
        //case 2: new boss has no children, employee has brothers left and right
        else if(hisBoss->getChild() == nullptr){
            Node* tmp = new Node(newEmployee->getData());
            tmp->setChild(newEmployee->getChild());
            Node* prevBrotherOfEmployee = newEmployee->getParent()->getChild();
            while(prevBrotherOfEmployee->getBrother() && prevBrotherOfEmployee->getBrother() != newEmployee){
                prevBrotherOfEmployee = prevBrotherOfEmployee->getBrother();
            }
            if(prevBrotherOfEmployee->getBrother() != newEmployee){
                newEmployee->getParent()->setChild(newEmployee->getBrother());
            }
            else{
                prevBrotherOfEmployee->setNextBrother(newEmployee->getBrother());
            }
            tmp->setNextBrother(nullptr);
            hisBoss->setChild(tmp);
            tmp->setParent(hisBoss);
            newEmployee->setChild(nullptr);
            newEmployee->setNextBrother(nullptr);
            delete newEmployee;
            return true;
        }

        //case 2.5: boss has children, employee has no brothers
        else if(hasNoBrothers(newEmployee)){
            Node* firstChildOfBoss = hisBoss->getChild();
            while(firstChildOfBoss->getBrother()){
                firstChildOfBoss = firstChildOfBoss->getBrother();
            }
            firstChildOfBoss->setNextBrother(newEmployee);
            newEmployee->getParent()->setChild(nullptr);
            newEmployee->setParent(hisBoss);
        }

        //case 3: boss has children, employee has brothers
        else{
            Node* tmp = new Node(newEmployee->getData());
            tmp->setChild(newEmployee->getChild());

            Node* prevBrotherOfEmployee = newEmployee->getParent()->getChild();
            while(prevBrotherOfEmployee->getBrother() && prevBrotherOfEmployee->getBrother() != newEmployee){
                prevBrotherOfEmployee = prevBrotherOfEmployee->getBrother();
            }

            if(prevBrotherOfEmployee->getBrother() != newEmployee){
                newEmployee->getParent()->setChild(newEmployee->getBrother());
            }
            else{
                prevBrotherOfEmployee->setNextBrother(newEmployee->getBrother());
            }
            Node* firstChildOfNewParent = hisBoss->getChild();
            while(firstChildOfNewParent->getBrother()){
                firstChildOfNewParent = firstChildOfNewParent->getBrother();
            }
            firstChildOfNewParent->setNextBrother(tmp);
            tmp->setNextBrother(nullptr);
            tmp->setParent(hisBoss);
            newEmployee->setChild(nullptr);
            newEmployee->setNextBrother(nullptr);
            delete newEmployee;
            return true;
        }
    }
    else if(newEmployee && newEmployee->getParent() == hisBoss){
        return true;
    }
    return false;
}

int Hierarchy::getDepth(Node *who) {
    int result = 0;
    while(who->getParent()){
        who = who->getParent();
        result += 1;
    }
    return result;
}



void Hierarchy::incorporate() {

    std::stack<Node*> BFS_STACK;
    std::queue<Node*> BFS_QUEUE;
    Node* current;

    BFS_QUEUE.push(this->root);

    while(!BFS_QUEUE.empty()){
        current = BFS_QUEUE.front();
        BFS_QUEUE.pop();
        BFS_STACK.push(current);

        while(current){
            if(current->getChild())
                BFS_QUEUE.push(current->getChild());
            current = current->getBrother();
        }
    }

    Node* maxSalary;
    Node* brother;
    std::vector<Node*> brothers;
    while(!BFS_STACK.empty()){
        current = BFS_STACK.top();
        BFS_STACK.pop();

        brother = current;
        if(!brother || !brother->getBrother()) continue;

        while(brother){
            brothers.push_back(brother);
            brother = brother->getBrother();
        }
        sortStrArr(brothers);

        int sz = brothers.size();
        maxSalary = brothers[0];
        for(int i=1; i<sz; ++i){
            if(getSalary(maxSalary) < getSalary(brothers[i])){
                maxSalary = brothers[i];
            }
        }

        for(int i=0; i<sz; ++i){
            if(brothers[i] == maxSalary){
                continue;
            }
            else {
                hire(brothers[i]->getData(), maxSalary->getData());
            }
        }
        brothers.clear();
    }

}

void Hierarchy::modernize(){
    std::stack<Node*> BFS_STACK;
    std::queue<Node*> BFS_QUEUE;
    Node* current;

    BFS_QUEUE.push(this->root);
    while(!BFS_QUEUE.empty()){
        current = BFS_QUEUE.front();
        BFS_QUEUE.pop();
        BFS_STACK.push(current);
        current = current->getChild();
        while(current){
            BFS_QUEUE.push(current);
            current = current->getBrother();
        }
    }

    while(!BFS_STACK.empty()){
        current = BFS_STACK.top();
        BFS_STACK.pop();
        if(getDepth(current) % 2 == 1){
            if(!current->getChild()) continue;

            Node* firstOfChildren = current->getChild();
            Node* lastOfBrothers = current->getParent()->getChild();
            while(lastOfBrothers->getBrother()){
                lastOfBrothers = lastOfBrothers->getBrother();
            }
            lastOfBrothers->setNextBrother(firstOfChildren);
            Node* parent = current->getParent();
            while(firstOfChildren){
                firstOfChildren->setParent(parent);
                firstOfChildren = firstOfChildren->getBrother();
            }
            Node* beforeCurrent = parent->getChild();
            if(beforeCurrent == current){
                parent->setChild(beforeCurrent->getBrother());
                beforeCurrent->setNextBrother(nullptr);
                beforeCurrent->setChild(nullptr);
                delete beforeCurrent;
                size--;
                continue;
            }
            while(beforeCurrent->getBrother() && beforeCurrent->getBrother() != current){
                beforeCurrent = beforeCurrent->getBrother();
            }
            beforeCurrent->setNextBrother(current->getBrother());
            current->setNextBrother(nullptr);
            current->setChild(nullptr);
            delete current;
            size--;
            continue;
        }
    }
}

Hierarchy Hierarchy::join(const Hierarchy& right) const{
    if(this->root->getData() != right.root->getData()){
        throw std::runtime_error("One of the hierarchies has boss other than Uspeshnia");
    }
    if(this == &right){
        Hierarchy result(*this);
        return result;
    }

    Hierarchy result;
    //BFS of both trees simultaniously to create result
    std::queue<Node*> BFS_Q;

    Node* childL = this->root->getChild();
    Node* childR = right.root->getChild();
    if(childL)
        BFS_Q.push(childL);
    if(childR)
        BFS_Q.push(childR);

    while(!BFS_Q.empty()){
        Node* current = BFS_Q.front();
        BFS_Q.pop();
        while(current){
            if(!result.find(current->getData())){
                result.hire(current->getData(), current->getParent()->getData());
            }
            if (current->getChild()) {
                BFS_Q.push(current->getChild());
            }
            current = current->getBrother();
        }
    }
    return result;
}

void Hierarchy::setName(string nName) {
    this->name = nName;
}
string Hierarchy::getName(){
    return this->name;
}