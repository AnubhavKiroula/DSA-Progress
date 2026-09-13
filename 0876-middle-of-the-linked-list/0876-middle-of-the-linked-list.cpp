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
    ListNode* middleNode(ListNode* head) {
        if(head == NULL) return head;
        ListNode *ptr;
        ptr = head;
        int cnt = 0;
        while(ptr!= NULL){
            cnt++;
            ptr = ptr->next;
        }
        ptr = head;
        for(int i=0;i<cnt/2;++i){
            ptr = ptr->next;
        }
        head = ptr;
        return head;
    }
};