/*
Second Largest Element In Tree
Send Feedback
Given a generic tree, find and return the node with second largest value in given tree. Return NULL if no node with required value is present.
Input format :
Line 1 : Elements in level order form separated by space (as per done in class). Order is -
Root_data, n (No_Of_Child_Of_Root), n children, and so on for every element
Output Format :
Second Largest node data
Sample Input 1 :
10 3 20 30 40 2 40 50 0 0 0 0
Sample Output 1 :
40
*/
//method 0:
//one way is find largest and replace it with -infinity...also check if there exist duplicates
//disadv: we are changing the input


//method 1: by finding largest of root and then proceeding
// Following is the given Tree node structure
/**************

 template <typename T>
class TreeNode {
public:
    T data;
    vector<TreeNode<T>*> children;

    TreeNode(T data) {
        this->data = data;
    }

    ~TreeNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }
};
***************/
#include<climits>
#include<utility>
TreeNode <int>* Largest(TreeNode<int> *root) {
    TreeNode <int>* largest=root;
    for(int i=0;i<root->children.size();i++){
        TreeNode <int>* temp=Largest(root->children[i]);
        if(temp->data > largest->data)
            largest=temp;
    }
    return largest;
}

pair<TreeNode <int>*,TreeNode <int>*>* secondLargest(TreeNode<int> *root,int waste){
    if(root==NULL){
        pair<TreeNode <int>*,TreeNode <int>*> *ans=new pair<TreeNode <int>*,TreeNode <int>*>();
        ans->first=root;
        ans->second=root;
        return ans;
    }
    TreeNode <int>* largest=Largest(root);

    pair<TreeNode <int>*,TreeNode <int>*> *ans=new pair<TreeNode <int>*,TreeNode <int>*>();
    ans->first=largest;
    ans->second=NULL;
    // cout<<"largest for root:"<<root->data<<" is:  "<<ans->first->data<<endl;

    for(int i=0;i<root->children.size();i++){
        pair<TreeNode <int>*,TreeNode <int>*> *cmp=secondLargest(root->children[i],waste);
        if(cmp->first->data != ans->first->data){

            if(ans->second==NULL)
                ans->second=cmp->first;
            else if(cmp->first->data > ans->second->data){
                ans->second=cmp->first;
            }
            else
                delete cmp;
        }
        else{

            if(ans->second==NULL)
                ans->second=cmp->second;
            else if(cmp->second!=NULL && cmp->second->data > ans->second->data)
                ans->second=cmp->second;
        }
    }
    //till now we didn't compared root explicitly
    if(ans->first->data < root->data){
        ans->second=ans->first;
        ans->first=root;
    }
    else if(ans->first->data == root->data)//it is the largest
    {}
    else{
        if(ans->second==NULL)
            ans->second=root;
        else if(root->data > ans->second->data)
            ans->second=root;
    }
    return ans;
}
TreeNode <int>* secondLargest(TreeNode<int> *root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    return secondLargest(root,0)->second;
}

//method 2: not finding largest, rather working with a pair with first=root, second=null
//large no. of cases form(see pic with this file's name)

//NOT NEED OF DYNAMIC ALLOCATION: fir delete karte reh jaoge

#include<climits>
#include<utility>

pair<TreeNode <int>*,TreeNode <int>*> secondLargestHelper(TreeNode<int> *root){
    if(root==NULL){
        pair<TreeNode <int>*,TreeNode <int>*> ans;
        ans.first=root;
        ans.second=root;
        return ans;
    }
    
    pair<TreeNode <int>*,TreeNode <int>*> ans;
    ans.first=root;
    ans.second=NULL;
        
    for(int i=0;i<root->children.size();i++){
        pair<TreeNode <int>*,TreeNode <int>*> cmp=secondLargestHelper(root->children[i]);
        if(cmp.first->data < ans.first->data){
            
            if(ans.second==NULL)
                ans.second=cmp.first;
            else if(cmp.first->data > ans.second->data){
                ans.second=cmp.first;
            }
        }
        else if(cmp.first->data == ans.first->data){
            if(ans.second==NULL)
                ans.second=cmp.second;
            else if(cmp.second != NULL && cmp.second->data > ans.second->data){
                ans.second=cmp.second;
            }
        }
        else{
            TreeNode <int>* saving_ans_first=ans.first;
            ans.first=cmp.first;
            if(cmp.second==NULL)
                ans.second=saving_ans_first;
            else if(cmp.second!=NULL && cmp.second->data > saving_ans_first->data)
                ans.second=cmp.second;
            else
                ans.second=saving_ans_first;
                // deletion can be done here appropriately
        }
    }
    
    return ans;
}
TreeNode <int>* secondLargest(TreeNode<int> *root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    return secondLargestHelper(root).second;
}



//wrong approach although seems fine
/*   Let us create below tree
   *            1
   *            |
   *            2
   *           / \
   *         4   500
   */
// Following is the given Tree node structure
/**************

 template <typename T>
class TreeNode {
public:
    T data;
    vector<TreeNode<T>*> children;

    TreeNode(T data) {
        this->data = data;
    }

    ~TreeNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }
};
***************/
#include<climits>
#include<utility>
TreeNode <int>* Largest(TreeNode<int> *root) {
    TreeNode <int>* largest=root;
    for(int i=0;i<root->children.size();i++){
        TreeNode <int>* temp=Largest(root->children[i]);
        if(temp->data > largest->data)
            largest=temp;
    }
    return largest;
}
TreeNode <int>* secondLargest(TreeNode<int> *root) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
	pair<TreeNode <int>*,TreeNode <int>*> cmp;
    cmp.first=NULL;
    cmp.second=root;
    for(int i=0;i<root->children.size();i++){
        TreeNode <int>* temp=Largest(root->children[i]);
        if(temp->data > cmp.second->data){
            cmp.first=cmp.second;
            cmp.second=temp;
        }
        else if(temp->data < cmp.second->data){//equality not allowed
            if(cmp.first==NULL)
                cmp.first=temp;
            else if(temp->data > cmp.first->data)
                cmp.first=temp;
        }
    }
    return cmp.first;
}

