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
    vector<int> palin(ListNode* head){
        vector<int> rtr;
        ListNode* p1=NULL;
        ListNode* p2=NULL;
        while(head != NULL){
            p2 = head->next;
            head->next = p1;
            p1 = head;
            head = p2;
        }
        head = p1;
        ListNode* ptr = head;
        while(ptr!=NULL){
            rtr.emplace_back(ptr->val);
            ptr = ptr->next;
        }
        return rtr;
    }
    bool isPalindrome(ListNode* head) {
        vector<int> chk;
        ListNode* ptr = head;
        while(ptr!=NULL){
            chk.emplace_back(ptr->val);
            ptr=ptr->next;
        }
        vector<int> ans = palin(head);
        if(ans == chk) return true;
        return false;
    }
};