#include <bits/stdc++.h>

using namespace std;
struct TrieNode
{
    map<char,TrieNode*> child;
    bool endOfWord;
};
TrieNode* getNewTrieNode()
{
    TrieNode* node=new TrieNode;
    node->endOfWord=false;
    return node;
}
TrieNode* root=getNewTrieNode();

//Insertion iterative
void insert_word(string word)
{
    TrieNode* curr=root;
    int n=word.length();
    for(int i=0;i<n;i++)
    {
        TrieNode* node=curr->child[word[i]];
        if(!node)
        {
            node=getNewTrieNode();
            curr->child[word[i]]=node;
        }
        curr=node;
    }
    curr->endOfWord=true;
}


//Insertion Recursive
void insert_word_recursive_util(TrieNode* root,string word,int id)
{
    //Base cases
    if(id==word.length())
    {
        root->endOfWord=true;
        return;
    }
    //Recursion
    char ch=word[id];
    TrieNode* node=root->child[ch];

    if(!node)
    {
        node=getNewTrieNode();
        root->child[ch]=node;
    }
    insert_word_recursive_util(node,word,id+1);
}
void insert_word_recursive(string word)
{
    insert_word_recursive_util(root,word,0);
}

//Search Iterative
bool search_word(string word)
{
    TrieNode* curr=root;
    for(int i=0;i<word.length();i++)
    {
        TrieNode* node=curr->child[word[i]];
        if(!node)
            return false;
        curr=node;
    }
    return true;
}
bool search_word_recursive_util(TrieNode* root,string word,int id)
{
    //Base case
    if(id==word.length())
        return root->endOfWord;
    //Recursion
    char ch=word[id];
    TrieNode* node=root->child[ch];
    if(!node)
        return false;
    return search_word_recursive_util(node,word,id+1);
}
bool search_word_recursive_(string word)
{
    return search_word_recursive_util(root,word,0);
}


//Delete word
//This is a recursive function, which returns true if parent should delete the mapping
bool delete_util(TrieNode* root,string word,int id)
{
    //base case
    if(id==word.length())
    {
        //Delete only if it is end of word
        if(!root->endOfWord)
            return false;
        //whether there are elements in the map or not, we have
        //to set the end of word as false
        root->endOfWord=false;
        //check if the map at that point is empty. If it is, then it needs to be deleted
        return root->child.size()==0;
    }
    char ch=word[id];
    TrieNode* node=root->child[ch];
    if(!node)
        return false;
    //recursion
    bool should_delete_curr=delete_util(node,word,id+1);

    if(should_delete_curr)
    {
        //Remove the char from the map
        root->child.erase(ch);
        //If no mappings left, return true
        return root->child.size()==0;
    }
    return false;
}
void delete_word(string word)
{
    delete_util(root,word,0);
}

void print(TrieNode* root)
{
    //Write the code for dfs here
}
int main()
{
    insert_word("aabb");
    cout<<search_word("aabb")<<" ";
    cout<<search_word("abab")<<" ";
    insert_word_recursive("abab");
    cout<<search_word_recursive_("abab")<<" ";
    cout<<search_word_recursive_("aabb")<<" ";
    insert_word("aaabbcd");
    insert_word("bbdcgfh");
    cout<<"\n";
    cout<<search_word_recursive_("abab")<<" ";
    cout<<search_word_recursive_("aabb")<<" ";
    cout<<search_word_recursive_("aaabbcd")<<" ";
    cout<<search_word_recursive_("bbdcgfh")<<" ";
    delete_word("abab");
    cout<<"\n";
    //print(root);
    //cout<<"\n";
    cout<<search_word_recursive_("abab")<<" ";
    cout<<search_word_recursive_("aabb")<<" ";
    cout<<search_word_recursive_("aaabbcd")<<" ";
    cout<<search_word_recursive_("bbdcgfh")<<" ";
    return 0;
}
