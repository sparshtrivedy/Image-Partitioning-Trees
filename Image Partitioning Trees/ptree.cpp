/*
*  File:        ptree.cpp
*  Description: Implementation of a partitioning tree class for CPSC 221 PA3
*  Date:        2022-03-03 01:53
*
*               ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS TO THE BOTTOM OF THIS FILE
*/

#include "ptree.h"
#include "hue_utils.h" // useful functions for calculating hue averages

using namespace cs221util;
using namespace std;

// The following definition may be convenient, but is not necessary to use
typedef pair<unsigned int, unsigned int> pairUI;

/////////////////////////////////
// PTree private member functions
/////////////////////////////////

/*
*  Destroys all dynamically allocated memory associated with the current PTree object.
*  You may want to add a recursive helper function for this!
*  POST: all nodes allocated into the heap have been released.
*/
void PTree::Clear() {
  // add your implementation below
  clearHelper(root);
}

void PTree::clearHelper(Node* curr){
  if (curr == NULL){
    return;
  } else {
    clearHelper(curr->A);
    clearHelper(curr->B);
    delete curr;
  }
}


/*
*  Copies the parameter other PTree into the current PTree.
*  Does not free any memory. Should be called by copy constructor and operator=.
*  You may want a recursive helper function for this!
*  PARAM: other - the PTree which will be copied
*  PRE:   There is no dynamic memory associated with this PTree.
*  POST:  This PTree is a physically separate copy of the other PTree.
*/
void PTree::Copy(const PTree& other) {
  //add your implementation below
  root = copyHelper(other.root);
}

Node* PTree::copyHelper(const Node* curr) {
  if (curr == NULL) {
    return NULL;
  }
  Node* newNode = new Node(curr->upperleft, curr->width, curr->height, curr->avg, NULL, NULL);
  newNode->A = copyHelper(curr->A);
  newNode->B = copyHelper(curr->B);
  return newNode;
}

