# Trie-Based-Dictionary
# DICTIONARY-TRIE

A **Dictionary** implementation using a **Trie (prefix tree)** data structure.  
Supports storing words with their meanings, and operations like insert, lookup, delete, update, and prefix suggestions.

---

## 📂 Repository Structure


---

## ✨ Features

- Insert a **word** along with its **meaning**  
- Search for a word to retrieve its meaning  
- Update the meaning of an existing word  
- Delete a word from the dictionary  
- Suggest words (and meanings) given a prefix  
- Case insensitivity (e.g. treat “Apple” and “apple” the same)  
- Efficient lookups and operations (average O(length_of_word))

---

## 🧠 How It Works (Brief Explanation)

A **Trie** (or prefix tree) is a tree-like data structure where each node corresponds to a character.  
- You traverse down the nodes following characters of the word.  
- A node has children for next possible letters.  
- Mark a node as the **end of word** and store the associated **meaning**.  
- For prefix suggestions, you traverse to the node representing the prefix, and then do a DFS (or BFS) over its descendants to collect words with that prefix.

Because operations are bounded by the length of the word (and prefix), it’s efficient for dictionary-style tasks.

---

## 🛠️ Usage Example (Pseudo / C++ style)

```cpp
#include "TrieDictionary.h"

int main() {
    TrieDictionary dict;

    dict.insert("apple", "A fruit that grows on trees");
    dict.insert("apply", "To put to use");
    dict.insert("app", "Short for application");

    auto meaning = dict.search("apple");
    if (!meaning.empty()) {
        cout << "apple: " << meaning << "\n";
    } else {
        cout << "Not found\n";
    }

    dict.update("app", "Abbreviation of application");
    dict.remove("apply");

    vector<string> suggestions = dict.suggest("app");
    for (auto &w : suggestions) {
        cout << w << " -> " << dict.search(w) << "\n";
    }

    return 0;
}
