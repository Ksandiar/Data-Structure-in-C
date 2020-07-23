#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
#define MALLOC(p,s) if (!((p) = malloc(s))) {fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE); }
#define FALSE 0
#define TRUE 1

typedef enum { head, entry }tagfield;
typedef struct matrixNode *matrixPointer;
typedef struct entrNnode {
	int row;
	int col;
	int value;
} entryNode;
typedef struct matrixNode {
	matrixPointer down;
	matrixPointer right;
	tagfield tag;
	union {
		matrixPointer next;
		entryNode entry;
	} u;
} matrixNode;
matrixPointer m1 = NULL, m2 = NULL, m3 = NULL;

matrixPointer newNode(void);
matrixPointer mread(void);
void mwrite(matrixPointer);
void merase(matrixPointer *);
matrixPointer madd(matrixPointer, matrixPointer);
matrixPointer mtranspose(matrixPointer);
matrixPointer mmult(matrixPointer, matrixPointer);
void startmenu(void);
int menu, tmenu;
int main(void) {
	printf("                                    자료구조 과제2\n");
	printf("                                                                       201510059\n");
	printf("                                                                 통계학과 윤창원\n");
	printf("---------------------------------------------------------------------------------\n");
	startmenu();
	return 0;
}

void startmenu(void) {
	printf("\n연산을 정해주세요.\n");
	printf("1.행렬 생성 2. 행렬 출력 3. 행렬 삭제 4. 행렬 합 5. 행렬 곱 6. 전치행렬화 7. 종료 예) 3 \n");
	scanf("%d", &menu);
	fflush(stdin);
	switch (menu) {
	case 1: 
		if (m1 == 0 && m2 == 0) {
			printf("첫번째 행렬을 생성합니다.\n");
			m1 = mread();
		}
		else if (m1 != 0 && m2 == 0) {
			printf("두번째 행렬을 생성합니다.\n");
			m2 = mread();
		}
		else printf("이미 행렬이 존재합니다.\n");
		startmenu();
		break;
	case 2:
		if (m1 == 0 && m2 == 0) {
			printf("행렬이 존재하지 않습니다.\n");
		}
		else if (m1 != 0 && m2 == 0) {
			printf("첫번째 행렬을 출력합니다.\n");
			mwrite(m1);
		}
		else {
			printf("모든 행렬을 출력합니다.\n");
			mwrite(m1);
			mwrite(m2);
		}
		startmenu();
		break;
	case 3: if (m1 == 0 && m2 == 0) {
		printf("행렬이 존재하지 않습니다.\n");
	}
		else if (m1 != 0 && m2 == 0) {
		printf("첫번째 행렬을 삭제합니다.\n");
		merase(&m1);
	}
		else {
		printf("모든 행렬을 삭제합니다.\n");
		merase(&m1);
		merase(&m2);
	}
		startmenu();
	break;
	case 4: if (m1 != 0 && m2 != 0) {
		m3 = madd(m1, m2);
		mwrite(m3);
		exit(0);
		}
		else {
		printf("행렬이 부족합니다.\n");
		startmenu();
	}
		break;
	case 5: if (m1 != 0 && m2 != 0) {
		m3 = mmult(m1, m2);
		mwrite(m3);
		exit(0);
		}
		else {
		printf("행렬이 부족합니다.\n");
		startmenu();
	}
		break;
	case 6: if (m1 == 0 && m2 == 0) {
		printf("행렬이 존재하지 않습니다.\n");
	}
		else if (m1 != 0 && m2 == 0) {
		m3 = mtranspose(m1);
		mwrite(m3);
		exit(0);
	}
		else {
		printf("전치행렬화는 행렬이 하나만 생성되어 있을 때 가능합니다.");
	}
		startmenu();
	case 7: exit(0);
	}	
}
matrixPointer newNode(void)
{
	matrixPointer temp;
	MALLOC(temp,sizeof(*temp));
	return temp;
}

