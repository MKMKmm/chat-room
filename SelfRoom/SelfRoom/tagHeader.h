typedef struct tagHeader
{
	char	type;
	int		len;
	int     flag;   //0ΪȺ�� 1Ϊ˽��
} Header, *pHeader;

#define LOGIN_IO		1
#define SEND_MESSAGE	3