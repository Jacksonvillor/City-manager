
// ######################################################################## //
//
//  本程序使用顺序表实现城市记录数据的管理.
//
//  创建日期: 2017-03-25
//
//  修改记录:
//  ( 1 ) 2017-03-25 创建了初始版本( v0.10 )
//
//  版 本 号: v0.10
//
//  备    注: 使用标准 C 代码实现
//
//  作    者: 刘伟
//
// ######################################################################## //

// CityMIS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 使用的库定义
#include < stdio.h >
#include < stdlib.h >
#include < string.h >

// ######################################################################## //
//                                                                          // 
//                              下面是数据定义区                               // 
//                                                                          // 
// ######################################################################## //

#define MAX_CITY_NUM 100
#define TRUE  1
#define FALSE 0

// 用结构体定义城市数据信息 ...
typedef struct
{
  int   ID;         // 城市唯一编号( 内部使用 )
  char  Name[ 20 ]; // 城市名称
  float Area;       // 面积( 平方公里 )
  float Population; // 人口( 万 )
  float GDP;        // 地区生产总值( 亿元 )
} CityRecord;

// 用结构体定义商品信息
typedef struct
{
  CityRecord DataArray[ MAX_CITY_NUM ]; // 采用数组( 顺序表 )储存城市信息( 结构体数组 ) ...
  int        MaxID;                     // 每个城市记录的唯一 'ID' 号, 由于记录可能增, 删, 所以必须动态维护这个值 ...
  int        Len;                       // 当前城市记录数量 ...
} CityList;

// ######################################################################## //
//                                                                          // 
//                            下面是各个函数定义                               // 
//                                                                          // 
// ######################################################################## //

void InitCityList( CityList *L );
int  AddCity( CityList *L, CityRecord ARecord );
int  InsertCity( CityList *L, int k, CityRecord ARecord );
int  DeleteCity( CityList *L, int k );
int  FindCityByName( CityList *L, char *s );
void CalcCityStatistic( CityList *L );
void InputCityData( CityList *L );
void DisplayCityList( CityList *L );

//////////////////////////////////////////////////////////////////////////////

// ######################################################################## //
//                                                                          // 
//                           下面是各个函数的实现                               // 
//                                                                          // 
// ######################################################################## //

// 顺序表初始化 ...
void InitCityList( CityList *L )
{
  L -> MaxID = 0;
  L -> Len   = -1;
}

// 将新的城市记录加入到顺序表尾 ...
int AddCity( CityList *L, CityRecord ARecord )
{
  int OK = TRUE;

  if ( L -> Len == ( MAX_CITY_NUM - 1 ) )
    OK = FALSE;
  else
  {
    L -> Len++;
	L -> DataArray[ L -> Len ] = ARecord;
  }

  return OK;
}

// 将新的城市记录加入到顺序表中第 'k' 个位置处 ...
int InsertCity( CityList *L, int k, CityRecord ARecord )
{
  int i, OK = TRUE;

  // 检查数组是否已满 ...
  if ( L -> Len >= ( MAX_CITY_NUM - 1 ) )
    OK = FALSE;
  else if ( ( k < 0 ) || ( k > L -> Len ) ) // 检查插入位置是否合理 ...
    OK = FALSE;
  else
  {
    //  数组插入元素 : 所有元素向后移动空出位置, 即 ' i -> i + 1 ' ... 
    for ( i = L -> Len; i >= k; i-- )
      L -> DataArray[ i + 1 ] = L -> DataArray[ i ];

	// 插入新商品记录 ...
	L -> DataArray[ k ] = ARecord;

	// 更新数组长度 ...
	L -> Len++;
  }

  return OK;
}

// 将顺序表中第 'k' 个位置处元素删除 ...
int DeleteCity( CityList *L, int k )
{
  int i, OK = TRUE;

  // 检查删除位置是否合理 ...
  if ( ( k < 0 ) || ( k > L -> Len ) ) 
    OK = FALSE;
  else
  {
    //  数组删除元素 : 所有元素向前移动覆盖元素, 即 ' i + 1 -> i ' ... 
    for ( i = k + 1; i <= L -> Len; i++ )
      L -> DataArray[ i - 1 ] = L -> DataArray[ i ];

	// 更新数组长度 ...
	L -> Len--;
  }

  return OK;
}

