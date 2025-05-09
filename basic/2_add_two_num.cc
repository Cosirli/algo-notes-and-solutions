
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode;
        ListNode* p = res, * prev;
        int half_sum, full_sum;
        bool carry = false;

        while (l1 != nullptr && l2 != nullptr) {
            half_sum = l1->val + l2->val;
            full_sum = half_sum + carry;
            p->val = full_sum % 10;
            carry = full_sum / 10;
            l1 = l1->next;
            l2 = l2->next;
            p->next = new ListNode;
            prev = p;
            p = p->next;
        }

        ListNode* l = (l1 == nullptr) ? l2 : l1;
        while (l) {
            half_sum = l->val;
            full_sum = half_sum + carry;
            p->val = full_sum % 10;
            carry = full_sum / 10;
            l = l->next;
            p->next = new ListNode;
            prev = p;
            p = p->next;
        }

        if (carry == 0) {
            delete p;
            prev->next = nullptr;
        } else {
            p->val = carry;
        }
        return res;
    }
};
