#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <iomanip>

// ============================================================================
// PART 1: Binary Search with Modern Structs & Projections
// ============================================================================

struct Nameval {
    // std::string_view acts like a lightweight, non-owning pointer to a string.
    // No allocation overhead, but far safer than a raw char*.
    std::string_view name;
    int value;
};

void run_binary_search_demo() {
    std::cout << "--- 🌴 HTML Entity Lookup (C++20 Binary Search) ---\n";

    // A modern container that manages its own size and memory.
    // Must be strictly sorted alphabetically by the 'name' field.
    const std::vector<Nameval> htmlchars = {
        {"AElig",  0x00c6},
        {"Aacute", 0x00c1},
        {"Acirc",  0x00c2}, 
        {"zeta",   0x03b6}  
    };

    const std::vector<std::string_view> test_queries = {
        "AElig", "Acirc", "zeta", "Abeta", "apple"
    };

    for (const auto& query : test_queries) {
        /*
         * In C++, std::ranges::lower_bound handles binary search beautifully.
         * 
         * The killer feature here is the final argument: `&Nameval::name`. 
         * This is a "Projection". It tells the algorithm: "Hey, look through the 
         * vector of Nameval structs, but only evaluate the 'name' field when 
         * comparing it against the query." No custom comparator needed!
         */
        auto it = std::ranges::lower_bound(htmlchars, query, {}, &Nameval::name);

        // lower_bound returns an iterator to the first element that doesn't come before the query.
        // We just verify we didn't fall off the end and that it's an exact match.
        if (it != htmlchars.end() && it->name == query) {
            std::cout << "[FOUND] " << std::setw(6) << std::left << query 
                      << " -> Hex value: 0x" << std::uppercase << std::hex 
                      << std::setw(4) << std::setfill('0') << it->value << "\n";
        } else {
            std::cout << "[MISS]  " << query << " not found in the entity table.\n";
        }
    }
}

// ============================================================================
// PART 2: Sorting with Ranges and Lambdas
// ============================================================================

void run_sorting_demo() {
    std::cout << "\n--- 💃 Array Sorting (C++20 Ranges) ---\n";

    std::vector<int> data = { 42, 7, -5, 12, 1024, 0, 7, -99, 3 };

    std::cout << "Before sort: ";
    for (int num : data) std::cout << num << " ";
    std::cout << "\n";

    /*
     * Goodbye custom loops, partition bugs, and manual sizing math.
     * std::ranges::sort takes the entire container directly instead of 
     * forcing you to pass `data.begin(), data.end()`. 
     * By default, it sorts in ascending order.
     */
    std::ranges::sort(data);

    std::cout << "After sort:  ";
    for (int num : data) std::cout << num << " ";
    std::cout << "\n";

    /*
     * Want a descending sort instead? Just pass a custom closure (lambda).
     * The syntax is clean, typed, and fully inlined by the compiler.
     */
    std::ranges::sort(data, [](int a, int b) { return a > b; });

    std::cout << "Desc sort:   ";
    for (int num : data) std::cout << num << " ";
    std::cout << "\n";
}

// ============================================================================
// ENTRY POINT
// ============================================================================

int main() {
    // Reset our output streams back to base-10 formatting for normal integers
    std::cout << std::dec << std::setfill(' ');
    
    run_binary_search_demo();
    run_sorting_demo();
    
    std::cout << "\n====================================================\n";
    std::cout << "All code executed cleanly. Nature is beautiful. 🌊\n";
    return 0;
}
