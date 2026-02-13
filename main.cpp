//
// Created by Samarth Mahendra on 2/13/26.
//


#include "core/Entry.h"
#include "core/key.h"
#include "core/value.h"
#include <iostream>


using namespace std;



int main() {

    Entry x = {
        Key("A"),
        Value("10"),
        1,
        false
    };

    cout<<x<<endl;

}