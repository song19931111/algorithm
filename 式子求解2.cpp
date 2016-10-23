#include <iostream>
using namespace std;
#define DEF_STR_LEN 1024
#define DEF_MAX_STACK_SIZE 1024
int g_count  = 0  ;
int g_ans =  0 ; 
template<typename T>
class  CStack{
public :
	int m_top ;  
	 T m_stack[DEF_MAX_STACK_SIZE];
	CStack()
	{
		m_top = -1; 
		memset(m_stack,0,sizeof(m_stack));
	}
	bool isEmpty()
	{
		if( m_top ==-1 )
			return true ;
		return false; 
	}
	T Pop(   )
	{
		if( m_top == -1 )
		{
			return false; 
		}
		return m_stack[ m_top-- ] ;
	}  
	void Push( T ch )
	{
		 m_stack[ ++m_top ] = ch ;
	}

};
int GetPrivilige( char ch )
{
	switch (ch)
	{
	
	case '*':
	return 4;
	case '+':
	case '#':
	return 3;
		case -1:
		return -1;
	default:
		return 0  ;
	}

}

int calculate(int n1  ,int n2, char opr)
{
	switch( opr )
	{
	case '+':
		return n1+n2; 
		break;
	case '*':
		return n1*n2;
		break ; 
	case '#':
		return n2-n1; 
		break ; 

	}
	return -9999999;
}
int MidExpress( char * str )
{
	int nbracketCount = 0  ; //左括号的个数
	if( NULL == str )
	{
		return -1 ; 
	}
	CStack<int> dig_stack ; 
	CStack<char> opr_stack;
	char *pFirst = str ;
	char *temp = new char[ 100 ];
	memset(temp,0,100);
	int index=  0 ;
	//bool bDigFlag = false;
	while( *str!=0 )
	{
		//判断是否是负号
			if ( *str=='-' )
			{
				if( pFirst!=str && (*(str-1)==')' || isdigit(*(str-1) )))
				{
					//减号
					*str ='#';
				}
				else
				{
					//负号
					*str='-';
				}
			}
		//如果是数字
		if  ( isdigit(*str) ||*str=='-' )
		{
			temp[index++] = *str;
			
			
			
			if( *(str+1)==0 ||!isdigit(*(str+1)) ) //如果是最后一个，或者下一个不是数字
			{
				temp[index] =0;
				int n  =  atoi(temp);
				dig_stack.Push(n);
				memset(temp,0,sizeof( temp ));
				index =  0 ;
			}
			str++;
			continue ;
		}
		else 
		{
			
				//判断当前优先级:
				if( GetPrivilige ( *str )> GetPrivilige (opr_stack.m_stack[ opr_stack.m_top ] )  )
				{
					//入栈
					opr_stack.Push(*str);
				}
				else
				{
					//否则取出栈顶元素，直至栈顶元素的优先级小于当前操作符:
					while( GetPrivilige (opr_stack.m_stack[ opr_stack.m_top ] )>=GetPrivilige ( *str ) )
					{
						char chOpr_ = opr_stack.Pop();
						int x1 = dig_stack.Pop();
						int x2 = dig_stack.Pop();
						int x3 = calculate(x1,x2,chOpr_);
						dig_stack.Push(x3);
					}
					//将该操作符放入栈:
					opr_stack.Push(*str);
				}
			}
		str++;
	}
	

	while( !opr_stack.isEmpty() )
	{
		char opr = opr_stack.Pop();
		int m1 = dig_stack.Pop(); 
		int m2 = dig_stack.Pop();
		int m3 = calculate(m1,m2,opr);
		dig_stack.Push(m3);
	}
	return dig_stack.Pop();
}
char * ChangeStr( char *pStr )
{
	int len  = strlen( pStr );
	char *pTemp = new char[ len +len-1 + 1 ];
	memset(pTemp ,0, 2*len);
	int iIndex = 0 ; 
	for( int i=0; i<len ;i++ )
	{
		pTemp[iIndex++] = pStr[i];
		if ( i ==len-1 )
		{
			continue  ;	
		}
		pTemp[iIndex++] =  'm';//代表占位符
	}
	pTemp[iIndex]  = 0  ;
	return pTemp;
}
int GetNextPos(char *pStr, int iCurrentIndex)
{
	int i=1; 
	while(1)
	{
		if( pStr[ iCurrentIndex +2] == 0  )
		{
			return -1 ;
		}
		if( *(pStr+iCurrentIndex+i)  == 'm')
		{
			return iCurrentIndex+i;
		}
		i++;
	}
}
char szSignal[] ={'+','-','*','#'};
bool AddSign( char *pStr, int iIndex , char chSign )
{
	if( pStr[ iIndex -1] == '0' &&chSign=='#' )
	{
		return false ;
	}
	pStr[iIndex]  =  chSign;
	return true;
}
int ChangeExpress( char  *pStr)
{
	char temp[1000]  = { 0};
	char *pFirst = pStr; 
	int iIndex =  0 ;
	//去掉字符串中的#号，并返回结果
	while( *pStr!=0 )
	{
		if ( * pStr=='#' )
		{
			if(pStr==pFirst)
			{
				pFirst++;
			}
			else
			{
				strncat(temp,pFirst,(pStr-pFirst));
				pFirst = pStr+1;
			}
		}
		pStr++ ;
		
	}
	strcat(temp,pFirst);
	//memset(pStr,0,DEF_STR_LEN);
	//strcpy(pStr,temp);
	return  MidExpress(temp);
}
void result( char *pStr, int pos)
{
	for( int k=0;k<4;k++ )
	{
		if( k==1)
		{
			int a = 10 ;
		}
		if ( false == AddSign(pStr,pos,szSignal[k]))
		{
			continue ; 
		}
		int iTempPos  = GetNextPos(pStr,pos);
		if( -1==iTempPos )
		{
			 //没有下一个了
			//cout <<pStr<<endl;
		if(ChangeExpress(pStr) ==g_ans)
		{
			g_count ++;
		}
			pStr[pos]='m';
			continue ; 
		}
		result(pStr,iTempPos);
	}
	//+ - * #都试完之后,恢复成m
	pStr[pos] ='m';
}

int main()
{
	char szInput[DEF_STR_LEN ]={0};
	cin>>szInput; 
	cin>>g_ans;
	char *pstrFormat = ChangeStr(szInput);
	result(pstrFormat,GetNextPos(pstrFormat,0));
	cout <<g_count<<endl;
	return 0  ;
}