/*
*  Private helper function for the constructor. Recursively builds the tree
*  according to the specification of the constructor.
*  You *may* change this if you like, but we have provided here what we
*  believe will be sufficient to use as-is.
*  PARAM:  im - full reference image used for construction
*  PARAM:  ul - upper-left image coordinate of the currently building Node's image region
*  PARAM:  w - width of the currently building Node's image region
*  PARAM:  h - height of the currently building Node's image region
*  RETURN: pointer to the fully constructed Node
*/
Node* PTree::BuildNode(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h) {
  // replace the line below with your implementation
  Node* currNode = new Node(ul, w, h, HSLAPixel(0,0,0), NULL, NULL);
  if (w == 1 && h == 1) {
    currNode->A = NULL;
    currNode->B = NULL;
    currNode->avg = *im.getPixel(ul.first, ul.second);
    return currNode;
  }
  if (w < h) {
    if (h%2 == 0) {
      double hue_x = 0;
      double hue_y = 0;
      double sat = 0;
      double lum = 0;

      for (int i=ul.first; i<ul.first+w; i++) {
        for (int j=ul.second; j<ul.second+h; j++) {
          hue_x += Deg2X((*im.getPixel(i,j)).h);
          hue_y += Deg2Y((*im.getPixel(i,j)).h);
          sat += (*im.getPixel(i,j)).s;
          lum += (*im.getPixel(i,j)).l;
        }
      }

      hue_x = hue_x/(w*h);
      hue_y = hue_y/(w*h);
      sat = sat/(w*h);
      lum = lum/(w*h);

      currNode->avg.h = XY2Deg(hue_x, hue_y);
      currNode->avg.s = sat;
      currNode->avg.l = lum;

      currNode->A = BuildNode(im, make_pair(ul.first, ul.second), w, h/2);
      currNode->B = BuildNode(im, make_pair(ul.first, ul.second + h/2), w, h/2);

      return currNode;
    } else {
      double hue_x = 0;
      double hue_y = 0;
      double sat = 0;
      double lum = 0;

      for (int i=ul.first; i<ul.first+w; i++) {
        for (int j=ul.second; j<ul.second+h; j++) {
          hue_x += Deg2X((*im.getPixel(i,j)).h);
          hue_y += Deg2Y((*im.getPixel(i,j)).h);
          sat += (*im.getPixel(i,j)).s;
          lum += (*im.getPixel(i,j)).l;
        }
      }

      hue_x = hue_x/(w*h);
      hue_y = hue_y/(w*h);
      sat = sat/(w*h);
      lum = lum/(w*h);

      currNode->avg.h = XY2Deg(hue_x, hue_y);
      currNode->avg.s = sat;
      currNode->avg.l = lum;

      currNode->A = BuildNode(im, make_pair(ul.first, ul.second), w, h/2);
      currNode->B = BuildNode(im, make_pair(ul.first, ul.second + h/2), w, h/2 + 1);

      return currNode;
    }
  } else {
    if (w%2 == 0) {
      double hue_x = 0;
      double hue_y = 0;
      double sat = 0;
      double lum = 0;

      for (int i=ul.first; i<ul.first+w; i++) {
        for (int j=ul.second; j<ul.second+h; j++) {
          hue_x += Deg2X((*im.getPixel(i,j)).h);
          hue_y += Deg2Y((*im.getPixel(i,j)).h);
          sat += (*im.getPixel(i,j)).s;
          lum += (*im.getPixel(i,j)).l;
        }
      }

      hue_x = hue_x/(w*h);
      hue_y = hue_y/(w*h);
      sat = sat/(w*h);
      lum = lum/(w*h);

      currNode->avg.h = XY2Deg(hue_x, hue_y);
      currNode->avg.s = sat;
      currNode->avg.l = lum;

      currNode->A = BuildNode(im, make_pair(ul.first, ul.second), w/2, h);
      currNode->B = BuildNode(im, make_pair(ul.first + w/2, ul.second), w/2, h);

      return currNode;
    } else {
      double hue_x = 0;
      double hue_y = 0;
      double sat = 0;
      double lum = 0;

      for (int i=ul.first; i<ul.first+w; i++) {
        for (int j=ul.second; j<ul.second+h; j++) {
          hue_x += Deg2X((*im.getPixel(i,j)).h);
          hue_y += Deg2Y((*im.getPixel(i,j)).h);
          sat += (*im.getPixel(i,j)).s;
          lum += (*im.getPixel(i,j)).l;
        }
      }

      hue_x = hue_x/(w*h);
      hue_y = hue_y/(w*h);
      sat = sat/(w*h);
      lum = lum/(w*h);

      currNode->avg.h = XY2Deg(hue_x, hue_y);
      currNode->avg.s = sat;
      currNode->avg.l = lum;

      currNode->A = BuildNode(im, make_pair(ul.first, ul.second), w/2, h);
      currNode->B = BuildNode(im, make_pair(ul.first + w/2, ul.second), w/2 + 1, h);

      return currNode;
    }
  }
}

////////////////////////////////
// PTree public member functions
////////////////////////////////

