/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode* , int> mpp;
        ListNode* tmp = head;
        while(tmp != NULL){
            if(mpp.find(tmp) != mpp.end()) return true;
            mpp[tmp] = 1;
            tmp = tmp->next;
        }
        return false;
    }
};