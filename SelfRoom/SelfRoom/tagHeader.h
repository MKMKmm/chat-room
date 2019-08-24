typedef struct tagHeader
{
	char	type;
	int		len;
	int     flag;   //0н╙х╨ад 1н╙к╫ад
} Header, *pHeader;

#define LOGIN_IO		1
#define SEND_MESSAGE	3