// 根据城市名称查找城市记录( 返回其在顺序表中的序号 ) ...
int FindCityByName( CityList *L, char *s )
{
  int i;

  if ( strlen( s ) ) // 输入的城市名称不能为空 ...
  {
    if ( L -> Len >= 0 ) // 城市顺序表不为空 ...
	{
      for ( i = 0; i <= L -> Len; i++ )
		if ( !strcmp( L -> DataArray[ i ].Name, s ) ) // 如果两个字符串相等, 则 'strcmp' 函数返回零 ...
		  return i;
	}
	else
	  return -1;
  }

  return -1;
}

// 计算城市统计指标 ...
void CalcCityStatistic( CityList *L )
{
  int i;
  float TotalArea = 0.0, TotalPopulation = 0.0, TotalGDP = 0.0;

  printf( "\n\n" );

  // 统计所有城市的 '面积( 平方公里 )', '人口( 万 )', 和 '地区生产总值( 亿元 )' 平均值 ...
  if ( L -> Len >= 0 )
  {
    for ( i = 0; i <= L -> Len; i++ )
	{
      TotalArea       += L -> DataArray[ i ].Area;
	  TotalPopulation += L -> DataArray[ i ].Population;
	  TotalGDP        += L -> DataArray[ i ].GDP;
	}

	// 打印输出统计结果 ...
	printf( "\t< 城市平均 面积 为 : %.2f ( 平方公里 )>\n", ( TotalArea / ( L -> Len + 1 ) ) );
	printf( "\t< 城市平均 人口 为 : %.2f ( 万 )>\n", ( TotalPopulation / ( L -> Len + 1 ) ) );
	printf( "\t< 城市平均 GDP 为 : %.2f ( 亿元 )>\n", ( TotalGDP / ( L -> Len + 1 ) ) );
  }
  else
	printf( "\t没有城市数据 !\n" );
}

// 录入城市数据 ...
void InputCityData( CityList *L )
{
  CityRecord ARecord;
  int        IsStop;

  // 初始化 ...
  ARecord.ID = 0;

  printf( "\n" );

  IsStop = FALSE;
  while( !IsStop )
  {
    printf( "\n" );
	printf( "\t请输入 < 城市名称 > ( 'q'/'Q' 退出 ) : " );
	scanf( "%s", ARecord.Name );
	if ( ( ARecord.Name[ 0 ] == 'q' ) || ( ARecord.Name[ 0 ] == 'Q' ) ) // 输入 'q | Q' 表示结束 ...
	  IsStop = TRUE;
	else
	{
      printf( "\t请输入 < 城市面积( 平方公里 ) > : " );
      scanf( "%f", &ARecord.Area );

      printf( "\t请输入 < 城市人口( 万 ) > : " );
      scanf( "%f", &ARecord.Population );

      printf( "\t请输入 < GDP( 亿元 ) > : " );
      scanf( "%f", &ARecord.GDP );

      // 自动维护城市 'Max ID' 号, 如同实际的数据库管理系统( DBMS )一样 ...
      L -> MaxID++;
      ARecord.ID = L -> MaxID;

	  // 加入数组末尾 ...
      if ( !AddCity( L, ARecord ) )
	  {
		printf( "\n\n\t", "城市列表已满, 无法增加新城市数据 !" );
		
		system( "PAUSE" );
	  }
	}
  }
}

// 显示输出城市列表 ...
void DisplayCityList( CityList *L )
{
  int i;

  printf( "\n\n" );

  if ( L -> Len >= 0 )
  {
    printf( "\t< Max ID = > %d\n", L -> MaxID );
	printf( "\t< Len    = > %d\n\n", L -> Len );
	  
	printf( "\t----------------------------------------------------------------------\n" );
    printf( "\t 序号  ID   名称      面积( 平方公里 )   人口( 万 )     GDP( 亿元 )\n" );
    printf( "\t----------------------------------------------------------------------\n" );

    for ( i = 0; i <= L -> Len; i++ )
	{
      printf( "\t %d", i );
	  printf( "     %d", L -> DataArray[ i ].ID );
	  printf( "     %s", L -> DataArray[ i ].Name );
	  printf( "        %.2f", L -> DataArray[ i ].Area );
	  printf( "        %.2f", L -> DataArray[ i ].Population );
      printf( "        %.2f\n", L -> DataArray[ i ].GDP );		
	}

	printf( "\t----------------------------------------------------------------------\n" );
  }
  else
	printf( "没有城市数据 !\n" );
}

