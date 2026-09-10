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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dum = new ListNode(0);
        dum->next = head;
        if(head == NULL) return head;
        ListNode *p1 = head;
        ListNode *p2 = dum;
        while(p1 != NULL){
            if(p1->next != NULL && p1->next->val == p1->val){
                while(p1->next != NULL && p1->next->val == p1->val){
                    p1 = p1->next;
                }
                p2->next = p1->next;
            }else{
                p2 = p2->next;
            }
            p1 = p1->next;
        }
        return dum->next;
    }
};