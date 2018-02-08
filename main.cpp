#include <bits/stdc++.h>

using namespace std;

typedef struct SplayTree SplayTree;
typedef SplayTree *pSplayTree;

typedef struct SplayNode SplayNode;
typedef SplayNode *pSplayNode;

struct SplayTree {
	pSplayNode root;

	// private function
	void (*leftRotate)(pSplayTree splaytree, pSplayNode p);
	void (*rightRotate)(pSplayTree splaytree, pSplayNode p);
	void (*splay)(pSplayTree splaytree, pSplayNode p);
	
	// public function
	pSplayNode (*find)(pSplayTree splaytree, int val);
	pSplayNode (*insert)(pSplayTree splaytree, int val);
	pSplayNode (*max)(pSplayTree splaytree);
	pSplayNode (*min)(pSplayTree splaytree);
	pSplayNode (*prev)(pSplayTree splaytree);
	pSplayNode (*next)(pSplayTree splaytree);
	pSplayNode (*join)(pSplayTree splaytree1, pSplayTree splaytree2);
	pSplayNode (*deleteNode)(pSplayTree splaytree, pSplayNode p);
	pSplayNode (*split)(pSplayTree splaytree, int val, pSplayTree splaytree1, pSplayTree splaytree2);
};

struct SplayNode {
	int val;
	pSplayNode father;
	pSplayNode left, right;
};

static void splaytree_leftRotate(pSplayTree splaytree, pSplayNode p)
{
	pSplayNode father = p->father;
	p->father = p->father->father;

	if (p->father != NULL)
		father == p->father->left ? p->father->left = p : p->father->right = p;
	else
		splaytree->root = p;
	if (p->right != NULL)
		p->right->father = father;
	father->father = p;
	father->right = p->right;
	p->right = father;
}

static void splaytree_rightRotate(pSplayTree splaytree, pSplayNode p)
{
	pSplayNode father = p->father;
	p->father = p->father->father;

	if (p->father != NULL)
		father == p->father->left ? p->father->left = p : p->father->right = p;
	else
		splaytree->root = p;
	if (p->left != NULL)
		p->left->father = father;
	father->father = p;
	father->left = p->left;
	p->left = father;
}

static void splaytree_splay(pSplayTree splaytree, pSplayNode p)
{
	for (pSplayNode father = p->father, theRootFaher = father;
			p->father != theRootFaher; father = p->father) {

		if (father->father == NULL) {
			father->left == p ? splaytree_leftRotate(splaytree, p) :
								splaytree_rightRotate(splaytree, p);
		} else {
			if (p->father->left == p && father->father->left == father)
				splaytree_leftRotate(splaytree, father),
				splaytree_leftRotate(splaytree, p);
			else if (p->father->left == p && father->father->right == father)
				splaytree_leftRotate(splaytree, p),
				splaytree_rightRotate(splaytree, p);
			else if (p->father->right == p && father->father->left == father)
				splaytree_rightRotate(splaytree, p),
				splaytree_leftRotate(splaytree, p);
			else
				splaytree_rightRotate(splaytree, father),
				splaytree_rightRotate(splaytree, p);
		}
	}
	splaytree->root = p;
}

static pSplayNode find(pSplayTree splaytree, int val)
{
	// if (splaytree->root == NULL)
	// 	return NULL;
	// SplayTree leftTree, rightTree;
	// INIT_SPLAYTREE(&leftTree, splaytree->root->left);
	// INIT_SPLAYTREE(&rightTree, splaytree->root->right);
	// return splaytree->root->val > val ? find(leftTree, val) : find(rightTree, val);
	pSplayNode ret = splaytree->root;
	for (; ret != NULL && ret->val != val; )
		ret = ret->val > val ? ret->left : ret->right;
	return ret;
		
}

static pSplayNode insert(pSplayTree splaytree, int val)
{
	pSplayNode ret = (pSplayNode)malloc(sizeof(SplayNode));
	INIT_SPLAYNODE(ret, val, NULL, NULL, NULL);
	if (splaytree->root == NULL) {
		splaytree->root = ret;
		return ret;	
	}
	for (pSplayNode it = splaytree->root; it != NULL; ) {
		if (it->val > val) {
			if (it->left == NULL) {
				it->left = ret;
				ret->father = it;
			}
			it = it->left;
		} else {
			if (it->right == NULL) {
				it->right = ret;
				ret->father = it;
			}
			it = it->right;
		}
	}
	return ret;
}

static pSplayNode prev(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	if (splaytree->root == NULL)	
		return ret;
	for (pSplayNode it = splaytree->root->left; it != NULL; ret = it, it = it->right) {}
	return ret;
}

static pSplayNode next(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	if (splaytree->root == NULL)	
		return ret;
	for (pSplayNode it = splaytree->root->right; it != NULL; ret = it, it = it->left) {}
	return ret;
}

static pSplayNode max(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	for (pSplayNode it = splaytree->root; it != NULL; ret = it, it = it->right) {}
	return ret;
}

static pSplayNode min(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	for (pSplayNode it = splaytree->root; it != NULL; ret = it, it = it->left) {}
	return ret;
}


static pSplayTree join(pSplayTree splaytree1, pSplayTree splaytree2)
{
	splaytree_splay(splaytree1, splaytree_max(spalytree1));
	splaytree1->root->right = splaytree2->root;
	splaytree2->root->fater = splaytree1->root;
	return splaytree1;
}

static pSplayNode deleteNode(pSplayTree splaytree, pSplayNode p)
{
	splaytree_splay(splaytree, p); 

}

#define INIT_SPLAYTREE(p, root)							\
	do {									\
		(p)->root = root						\
		(p)->leftRotate = splaytree_leftRotate				\
		(p)->rightRotate = splaytree_rightRotate			\
		(p)->splay = splaytree_splay					\
		(p)->find = splaytree_find					\
		(p)->insert = splaytree_insert					\
		(p)->max = splaytree_max					\
		(p)->min = splaytree_min					\
		(p)->prev = splaytree_prev					\
		(p)->next = splaytree_next					\
		(p)->join = splaytree_join					\
		(p)->deleteNode = splaytree_deleteNode				\
		(p)->split = splaytree_split					\
	}while(0)

#define INIT_SPLAYNODE(p, val, father, left, right)	    			\
	do {									\
		(p)->val = (val);						\
		(p)->father = (father);						\
		(p)->left = (left);						\
		(p)->right = (right);						\
	}while(0)

int main()
{

	return 0;
}
