#pragma once

#include "../Catch2/catch_amalgamated.cpp"
#include "../implementation/Node.h"

TEST_CASE("Ctors and operator="){
    Node a;
    REQUIRE(a.getChild() == nullptr);
    REQUIRE(a.getBrother() == nullptr);
    REQUIRE(a.getParent() == nullptr);
    REQUIRE(a.getData() == "");

    Node b("test");
    REQUIRE(b.getData() == "test");

    Node c = b;
    REQUIRE(c.getData() == "test");
}

TEST_CASE("initialise all private members"){
    Node* a = new Node("test");
    Node* b = new Node("b");
    Node* c = new Node("c");
    Node* d = new Node("d");
    a->setParent(b);
    b->setChild(a);
    a->setChild(c);
    c->setParent(a);
    a->setNextBrother(d);
    d->setParent(b);
    REQUIRE(a->getData() == "test");
    REQUIRE(a->getChild() == c);
    REQUIRE(a->getParent() == b);
    REQUIRE(a->getBrother() == d);
    REQUIRE(b->getChild() == a);
    REQUIRE(b->getParent() == nullptr);
    REQUIRE(b->getBrother() == nullptr);
    REQUIRE(c->getParent() == a);
    REQUIRE(c->getChild() == nullptr);
    REQUIRE(c->getBrother() == nullptr);
    REQUIRE(d->getParent() == b);
    REQUIRE(d->getChild() == nullptr);
    REQUIRE(d->getBrother() == nullptr);
    REQUIRE(d->getData() == "d");
    delete b;
}