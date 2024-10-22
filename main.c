#include<stdio.h>
#include<stdlib.h>

#define PARKINGLOTSIZE 2            //停车场大小
#define PERPERIOD 30            //每多少分钟计一次费
#define PERPRIZE 1          //每次计费加多少钱

typedef struct car{         //车的结构体（有进出行为元素，车牌号元素，和时刻元素）
    char behavior;
    int number;
    int time;
}car;


typedef struct StackNode{           //栈节点的结构体
    car data;
}Stack;

typedef struct QueueNode{           //队列节点结构体
    car data;
    struct QueueNode* next;
}QueueNode;

typedef struct Queue{               //队列结构体（存储队列的头和尾）
    QueueNode* head;
    QueueNode* tail;
}Queue;

void push(Stack* Stack,car info,int* top){          //将元素压入栈中
    Stack[*top]=info;
    *top++;
}

int isEmptyStack(int top){          //检查栈是否为空
    return top==0;
}

car pop(StackNode* Stack,int* top){         //将栈顶元素弹出
    if(isEmptyStack(Stack)){
        car popinfo=Stack[*top];
        *top--;
        return popinfo;
    }
    else{
        printf("停车场内没有车");
        return;
    }
}
int seekStackCarNumber(Stack* Stack,int top,int seek){          //寻找栈中是否有符合车牌号的车
    if(isEmptyStack(Stack)){            //若为空栈则返回零
        return 0;
    }
    for(int i=0;i<top;i++){         
        if(Stack[i]->number==seek){         //若找到则返回其在第几个
            return i+1;
        }
    }
    return 0;
}

void clearStack(int* top){          //情况栈
    *top=0;
}

void initQueue(Queue* Queue){           //初始化队列
    Queue->head=NULL;
    Queue->tail=NULL;
}

void enQueue(Queue* Queue,car info,int* location){          //进入队列
    QueueNode* NewNode=(Queue*)malloc(sizeof(QueueNode));
    if(NewNode==NULL){          //查看内存是否分配正确
        printf("内存分配失败。\n");
        return;
    }
    NewNode->data=info;         //将数据填入
    NewNode->next=NULL;
    *location++;            //location记录队列中有几个元素
    if(Queue->head==NULL){          //若队列为空则初始化头、尾指针
        Queue->head=NewNode;
        Queue->tail=NewNode->next;
    }
    else{
        Queue->tail=NewNode;            //队列不为空的情况
        Queue->tail=Queue->tail->next;
    }
}

int isEmptyQueue(Queue* Queue){         //检查是否为空队列
    return Queue->head==NULL;
}

car deQueue(Queue* Queue,int* location){            //出队操作，返回出队的元素
    if(isEmptyQueue(Queue)){            //检查是否为空队列
        printf("这是一个空队列。\n");
        return;
    }
    QueueNode* temp=Queue->head;            //用temp暂时记录地址，待会释放
    car data=temp->data;            //保存要出队的元素
    Queue->head=Queue->head->next;
    free(temp);
    *location--;
    return data;
}

int seekQueueCarNumber(Queue* Queue,int seek){          //查找队列中是否有对应车牌号的车
    if(isEmptyQueue(Queue)){            //跳过空队列情况
        return 0;
    }
    QueueNode* cur=Queue->head;
    int where=1;            //where为该元素在第几个位置
    while(cur!=NULL){
        if(cur->data->number==seek){
            return where;
        }
        cur=cur->next;
        where++;
    }
    return 0;
}

void clearQueue(Queue* Queue){          //清空队列
    while(!isEmptyQueue(Queue)){
        deQueue(Queue);
    }
}

int main(void){
    Stack ParkingLot[PARKINGLOTSIZE];           //停车场栈
    int LotTop=0;           //停车场栈栈顶
    Stack GiveWay[PARKINGLOTSIZE];          //临时栈
    int WayTop=0;           //临时栈栈顶

    Queue TemporaryRoad;            //便道
    int location=0;         //便道内元素个数
    initQueue(TemporaryRoad);

    car next;           //下一个输入的信息
    scanf("%c%d%d",&next->behavior,&next->number,&next->time);
    while(next->behavior!='E'){
        if(next->behavior=='A'){            //有车驶入，判断去向
            if(LotTop<2){           //进入停车场
                push(ParkingLot,next,&LotTop);
                printf("汽车在停车场第%d个位置",LotTop);
            }
            else{           //进入便道
                enQueue(TemporaryRoad,next);
                printf("汽车在便道第%d个位置",);
            }
        }
        elif(next->behavior=='D'){          //有车驶出
            int temp=0;         //temp记录要驶出的车在停车场或是便道内的第几个位置
            if(temp=seekStackCarNumber(ParkingLot,LotTop,next->number)){            //若驶出车原本在停车场内
                if(temp==LotTop){           //若为能直接驶出的栈顶车
                    car former=pop(ParkingLot,LotTop);
                    printf("%d车在停车场停留%d分钟，应交纳%d元",next->time-former->time,(next->time-former->time)/PERPERIOD*PERPRIZE);
                }
                else{           //若为不能直接驶出的栈内车

                }
            }
            else if(temp=seekQueueCarNumber(TemporaryRoad,next->number)){           //若驶出车原本在便道内
                if(temp==1){            //若该车在队列的头位置
                    deQueue(TemporaryRoad,location);            //出队
                    printf("%d车在停车场停留0分钟，应交纳0元",next->number);
                }
                else{
                    printf("便道只有最前面的车可以离开，输入的信息不合逻辑");           //便道内的车无法驶出
                }
            }
            else{
                printf("该车不在停车场或便道内");           //若要驶出的车既不在停车场内也不在便道内
            }
        else{
            printf("输入的格式错误，汽车只有'A'和'D'两种行为");         //输入的车行为既不是驶出也不是驶入
        }
        }
    }
    
}