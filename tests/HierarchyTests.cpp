#pragma once

#include "../Catch2/catch_amalgamated.cpp"
#include "../implementation/implementation.h"

//the most basic cases are already working because of the tests.cpp


const string alphabet =
        "Uspeshnia - a \n"
        "Uspeshnia - b \n"
        "Uspeshnia - c \n"
        "a - d \n"
        "a - e \n"
        "a - f \n"
        "b - g \n"
        "b - h \n"
        "c - i \n"
        "c - j \n"
        "c - k \n"
        "d - l \n"
        "e - m \n"
        "e - n \n"
        "f - o \n"
        "h - p \n"
        "j - q \n"
        "j - r \n"
        "j - s \n"
        "k - t \n"
        "n - u \n"
        "n - v \n"
        "q - w \n"
        "t - x \n"
        "t - y \n"
        "w - z \n";

const string numbers =
        "Uspeshnia - 1 \n"
        "Uspeshnia - 2 \n"
        "Uspeshnia - 3 \n"
        "Uspeshnia - 4 \n"
        "1 - 11 \n"
        "1 - 12 \n"
        "1 - 13 \n"
        "1 - 14 \n"
        "2 - 21 \n"
        "2 - 22 \n"
        "3 - 31 \n"
        "3 - 32 \n"
        "3 - 33 \n"
        "4 - 41 \n"
        "4 - 42 \n"
        "4 - 43 \n"
        "4 - 44 \n"
        "12 - 121 \n"
        "22 - 221 \n"
        "22 - 222 \n"
        "42 - 421 \n"
        "44 - 441 \n"
        "44 - 442 \n"
        "44 - 443 \n"
        "44 - 444 \n"
        "121 - 1211 \n"
        "221 - 2211 \n"
        "222 - 2221 \n"
        "222 - 2222 \n"
        "444 - 4441 \n"
        "444 - 4442 \n"
        "444 - 4443 \n"
        "444 - 4444 \n"
        "1211 - 12111 \n"
        "1211 - 12112 \n"
        "1211 - 12113 \n"
        "2222 - 22221 \n"
        "2222 - 22222 \n"
        "4444 - 44441 \n"
        "22222 - 222221 \n"
        "22222 - 222222 \n"
        "222222 - 2222221 \n";




TEST_CASE("hire and fire multiple people"){
    Hierarchy test;
    test.hire("a", "Uspeshnia");
    test.hire("b", "Uspeshnia");
    test.hire("c", "Uspeshnia");
    test.hire("d", "Uspeshnia");
    test.hire("e", "Uspeshnia");
    REQUIRE(test.num_employees() == 6);
    REQUIRE(test.num_subordinates("Uspeshnia") == 5);
    REQUIRE(test.find("a"));
    REQUIRE(test.find("e"));
    test.fire("c");
    REQUIRE(!test.find("c"));
    test.fire("d");
    test.fire("b");
    REQUIRE(test.num_subordinates("Uspeshnia") == 2);
    REQUIRE(test.num_employees() == 3);

    test.hire("b","a");
    test.hire("e","b");
    test.hire("c","b");
    REQUIRE(test.num_employees() == 5);
    REQUIRE(test.num_subordinates("a") == 1);
    REQUIRE(test.num_subordinates("b") == 2);
    REQUIRE(test.getSalary("a") == 600);
    REQUIRE(test.getSalary("b") > test.getSalary("a"));
}

TEST_CASE("longest chain"){
    Hierarchy h(alphabet);
    REQUIRE(h.longest_chain() == 6);
    Hierarchy g(numbers);
    REQUIRE(g.longest_chain() == 8);
}

TEST_CASE("eval"){
    Hierarchy h;
    h.eval("Uspeshnia - 1");
    h.eval("                Uspeshnia                   -                     2");
    h.eval("Uspeshnia - 3 Uspeshnia - 4 1-2");
    h.eval("1 - 11\n1-12\n1-13 1-14");
    REQUIRE(h.num_employees() == 9);
    REQUIRE(h.longest_chain() == 3);
    REQUIRE(h.getSalary("Uspeshnia") == 1750);
    REQUIRE(h.getSalary("1") == 2500);
    REQUIRE(h.print() == "Uspeshnia-1\nUspeshnia-3\nUspeshnia-4\n1-11\n1-12\n1-13\n1-14\n1-2\n");
}

