/*
21. Merge Two Sorted Lists
Easy

You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:

Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:

Input: list1 = [], list2 = []
Output: []

Example 3:

Input: list1 = [], list2 = [0]
Output: [0]

 

Constraints:

    The number of nodes in both lists is in the range [0, 50].
    -100 <= Node.val <= 100
    Both list1 and list2 are sorted in non-decreasing order.


*/
//efficient method
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (!l1)
        {
            return l2;
        }
        if (!l2)
        {
            return l1;
        }
        if (l1->val > l2->val)
        {
            return mergeTwoLists(l2, l1);
        }
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
};

//saves comparison for first node in new link list
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *fakeHead = new ListNode(0);
        ListNode *t1 = l1;
        ListNode *t2 = l2;
        ListNode *result = fakeHead;
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        while (t1 != NULL && t2 != NULL)
        {
            if (t1->val <= t2->val)
            {
                result->next = t1;
                t1 = t1->next;
            }

            else
            {
                result->next = t2;
                t2 = t2->next;
            }
            result = result->next;
        }

        // check if any element remains in either of the list
        if (t2 != NULL)
            result->next = t2;
        if (t1 != NULL)
            result->next = t1;

        return fakeHead->next;
    }
};