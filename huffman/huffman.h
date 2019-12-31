#ifndef HUFFMAN_H_
#define HUFFMAN_H_



typedef struct
{
	char value[3];     //字符值
	char code[100];    //字符编码
	int time;          //字符出现的次数
	int codelen;       //字符编码长度
}HuffmanCode;

struct Node
{
	int time;  //结点次数
	char value[3];   //字符值
	struct Node *Lchild;   //左结点
	struct Node *Rchild;   //右节点
};
struct filehead
{
	int totallen;
	int last;
	int time;
	int num;
};

int strncmp(char *a,char *b,int num);   //比较　a 和 b字符串的　　前num个字节 
int  read_cnt(char *path,HuffmanCode *node);  //统计出现频率
struct Node* build(HuffmanCode *node,int num);//建树
void Huffmancode(struct Node *node,int len,HuffmanCode *arr,int num);//计算huffman编码
void writecode(char *path,HuffmanCode *arr,int num,char *writepath);     //将二进制代码写入文件中
void Decode();//译码函数
void commpression();   //压缩


#endif
