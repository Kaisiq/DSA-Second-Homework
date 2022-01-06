#include <iostream>
#include "implementation/implementation.h"

void help(){

    std::cout << "help – извежда списък на поддържаните команди с кратка помощна информация за тях\n";
    std::cout << "load име_на_обект име_на_файл – зарежда данни за йерархия от файл с подаденото име и създава дърво, асоциирано с име_на_обект\n";
    std::cout << "save име_на_обект име_на_файл – записва информацията за йерархията на посочения обект във файл с посоченото име\n";
    std::cout << "find име_на_обект име_на_служител – проверява дали в посочения обект съществува служител с посоченото име\n";
    std::cout << "num_subordinates име_на_обект име_на_служител – извежда броя преки подчинени на дадения служител  в посочения обект\n";
    std::cout << "manager име_на_обект име_на_служител – извежда името на ръководителя на дадения служител  в посочения обект\n";
    std::cout << "num_employees име_на_обект – извежда броя служители в посочения обект\n";
    std::cout << "overloaded име_на_обект – извежда броя служители в посочения обект, за които броят подчинени (преки или не) е по-голям от 20\n";
    std::cout << "join име_на_обект_1 име_на_обект_2 име_на_обект_резултат – обединява двата подадени обекта в нов обект с име име_на_обект_резултат\n";
    std::cout << "fire име_на_обект име_на_служител – премахва служителя от съответния обект\n";
    std::cout << "hire име_на_обект име_на_служител име_на_ръководител – назначава служителя в съответния обект като подчинен на подадения ръководител\n";
    std::cout << "salary име_на_обект име_на_служител – извежда заплатата на служителя\n";
    std::cout << "incorporate име_на_обект – инкорпорира фирмата\n";
    std::cout << "modernize име_на_обект – модернизира фирмата\n";
    std::cout << "exit - прекратява изпълнението на програмата\n";
}

bool find(Hierarchy* h, string person){
    return h->find(person);
}