TEST_CASE("almost all possible functions over the two custom hierarchies"){
    Hierarchy h(alphabet);
    Hierarchy g(numbers);
    Hierarchy k = h.join(g);
    REQUIRE(h.print() == "Uspeshnia-a\n"
                         "Uspeshnia-b\n"
                         "Uspeshnia-c\n"
                         "a-d\n"
                         "a-e\n"
                         "a-f\n"
                         "b-g\n"
                         "b-h\n"
                         "c-i\n"
                         "c-j\n"
                         "c-k\n"
                         "d-l\n"
                         "e-m\n"
                         "e-n\n"
                         "f-o\n"
                         "h-p\n"
                         "j-q\n"
                         "j-r\n"
                         "j-s\n"
                         "k-t\n"
                         "n-u\n"
                         "n-v\n"
                         "q-w\n"
                         "t-x\n"
                         "t-y\n"
                         "w-z\n");
    REQUIRE(g.print() == "Uspeshnia-1\n"
                         "Uspeshnia-2\n"
                         "Uspeshnia-3\n"
                         "Uspeshnia-4\n"
                         "1-11\n"
                         "1-12\n"
                         "1-13\n"
                         "1-14\n"
                         "2-21\n"
                         "2-22\n"
                         "3-31\n"
                         "3-32\n"
                         "3-33\n"
                         "4-41\n"
                         "4-42\n"
                         "4-43\n"
                         "4-44\n"
                         "12-121\n"
                         "22-221\n"
                         "22-222\n"
                         "42-421\n"
                         "44-441\n"
                         "44-442\n"
                         "44-443\n"
                         "44-444\n"
                         "121-1211\n"
                         "221-2211\n"
                         "222-2221\n"
                         "222-2222\n"
                         "444-4441\n"
                         "444-4442\n"
                         "444-4443\n"
                         "444-4444\n"
                         "1211-12111\n"
                         "1211-12112\n"
                         "1211-12113\n"
                         "2222-22221\n"
                         "2222-22222\n"
                         "4444-44441\n"
                         "22222-222221\n"
                         "22222-222222\n"
                         "222222-2222221\n");

    REQUIRE(h.longest_chain() == 6);
    REQUIRE(h.num_employees() == 27);
    REQUIRE(h.num_subordinates("Uspeshnia") == 3);
    REQUIRE(h.manager("c") == "Uspeshnia");
    REQUIRE(!h.find("1"));
    REQUIRE(!h.fire("1"));
    REQUIRE(!h.fire("Uspeshnia"));
    REQUIRE(h.getSalary("Uspeshnia") == 2650);
    REQUIRE(h.getSalary("1") == -1);
    REQUIRE(h.getSalary("b") == 1050);
    REQUIRE(h.getSalary("m") == 0);
    REQUIRE(h.num_overloaded() == 1);

    h.incorporate();
    REQUIRE(h.print() ==
            "Uspeshnia-c\n"
            "c-a\n"
            "c-b\n"
            "c-j\n"
            "a-e\n"
            "b-h\n"
            "j-i\n"
            "j-k\n"
            "j-q\n"
            "e-d\n"
            "e-f\n"
            "e-n\n"
            "h-g\n"
            "h-p\n"
            "k-t\n"
            "q-r\n"
            "q-s\n"
            "q-w\n"
            "d-l\n"
            "f-o\n"
            "n-m\n"
            "n-u\n"
            "t-x\n"
            "w-z\n"
            "u-v\n"
            "x-y\n");
    REQUIRE(h.longest_chain() == 7);
    REQUIRE(h.num_employees() == 27);
    REQUIRE(h.num_subordinates("Uspeshnia") == 1);
    REQUIRE(h.manager("a") == "c");
    REQUIRE(h.manager("2") == "");
    REQUIRE(h.num_subordinates("c") == 3);
    REQUIRE(h.num_subordinates("j") == 3);
    REQUIRE(h.num_subordinates("1") == -1);




    REQUIRE(g.longest_chain() == 8);
    REQUIRE(g.num_employees() == 43);
    REQUIRE(g.num_subordinates("Uspeshnia") == 4);
    REQUIRE(g.manager("c") == "");
    REQUIRE(g.manager("3") == "Uspeshnia");
    REQUIRE(g.find("1"));
    REQUIRE(!g.find("a"));
    REQUIRE(!g.fire("a"));
    REQUIRE(!g.fire("Uspeshnia"));
    REQUIRE(g.getSalary("Uspeshnia") == 3900);
    REQUIRE(g.getSalary("a") == -1);
    REQUIRE(g.getSalary("44") == 2250);
    REQUIRE(g.getSalary("222") == 1250);
    REQUIRE(g.num_overloaded() == 1);

    g.incorporate();
    REQUIRE(g.print() ==
            "Uspeshnia-4\n"
            "4-1\n"
            "4-2\n"
            "4-3\n"
            "4-44\n"
            "1-12\n"
            "2-22\n"
            "3-31\n"
            "44-41\n"
            "44-42\n"
            "44-43\n"
            "44-444\n"
            "12-11\n"
            "12-121\n"
            "12-13\n"
            "12-14\n"
            "22-21\n"
            "22-222\n"
            "31-32\n"
            "31-33\n"
            "42-421\n"
            "444-441\n"
            "444-442\n"
            "444-443\n"
            "444-4444\n"
            "121-1211\n"
            "222-221\n"
            "222-2222\n"
            "4444-4441\n"
            "4444-4442\n"
            "4444-4443\n"
            "4444-44441\n"
            "1211-12111\n"
            "221-2211\n"
            "2222-2221\n"
            "2222-22222\n"
            "12111-12112\n"
            "12111-12113\n"
            "22222-22221\n"
            "22222-222222\n"
            "222222-222221\n"
            "222222-2222221\n");
    REQUIRE(g.longest_chain() == 9);
    REQUIRE(g.num_employees() == 43);
    REQUIRE(g.num_subordinates("Uspeshnia") == 1);
    REQUIRE(g.manager("a") == "");
    REQUIRE(g.manager("2") == "4");
    REQUIRE(g.num_subordinates("2") == 1);
    REQUIRE(g.num_subordinates("44") == 4);
    REQUIRE(g.num_subordinates("112") == -1);


    REQUIRE(k.print() == "Uspeshnia-1\n"
                         "Uspeshnia-2\n"
                         "Uspeshnia-3\n"
                         "Uspeshnia-4\n"
                         "Uspeshnia-a\n"
                         "Uspeshnia-b\n"
                         "Uspeshnia-c\n"
                         "1-11\n"
                         "1-12\n"
                         "1-13\n"
                         "1-14\n"
                         "2-21\n"
                         "2-22\n"
                         "3-31\n"
                         "3-32\n"
                         "3-33\n"
                         "4-41\n"
                         "4-42\n"
                         "4-43\n"
                         "4-44\n"
                         "a-d\n"
                         "a-e\n"
                         "a-f\n"
                         "b-g\n"
                         "b-h\n"
                         "c-i\n"
                         "c-j\n"
                         "c-k\n"
                         "12-121\n"
                         "22-221\n"
                         "22-222\n"
                         "42-421\n"
                         "44-441\n"
                         "44-442\n"
                         "44-443\n"
                         "44-444\n"
                         "d-l\n"
                         "e-m\n"
                         "e-n\n"
                         "f-o\n"
                         "h-p\n"
                         "j-q\n"
                         "j-r\n"
                         "j-s\n"
                         "k-t\n"
                         "121-1211\n"
                         "221-2211\n"
                         "222-2221\n"
                         "222-2222\n"
                         "444-4441\n"
                         "444-4442\n"
                         "444-4443\n"
                         "444-4444\n"
                         "n-u\n"
                         "n-v\n"
                         "q-w\n"
                         "t-x\n"
                         "t-y\n"
                         "1211-12111\n"
                         "1211-12112\n"
                         "1211-12113\n"
                         "2222-22221\n"
                         "2222-22222\n"
                         "4444-44441\n"
                         "w-z\n"
                         "22222-222221\n"
                         "22222-222222\n"
                         "222222-2222221\n");
    REQUIRE(k.longest_chain() == 8);
    REQUIRE(k.num_employees() == 69);
    REQUIRE(k.num_subordinates("Uspeshnia") == 7);
    REQUIRE(k.manager("4") == "Uspeshnia");
    REQUIRE(!k.find("112"));
    REQUIRE(k.getSalary("Uspeshnia") == 6550);
    REQUIRE(k.getSalary("a") == 1800);
    REQUIRE(k.getSalary("44") == 2250);
    REQUIRE(k.getSalary("222") == 1250);
    REQUIRE(k.num_overloaded() == 1);

    Hierarchy l(k.join(k));
    REQUIRE(k.longest_chain() == l.longest_chain());
    REQUIRE(k.num_employees() == l.num_employees());
    REQUIRE(k.num_subordinates("Uspeshnia") == l.num_subordinates("Uspeshnia"));
    REQUIRE(k.manager("4") == l.manager("4"));
    REQUIRE(!l.find("112"));
    REQUIRE(k.getSalary("Uspeshnia") == l.getSalary("Uspeshnia"));
    REQUIRE(k.getSalary("a") == l.getSalary("a"));
    REQUIRE(k.getSalary("44") == l.getSalary("44"));
    REQUIRE(k.getSalary("222") == l.getSalary("222"));
    REQUIRE(k.num_overloaded() == l.num_overloaded());
}
