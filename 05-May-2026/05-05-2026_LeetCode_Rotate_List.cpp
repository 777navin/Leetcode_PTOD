/*
Date: 05-05-2026
Problem Name: 61. Rotate List
Platform: LeetCode
Difficulty: Medium
Tags: Linked List, Two Pointers

Problem Summary:
Given the head of a linked list, rotate the list to the right by k places.

Methods to Solve:
1. Brute Force
2. Optimal Approach

For EACH method include:

Method 1: Brute Force
- Intuition: Rotate the linked list by 1 place to the right, and repeat this process k times.
- Approach: Traverse to find the last node and the second last node. Make the last node point to the head, update the head, and make the second last node point to NULL. Repeat this process k times.
- Dry Run: head = [1,2,3], k = 1. Last is 3, second last is 2. 3->next = 1, head = 3, 2->next = NULL. Result: [3,1,2].
- Time Complexity: O(k * N) where N is the number of nodes in the list.
- Space Complexity: O(1)
- Why better than previous method: N/A
- When to use: Not recommended as it will result in Time Limit Exceeded (TLE) for large values of k.

Method 2: Optimal Approach
- Intuition: Instead of rotating one by one, we can make the linked list circular and then break it at the correct final position. The effective number of rotations needed is k % length.
- Approach:
  1. Calculate the length of the list and find the original tail node.
  2. Connect the tail to the head to form a circular linked list.
  3. Find the new tail, which will be positioned at `(length - k % length)` steps from the head.
  4. Break the circle by setting the new tail's next pointer to NULL and update the head to be the new tail's next node.
- Dry Run: head = [1,2,3,4,5], k = 2. Length = 5. Effective k = 2 % 5 = 2. Break the link at 5 - 2 = 3rd node (node 3). New head = 4. Result: [4,5,1,2,3].
- Time Complexity: O(N) where N is the number of nodes to compute the length and find the break point.
- Space Complexity: O(1)
- Why better than previous method: Drastically reduces the time complexity from O(k * N) to O(N).
- When to use: Always optimal for this problem.

Comparison Table:
Method          | TC       | SC   | Best Use Case
----------------|----------|------|---------------------------
Brute Force     | O(k * N) | O(1) | Small values of k and N
Optimal Approach| O(N)     | O(1) | General case (Recommended)

Final Recommended Solution: Optimal Approach
*/

#include <iostream>

using namespace std;

// ==========================================
// LOCAL TESTING STRUCTS
// (Uncomment this block to run locally / push to GitHub)
// ==========================================
/*
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // Base cases: empty list, single node, or no rotation needed
        if (!head || !head->next || k == 0) {
            return head;
        }

        // Step 1: Find the length and the tail node
        ListNode* tail = head;
        int length = 1;
        while (tail->next) {
            tail = tail->next;
            length++;
        }

        // Step 2: Make the list circular
        tail->next = head;

        // Step 3: Find the effective rotations and the new tail position
        k = k % length;
        int stepsToNewTail = length - k;

        ListNode* newTail = tail;
        while (stepsToNewTail--) {
            newTail = newTail->next;
        }

        // Step 4: Break the circle and set the new head
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};

// ==========================================
// DRIVER CODE
// (Uncomment this block to run locally / push to GitHub)
// ==========================================
/*
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Helper function to create a linked list from an initializer list
    auto createList = [](initializer_list<int> vals) -> ListNode* {
        ListNode dummy;
        ListNode* curr = &dummy;
        for (int val : vals) {
            curr->next = new ListNode(val);
            curr = curr->next;
        }
        return dummy.next;
    };

    // Helper function to print the linked list
    auto printList = [](ListNode* head) {
        if (!head) {
            cout << "[]\n";
            return;
        }
        while (head) {
            cout << head->val;
            if (head->next) cout << " -> ";
            head = head->next;
        }
        cout << "\n";
    };

    Solution sol;

    // Test Case 1
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    int k1 = 2;
    cout << "Original List: ";
    printList(head1);
    ListNode* res1 = sol.rotateRight(head1, k1);
    cout << "Rotated by " << k1 << ": ";
    printList(res1);

    cout << "-----------------------\n";

    // Test Case 2
    ListNode* head2 = createList({0, 1, 2});
    int k2 = 4;
    cout << "Original List: ";
    printList(head2);
    ListNode* res2 = sol.rotateRight(head2, k2);
    cout << "Rotated by " << k2 << ": ";
    printList(res2);

    return 0;
}
*/
