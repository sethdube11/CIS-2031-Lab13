#include <iostream>
#include <string>
#include "catch_amalgamated.hpp"
using std::cout;
using std::string;
using std::endl;


struct List {
    string value;
    List* next;
};

//Prints the list to cout
void print( List* l ){
    while ( l != NULL ){
        //As long as l is not null....
        cout << l->value << endl; //Print out it's value
        l = l->next; //Move on to the next value
    }
}

//Returns the number of items in the list
int length(List* l){
    if ( l == NULL )
        return 0;
    return 1 + length(l->next);
}

//Get the Nth item from the list
string get(List* l, int index){
    if ( l == NULL )
        return "";
    if ( index == 0 )
        return l->value;
    return get(l->next, index-1);
}

//Returns true if the list contains needle
bool contains(List* l, string needle){
    if ( l == NULL )
        return false;
    if ( l->value == needle )
        return true;
    return contains( l->next, needle );
}

//Add an item to the list
void insertAt(List* &list, int pos, string value){
    if ( list == NULL || pos == 0 )
        list = new List{value, list};
    else
        insertAt( list->next, pos-1, value );
}

//Remove an item from the list
void deleteAt(List* &list, int pos){
    if ( list == NULL )
        return; //Nothing to do
    else if ( pos == 0 )
        list = list->next;
    else
        deleteAt( list->next, pos-1 );
}

/////////////////////////////////////////////////////
//
//  EVERYTHING BELOW HERE IS TESTS FOR THE LIST
//  🛑 Don't change it! 🛑
//
string testPrint(List* l){
    if ( l == NULL )
        return "";
    return l->value + testPrint(l->next);
}

TEST_CASE("Testing an empty list") {
    List* theList = NULL;
    SECTION("An empty list has length zero"){
        REQUIRE( length(theList) == 0 );
    }
    SECTION("An empty list does not contain 'A'"){
        REQUIRE( contains(theList, "A") == false );
    }
    SECTION("An empty list is empty"){
        REQUIRE( testPrint(theList) == "" );
    }
}

TEST_CASE("Inserting at position zero") {
    List* theList = NULL;
    insertAt(theList, 0, "C");
    REQUIRE( testPrint(theList) == "C" );
    insertAt(theList, 0, "B");
    REQUIRE( testPrint(theList) == "BC" );
    insertAt(theList, 0, "A");
    REQUIRE( testPrint(theList) == "ABC" );
}

TEST_CASE("Inserting at position one") {
    List* theList = NULL;
    insertAt(theList, 0, "D");
    insertAt(theList, 0, "C");
    insertAt(theList, 0, "A");
    REQUIRE( testPrint(theList) == "ACD" );
    insertAt(theList, 1, "B");
    REQUIRE( testPrint(theList) == "ABCD" );
}

TEST_CASE("Inserting at a position larger than length") {
    List* theList = NULL;
    insertAt(theList, 100, "A");
    REQUIRE( testPrint(theList) == "A" );
    insertAt(theList, 100, "B");
    REQUIRE( testPrint(theList) == "AB" );
    insertAt(theList, 100, "C");
    REQUIRE( testPrint(theList) == "ABC" );
}

TEST_CASE("Deletion Tests") {
    List* theList = NULL;

    REQUIRE( testPrint(theList) == "" );

    SECTION("Deleting item zero from an empty list"){
        deleteAt(theList, 0);
        REQUIRE( testPrint(theList) == "" );
    }

    SECTION("Deleting item one from an empty list"){
        deleteAt(theList, 1);
        REQUIRE( testPrint(theList) == "" );
    }

    insertAt(theList, 100, "A");
    insertAt(theList, 100, "B");
    insertAt(theList, 100, "C");
    insertAt(theList, 100, "D");
    REQUIRE( testPrint(theList) == "ABCD" );

    SECTION("Deleting the zeroth item"){
        deleteAt(theList, 0);
        REQUIRE( testPrint(theList) == "BCD" );
    }

    SECTION("Deleting the first item"){
        deleteAt(theList, 1);
        REQUIRE( testPrint(theList) == "ACD" );
    }

    SECTION("Deleting the last (third) item"){
        deleteAt(theList, 3);
        REQUIRE( testPrint(theList) == "ABC" );
    }

    SECTION("Deleting the nonexistant fourth item"){
        deleteAt(theList, 4);
        REQUIRE( testPrint(theList) == "ABCD" );
    }

    SECTION("Deleting the nonexistant fifth item"){
        deleteAt(theList, 4);
        REQUIRE( testPrint(theList) == "ABCD" );
    }
}

TEST_CASE("Get Tests") {
    List* theList = NULL;
    insertAt(theList, 100, "A");
    insertAt(theList, 100, "B");
    insertAt(theList, 100, "C");

    REQUIRE( get(theList, 0) == "A" );
    REQUIRE( get(theList, 1) == "B" );
    REQUIRE( get(theList, 2) == "C" );
    REQUIRE( get(theList, 3) == "" );

}

TEST_CASE("Contains Tests") {
    List* theList = NULL;
    insertAt(theList, 100, "A");
    insertAt(theList, 100, "B");
    insertAt(theList, 100, "C");
    REQUIRE( testPrint(theList) == "ABC" );

    SECTION("Finds the first Item"){
        REQUIRE( contains(theList, "A") );
    }

    SECTION("Finds the second Item"){
        REQUIRE( contains(theList, "B") );
    }

    SECTION("Finds the last Item"){
        REQUIRE( contains(theList, "C") );
    }

    SECTION("Does not find item that isn't there"){
        REQUIRE( !contains(theList, "D") );
    }
}

TEST_CASE("Length Tests") {
    List* theList = NULL;
    REQUIRE( length(theList) == 0 );
    insertAt(theList, 0, "A");
    REQUIRE( length(theList) == 1 );
    insertAt(theList, 0, "B");
    REQUIRE( length(theList) == 2 );
    insertAt(theList, 0, "C");
    REQUIRE( length(theList) == 3 );
}