int main() {
    std::vector<Hierarchy*> AllHierarchies;
    std::cout << "Hello to the Hierarchy programm!\n";
    help();
    string command;
    bool success;
    while(true){
        try {
            success = false;
            std::cin >> command;
            if (command == "exit") {
                AllHierarchies.clear();
                return 0;
            } else if (command == "help") {
                help();
            } else if (command == "load") {
                bool found = 0;
                string nameOfHierarchy;
                string nameOfFile;
                std::cin >> nameOfHierarchy;
                getline(std::cin, nameOfFile);
                if (nameOfFile != "")
                    nameOfFile = nameOfFile.substr(1, nameOfFile.size());
                int sz = AllHierarchies.size();
                int i;
                for (i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    if (nameOfFile.empty()) {
                        string line;
                        Hierarchy *a = new Hierarchy;
                        a->setName(nameOfHierarchy);
                        while (getline(std::cin, line)) {
                            a->eval(line);
                        }
                        a->setName(nameOfHierarchy);
                        AllHierarchies.push_back(a);
                        continue;
                    } else {
                        std::ifstream file;
                        file.open(nameOfFile, std::fstream::in | std::fstream::out);
                        if (file.is_open() && file.good()) {
                            if (file.eof()) {
                                std::cout << "The file is empty.\n";
                            } else {
                                Hierarchy *a = new Hierarchy();
                                string toEval;
                                while (getline(file, toEval)) {
                                    a->eval(toEval);
                                }
                                a->setName(nameOfHierarchy);
                                AllHierarchies.push_back(a);
                                std::cout << nameOfHierarchy << " was loaded successfully!\n";
                            }
                        } else {
                            std::cerr << "Couldn't open file. Cancelling operation\n";
                        }
                        file.close();
                    }
                } else {
                    if (nameOfFile.empty()) {
                        string line;
                        while (getline(std::cin, line)) {
                            if (line != "") {
                                AllHierarchies[i]->eval(line);
                            }
                        }
                        std::cout << nameOfHierarchy << " was loaded successfully!\n";
                        continue;
                    } else {
                        std::ifstream file;
                        file.open(nameOfFile, std::fstream::in | std::fstream::out);
                        if (file.is_open() && file.good()) {
                            if (file.eof()) {
                                std::cout << "The file is empty.\n";
                            } else {
                                string toEval;
                                while (getline(file, toEval)) {
                                    AllHierarchies[i]->eval(toEval);
                                }
                            }
                        } else {
                            std::cerr << "Couldn't open file. Cancelling operation\n";
                        }
                        file.close();
                    }
                }
            } else if (command == "save") {
                bool found = false;
                string nameOfHierarchy;
                string nameOfFile;
                std::cin >> nameOfHierarchy;
                getline(std::cin, nameOfFile);
                if (nameOfFile != "")
                    nameOfFile = nameOfFile.substr(1, nameOfFile.size());
                int sz = AllHierarchies.size();
                int i;
                for (i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        found = true;
                        break;
                    }
                }
                if (found == true) {
                    if (nameOfFile.empty()) {
                        std::cout << AllHierarchies[i]->print();
                    } else {
                        std::ofstream file;
                        file.open(nameOfFile);
                        if (file) {
                            if (file.eof()) {
                                file << AllHierarchies[i]->print();
                                std::cout << "The information was saved on the file.\n";
                            } else {
                                std::cerr << "File is not empty!" << std::endl;
                                std::cout << "Do you want to overwrite it?  ->  Y/N\n";
                                char option;
                                std::cin >> option;
                                option = tolower(option);
                                if (option == 'y') {
                                    file.clear();
                                    file << AllHierarchies[i]->print();
                                    std::cout << "The information was saved on the file.\n";
                                } else {
                                    std::cout << "The operation was cancelled.\n";
                                }
                            }
                        } else {
                            std::cerr << "Couldn't open file. Cancelling operation\n";
                        }
                        file.close();
                    }
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "find") {
                string nameOfHierarchy;
                string nameOfPerson;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                int sz = AllHierarchies.size();
                std::cout << sz;
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        if (find(AllHierarchies[i], nameOfPerson)) {
                            std::cout << nameOfPerson + " exists in hierarchy " + nameOfHierarchy + "\n";
                        } else {
                            std::cout << nameOfPerson + " doesn't exist in " + nameOfHierarchy + "\n";
                        }
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "num_subordinates") {
                string nameOfHierarchy;
                string nameOfPerson;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        std::cout << nameOfPerson << " has " << AllHierarchies[i]->num_subordinates(nameOfPerson) << " subordinates\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "manager") {
                string nameOfHierarchy;
                string nameOfPerson;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        std::cout << nameOfPerson << "'s manager is " << AllHierarchies[i]->manager(nameOfPerson) << "\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "num_employees") {
                string nameOfHierarchy;
                std::cin >> nameOfHierarchy;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        std::cout << "There are " << AllHierarchies[i]->num_employees() << " employees in the Hierarchy" << nameOfHierarchy << "\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "overloaded") {
                string nameOfHierarchy;
                std::cin >> nameOfHierarchy;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        if(AllHierarchies[i]->num_overloaded() == 0)
                            std::cout << "There are no overloaded workers in " << nameOfHierarchy << "\n";
                        else
                            std::cout << "There are " << AllHierarchies[i]->num_overloaded() << " overloaded workers in" << nameOfHierarchy << "\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "join") {
                string h1;
                string h2;
                string resultH;
                std::cin >> h1 >> h2 >> resultH;
                int i1 = -1;
                int i2 = -1;
                int iRes = -1;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == h1) {
                        i1 = i;
                    }
                    if (AllHierarchies[i]->getName() == h2) {
                        i2 = i;
                    }
                    if (AllHierarchies[i]->getName() == resultH) {
                        iRes = i;
                    }
                }
                if (i1 == -1 || i2 == -1) {
                    std::cerr << "One of the given hierarchy names doesn't exist\n";
                    continue;
                }
                if (iRes != -1) {
                    AllHierarchies.erase(AllHierarchies.cbegin() + iRes);
                }
                Hierarchy result = AllHierarchies[i1]->join(*AllHierarchies[i2]);
                result.setName(resultH);
                AllHierarchies.push_back(&result);
                std::cout << "The hierarchies " << h1 << " and " << h2 << " were successfully joined together into " << resultH << "\n";
            } else if (command == "fire") {
                string nameOfHierarchy;
                string nameOfPerson;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        AllHierarchies[i]->fire(nameOfPerson);
                        std::cout << nameOfPerson << " was successfully removed\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "hire") {
                string nameOfHierarchy;
                string nameOfPerson;
                string nameOfBoss;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                std::cin >> nameOfBoss;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        AllHierarchies[i]->hire(nameOfPerson, nameOfBoss);
                        std::cout << nameOfPerson << " was successfully hired under " << nameOfBoss << "\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "salary") {
                string nameOfHierarchy;
                string nameOfPerson;
                std::cin >> nameOfHierarchy;
                std::cin >> nameOfPerson;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        std::cout << "The salary of " << nameOfPerson << " is: " << AllHierarchies[i]->getSalary(nameOfPerson) << "\n";
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "incorporate") {
                string nameOfHierarchy;
                std::cin >> nameOfHierarchy;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        AllHierarchies[i]->incorporate();
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    std::cout << "Successfully incorporated " << nameOfHierarchy << "\n";
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else if (command == "modernize") {
                string nameOfHierarchy;
                std::cin >> nameOfHierarchy;
                int sz = AllHierarchies.size();
                for (int i = 0; i < sz; ++i) {
                    if (AllHierarchies[i]->getName() == nameOfHierarchy) {
                        AllHierarchies[i]->modernize();
                        success = true;
                        break;
                    }
                }
                if (success == true) {
                    std::cout << "Successfully modernized " << nameOfHierarchy << "\n";
                    continue;
                } else {
                    std::cerr << "Couldn't find Hierarchy, stopping operation\n";
                }
            } else {
                std::cerr << "Wrong command. Type \"help\" for help.\n";
            }
        }
        catch(...){
            std::cerr << "Error. Operation was stopped.\n";
            continue;
        }
    }
    return 0;
}
