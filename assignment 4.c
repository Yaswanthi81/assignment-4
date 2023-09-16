  #include <stdio.h>
#include <stdlib.h>

// Define a linked list node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to reverse a linked list iteratively
struct Node* reverseListIterative(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Function to find the length of a linked list
int getLength(struct Node* head) {
    int length = 0;
    struct Node* current = head;
    while (current != NULL) {      
        length++;
        current = current->next;
    }
    return length;
}

// Function to reverse k nodes in a linked list
struct Node* reverseKNodes(struct Node* head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }

    int length = getLength(head);

    if (length < k) {
        return head;
    }

    struct Node* prevTail = NULL;
    struct Node* newHead = NULL;

    while (length >= k) {
        struct Node* currentHead = head;
        struct Node* prev = NULL;

        for (int i = 0; i < k; i++) {
            struct Node* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        if (prevTail != NULL) {
            prevTail->next = prev;
        } else {
            newHead = prev;
        }

        currentHead->next = head;

        prevTail = currentHead;
        length -= k;
    }

    return newHead;
}

// Function to reverse the linked list from position m to n
struct Node* reverseBetween(struct Node* head, int m, int n) {
    if (head == NULL || m == n) {
        return head;
    }

    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    dummy->next = head;
    struct Node* prevM = dummy;

    for (int i = 1; i < m; i++) {
        if (prevM == NULL) {
            return head;
        }
        prevM = prevM->next;
    }

    struct Node* mNode = prevM->next;
    struct Node* prev = NULL;
    struct Node* current = mNode;
    struct Node* next = NULL;

    for (int i = m; i <= n; i++) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    prevM->next = prev;
    mNode->next = current;

    return dummy->next;
}

// Function to find the nth node from the end of a linked list
struct Node* findNthFromEnd(struct Node* head, int n) {
    if (head == NULL || n <= 0) {
        return NULL;
    }

    struct Node* first = head;
    struct Node* second = head;

    for (int i = 0; i < n; i++) {
        if (first == NULL) {
            return NULL; // List is shorter than n
        }
        first = first->next;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    return second;
}

// Function to swap pairwise nodes of a linked list
struct Node* swapPairs(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    dummy->next = head;
    struct Node* prev = dummy;

    while (prev->next != NULL && prev->next->next != NULL) {
        struct Node* first = prev->next;
        struct Node* second = prev->next->next;

        first->next = second->next;
        second->next = first;
        prev->next = second;

        prev = first;
    }

    return dummy->next;
}

// Function to find the middle of a linked list
struct Node* findMiddle(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to count the number of times a given int occurs in a linked list
int countOccurrences(struct Node* head, int key) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        if (current->data == key) {
            count++;
        }
        current = current->next;
    }

    return count;
}

// Function to delete all occurrences of a given key in a linked list
void deleteAllOccurrences(struct Node** head, int key) {
    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    dummy->next = *head;
    struct Node* prev = dummy;
    struct Node* current = *head;

    while (current != NULL) {
        if (current->data == key) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    *head = dummy->next;
}

// Function to merge two sorted linked lists 
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tail = dummy;
    dummy->next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next; 
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    }

    if (list2 != NULL) {
        tail->next = list2;
    }

    return dummy->next;
}

// Function to add two numbers represented by singly linked lists
struct Node* addNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* current = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = sum;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode; 
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    if (carry > 0) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = carry;
        newNode->next = NULL;
        current->next = newNode;
    }

    return result;
}

// Function to multiply two numbers represented by singly linked lists
struct Node* multiplyNumbers(struct Node* num1, struct Node* num2) {
    // Initialize the result as 0
    struct Node* result = (struct Node*)malloc(sizeof(struct Node));
    result->data = 0;
    result->next = NULL;

    struct Node* current1 = num1;
    int multiplier = 1; 

    // Iterate through num1 and multiply num2 by each digit of num1
    while (current1 != NULL) {
        int digit = current1->data;

        struct Node* current2 = num2;
        struct Node* partialResult = (struct Node*)malloc(sizeof(struct Node));
        partialResult->data = 0;
        partialResult->next = NULL;
        struct Node* currentResult = partialResult;

        int carry = 0;

        // Multiply num2 by the current digit of num1
        while (current2 != NULL) {
            int product = digit * current2->data + carry;
            carry = product / 10;
            product %= 10;  

            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = product;
            newNode->next = NULL;
            currentResult->next = newNode;
            currentResult = newNode;

            current2 = current2->next;
        }

        // Add the partial result to the overall result
        result = addNumbers(result, partialResult->next);

        // Free the memory used by the partial result
        while (partialResult != NULL) {
            struct Node* temp = partialResult;  
            partialResult = partialResult->next;
            free(temp);
        }

        // Move to the next digit of num1
        current1 = current1->next;
        multiplier *= 10;
    }

