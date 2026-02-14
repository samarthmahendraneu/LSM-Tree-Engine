//
// Created by Samarth Mahendra on 2/14/26.
//

#ifndef WAL_H
#define WAL_H

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../types/Entry.h"


class Wal {

public:
    explicit Wal(const std::string& path);

    void append(Entry& entry);

    vector<Entry> replay();

private:
    ofstream out_;
    string path_;
};



#endif //WAL_H
