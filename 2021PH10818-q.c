#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int x) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = x;
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int x;
    scanf("%d", &x);

    if(x == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present
    struct Employee* par = create_employee(x);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();
    
    return par;
}

// The following function 
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d ", ceo->emp_id);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
} 




//-------Linked List Code-----------
struct Node
{
    int data;
    struct Node* next;
};

// create a node with data as x
struct Node* create_node(int x) {
    struct Node* ptr = malloc(sizeof(struct Node));
    ptr->next = NULL;
    ptr->data = x;
    return ptr;
}

// delete the node at `ptr` and free its memory
void delete_node(struct Node* ptr) {
    free(ptr);
}
// Use this to operate on the list, this will always point at the head of the list.
struct Node* PythonListHead = NULL;


// prints the list in space seperated format
void print_list(struct Node* head) {
    struct Node* cur = head;
    while(cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


// helper function that returns pointer to `Node` at `position`
// if there is no such position, it returns NULL
struct Node* get_node_at_pos(int position) {
    int pos = 0;
    struct Node* cur = PythonListHead;
    while(cur) {
        if(pos == position) return cur;
        pos++;
        cur = cur->next;
    }
    return NULL;
}


// Return the number of elements in the list
int len() {
    int length = 0;
    struct Node* cur = PythonListHead;
    while(cur) {
        length++;
        cur = cur->next;
    }
    return length;
}


// Add an item to the end of the list
void append(int x) {
    struct Node* cur = PythonListHead;
    if(cur == NULL) {
        // no list exists, we have to create one
        PythonListHead = create_node(x);
    }
    else {
        int pos = len() - 1;
        struct Node* last_node = get_node_at_pos(pos);
        last_node->next = create_node(x);
    }
}
//--------Linked List Code ends here---------




// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

struct Employee* CEO = NULL;
// CEO is a global pointer that points to the CEO of the company



void EmployeesAtSameLevel_helper(int level,struct Employee* ptr,int current){
    if(current==level) printf("%d ",ptr->emp_id);
    else{
        if(ptr->subordinate_1!=NULL) EmployeesAtSameLevel_helper(level,ptr->subordinate_1,current+1);
        if(ptr->subordinate_2!=NULL) EmployeesAtSameLevel_helper(level,ptr->subordinate_2,current+1);
    }
}


/*  In this function you have to print all the employees at a given level, Note that ceo is at level 0
In any of the functions which involve printing you need not print -1 for NULL pointers */
void EmployeesAtSameLevel(int level) {
    // The level may be any integer
    if(CEO==NULL) return;
    EmployeesAtSameLevel_helper(level,CEO,0);
}


void get_employees_helper(struct Employee* ceo) {
    if(ceo){
        printf("%d ", ceo->emp_id);
        get_employees_helper(ceo->subordinate_1);
        get_employees_helper(ceo->subordinate_2);
        return;
    }
}

// You have to print the employees as you search the organization look for the examples in the pdf and the input.txt and output.txt for details
// Note: You do not have to print -1 for NULL pointers
void get_employees() {
    get_employees_helper(CEO);
    return;
}


int sub1(int id,struct Employee* head){
    if (head!=NULL){
        if (head->emp_id==id && head->subordinate_1!=NULL) return head->subordinate_1->emp_id;
        else{
            int a=sub1(id,head->subordinate_1);
            if(a!=-2) return a;
            else return sub1(id,head->subordinate_2);
        }
    }
    return -2;
}

int sub2(int id,struct Employee* head){
    if (head!=NULL){
        if (head->emp_id==id && head->subordinate_2!=NULL) return head->subordinate_2->emp_id;
        else{
            int a=sub2(id,head->subordinate_1);
            if(a!=-2) return a;
            else return sub2(id,head->subordinate_2);
        }
    }
    return -2;
}

int boss_helper(int id, int parent,struct Employee* head){
    if (head!=NULL){
        if (head->emp_id==id) return parent;
        else{
            int a=boss_helper(id,head->emp_id,head->subordinate_1);
            if(a!=-2) return a;
            else return boss_helper(id,head->emp_id,head->subordinate_2);
        }
    }
    return -2;
}


/* The following function takes an emp_id this will belong to a employee in the organisation and your task is to return the emp_id of its boss
Note: If the boss does not exit return -1 */
int Boss(int emp_id) { 
    if(CEO->emp_id==emp_id) return -1;
    else{
        return boss_helper(emp_id,-1,CEO);
    }
}


/* In the following function you have to print the immediate team of a employee - it includes their boss and their subordinates
Note: You do not have to print -1 for NULL pointers */

void ImmediateTeam(int emp_id) {
    if (CEO==NULL) return;
    else{
        int h=Boss(emp_id);
        int a=sub1(emp_id,CEO);
        int b=sub2(emp_id,CEO);
        if(h>=0) printf("%d ",h);
        if(a!=-2) printf("%d ",a);
        if(b!=-2) printf("%d ",b);
    }
    return;
}


int Level_helper(int id,int count,struct Employee* pointer){
    if (pointer==NULL) return -1;
    if (pointer->emp_id==id) return count;
    else{
        int left=Level_helper(id,count+1,pointer->subordinate_1);
        if (left!=-1) return left;
        else{
            return Level_helper(id,count+1,pointer->subordinate_2);
        }
    }
    return -1;
}

// The following function returns the level of a employee with the given emp_id
int Level(int emp_id) {
    // Note that ceo has level 0
    return Level_helper(emp_id,0,CEO);
}


int CommonParent(int id1,int id2){
    int parent1,parent2;
    if(Level(id1)>Level(id2)){
        while(Level(id1)>Level(id2)){
            id1=Boss(id1);
        }
    }
    if(Level(id2)>Level(id1)){
        while(Level(id2)>Level(id1)){
            id2=Boss(id2);
        }
    }

    if(id1==id2) return id1;
    else{
        parent1=Boss(id1);
        parent2=Boss(id2);
    }
    if (parent1==parent2) return parent1;
    else{
        return CommonParent(parent1,parent2);
    }
}

// The following function gives the distance between employees with emp_id1 and emp_id2
int Distance(int emp_id1, int emp_id2) {
    // If emp_id1 and emp_id2 are equal the distance is 0, both emp_id's will exist in the organisation
    int common_boss=CommonParent(emp_id1,emp_id2);
    int parentlevel=Level(common_boss);
    int id1level=Level(emp_id1);
    int id2level=Level(emp_id2);
    return (id1level+id2level-(2*parentlevel));
}


void leaf(struct Employee* node){
    if (node->subordinate_1==NULL && node->subordinate_2==NULL)  append(node->emp_id);
    else{
        if(node->subordinate_1!=NULL) leaf(node->subordinate_1);
        if(node->subordinate_2!=NULL) leaf(node->subordinate_2);
    }
}

/* The following function returns the diameter of a Organisation - 
a diameter is the maximum distance between any two emp_ids in the organisation. You can use the distance function implemented above */

int Diameter() {
    if(CEO==NULL) return 0;
    int max=0;
    int dist=0;
    int leaf1=0;
    int leaf2=0;
    leaf(CEO);
    int length=len();
    for (int i=0;i<length;i++){
        leaf1=get_node_at_pos(i)->data;
        for(int j=0;j<length;j++){
            leaf2=get_node_at_pos(j)->data;
            dist=Distance(leaf1,leaf2);
            if (dist>max) max=dist;
        }
    }
    return max;
}

/* The following function takes an emp_id of a employee and returns the number of employees directly connected to it.
NULL pointers are not included */

int TeamSize(int emp_id) {
    int count=0;
    int a=Boss(emp_id);
    int b=sub1(emp_id,CEO);
    int c=sub2(emp_id,CEO);
    if (a>=0) count++;
    if (b!=-2) count++;
    if (c!=-2) count++;
    return count;
}

// --------------------------------------------------- YOU CAN EDIT ABOVE THIS LINE -----------------------------------

/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T; 
    scanf("%d", &T);

    char operation_type[50];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "level") == 0) {
            int x;
            scanf("%d", &x);
            int d = Level(x);
            printf("%d\n", d);
        } 

        if(strcmp(operation_type, "distance") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int d = Distance(x, y);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "employees_at_same_level") == 0) {
            int x;
            scanf("%d", &x);
            EmployeesAtSameLevel(x);
            printf("\n");
        }

        if(strcmp(operation_type, "get_employees") == 0) {
            get_employees();
            printf("\n");
        }

        if(strcmp(operation_type, "boss") == 0) {
            int x;
            scanf("%d", &x);
            int d = Boss(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "diameter") == 0) {
            int d = Diameter();
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "immediate_team") == 0) {
            int x;
            scanf("%d", &x);
            ImmediateTeam(x);
            printf("\n");
        }

        if(strcmp(operation_type, "team_size") == 0) {
            int x;
            scanf("%d", &x);
            int d = TeamSize(x);
            printf("%d\n", d);
        }
    }

    return 0;
}
