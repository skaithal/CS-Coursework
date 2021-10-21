/* Credit given to ECS 36C Files Resources,
 * Further implementation completed by ->
 * Name: Sanjana Aithal
 * ID: 917496419 */

#ifndef MULTISET_H_
#define MULTISET_H_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size();
  // Returns true if multiset is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key);
  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key);

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K &key);
  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K &key);

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K &Floor(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K &Ceil(const K &key);

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K &Max();
  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K &Min();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  struct Node {
    K key;                       /* the value of the node */
    size_t count;                /* how many times the node exists */
    std::unique_ptr<Node> left;  /* pointer to the left node */
    std::unique_ptr<Node> right; /* pointer to the right node */
  };

  /* pointer to the root of the binary search treee */
  std::unique_ptr<Node> root;

  /* how many items are in the bst */
  size_t cur_size = 0;

  /* variables used to return in the Ceil() and Floor() methods */
  K ceil;
  K floor;

  // Private methods

  // Finds the appropriate node, returns the node
  Node *Find(Node *n, const K &key);

  // Internal helper method to return the node of the minimum key
  Node *Min(Node *n);

  // Internal helper method for the Insert function
  void Insert(std::unique_ptr<Node> &n, const K &key);

  // Internal helper method for the Remove function
  void Remove(std::unique_ptr<Node> &n, const K &key);
};

/* Your implementation of the class should be located below
 * Note: because the public methods are explained above, I have only explained
 * the steps, and not given a * * summary of the method. */

template <typename K>
typename Multiset<K>::Node *Multiset<K>::Find(Node *n, const K &key) {
  /* while the node is not null: if node is found, return node */
  while (n) {
    if (key == n->key) {
      return n;
    }
    if (key < n->key)
      n = n->left.get();
    else
      n = n->right.get();
  }

  return 0;
}

template <typename K>
size_t Multiset<K>::Size() {
  return cur_size;
}

template <typename K>
bool Multiset<K>::Empty() {
  /* if the bst is empty, return true */
  if (cur_size == 0) return true;
  return false;
}

template <typename K>
void Multiset<K>::Insert(std::unique_ptr<Node> &n, const K &key) {
  /* if pointer is null, the new node will be inserted there */
  if (!n) {
    n = std::unique_ptr<Node>(new Node{key, 1});

    /* increment cur_size to increase size of multiset */
    cur_size++;
  }
  /* if the key = to a key already in the multiset, count++ */
  else if (key == n->key) {
    (n->count)++;

    /* increment cur_size to increase size of multiset */
    cur_size++;
  }
  /* if the key is less than the node's key, recurse left */
  else if (key < n->key) {
    Insert(n->left, key);
  }
  /* if the key is greater than the node's key, recurse right */
  else {
    Insert(n->right, key);
  }
}

template <typename K>
void Multiset<K>::Insert(const K &key) {
  /* call Insert helper method */
  Insert(root, key);
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::Min(Node *n) {
  /* if the left-most node has been obtained (the minimum), return the node */
  if (n->left)
    return Min(n->left.get());
  else
    return n;
}

template <typename K>
void Multiset<K>::Remove(std::unique_ptr<Node> &n, const K &key) {
  /* if the key does not exist, throw exception */
  if (!n) {
    std::__throw_invalid_argument("Invalid key");
    return;
  }

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else { /* Found node */
    /* if the key exists multiple times, simply decrement the internal counter
     */
    if (n->count > 1)
      (n->count)--;
    else if (n->left && n->right) {
      /* Two children: replace with min node in right subtree */
      n->key = Min(n->right.get())->key;
      Remove(n->right, n->key);

    } else {
      /* Replace with only child or with nullptr */
      n = std::move((n->left) ? n->left : n->right);
    }
    /* decrement cur_size to decrease size of multiset */
    cur_size--;
  }
}

template <typename K>
void Multiset<K>::Remove(const K &key) {
  /* call the Remove helper method */
  Remove(root, key);
}

template <typename K>
bool Multiset<K>::Contains(const K &key) {
  /* get root node */
  Node *n = root.get();

  /* call Find() method to node, if DNE return false */
  if ((Find(n, key)) == 0) 
    return false; 

  /* if a node is found, return true */
  return true;
}

template <typename K>
size_t Multiset<K>::Count(const K &key) {
  /* get root node */
  Node *n = root.get();

  /* if the result is not a null pointer, return result */
  if (Find(n, key)) return (Find(n, key))->count;
  /* otherwise, if key was not found, throw exception */
  else
    std::__throw_invalid_argument("Invalid key");
}

template <typename K>
const K &Multiset<K>::Floor(const K &key) {
  /* if bst is empty, throw exception */
  if (Empty()) std::__throw_out_of_range("Empty multiset");

  /* if the key is less than the minimum, there exists no floor value --> throw
   * exception */
  if (key < Min()) std::__throw_invalid_argument("Invalid key");

  /* if the key exists in the bst, it is its own floor */
  if (Contains(key)) {
    floor = key;
    return floor;
  }

  /* get root node */
  Node *n = root.get();

  /* everytime you traverse right, you save the previous node's value as the
   * floor */
  floor = Min();
  while (n) {
    if (key < n->key) {
      n = n->left.get();
    } else {
      floor = n->key;
      n = n->right.get();
    }
  }

  return floor;
}

template <typename K>
const K &Multiset<K>::Ceil(const K &key) {
  
  /* if bst is empty, throw exception */
  if (Empty()) std::__throw_out_of_range("Empty multiset");

  /* if the key is greater than the maximum, there exists no ceil value -->
   * throw exception */
  if (key > Max()) std::__throw_invalid_argument("Invalid key");

  /* if the key exists in the bst, it is its own ceil */
  if (Contains(key)) {
    ceil = key;
    return key;
  }


  /* get root */
  Node *n = root.get();

  /* everytime you traverse left, you save the previous node's value as the ceil
   */
  ceil = Max();
  while (n) {
    if (key < n->key) {
      ceil = n->key;
      n = n->left.get();
    } else {
      n = n->right.get();
    }
  }

  

  return ceil;
}

template <typename K>
const K &Multiset<K>::Max() {
  /* if the multiset is empty, throw exception */
  if (Empty()) std::__throw_out_of_range("Empty Multiset!");

  /* get root node */
  Node *n = root.get();

  /* while the node at the right is not null, keep going right */
  while (n->right) n = n->right.get();

  /* when the right-most node is found, that is the maximum! */
  return n->key;
}

template <typename K>
const K &Multiset<K>::Min() {
  /* if the multiset is empty, throw exception */
  if (Empty()) std::__throw_out_of_range("Empty Multiset!");

  /* get root node */
  Node *n = root.get();

  /* while the node at the left is not null, keep going left */
  while (n->left) n = n->left.get();

  /* when the left-most node is found, that is the minumum! */
  return n->key;
}

#endif  // MULTISET_H_
