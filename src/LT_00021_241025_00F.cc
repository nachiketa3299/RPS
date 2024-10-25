
struct ListNode 
{
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 10:12 - 
// Merge 2 lists into 1 "sorted" list.
// Returns the head of the merged (sorted) linked list

// number of nodes in both lists is in the range [0, 50]
// Node.val in [-100, 100]
// list1 & list2 are sorted in non-decreasing order


class Solution 
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
	{
		const auto isList1BiggerAtStart = list1->val >= list2->val;
		auto* biggerList = isList1BiggerAtStart ? list1 : list2;
		auto* smallerList  = isList1BiggerAtStart ? list2 : list1;

		auto* biggerPtr = biggerList;
		auto* smallerPtr = smallerList;

		while (smallerPtr->next != nullptr)
		{
			// 다음 노드의 값이 큰 리스트 보다 작다?
			while (smallerPtr->next->val <= biggerPtr->val)
			{
				smallerPtr = smallerPtr->next;
			}
		}
    }
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
	ListNode* dummy;
	ListNode* temp;

	dummy = new ListNode();
	temp = dummy;

	while (list1 && list2) 
	{
		if (list1->val < list2->val)
		{
			temp->next = list1;
			list1 = list1->next;
		}
		else
		{
			temp->next = list2;
			list2 = list2->next;
		}

		temp = temp->next;
	}

	if (list1)
		temp->next = list1;
	if (list2)
		temp->next = list2;

	return dummy->next;
}
