/*
 Name: Natnael Gebremariam
 Description: Create and navigate to find the
              longest zig zag path in a binary tree
 Input: Binary tree string 
 Output: Longest zig zag path
*/
#include "binTree.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std; 

binTree::binTree()
{
    root=nullptr; 
} 
binTree::~binTree()
{
    deallocateTree(root); 
}
void binTree::deallocateTree(binTreeNode* r)
{
    if(r == nullptr) return; 
    deallocateTree(r->left);
    deallocateTree(r->right); 
    delete r; 
    //return; 

}
void binTree::buildTree(std::vector<std::string> locations)
{
    //if empty return nothing, else build tree with new node from point zero 
    if(locations.empty()) return; 
    root= buildTree(new binTreeNode(), locations, 0); 
    
}
binTreeNode* binTree::buildTree(binTreeNode * r, std::vector<std::string> locations,
int index)
{
    //clear is _ or location is greater then array 
    if(index >= locations.size() || locations[index]=="_")
    {
        deallocateTree(r);
        return nullptr; 
    } 
    //assigne current location and build tree 
    r->location = locations[index];
    r->left=buildTree(new binTreeNode(), locations, index*2+1);
    r->right=buildTree(new binTreeNode(), locations, (index+1)*2);
    return r;   
}
std::vector<std::string> binTree::zigzag()
{
    //return a vector of nodes (longest path) 
    //if empty, return empty vector 
    if(root == nullptr)
    {
        std::vector<std::string>temp={};
        return temp; 
    }
    
    //temp path to call private function/ call left and right
    std::vector<std::string> temp_path;
    temp_path.push_back(root->location);   
    std::vector<std::string> leftP = zigzag(root->left, true, temp_path);
    std::vector<std::string> rightP = zigzag(root->right, false,temp_path); 
    
    //if right is larger, right is longest else left is
    if(rightP.size() > leftP.size()){
        return rightP; 
    } 
    return leftP; 

    

}
std::vector<std::string> binTree::zigzag(binTreeNode* r, bool childType, 
std::vector<std::string> path)
{
    std::vector<std::string> altPath;
    //if path is null, return empty path  
    if(r == nullptr)
    {
        return path;
    }
    //push pack the current location to path
    path.push_back(r->location); 
    //if left side of parent, search right side for a zigzag 
    //else search right side for longer zigzag and reset start location 
    if(childType)
    {
        path = zigzag(r->right, false, path);
        altPath = zigzag(r->left, true, {r->location}); 
    }
    //if right side of parent, search left side for a zigzag 
    //else search left side for longer zigzag and reset start location 
    if(!childType)
    {
        path = zigzag(r->left, true, path);
        altPath = zigzag(r->right, false, {r->location}); 
    }
    //if path size is greater return else altPath
    if(path.size() > altPath.size())
    {
        return path; 
    }
    return altPath; 
}
// std::vector<std::string> binTree::zigzag(binTreeNode* r, bool childType, 
// std::vector<std::string> path)
// {
//     std::vector<std::string> leftPath, rightPath;

//     if (r == nullptr) 
//     {
//         path = {}; 
//         return path;
//     }
    
//     //path from root and current location(node)
//     path.push_back(r->location);
    
//     // if no child node, return the path (backtracking ki)
//     if (r->left == nullptr && r->right == nullptr) {
        
        
//         return path;
//     }
    
//     // If left child found, look for zigzag paths in the right subtree
//     if(childType)
//     {
//         if(r->right != nullptr)
//         {
//             rightPath = zigzag(r->right, false, path);
//         }
//         if(r->left != nullptr)
//         { 
//             leftPath.push_back(r->location); 
//             leftPath = zigzag(r->left, true, leftPath); 
//         }
//     }

//     if(!childType)
//     {
//         if(r->left != nullptr)
//         {
//             leftPath = zigzag(r->left, true, path);
//         }
//         if(r->right != nullptr)
//         { 
           
//             rightPath.push_back(r->location);    
//             rightPath = zigzag(r->right, false, rightPath); 
//         }
//     }

//     // Return the longer path
//     if(leftPath.size() > rightPath.size())
//     {
//         return leftPath; 
//     }
    
//     return rightPath; 
   
// }

