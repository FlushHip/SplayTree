#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	pSplayTree (*join)(pSplayTree splaytree1, pSplayTree splaytree2);
	pSplayTree (*deleteNode)(pSplayTree splaytree, pSplayNode p);
	void (*split)(pSplayTree splaytree, int val, pSplayTree *ptr_splaytree1, pSplayTree *ptr_splaytree2);
};

struct SplayNode {
	int val;
	pSplayNode father;
	pSplayNode left, right;
};

static void splaytree_leftRotate(pSplayTree splaytree, pSplayNode p);
static void splaytree_rightRotate(pSplayTree splaytree, pSplayNode p);
static void splaytree_splay(pSplayTree splaytree, pSplayNode p);
static pSplayNode splaytree_find(pSplayTree splaytree, int val);
static pSplayNode splaytree_insert(pSplayTree splaytree, int val);
static pSplayNode splaytree_prev(pSplayTree splaytree);
static pSplayNode splaytree_next(pSplayTree splaytree);
static pSplayNode splaytree_max(pSplayTree splaytree);
static pSplayNode splaytree_min(pSplayTree splaytree);
static pSplayTree splaytree_join(pSplayTree splaytree1, pSplayTree splaytree2);
static pSplayTree splaytree_deleteNode(pSplayTree splaytree, pSplayNode p);
static void splaytree_split(pSplayTree splaytree, int val, pSplayTree *ptr_splaytree1, pSplayTree *ptr_splaytree2);

#define INIT_SPLAYTREE(p, _root)						\
	do {									\
		(p)->root = _root;						\
		(p)->leftRotate = &splaytree_leftRotate;			\
		(p)->rightRotate = &splaytree_rightRotate;			\
		(p)->splay = &splaytree_splay;					\
		(p)->find = &splaytree_find;					\
		(p)->insert = &splaytree_insert;				\
		(p)->max = &splaytree_max;					\
		(p)->min = &splaytree_min;					\
		(p)->prev = &splaytree_prev;					\
		(p)->next = &splaytree_next;					\
		(p)->join = &splaytree_join;					\
		(p)->deleteNode = &splaytree_deleteNode;			\
		(p)->split = &splaytree_split;					\
	}while(0)

#define INIT_SPLAYNODE(p, _val, _father, _left, _right)	    			\
	do {									\
		(p)->val = (_val);						\
		(p)->father = (_father);					\
		(p)->left = (_left);						\
		(p)->right = (_right);						\
	}while(0)

static void splaytree_leftRotate(pSplayTree splaytree, pSplayNode p)
{
	pSplayNode father = p->father;
	p->father = p->father->father;

	if (p->father != NULL)
		father == p->father->left ? (p->father->left = p) : (p->father->right = p);
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
		father == p->father->left ? (p->father->left = p) : (p->father->right = p);
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

static pSplayNode splaytree_find(pSplayTree splaytree, int val)
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

static pSplayNode splaytree_insert(pSplayTree splaytree, int val)
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
				break;
			}
			it = it->left;
		} else {
			if (it->right == NULL) {
				it->right = ret;
				ret->father = it;
				break;
			}
			it = it->right;
		}
	}
	return ret;
}

static pSplayNode splaytree_prev(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	if (splaytree->root == NULL)	
		return ret;
	for (pSplayNode it = splaytree->root->left; it != NULL; ret = it, it = it->right) {}
	return ret;
}

static pSplayNode splaytree_next(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	if (splaytree->root == NULL)	
		return ret;
	for (pSplayNode it = splaytree->root->right; it != NULL; ret = it, it = it->left) {}
	return ret;
}

static pSplayNode splaytree_max(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	for (pSplayNode it = splaytree->root; it != NULL; ret = it, it = it->right) {}
	return ret;
}

static pSplayNode splaytree_min(pSplayTree splaytree)
{
	pSplayNode ret = NULL;
	for (pSplayNode it = splaytree->root; it != NULL; ret = it, it = it->left) {}
	return ret;
}


static pSplayTree splaytree_join(pSplayTree splaytree1, pSplayTree splaytree2)
{
	splaytree_splay(splaytree1, splaytree_max(splaytree1));
	splaytree1->root->right = splaytree2->root;
	splaytree2->root->father = splaytree1->root;
	return splaytree1;
}

static pSplayTree splaytree_deleteNode(pSplayTree splaytree, pSplayNode p)
{
	SplayTree rightTree, leftTree;
	splaytree_splay(splaytree, p); 
	// leftTree = (pSplayTree)splaytree->root->left;
	// rightTree = (pSplayTree)splaytree->root->right;
	INIT_SPLAYTREE(&leftTree, splaytree->root->left);
	INIT_SPLAYTREE(&rightTree, splaytree->root->right);
	free(p);

	if (rightTree.root != NULL)
		rightTree.root->father = NULL;
	if (leftTree.root != NULL)
		leftTree.root->father = NULL;
	if (leftTree.root == NULL)
		return splaytree->root = leftTree.root, splaytree;
	if (rightTree.root == NULL)
		return splaytree->root = rightTree.root, splaytree;
	return splaytree->root = leftTree.root, splaytree_join(splaytree, &rightTree);
}

static void splaytree_split(pSplayTree splaytree, int val, pSplayTree *ptr_splaytree1, pSplayTree *ptr_splaytree2)
{
	*ptr_splaytree1 = (pSplayTree)malloc(sizeof(SplayTree));
	*ptr_splaytree2 = (pSplayTree)malloc(sizeof(SplayTree));
	INIT_SPLAYTREE(*ptr_splaytree1, NULL);
	INIT_SPLAYTREE(*ptr_splaytree2, NULL);
	splaytree_splay(splaytree, splaytree_find(splaytree, val));
	(*ptr_splaytree1)->root = splaytree->root->left;
	(*ptr_splaytree2)->root = splaytree->root->right;
	(*ptr_splaytree1)->root->father = (*ptr_splaytree2)->root->father = NULL;
	free(splaytree);
}

void midVisit(pSplayTree splaytree, pSplayNode p)
{
	if (p == NULL)	
		return ;
	midVisit(splaytree, p->left);
	printf("%d\n", p->val);
	midVisit(splaytree, p->right);
}

int main(int argc, char *argv[])
{
	pSplayTree splaytree = (pSplayTree)malloc(sizeof(SplayTree));
	INIT_SPLAYTREE(splaytree, NULL);

	for (int i = 1; i < argc; i++) {
		int num = atoi(argv[i]);
		splaytree->insert(splaytree, num);
	}
	midVisit(splaytree, splaytree->root);
	splaytree->deleteNode(splaytree, splaytree->find(splaytree, 1));
	midVisit(splaytree, splaytree->root);
	return 0;
}