matrixPointer mread(void) {
	matrixPointer hdnode[MAX_SIZE];
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrixPointer temp, last, node;

	printf("행과 열 그리고 0이 아닌 값의 개수를 입력해주세요. 예)2/2/4\n");
	scanf("%d/%d/%d", &numRows, &numCols, &numTerms);
	fflush(stdin);
	numHeads = (numCols > numRows)? numCols : numRows;
	node = newNode(); node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;
	node->u.entry.value = numTerms;
	node->down = NULL;

	if (!numHeads) node->right = node;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = newNode();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];
		for (i = 0; i < numTerms; i++) {
			printf("행과열 그리고 값을 입력하십시오.(행 순서대로 입력) 예)1/1/4\n");
			scanf("%d/%d/%d", &row, &col, &value);
			fflush(stdin);
			if (row > currentRow) {
				last->right = hdnode[currentRow];
				currentRow = row; last = hdnode[row];
			}
			MALLOC(temp, sizeof(*temp));
			temp->tag = entry; temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[currentRow];
		for (i = 0; i < numCols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHeads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHeads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}

void mwrite(matrixPointer node) {
	int i;
	matrixPointer temp, head = node->right;
	printf("\n 행의 수 = %d, 열의 수 = %d \n", node->u.entry.row, node->u.entry.col);
	printf("행렬 : \n\n");
	for (i = 0; i < node->u.entry.row; i++) {
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n", temp->u.entry.row,temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	}
}

void merase(matrixPointer *node) {
	matrixPointer x, y, head = (*node)->right;
	int i;
	for (i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}
	y = head;
	while (y != *node) {
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;
}

matrixPointer madd(matrixPointer m1, matrixPointer m2)
{
	int i, m3Heads, currentRow;
	matrixPointer temp1, temp2, temp3, m3 = NULL;
	matrixPointer head1, head2, node, temp = NULL;
	matrixPointer m3Hdnode[MAX_SIZE], last;
	head1 = m1->right; head2 = m2->right;
	/* m3: 합행렬의 최고 node */
	if (m1->u.entry.col != m2->u.entry.col ||
		m1->u.entry.row != m2->u.entry.row)
	{
		printf("두 행의 크기가 다릅니다.₩n");
		exit(0);
	}
	m3 = newNode();
	m3->tag = entry;
	m3->u.entry.row = m1->u.entry.row;
	m3->u.entry.col = m1->u.entry.col;
	m3Heads = (m3->u.entry.col > m3->u.entry.row) ?
		m3->u.entry.col : m3->u.entry.row;
	if (!m3Heads)
		m3->right = m3;
	else
	{
		for (i = 0; i < m3Heads; i++)
		{
			temp3 = newNode();
			m3Hdnode[i] = temp3;
			m3Hdnode[i]->tag = head;
			m3Hdnode[i]->right = temp3;
			m3Hdnode[i]->u.next = temp3;
		}
		currentRow = 0;
		last = m3Hdnode[0];
		temp1 = m1->right;
		temp2 = m2->right;
		while (!(temp1 == m1 && temp2 == m2))
		{
			if (temp1->tag == head)
			{
				if (temp1->right == temp1)
				{
					temp1 = temp1->u.next; /* 다음 행으로 이동 */
					continue;
				}
				temp1 = temp1->right; /* 행 안에서 다음 열로 이동 */
			}
			if (temp2->tag == head)
			{
				if (temp2->right == temp2)
				{
					temp2 = temp2->u.next; /* 다음 행으로 이동 */
					continue;
				}
				temp2 = temp2->right; /* 행 안에서 다음 열로 이동 */
			}
			switch (COMPARE(temp1->u.entry.row, temp2->u.entry.row)) /*행과 열이 일치하는지 검사*/
			{
			case -1:
				temp = temp1;
				temp1 = temp1->right;
				break;
			case 0:
				switch (COMPARE(temp1->u.entry.col, temp2->u.entry.col))
				{ 
				case -1:
					temp = temp1;
					temp1 = temp1->right;
					break;
				case 0:
					temp = NULL;
					if (temp1->u.entry.row > currentRow)
					{
						last->right = m3Hdnode[currentRow];
						currentRow = temp1->u.entry.row;
						last = m3Hdnode[temp1->u.entry.row];
					}
					node = newNode();
					node->tag = entry;
					node->u.entry.row = temp1->u.entry.row;
					node->u.entry.col = temp1->u.entry.col;
					node->u.entry.value = temp1->u.entry.value + temp2->u.entry.value;
					last->right = node;
					last = node;
					m3Hdnode[temp1->u.entry.col]->u.next->down = node;
					m3Hdnode[temp1->u.entry.col]->u.next = node;
					temp1 = temp1->right;
					temp2 = temp2->right;
					break;
				case 1:
					temp = temp2;
					temp2 = temp2->right;
					break;
				}
				break;
			case 1:
				temp = temp2;
				temp2 = temp2->right;
				break;
			}
			if (temp != NULL) /*남은 항 삽입*/
			{
				if (temp->u.entry.row > currentRow)
				{
					last->right = m3Hdnode[currentRow];
					currentRow = temp->u.entry.row;
					last = m3Hdnode[temp->u.entry.row];
				}
				node = newNode();
				node->tag = entry;
				node->u.entry.row = temp->u.entry.row;
				node->u.entry.col = temp->u.entry.col;
				node->u.entry.value = temp->u.entry.value;
				last->right = node;
				last = node;
				m3Hdnode[temp->u.entry.col]->u.next->down = node;
				m3Hdnode[temp->u.entry.col]->u.next = node;
			}
			if (temp1->tag == head)
				temp1 = temp1->u.next;
			if (temp2->tag == head)
				temp2 = temp2->u.next;
		}
		/*마지막 정리*/
		last->right = m3Hdnode[currentRow];
		for (i = 0; i < m3->u.entry.col; i++)
			m3Hdnode[i]->u.next->down = m3Hdnode[i];
		for (i = 0; i < m3Heads - 1; i++)
			m3Hdnode[i]->u.next = m3Hdnode[i + 1];
		m3Hdnode[m3Heads - 1]->u.next = m3;
		m3->right = m3Hdnode[0];
	}
	return m3;
}
matrixPointer mtranspose(matrixPointer node)
{
	int numHeads, numCols, numRows, i, j, currentRow;
	int row, col, value;
	matrixPointer tNode, temp, last;
	matrixPointer tHdnode[MAX_SIZE];
	matrixPointer nodeHead = node->right, nodeTemp;
	/*tNode: 전치행렬의 최고 노드*/
	numCols = node->u.entry.row;
	numRows = node->u.entry.col;
	numHeads = (numCols > numRows) ? numCols : numRows;
	tNode = newNode();
	tNode->tag = entry;
	tNode->u.entry.row = numRows;
	tNode->u.entry.col = numCols;
	if (!numHeads)
		tNode->right = tNode;
	else
	{
		for (i = 0; i < numHeads; i++)
		{
			temp = newNode();
			tHdnode[i] = temp;
			tHdnode[i]->tag = head;
			tHdnode[i]->right = temp;
			tHdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = tHdnode[0];
		for (j = 0; j < node->u.entry.col; j++)
		{ /*행렬의 열만큼 반복*/
			for (nodeTemp = nodeHead->down; nodeTemp != nodeHead;
				nodeTemp = nodeTemp->down) /*행렬의 열을 따라 스캔, 열을 행으로 변환*/
			{
				row = nodeTemp->u.entry.col;
				col = nodeTemp->u.entry.row;
				value = nodeTemp->u.entry.value;
				if (row > currentRow)
				{
					last->right = tHdnode[currentRow];
					currentRow = row;
					last = tHdnode[row];
				}
				temp = newNode();
				temp->tag = entry;
				temp->u.entry.row = row;
				temp->u.entry.col = col;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;
				tHdnode[col]->u.next->down = temp;
				tHdnode[col]->u.next = temp;
			}
			nodeHead = nodeHead->u.next;
		}
		/* 마지막 정리 */
		last->right = tHdnode[currentRow];
		for (i = 0; i < numCols; i++)
			tHdnode[i]->u.next->down = tHdnode[i];
		for (i = 0; i < numHeads - 1; i++)
			tHdnode[i]->u.next = tHdnode[i + 1];
		tHdnode[numHeads - 1]->u.next = tNode;
		tNode->right = tHdnode[0];
	}
	return tNode;
}

matrixPointer mmult(matrixPointer m1, matrixPointer m2)
{
	int numRows, numCols, numHeads, i, j;
	int row, col, value, currentRow;
	int done = FALSE;
	matrixPointer temp, last, multNode = NULL, findNode;
	matrixPointer multHdnode[MAX_SIZE];
	matrixPointer m1Head, m2Head, m1Temp, m2Temp;
	/*multNode: 곱행렬의 최고 노드*/
	if (m1->u.entry.col != m2->u.entry.row)
	{
	printf("행렬의 크기가 맞지 않습니다.₩n");
	exit(0);
	}
	else 
	{
		m1Head = m1->right;
		m2Head = m2->right;
		numRows = m1->u.entry.row;
		numCols = m2->u.entry.col;
		numHeads = (numCols > numRows) ? numCols : numRows;
		
		multNode = newNode();
		multNode->tag = entry;
		multNode->u.entry.row = numRows;
		multNode->u.entry.col = numCols;
		if (!numHeads)
			multNode->right = multNode;
		else
		{
			for (i = 0; i < numHeads; i++)
			{
				temp = newNode();
				multHdnode[i] = temp;
				multHdnode[i]->tag = head;
				multHdnode[i]->right = temp;
				multHdnode[i]->u.next = temp;
			}
			currentRow = 0;
			last = multHdnode[0];
			/* 첫번째 행렬의 행 만큼 반복*/
			for (i = 0; i < m1->u.entry.row; i++)
			{
				row = 0, col = 0, value = 0;
				/* 두번째 행렬의 열만큼 반복*/
				for (j = 0; j < m2->u.entry.col; )
				{
					/*done: 열 이동 여부 */
					if (j == 0 && done == FALSE)
					{
						m1Temp = m1Head->right; /*첫번째 행렬은 행으로*/
						m2Temp = m2Head->down; /* 두번째 행렬은 열로*/
					}
					/*열 노드가 존재하지 않음*/
					if (m2Temp->tag == head || m2Temp->down == m2Temp)
					{
						done = FALSE;
						m2Head = m2Head->u.next;
						m2Temp = m2Head->down;
						/* 첫번째 행렬의 행 초기화*/
						m1Temp = m1Head->right;
						row = 0, col = 0, value = 0;
						j++;
					}
					if (m1Temp->tag == head)
					{
						/* 첫번째 행렬의 행 노드가 존재하지 않음*/
						if (m1Temp->right == m1Temp)
						{
							done = FALSE;
							break;
						}
						/* 첫번째 행렬의 행의 수가 두번째 행렬의 열의 수보다 작음 */
						if (m2Head->u.next != m2)
						{
							m1Temp = m1Head->right; 
							row = 0, col = 0, value = 0;
							m2Head = m2Head->u.next;
							m2Temp = m2Head->down;
							done = FALSE;
							j++;
						}
						else
							j++;
					}
					if (j >= m2->u.entry.col)
						break;
					/* 첫번째 행렬의 열과 두번째 행렬의 행 수를 비교*/
					switch (COMPARE(m1Temp->u.entry.col, m2Temp->u.entry.row))
					{
					case -1:
						m1Temp = m1Temp->right;
						/* m2Temp는 이동시키면 안되므로 done = TRUE */
						done = TRUE;
						continue;
					case 0:
						done = TRUE;
						if (value != 0)
						{
							row = m1Temp->u.entry.row;
							col = m2Temp->u.entry.col;
							findNode = multHdnode[row]->right;
							while (1)
							{
								/* 생성된 값과 같은 위치의 노드 존재 */
								if (findNode->u.entry.col == col)
								{
									findNode->u.entry.value =
										findNode->u.entry.value + value;
									break;
								}
								else
									findNode = findNode->right;
								if (findNode->tag == head)
									break;
							}
							m1Temp = m1Temp->right;
							m2Temp = m2Temp->down;
						}
						else if (value == 0)
						{ /* 생성된 값의 위치가 처음 */
							row = m1Temp->u.entry.row;
							col = m2Temp->u.entry.col;
							value = m1Temp->u.entry.value * m2Temp->u.entry.value;
							if (row > currentRow)
							{
								last->right = multHdnode[currentRow];
								currentRow = row;
								last = multHdnode[row];
							}
							temp = newNode();
							temp->tag = entry;
							temp->u.entry.row = row;
							temp->u.entry.col = col;
							temp->u.entry.value = value;
							last->right = temp;
							last = temp;
							multHdnode[col]->u.next->down = temp;
							multHdnode[col]->u.next = temp;
							m1Temp = m1Temp->right;
							m2Temp = m2Temp->down;
						}
						continue;
					case 1:
						done = TRUE;
						m2Temp = m2Temp->down;
						continue;
					}
				}
				/* 첫번째 행렬 행 이동 */
				m1Head = m1Head->u.next;
				m2Head = m2->right;
				done = FALSE;
			}
			/*마지막 정리*/
			last->right = multHdnode[currentRow];
			for (i = 0; i < numCols; i++)
				multHdnode[i]->u.next->down = multHdnode[i];
			for (i = 0; i < numHeads - 1; i++)
				multHdnode[i]->u.next = multHdnode[i + 1];
			multHdnode[numHeads - 1]->u.next = multNode;
			multNode->right = multHdnode[0];
		}
	}
	return multNode;
}
