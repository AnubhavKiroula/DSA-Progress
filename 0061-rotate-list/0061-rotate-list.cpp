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
    ListNode* rotateRight(ListNode* head, int k) {
        int len =1;
        if(head == NULL || head->next == NULL || k==0) return head;
        ListNode *p1 = head;
        while(p1->next){
            p1 = p1->next;
            len++;
        }
        k %= len;
        if(k==0) return head;
        p1->next = head;
        int steps = len-k;
        ListNode *p2 = head;
        for(int i=1;i<steps;++i) p2 = p2->next;
        ListNode *p3 = p2->next;
        p2->next = NULL;
        return p3;
    }
};