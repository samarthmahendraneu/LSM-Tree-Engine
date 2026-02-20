#pragma once

#include <vector>
#include <random>
#include <optional>
#include <cassert>

template <typename Key, typename Comparator>
class SkipList {
private:
    struct Node {
        std::optional<Key> key;     // empty for head sentinel
        std::vector<Node*> next;

        explicit Node(int level) : key(std::nullopt), next(level, nullptr) {}
        Node(const Key& k, int level) : key(k), next(level, nullptr) {}
    };

public:
    explicit SkipList(Comparator cmp, int max_level = 16, double p = 0.5)
        : cmp_(cmp),
          max_level_(max_level),
          prob_(p),
          level_(1),
          head_(new Node(max_level_)) {}   // ✅ sentinel head

    ~SkipList() {
        Node* curr = head_;
        while (curr) {
            Node* next0 = curr->next[0];
            delete curr;
            curr = next0;
        }
    }

    void insert(const Key& key) {
        std::vector<Node*> update(max_level_, nullptr);
        Node* x = head_;

        for (int i = level_ - 1; i >= 0; --i) {
            while (x->next[i] && less(x->next[i], key)) {
                x = x->next[i];
            }
            update[i] = x;
        }

        int new_level = randomLevel();
        if (new_level > level_) {
            for (int i = level_; i < new_level; ++i) update[i] = head_;
            level_ = new_level;
        }

        Node* n = new Node(key, new_level);
        for (int i = 0; i < new_level; ++i) {
            n->next[i] = update[i]->next[i];
            update[i]->next[i] = n;
        }
    }

    Node* lower_bound(const Key& key) const {
        Node* x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (x->next[i] && less(x->next[i], key)) {
                x = x->next[i];
            }
        }
        return x->next[0];
    }

private:
    bool less(const Node* node, const Key& key) const {
        // node is a real node, never head
        assert(node && node->key.has_value());
        return cmp_(node->key.value(), key);
    }

    int randomLevel() {
        static thread_local std::mt19937 gen(std::random_device{}());
        static thread_local std::uniform_real_distribution<> dist(0.0, 1.0);

        int lvl = 1;
        while (dist(gen) < prob_ && lvl < max_level_) ++lvl;
        return lvl;
    }

    Comparator cmp_;
    int max_level_;
    double prob_;
    int level_;
    Node* head_;
};