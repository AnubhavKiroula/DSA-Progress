/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL)
            return head;
        int size = 0;
        ListNode* ptr = head;
        while (ptr != NULL) {
            size++;
            ptr = ptr->next;
        }
        if (n == size) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return head;
        }
        ListNode* prev = head;
        for (int i = 0; i < size - n - 1; i++)
            prev = prev->next;
        ListNode* target = prev->next;
        prev->next = target->next;
        delete target;
        return head;
    }
};