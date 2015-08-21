#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Entity.h"

#define CELL_SIZE 40
#define BLOCK_WIDTH_COUNT 4

using namespace cocos2d;

class BlockManager;

class BlockI;

class Block:public Entity
{
public: //System functions
	Block();
	~Block();
	CREATE_FUNC(Block);
	virtual bool init();

public:
	typedef enum
	{
		Up,
		Down,
		Left,
		Right
	}Direction;
	typedef enum
	{
		D0    = 0,
		D90   = 90,
		D180  = 180,
		D270  = 270
	}Degree;
	typedef enum
	{
		I,
		L,
		L_Reverse,
		T,
		Z,
		Z_Reverse,
		O
	}BlockType;
	typedef struct
	{
		CCPoint points[4];
	}CellPosition;

public: //Custom functions
	virtual bool doTurn90Degrees();
	virtual bool doMove(Direction direction);
	void bindManager(BlockManager* manager);
//	void setIndexInArray(int index);
	bool increaseTimeCounter(); //ʱ�������󷵻��Ƿ���Ҫ����λ��
	static Block* generateNewBlock();
	CellPosition getCellPosition();
//	void resetTimeCounter();
	void initializeBlock(); //��ʼ�������ڵ�����
	void setBlockData(CCPoint blockPoint, CCPoint stagePoint); //����ͨ���˺����趨blockData�����е�����ֵ
	

private:
	virtual void _limitLine(Direction direction);
	virtual bool _canMove(Direction direction);

private:
	CCPoint m_blockData[BLOCK_WIDTH_COUNT][BLOCK_WIDTH_COUNT];
	BlockManager* m_manager;
	BlockType m_type;
	int m_timeCounter;
	CCPoint m_position; //�Ծ�������Ϊ��׼ �ڹ������� ��Ӧ�������½ǵ�λ��
//	int m_indexInArray;

}; //class Block

#endif //__BLOCK_H__