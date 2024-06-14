#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the traffic data
typedef struct TrafficNode
{
    char intersection[100]; // Intersection name
    char street[100];       // Street name
    int trafficSignalCount; // Number of traffic signals
    int trafficDensity;     // Traffic density
    int parkingSpaces;      // Available parking spaces
    int alternativeRoutes;  // Number of alternative routes
    struct TrafficNode *next;
} TrafficNode;

// Function prototypes
TrafficNode *createNode(char *intersection, char *street, int trafficSignalCount, int trafficDensity, int parkingSpaces, int alternativeRoutes);
void insertNode(TrafficNode **head, char *intersection, char *street, int trafficSignalCount, int trafficDensity, int parkingSpaces, int alternativeRoutes);
void deleteNode(TrafficNode **head, char *intersection);
TrafficNode *searchNode(TrafficNode *head, char *intersection);
void bubbleSort(TrafficNode *head);
void displayList(TrafficNode *head);
void manageParking(TrafficNode *head, char *intersection, int change);
void suggestAlternateRoutes(TrafficNode *head, char *intersection);

int main()
{
    TrafficNode *head = NULL;
    int choice;
    char intersection[100];
    char street[100];
    int trafficSignalCount;
    int trafficDensity;
    int parkingSpaces;
    int alternativeRoutes;

    while (1)
    {
        printf("\nSmart City Traffic Management System - Dhaka City\n");
        printf("1. Insert Traffic Data\n");
        printf("2. Delete Traffic Data\n");
        printf("3. Search Traffic Data\n");
        printf("4. Sort Traffic Data\n");
        printf("5. Display Traffic Data\n");
        printf("6. Manage Parking Spaces\n");
        printf("7. Suggest Alternate Routes\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice)
        {
        case 1:
            printf("\nEnter Intersection Name: ");
            fgets(intersection, sizeof(intersection), stdin);
            intersection[strcspn(intersection, "\n")] = 0; // Remove the newline character
            printf("Enter Street Name: ");
            fgets(street, sizeof(street), stdin);
            street[strcspn(street, "\n")] = 0; // Remove the newline character
            printf("Enter Number of Traffic Signals: ");
            scanf("%d", &trafficSignalCount);
            printf("Enter Traffic Density: ");
            scanf("%d", &trafficDensity);
            printf("Enter Number of Parking Spaces: ");
            scanf("%d", &parkingSpaces);
            printf("Enter Number of Alternative Routes: ");
            scanf("%d", &alternativeRoutes);
            insertNode(&head, intersection, street, trafficSignalCount, trafficDensity, parkingSpaces, alternativeRoutes);
            break;
        case 2:
            printf("\nEnter Intersection Name to Delete: ");
            fgets(intersection, sizeof(intersection), stdin);
            intersection[strcspn(intersection, "\n")] = 0; // Remove the newline character
            deleteNode(&head, intersection);
            break;
        case 3:
            printf("\nEnter Intersection Name to Search: ");
            fgets(intersection, sizeof(intersection), stdin);
            intersection[strcspn(intersection, "\n")] = 0; // Remove the newline character
            TrafficNode *found = searchNode(head, intersection);
            if (found)
            {
                printf("\nIntersection: %s\nStreet: %s\nTraffic Signals: %d\nTraffic Density: %d\nParking Spaces: %d\nAlternative Routes: %d\n",
                       found->intersection, found->street, found->trafficSignalCount, found->trafficDensity, found->parkingSpaces, found->alternativeRoutes);
            }
            else
            {
                printf("\nIntersection not found.\n");
            }
            break;
        case 4:
            bubbleSort(head);
            break;
        case 5:
            displayList(head);
            break;
        case 6:
            printf("\nEnter Intersection Name to Manage Parking: ");
            fgets(intersection, sizeof(intersection), stdin);
            intersection[strcspn(intersection, "\n")] = 0; // Remove the newline character
            int change;
            printf("Enter Change in Parking Spaces (positive or negative): ");
            scanf("%d", &change);
            manageParking(head, intersection, change);
            break;
        case 7:
            printf("\nEnter Intersection Name to Suggest Alternate Routes: ");
            fgets(intersection, sizeof(intersection), stdin);
            intersection[strcspn(intersection, "\n")] = 0; // Remove the newline character
            suggestAlternateRoutes(head, intersection);
            break;
        case 8:
            exit(0);
        default:
            printf("\nInvalid choice.\n");
        }
    }

    return 0;
}

// Create a new node
TrafficNode *createNode(char *intersection, char *street, int trafficSignalCount, int trafficDensity, int parkingSpaces, int alternativeRoutes)
{
    TrafficNode *newNode = (TrafficNode *)malloc(sizeof(TrafficNode));
    strcpy(newNode->intersection, intersection);
    strcpy(newNode->street, street);
    newNode->trafficSignalCount = trafficSignalCount;
    newNode->trafficDensity = trafficDensity;
    newNode->parkingSpaces = parkingSpaces;
    newNode->alternativeRoutes = alternativeRoutes;
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the end of the list
void insertNode(TrafficNode **head, char *intersection, char *street, int trafficSignalCount, int trafficDensity, int parkingSpaces, int alternativeRoutes)
{
    TrafficNode *newNode = createNode(intersection, street, trafficSignalCount, trafficDensity, parkingSpaces, alternativeRoutes);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        TrafficNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Delete a node by intersection name
void deleteNode(TrafficNode **head, char *intersection)
{
    TrafficNode *temp = *head;
    TrafficNode *prev = NULL;

    if (temp != NULL && strcmp(temp->intersection, intersection) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->intersection, intersection) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Intersection not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Search for a node by intersection name
TrafficNode *searchNode(TrafficNode *head, char *intersection)
{
    TrafficNode *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->intersection, intersection) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Bubble sort the linked list based on traffic density
void bubbleSort(TrafficNode *head)
{
    int swapped;
    TrafficNode *ptr1;
    TrafficNode *lptr = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->trafficDensity > ptr1->next->trafficDensity)
            {
                // Swap the data
                int tempDensity = ptr1->trafficDensity;
                char tempIntersection[100];
                char tempStreet[100];
                int tempSignalCount;
                int tempParkingSpaces;
                int tempAlternativeRoutes;

                strcpy(tempIntersection, ptr1->intersection);
                strcpy(tempStreet, ptr1->street);
                tempSignalCount = ptr1->trafficSignalCount;
                tempParkingSpaces = ptr1->parkingSpaces;
                tempAlternativeRoutes = ptr1->alternativeRoutes;

                ptr1->trafficDensity = ptr1->next->trafficDensity;
                strcpy(ptr1->intersection, ptr1->next->intersection);
                strcpy(ptr1->street, ptr1->next->street);
                ptr1->trafficSignalCount = ptr1->next->trafficSignalCount;
                ptr1->parkingSpaces = ptr1->next->parkingSpaces;
                ptr1->alternativeRoutes = ptr1->next->alternativeRoutes;

                ptr1->next->trafficDensity = tempDensity;
                strcpy(ptr1->next->intersection, tempIntersection);
                strcpy(ptr1->next->street, tempStreet);
                ptr1->next->trafficSignalCount = tempSignalCount;
                ptr1->next->parkingSpaces = tempParkingSpaces;
                ptr1->next->alternativeRoutes = tempAlternativeRoutes;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Display the linked list
void displayList(TrafficNode* head) {
    TrafficNode* temp = head;
    while (temp != NULL) {
        printf("Intersection: %s\nStreet: %s\nTraffic Signals: %d\nTraffic Density: %d\nParking Spaces: %d\nAlternative Routes: %d\n",
               temp->intersection, temp->street, temp->trafficSignalCount, temp->trafficDensity, temp->parkingSpaces, temp->alternativeRoutes);
        temp = temp->next;
    }
}

// Manage parking spaces
void manageParking(TrafficNode* head, char* intersection, int change) {
    TrafficNode* node = searchNode(head, intersection);
    if (node) {
        node->parkingSpaces += change;
        printf("Parking spaces at %s updated to %d\n", intersection, node->parkingSpaces);
    } else {
        printf("Intersection not found.\n");
    }
}

// Suggest alternative routes
void suggestAlternateRoutes(TrafficNode* head, char* intersection) {
    TrafficNode* node = searchNode(head, intersection);
    if (node) {
        if (node->alternativeRoutes > 0) {
            printf("There are %d alternative routes from %s.\n", node->alternativeRoutes, intersection);
        } else {
            printf("No alternative routes available from %s.\n", intersection);
        }
    } else {
        printf("Intersection not found.\n");
    }
}
