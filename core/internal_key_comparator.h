//
// Created by Samarth Mahendra on 2/13/26.
//

#ifndef INTERNAL_KEY_COMPARATOR_H
#define INTERNAL_KEY_COMPARATOR_H

#pragma once
#include "internal_key.h"

struct InternalKeyComparator {
    bool operator()(const InternalKey& a,
                    const InternalKey& b) const {

        // 1. Order by user key (ascending)
        if (a.user_key().bytes() != b.user_key().bytes()) {
            return a.user_key().bytes() < b.user_key().bytes();
        }

        // 2. For same user key, newer versions first
        if (a.sequence() != b.sequence()) {
            return a.sequence() > b.sequence(); // DESC
        }

        // 3. Optional: DELETE before PUT for same seq
        return a.type() > b.type();
    }
};


#endif //INTERNAL_KEY_COMPARATOR_H