/*
*  Constructor that builds the PTree using the provided PNG.
*
*  The PTree represents the sub-image (actually the entire image) from (0,0) to (w-1, h-1) where
*  w-1 and h-1 are the largest valid image coordinates of the original PNG.
*  Each node corresponds to a rectangle of pixels in the original PNG, represented by
*  an (x,y) pair for the upper-left corner of the rectangle, and two unsigned integers for the
*  number of pixels on the width and height dimensions of the rectangular sub-image region the
*  node defines.
*
*  A node's two children correspond to a partition of the node's rectangular region into two
*  equal (or approximately equal) size regions which are either tiled horizontally or vertically.
*
*  If the rectangular region of a node is taller than it is wide, then its two children will divide
*  the region into vertically-tiled sub-regions of equal height:
*  +-------+
*  |   A   |
*  |       |
*  +-------+
*  |   B   |
*  |       |
*  +-------+
*
*  If the rectangular region of a node is wider than it is tall, OR if the region is exactly square,
*  then its two children will divide the region into horizontally-tiled sub-regions of equal width:
*  +-------+-------+
*  |   A   |   B   |
*  |       |       |
*  +-------+-------+
*
*  If any region cannot be divided exactly evenly (e.g. a horizontal division of odd width), then
*  child B will receive the larger half of the two subregions.
*
*  When the tree is fully constructed, each leaf corresponds to a single pixel in the PNG image.
* 
*  For the average colour, this MUST be computed separately over the node's rectangular region.
*  Do NOT simply compute this as a weighted average of the children's averages.
*  The functions defined in hue_utils.h and implemented in hue_utils.cpp will be very useful.
*  Computing the average over many overlapping rectangular regions sounds like it will be
*  inefficient, but as an exercise in theory, think about the asymptotic upper bound on the
*  number of times any given pixel is included in an average calculation.
* 
*  PARAM: im - reference image which will provide pixel data for the constructed tree's leaves
*  POST:  The newly constructed tree contains the PNG's pixel data in each leaf node.
*/
PTree::PTree(PNG& im) {
  // add your implementation below
  int width = im.width();
  int height = im.height();
  pair<int, int> up = make_pair(0, 0);
  root = BuildNode(im, up, width, height);
}

/*
*  Copy constructor
*  Builds a new tree as a copy of another tree.
*
*  PARAM: other - an existing PTree to be copied
*  POST:  This tree is constructed as a physically separate copy of other tree.
*/
PTree::PTree(const PTree& other) {
  // add your implementation below
  Copy(other);
}

/*
*  Assignment operator
*  Rebuilds this tree as a copy of another tree.
*
*  PARAM: other - an existing PTree to be copied
*  POST:  If other is a physically different tree in memory, all pre-existing dynamic
*           memory in this tree is deallocated and this tree is reconstructed as a
*           physically separate copy of other tree.
*         Otherwise, there is no change to this tree.
*/
PTree& PTree::operator=(const PTree& other) {
  //add your implementation below
  PTree ptr = other;
  if (this != &other) {
    Clear();
    root = ptr.root;
    ptr.root = NULL;
  }
  return *this;
}

/*
*  Destructor
*  Deallocates all dynamic memory associated with the tree and destroys this PTree object.
*/
PTree::~PTree() {
  // add your implementation below
  Clear();
}

/*
*  Traverses the tree and puts the leaf nodes' color data into the nodes'
*  defined image regions on the output PNG.
*  For non-pruned trees, each leaf node corresponds to a single pixel that will be coloured.
*  For pruned trees, each leaf node may cover a larger rectangular region that will be
*  entirely coloured using the node's average colour attribute.
*
*  You may want to add a recursive helper function for this!
*
*  RETURN: A PNG image of appropriate dimensions and coloured using the tree's leaf node colour data
*/
PNG PTree::Render() const {
  // replace the line below with your implementation
  PNG img = PNG(root->width, root->height);
  renderHelper(root, img);
  return img;
}

void PTree::renderHelper(Node* curr, PNG& img) const{
  if (curr->A == NULL && curr->B == NULL){
    for(int i = curr->upperleft.first; i < curr->upperleft.first+curr->width; i++){
      for(int j = curr->upperleft.second; j < curr->upperleft.second+curr->height; j++){
        *img.getPixel(i,j) = curr->avg;
      }
    }
  }
  else{
    renderHelper(curr->A, img);
    renderHelper(curr->B, img); 
  }
}

/*
*  Trims subtrees as high as possible in the tree. A subtree is pruned
*  (its children are cleared/deallocated) if ALL of its leaves have colour
*  within tolerance of the subtree root's average colour.
*  Pruning criteria should be evaluated on the original tree, and never on a pruned
*  tree (i.e. we expect that Prune would be called on any tree at most once).
*  When processing a subtree, you should determine if the subtree should be pruned,
*  and prune it if possible before determining if it has subtrees that can be pruned.
* 
*  You may want to add (a) recursive helper function(s) for this!
*
*  PRE:  This tree has not been previously pruned (and is not copied/assigned from a tree that has been pruned)
*  POST: Any subtrees (as close to the root as possible) whose leaves all have colour
*        within tolerance from the subtree's root colour will have their children deallocated;
*        Each pruned subtree's root becomes a leaf node.
*/
void PTree::Prune(double tolerance) {
  // add your implementation below
  pruneHelper(root,tolerance);
}