//////////////////////////////////////////////////////////////////////////////

// ######################################################################## //
//                                                                          // 
//                             下面是主程序的实现                              // 
//                                                                          // 
// ######################################################################## //

void main( void )
{
  CityList   BigCityList; // 顺序表结构的城市数据 ...
  CityRecord ARecord;     // 城市数据结构体 ...
  int        k;
  char       s[ 20 ];

  // 顺序表初始化 ...
  InitCityList( &BigCityList );

  // 用户通过键盘输入城市数据 ...
  InputCityData( &BigCityList );

  // 显示城市列表 ...
  DisplayCityList( &BigCityList );

  // ------------------------------------------------------------
  //
  // 插入城市记录 ...
  //
  // ------------------------------------------------------------

  printf( "\n\n\t请输入 < 插入新数据位置 > : " ); // 算法插入是基于位置 '0', 用户输入时基于位置 '1' ...
  scanf( "%d", &k );
  if ( k >= 1 )
	k--;

  // 初始化 ...
  ARecord.ID = 0;

  printf( "\n\n" );

  printf( "\t请输入 < 城市名称 > : " );
  scanf( "%s", ARecord.Name );

  printf( "\t请输入 < 城市面积( 平方公里 ) > : " );
  scanf( "%f", &ARecord.Area );

  printf( "\t请输入 < 城市人口( 万 ) > : " );
  scanf( "%f", &ARecord.Population );

  printf( "\t请输入 < GDP( 亿元 ) > : " );
  scanf( "%f", &ARecord.GDP );

  // 自动维护城市 'Max ID' 号, 如同实际的数据库管理系统( DBMS )一样 ...
  BigCityList.MaxID++;
  ARecord.ID = BigCityList.MaxID;
  if ( !InsertCity( &BigCityList, k, ARecord ) )
    printf( "\n\n\t", "城市列表已满, 无法增加新城市数据 !" );

  // 显示城市列表 ...
  DisplayCityList( &BigCityList );

  // ------------------------------------------------------------
  //
  // 删除城市记录 ...
  //
  // ------------------------------------------------------------

  printf( "\n\n\t请输入 < 删除数据位置 > : " ); // 算法删除是基于位置 '0', 用户输入时基于位置 '1' ...
  scanf( "%d", &k );
  if ( k >= 1 )
	k--;

  if ( DeleteCity( &BigCityList, k ) )
	printf( "\n\n\t删除数据成功 !" );
  else
	printf( "\n\n\t删除数据失败 !" );

  // 显示城市列表 ...
  DisplayCityList( &BigCityList );

  // ------------------------------------------------------------
  //
  // 查找城市记录 ...
  //
  // ------------------------------------------------------------

  printf( "\n\n\t请输入 < 待查找城市名称 > : " );
  scanf( "%s", s );

  k = FindCityByName( &BigCityList, s );
  if ( k >= 0 )
  {
	printf( "\n\n\t给定城市已找到, 信息如下 : \n" );
	printf( "\t< 城市名称 >            : %s\n", BigCityList.DataArray[ k ].Name );
    printf( "\t< 城市面积( 平方公里 ) > : %.2f\n", BigCityList.DataArray[ k ].Area );
    printf( "\t< 城市人口( 万 ) >      : %.2f\n", BigCityList.DataArray[ k ].Population );
    printf( "\t< GDP( 亿元 ) >        : %.2f\n\n\n", BigCityList.DataArray[ k ].GDP );
  }
  else
    printf( "\n\n\t未找到给定城市 !" );

  // 显示城市统计数据 ...
  CalcCityStatistic( &BigCityList );

  // 等待用户输入任意一键返回 ...
  printf( "\n\n" );
  system( "PAUSE" );
}

//////////////////////////////////////////////////////////////////////////////
