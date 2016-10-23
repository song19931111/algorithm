//#include<iostream>
//#include<algorithm>
//#define DEF_MAX_STACK_SIZE 100 
//using namespace std ;
//template<typename T>
//class  CStack{
//public :
//	int m_top ;  
//	 T m_stack[DEF_MAX_STACK_SIZE];
//	CStack()
//	{
//		m_top = -1; 
//		memset(m_stack,0,sizeof(m_stack));
//	}
//	bool isEmpty()
//	{
//		if( m_top ==-1 )
//			return true ;
//		return false; 
//	}
//	T Pop(   )
//	{
//		if( m_top == -1 )
//		{
//			return false; 
//		}
//		return m_stack[ m_top-- ] ;
//	}  
//	void Push( T ch )
//	{
//		 m_stack[ ++m_top ] = ch ;
//	}
//
//};
//int GetPrivilige( char ch )
//{
//	switch (ch)
//	{
//	
//	case '*':
//	case '/':
//	return 4;
//	case '+':
//	case '#':
//	return 3;
//		case -1:
//		return -1;
//	case '(':
//		return 2;
//	default:
//		return 0  ;
//	}
//
//}
//
//int calculate(int n1  ,int n2, char opr)
//{
//	switch( opr )
//	{
//	case '+':
//		return n1+n2; 
//		break;
//	case '*':
//		return n1*n2;
//		break ; 
//	case '#':
//		return n2-n1; 
//		break ; 
//
//	}
//	return -9999999;
//}
//int MidExpress( char * str )
//{
//	int nbracketCount = 0  ; //左括号的个数
//	if( NULL == str )
//	{
//		return -1 ; 
//	}
//	CStack<int> dig_stack ; 
//	CStack<char> opr_stack;
//	char *pFirst = str ;
//	char *temp = new char[ 100 ];
//	memset(temp,0,100);
//	int index=  0 ;
//	//bool bDigFlag = false;
//	while( *str!=0 )
//	{
//		//判断是否是负号
//			if ( *str=='-' )
//			{
//				if( pFirst!=str && (*(str-1)==')' || isdigit(*(str-1) )))
//				{
//					//减号
//					*str ='#';
//				}
//				else
//				{
//					//负号
//					*str='-';
//				}
//			}
//		//如果是数字
//		if  ( isdigit(*str) ||*str=='-' )
//		{
//			temp[index++] = *str;
//			
//			
//			
//			if( *(str+1)==0 ||!isdigit(*(str+1)) ) //如果是最后一个，或者下一个不是数字
//			{
//				temp[index] =0;
//				int n  =  atoi(temp);
//				dig_stack.Push(n);
//				memset(temp,0,sizeof( temp ));
//				index =  0 ;
//			}
//			str++;
//			continue ;
//		}
//		else 
//		{
//			
//				//如果是( 直接入栈:
//				if( *str=='(' )
//				{
//					opr_stack.Push(*str);
//					str++;
//					//nbracketCount++; //左括号的个数 ++
//					continue  ;
//				}
//				if( *str==')' )
//				{
//					//nbracketCount --;
//					while( opr_stack.m_stack[ opr_stack.m_top ] != '(')
//					{
//						//出栈
//						char chOpr = opr_stack.Pop();
//						//取数，计算
//						int n1 = dig_stack.Pop();
//						int n2 = dig_stack.Pop();
//						int nResult  =  calculate( n1,n2,chOpr );
//						dig_stack.Push(nResult);
//					}
//					opr_stack.Pop();  //左括号出栈
//					str++;
//					continue;
//				}
//				//判断当前优先级:
//				if( GetPrivilige ( *str )> GetPrivilige (opr_stack.m_stack[ opr_stack.m_top ] )  )
//				{
//					//入栈
//					opr_stack.Push(*str);
//				}
//				else
//				{
//					//否则取出栈顶元素，直至栈顶元素的优先级小于当前操作符:
//					while( GetPrivilige (opr_stack.m_stack[ opr_stack.m_top ] )>=GetPrivilige ( *str ) )
//					{
//						char chOpr_ = opr_stack.Pop();
//						int x1 = dig_stack.Pop();
//						int x2 = dig_stack.Pop();
//						int x3 = calculate(x1,x2,chOpr_);
//						dig_stack.Push(x3);
//					}
//					//将该操作符放入栈:
//					opr_stack.Push(*str);
//				}
//			}
//		str++;
//	}
//	
//
//	while( !opr_stack.isEmpty() )
//	{
//		char opr = opr_stack.Pop();
//		int m1 = dig_stack.Pop(); 
//		int m2 = dig_stack.Pop();
//		int m3 = calculate(m1,m2,opr);
//		dig_stack.Push(m3);
//	}
//	return dig_stack.Pop();
//}
//char * AddBracket( char *pStr, int iLeft ,int iRight )
//{
//	 int len =  strlen(pStr)+ 1; 
//	 char *pTemp = new char[ len+2 ];
//	 memset(pTemp,0,len+2);
//	 strncpy(pTemp,pStr,iLeft);
//	 pTemp[iLeft] ='(';
//	 strncat(pTemp,pStr+iLeft,iRight-iLeft+1);
//	 pTemp[iRight+2] =')';
//	 strcat(pTemp+iRight+3,pStr+iRight+1);
//	 return pTemp  ;
//}
//int cmp( int a, int b )
//{
//	return a<b;
//}
//int main()
//{
//	//char temp[] = "55-33*22-11*22+33-56";
//	//cout<<AddBracket(temp,3,7);
//	char szInput[1024] ; 
//	cin>>szInput;
//	int result[1024]= {0};
//	int len =strlen( szInput ) +1;
//	int count  =  0 ;
//	for( int i=0;i<len-1;i++)
//	{
//		for( int j=i+1;j<len;j++ )
//		{
//			if( isdigit(szInput[i]) &&  isdigit(szInput[j]))
//			{
//				result[count++]  =  MidExpress(AddBracket(szInput,i,j));
//			}
//		}
//	}
//	sort(result,result+count,cmp);
//	int iNewCount =  0 ;
//
//	for( int i=0;i<count ;i++ )
//	{
//		if( 0==i  )
//		{
//			iNewCount ++;
//		}
//		if( i>0 &&result[i]!=result[i-1])
//		{
//			iNewCount ++ ;
//		}
//	}
//	cout <<iNewCount<<endl;
//	for( int i=0;i<count ;i++ )
//	{
//		if( 0==i )
//		{
//			cout <<result[i]<<endl;
//		}
//		if( i>0 &&result[i]!=result[i-1])
//		{
//			cout <<result[i]<<endl;
//		}
//	}
//	return 0  ;
//}