    return result;
}

// Function to intersect two linked lists
struct Node* intersectLists(struct Node* list1, struct Node* list2) {
    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    dummy->next = NULL;
    struct Node* tail = dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data == list2->data) {
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = list1->data;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
            list1 = list1->next;
            list2 = list2->next;
        } else if (list1->data < list2->data) {
            list1 = list1->next;
        } else {
            list2 = list2->next;
        }
    }

    return dummy->next;
}

// Function to partition a linked list
void partitionList(struct Node** head, int x) {
    struct Node* beforeHead = (struct Node*)malloc(sizeof(struct Node));
    struct Node* beforeTail = beforeHead;
    struct Node* afterHead = (struct Node*)malloc(sizeof(struct Node));
    struct Node* afterTail = afterHead;

    struct Node* current = *head;

    while (current != NULL) {
        if (current->data < x) {
            beforeTail->next = current;
            beforeTail = beforeTail->next;  
        } else {
            afterTail->next = current;
            afterTail = afterTail->next;
        }
        current = current->next;
    }

    beforeTail->next = NULL;
    afterTail->next = NULL;

    beforeTail->next = afterHead->next;
    *head = beforeHead->next;
}

int main() {
    // Task 1: Reverse a linked list using an iterative method
    struct Node* list1 = NULL;
    insertAtBeginning(&list1, 1);
    insertAtBeginning(&list1, 2);
    insertAtBeginning(&list1, 3);
    printf("Original Linked List: ");
    printList(list1);
    list1 = reverseListIterative(list1);
    printf("Reversed Linked List (Iterative): ");
    printList(list1);

    // Task 2: Reverse a linked list from position m to n
    struct Node* list2 = NULL;
    insertAtBeginning(&list2, 1);
    insertAtBeginning(&list2, 2);
    insertAtBeginning(&list2, 3);
    insertAtBeginning(&list2, 4);
    insertAtBeginning(&list2, 5);
    printf("Original Linked List for Task 2: ");
    printList(list2);
    list2 = reverseBetween(list2, 2, 4);
    printf("Reversed Linked List from position 2 to 4: ");
    printList(list2);

    // Task 3: Find the nth node from the end of a linked list
    struct Node* list3 = NULL;
    insertAtBeginning(&list3, 1);
    insertAtBeginning(&list3, 2);
    insertAtBeginning(&list3, 3);
    insertAtBeginning(&list3, 4);
    insertAtBeginning(&list3, 5);
    printf("Original Linked List for Task 3: "); 
    printList(list3);
    int n = 3;
    struct Node* nthFromEnd = findNthFromEnd(list3, n);
    if (nthFromEnd != NULL) {
        printf("The %dth node from the end is %d\n", n, nthFromEnd->data);
    } else {
        printf("The list is too short for the %dth node from the end\n", n);
    }

    // Task 4: Swap pairwise nodes of a linked list
    struct Node* list4 = NULL;
    insertAtBeginning(&list4, 1);
    insertAtBeginning(&list4, 2);
    insertAtBeginning(&list4, 3);
    insertAtBeginning(&list4, 4);
    insertAtBeginning(&list4, 5);
    printf("Original Linked List for Task 4: ");
    printList(list4);
    list4 = swapPairs(list4);
    printf("Linked List after Swapping Pairs: ");
    printList(list4);

    // Task 5: Reverse every alternate k nodes efficiently
    struct Node* list5 = NULL;
    insertAtBeginning(&list5, 1);
    insertAtBeginning(&list5, 2);
    insertAtBeginning(&list5, 3);
    insertAtBeginning(&list5, 4);
    insertAtBeginning(&list5, 5);
    insertAtBeginning(&list5, 6);
    printf("Original Linked List for Task 5: ");
    printList(list5);
    int k = 3;
    list5 = reverseKNodes(list5, k);
    printf("Linked List after Reversing Every Alternate %d Nodes: ", k);
    printList(list5);

    // Task 6: Print the middle of a given linked list 
    struct Node* list6 = NULL;
    insertAtBeginning(&list6, 1);
    insertAtBeginning(&list6, 2);
    insertAtBeginning(&list6, 3);
    insertAtBeginning(&list6, 4);
    insertAtBeginning(&list6, 5);
    printf("Original Linked List for Task 6: ");
    printList(list6);
    struct Node* middle = findMiddle(list6);
    if (middle != NULL) {
        printf("The middle of the Linked List is %d\n", middle->data);
    } else {
        printf("The list is empty\n");
    }

    // Task 7: Count the number of times a given int occurs in a linked list
    struct Node* list7 = NULL;
    insertAtBeginning(&list7, 1);
    insertAtBeginning(&list7, 2);
    insertAtBeginning(&list7, 3);
    insertAtBeginning(&list7, 2);
    insertAtBeginning(&list7, 4);
    insertAtBeginning(&list7, 2);
    printf("Original Linked List for Task 7: ");
    printList(list7);
    int key7 = 2;
    int count7 = countOccurrences(list7, key7);
    printf("The number %d occurs %d times in the Linked List\n", key7, count7);

    // Task 8: Delete all occurrences of a given key in a linked list
    struct Node* list8 = NULL;
    insertAtBeginning(&list8, 1);
    insertAtBeginning(&list8, 2);
    insertAtBeginning(&list8, 3);
    insertAtBeginning(&list8, 2);
    insertAtBeginning(&list8, 4);
    insertAtBeginning(&list8, 2);
    printf("Original Linked List for Task 8: ");
    printList(list8); 
    int key8 = 2;
    deleteAllOccurrences(&list8, key8);
    printf("Linked List after deleting all occurrences of %d: ", key8);
    printList(list8);

    // Task 9: Merge two sorted linked lists
    struct Node* list9a = NULL;
    struct Node* list9b = NULL;
    insertAtBeginning(&list9a, 8);
    insertAtBeginning(&list9a, 4);
    insertAtBeginning(&list9a, 2);
    insertAtBeginning(&list9b, 7);
    insertAtBeginning(&list9b, 6);
    insertAtBeginning(&list9b, 5);
    printf("List 1 for Task 9: ");
    printList(list9a);
    printf("List 2 for Task 9: ");
    printList(list9b);
    struct Node* mergedList9 = mergeSortedLists(list9a, list9b);
    printf("Merged Sorted List for Task 9: ");
    printList(mergedList9);

    // Task 10: Add two numbers represented by singly linked lists
    struct Node* num1 = NULL; 
    struct Node* num2 = NULL;
    insertAtBeginning(&num1, 9);
    insertAtBeginning(&num1, 9);
    insertAtBeginning(&num1, 9);
    insertAtBeginning(&num2, 5);
    insertAtBeginning(&num2, 9);
    insertAtBeginning(&num2, 2);
    printf("Number 1 for Task 10: ");
    printList(num1);
    printf("Number 2 for Task 10: ");
    printList(num2);
    struct Node* sum = addNumbers(num1, num2);
    printf("Sum of Numbers for Task 10: ");
    printList(sum); 

    // Task 11: Multiply two numbers represented by singly linked lists
    struct Node* num3 = NULL;
    struct Node* num4 = NULL;
    insertAtBeginning(&num3, 1);
    insertAtBeginning(&num3, 2);
    insertAtBeginning(&num3, 3);
    insertAtBeginning(&num4, 4);
    insertAtBeginning(&num4, 5);
    printf("Number 3 for Task 11: ");
    printList(num3);
    printf("Number 4 for Task 11: ");
    printList(num4);
    struct Node* product = multiplyNumbers(num3, num4);
    printf("Product of Numbers for Task 11: ");
    printList(product);

    // Task 12: Intersect two linked lists
    struct Node* list12a = NULL;
    struct Node* list12b = NULL;
    insertAtBeginning(&list12a, 4);
    insertAtBeginning(&list12a, 5);
    insertAtBeginning(&list12a, 6);
    insertAtBeginning(&list12a, 7);
    insertAtBeginning(&list12b, 2);
    insertAtBeginning(&list12b, 5);
    insertAtBeginning(&list12b, 8);
    printf("List 1 for Task 12: ");
    printList(list12a);
    printf("List 2 for Task 12: ");
    printList(list12b);
    struct Node* intersection12 = intersectLists(list12a, list12b);
    printf("Intersection of Lists for Task 12: ");
    printList(intersection12);

    // Task 13: Partition a linked list
    struct Node* list13 = NULL;
    insertAtBeginning(&list13, 5);
    insertAtBeginning(&list13, 2);
    insertAtBeginning(&list13, 8);
    insertAtBeginning(&list13, 3);
    insertAtBeginning(&list13, 4);
    insertAtBeginning(&list13, 2);
    printf("Original Linked List for Task 13: ");
    printList(list13);
    int x13 = 3;
    partitionList(&list13, x13);
    printf("Partitioned Linked List for Task 13: ");
    printList(list13);

    return 0;
}