/*
*  File:        ptree-private.h
*  Description: Private functions for the PTree class
*  Date:        2022-03-06 03:30
*
*               DECLARE YOUR PTREE PRIVATE MEMBER FUNCTIONS HERE
*/

#ifndef _PTREE_PRIVATE_H_
#define _PTREE_PRIVATE_H_

/////////////////////////////////////////////////
// DEFINE YOUR PRIVATE MEMBER FUNCTIONS HERE
//
// Just write the function signatures.
//
// Example:
//
// Node* MyHelperFunction(int arg_a, bool arg_b);
//
/////////////////////////////////////////////////
int numLeavesHelper(Node* curr) const;
int sizeHelper(Node* curr) const;
void clearHelper(Node* curr);
Node* copyHelper(const Node* curr);
void renderHelper(Node* curr, PNG& img) const;
void pruneHelper(Node* curr, double tol);
bool isWithinTolerance(Node* curr, HSLAPixel avg, double tol);
void flipHorizontalHelper(Node* curr);
void flipVerticalHelper(Node* curr);
#endif