void PTree::pruneHelper(Node* curr, double tol) {
  if (curr == NULL || (curr->A == NULL && curr->B == NULL) ) return;
  if (isWithinTolerance(curr, curr->avg, tol)) {
    clearHelper(curr->A);
    clearHelper(curr->B);
    curr->A = NULL;
    curr->B = NULL;
  } else {
    pruneHelper(curr->A, tol);
    pruneHelper(curr->B, tol);
  }
}


bool PTree::isWithinTolerance(Node* curr, HSLAPixel avg, double tol) {
  if (curr->A == NULL && curr->B == NULL) {
    return (avg.dist(curr->avg) <= tol);
  } else {
    return (isWithinTolerance(curr->A, avg, tol) && isWithinTolerance(curr->B, avg, tol));
  }
}


/*
*  Returns the total number of nodes in the tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*/
int PTree::Size() const {
  // replace the line below with your implementation
  int n = sizeHelper(root);
  return n;
}

int PTree::sizeHelper(Node* curr) const {
  int num=1;

  if (curr==NULL){
    return 0;
  }

  else
  {
    num += sizeHelper(curr->A);
    num += sizeHelper(curr->B);
    return num;
  }
}

/*
*  Returns the total number of leaf nodes in the tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*/
int PTree::NumLeaves() const {
  // replace the line below with your implementation
  int n = numLeavesHelper(root);
  return n;
}

int PTree::numLeavesHelper(Node* curr) const {
  if (curr == NULL) {
    return 0;
  }
  if (curr->A == NULL && curr->B == NULL) {
    return 1;
  } else {
    return numLeavesHelper(curr->A) + numLeavesHelper(curr->B);
  }
}

/*
*  Rearranges the nodes in the tree, such that a rendered PNG will be flipped horizontally
*  (i.e. mirrored over a vertical axis).
*  This can be achieved by manipulation of the nodes' member attribute(s).
*  Note that this may possibly be executed on a pruned tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*
*  POST: Tree has been modified so that a rendered PNG will be flipped horizontally.
*/
void PTree::FlipHorizontal() {
  // add your implementation below
  flipHorizontalHelper(root);
}

void PTree::flipHorizontalHelper(Node* curr) {
  if (curr->A == NULL && curr->B == NULL) {
    curr->upperleft.first = root->width - curr->upperleft.first - 1;
  } else {
    flipHorizontalHelper(curr->A);
    flipHorizontalHelper(curr->B);
  }
}

/*
*  Like the function above, rearranges the nodes in the tree, such that a rendered PNG
*  will be flipped vertically (i.e. mirrored over a horizontal axis).
*  This can be achieved by manipulation of the nodes' member attribute(s).
*  Note that this may possibly be executed on a pruned tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*
*  POST: Tree has been modified so that a rendered PNG will be flipped vertically.
*/
void PTree::FlipVertical() {
  // add your implementation below
  flipVerticalHelper(root);
}

void PTree::flipVerticalHelper(Node* curr) {
  if (curr->A == NULL && curr->B == NULL) {
    curr->upperleft.second = root->height - curr->upperleft.second - 1;
  } else {
    flipVerticalHelper(curr->A);
    flipVerticalHelper(curr->B);
  }
}

/*
    *  Provides access to the root of the tree.
    *  Dangerous in practice! This is only used for testing.
    */
Node* PTree::GetRoot() {
  return root;
}

//////////////////////////////////////////////
// PERSONALLY DEFINED PRIVATE MEMBER FUNCTIONS
//////////////////////////////////////////////

