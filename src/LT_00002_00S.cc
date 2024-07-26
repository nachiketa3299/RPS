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

		auto carry = 0;
		ListNode* ret = nullptr;
		ListNode* ret_ptr = nullptr;

		while (true) {
			if (l1 == nullptr && l2 == nullptr) {
				break;
			}

			auto const l1_val = l1 == nullptr ? 0 : l1->val;
			auto const l2_val = l2 == nullptr ? 0 : l2->val;

			auto const raw_sum = l1_val + l2_val + carry;

			auto const ret_val = raw_sum % 10;
			carry = raw_sum >= 10 ? 1 : 0;

			if (ret != nullptr) {
				ret_ptr = ret_ptr->next = new ListNode(ret_val);
			} else {
				ret_ptr = ret = new ListNode(ret_val);
			}

			if (l1 != nullptr) {
				l1 = l1->next;
			}

			if (l2 != nullptr) {
				l2 = l2->next;
			}
		}

		if (carry != 0) {
			ret_ptr->next = new ListNode(carry);
		}

		return ret;
    }
};