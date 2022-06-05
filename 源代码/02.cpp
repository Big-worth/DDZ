#define kPlayerName "永无止境"
#define kPlaMax 500
#include "DdzV200.h"

char last_landowner='A';//初始化
char next_landowner='A';
char my_landwoner='A';

int other_statistics=1;//统计访问次数为了判断地主位置
void different_select(struct Ddz * pDdz,char last_landowner,char next_landowner,char my_landowner);//根据所处位置不同采取不同出牌方式
void last_landowner_come_method(struct Ddz * pDdz);//上一家是地主的出牌方法
void next_landowner_come_method(struct Ddz * pDdz);//下一家是地主的出牌方法
void my_landowner_come_method(struct Ddz * pDdz);//自己是地主的出牌方法

void two_other_already(struct Ddz * pDdz);//判断地主位置
double CalCardsValue(int iPlaOnHand[]);//上一家是地主的估值方法
double CalCardsValue1(int iPlaOnHand[]);//下一家是地主的估值方法
double CalCardsValue2(int iPlaOnHand[]);//自己是地主的估值方法		



void two_other_already(struct Ddz * pDdz)//判断地主位置
{
	
	while(other_statistics==1)
	{
          if(pDdz->iLastPassCount==0&&pDdz->iOTmax==1)//自己上一家是地主
		  {
           last_landowner=pDdz->cLandlord;//修改全局变量值
		  
		  }
      else if(pDdz->iLastPassCount==0&&pDdz->iOTmax==2||pDdz->iLastPassCount==1&&pDdz->iOTmax==1)//自己下一家是地主
		{
        next_landowner=pDdz->cLandlord;
	

		}
	  else
	  {
		  my_landwoner=pDdz->cLandlord;
		
	  }
       other_statistics++;//改变全局变量

	}
other_statistics=1;
/*
	if(pDdz->iStatus<1)//	int  iStatus;			//引擎状态-1错误,0结束,1开始
	{

	 other_statistics=1;//一局结束重置数据进入下一局
	}*/
}


void different_select(struct Ddz * pDdz,char last_landowner,char next_landowner,char my_landowner)//根据位置不同选择不同的出牌方法
{
   if(last_landowner==pDdz->cLandlord)//上一家是地主的出牌方法
	{
	 last_landowner_come_method(pDdz);

	}
   else if(next_landowner==pDdz->cLandlord)//下一家是地主的出牌方法
	{
	next_landowner_come_method(pDdz);

	}
	else if(my_landowner==pDdz->cLandlord)//自己是地主的出牌方法
	{
		my_landowner_come_method(pDdz);

	}

}





void last_landowner_come_method(struct Ddz * pDdz)//上一家是地主的出牌方式采用估值法
{
		int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//主要计算推荐出牌pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//假设取走了第i组牌，将剩余的牌放入pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue(pDdz->iPlaOnHand);			//计算余牌估值
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}
	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];
	pDdz->iToTable[i] = -1;

		if(pDdz->iOTmax<22)//在轮次少于22手数时不出大牌
		 {
				 for(int j=0;j<iMax;j++)
				 {
		            if(pDdz->iPlaArr[j][0]/4==pDdz->iPlaArr[j][1]/4&&pDdz->iPlaArr[j][1]/4==pDdz->iPlaArr[j][2]/4&&pDdz->iPlaArr[j][2]/4==pDdz->iPlaArr[j][3]/4)//如果推荐的出牌是炸弹
						 {
                                
                                for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//将其全部置为-1
								goto end;
						 }
					else if(pDdz->iPlaArr[j][0]/4==13&&pDdz->iPlaArr[j][1]/4==13)//推荐出牌为大小王
					{
						  for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//将其全部置为-1
						  goto end;
					}
				 

			 }
	  }


end:	pDdz->iToTable[i] = -1;
}


void next_landowner_come_method(struct Ddz * pDdz)//下一家是地主的出牌方式
{
	
        
	int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//主要计算推荐出牌pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//假设取走了第i组牌，将剩余的牌放入pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue1(pDdz->iPlaOnHand);
		//计算余牌估值
	
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}
	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)

		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];//得到想要出的牌
  	
	 
	
	



}


void my_landowner_come_method(struct Ddz * pDdz)//自己是地主的出牌方式
{

 	int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//主要计算推荐出牌pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//假设取走了第i组牌，将剩余的牌放入pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue2(pDdz->iPlaOnHand);			//计算余牌估值
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}

	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];


	if(pDdz->iOTmax<22)//在轮次少于22手数时不出大牌
		 {
				 for(int j=0;j<iMax;j++)
				 {
		            if(pDdz->iPlaArr[j][0]/4==pDdz->iPlaArr[j][1]/4&&pDdz->iPlaArr[j][1]/4==pDdz->iPlaArr[j][2]/4&&pDdz->iPlaArr[j][2]/4==pDdz->iPlaArr[j][3]/4)//如果推荐的出牌是炸弹
						 {
                                
                                for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//将其全部置为-1
								goto end;
						 }
					else if(pDdz->iPlaArr[j][0]/4==13&&pDdz->iPlaArr[j][1]/4==13)//推荐出牌为大小王
					{
						  for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//将其全部置为-1
						  goto end;
					}
				 

			 }
	  }


end:	pDdz->iToTable[i] = -1;


}



double CalCardsValue(int iPlaOnHand[])	
{

	double sum_count=100,one_sum=0,two_sum=0,three_sum=0;//分
	     
	int  i;
	int  x;
    int j;
	int  card_stye_deal[3][17] = {-1}; //处理的牌
	int birst=0;//炸弹数量
	int one_cards_count = 0,two_cards_count=0,	Car_count=0;        

	for(i=0;i<15;i++)
	{
	card_stye_deal[0][i+3]=i+3;
	}//存储牌值3 4 5 6 .......
	for (i = 0; iPlaOnHand[i] >= 0; i++)  
	{//手中的牌
		sum_count = sum_count - 2 ;                  //每多一张牌分数减2分
		x = iPlaOnHand[i] / 4 + 3;//判断牌是多少3 4 5 .......
		card_stye_deal[1][x]++;//判断牌值所对应的牌的张数
		Car_count++; //手中剩余牌的数量

	}
	//如果手中没牌，为最大估分，加10000  
	if (Car_count == 0)
	{
		sum_count =sum_count+ 1000000;
	}


	//  手中剩余牌的话

	else {
		if (card_stye_deal[1][14] > 0)         //A
		{
			if (card_stye_deal[1][14] == 1)//1张
			{
				sum_count +=2;
			}
			else if (card_stye_deal[1][14] == 2)//2张
			{
				sum_count+=4;
			}
			else if (card_stye_deal[1][11] == 3)//3张
			{
				sum_count+=6;
			}
		}
		if (card_stye_deal[1][15]>0)//2
		{
			if (card_stye_deal[1][15] == 1)   // 1张    
			{
				sum_count+=3;
			}
			else if (card_stye_deal[1][15] == 2)//2张
			{
				sum_count+=5;
			}
			else if (card_stye_deal[1][15] == 3)//3张
			{
			sum_count+=7;
			}

		}
		if (card_stye_deal[1][16]>0)                  //王
		{
			if (card_stye_deal[1][16] == 1)
			{
				sum_count+=5;             //一个王
			}
			else if (card_stye_deal[1][16] == 2)
			{
				sum_count+=10 ;  //两个王     
			}
		}
		//手中剩余大于5张牌
	if (Car_count>5)      //构成双顺后的单牌统计
			{
				for (i = 0; i<5; i++)
				{
				if (card_stye_deal[1][i] == 4)        //炸弹的数量
				{
					birst++;
				}
					card_stye_deal[2][i] = card_stye_deal[1][i] - 2;//比较是否是双以上
					if (card_stye_deal[2][i] == 1)//三个一样的个数
					{
						two_cards_count++;
					}
				
				if (card_stye_deal[1][i]>1 && card_stye_deal[1][i + 1]>1 && card_stye_deal[1][i + 2]>1)  //双顺  
				{
					two_sum = 	two_sum+30;//3个
					if (card_stye_deal[1][i + 3]>1)       //4个顺
					{
						two_sum = 	two_sum+40;
						if (card_stye_deal[1][i + 4]>1)   //5个顺
						{
						two_sum = 	two_sum+50;
						}
					}
				}


				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //单顺估值
					{

						one_sum = one_sum + 5.5;				   
						if (card_stye_deal[1][i + 5]>0)         
						{

				        	one_sum = one_sum + 6.5;
							if (card_stye_deal[1][i + 6]>0)    
							{

							one_sum = one_sum + 7;
	                        if(card_stye_deal[1][i + 7]>0)
							{

									one_sum = one_sum +8;
									if(card_stye_deal[1][i + 8]>0)
									{
                                    one_sum = one_sum +10;

							       if(card_stye_deal[1][i + 9]>0)
								   {
								    one_sum = one_sum +13;
									}
									}
							}

							





							}
						}
					}
				sum_count=two_sum+sum_count+birst*25+sum_count+one_sum*2;	
				}
				//sum_count=two_sum+sum_count+birst*25;

			}
			

		if (Car_count>5)       //手中的牌大 于五张，可以构成单顺
		{

			for (i = 0; i<15; i++)            //分类估分前的准备    
			{
				if (card_stye_deal[1][i] == 4)        //炸弹的数量
				{
					birst++;
				}
			
			   card_stye_deal[2][i] =card_stye_deal[1][i] - 1;      //除去构成单顺的可能  Paid[2][i]为独牌的情况
					if (card_stye_deal[2][i] == 1)
					{
						one_cards_count ++;//单独的牌的数量
					}
					sum_count =sum_count+one_cards_count *1.5+birst*25;  
			
			}
		
   
			for (i = 0; i<15; i++)    //只用考虑 3~A
			{
				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //单顺估值
					{

						one_sum = one_sum + 5.5;				   
						if (card_stye_deal[1][i + 5]>0)         
						{

				        	one_sum = one_sum + 6.5;
							if (card_stye_deal[1][i + 6]>0)    
							{

							one_sum = one_sum + 7;
							if(card_stye_deal[1][i + 7]>0)
							{

									one_sum = one_sum +8;
									if(card_stye_deal[1][i + 8]>0)
									{
                                    one_sum = one_sum +10;

							       if(card_stye_deal[1][i + 9]>0)
								   {
								    one_sum = one_sum +13;
									}
									}
							}

							}
						
						}
					}
				sum_count=sum_count+one_sum*2;	

			}
			
		}

		/*

		residue_card_count14(int iPlaOnHand[]);//剩余14以上张牌时

	residue_card_coun10(int iPlaOnHand[]);//剩余10以上张牌时
		residue_card_count7(int iPlaOnHand[]);//剩余7以上张牌时
				residue_card_count5(int iPlaOnHand[]);//剩余5以上张牌时
				residue_card_count3(int iPlaOnHand[]);//剩余3以上张牌时
					residue_card_count0(int iPlaOnHand[]);//剩余  0以上张牌时




*/

	else if (Car_count == 3)  
		{
			int remain_count = 0;
			int  three_cards_same=0;
			int  two_cards_same=0;
			int  one_cards_same=0;
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 3)//最后三张一样
				{
			          remain_count=remain_count+13;
				}
				else if (card_stye_deal[1][i] == 2)//有两张一样
				{
		             	remain_count=remain_count+11;
				}

		     	else
				{                    //三张各不相同
	
			      	if (card_stye_deal[0][i]<10) //牌小于10 
					{
					  remain_count=remain_count + 5 ;
	
					}
				    else
					{        //牌大于10
					
					remain_count=remain_count +47;
					}
				}
					sum_count=remain_count;
			}
	
		}

		

else if (Car_count == 2)//手牌剩余2张时
		{
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 2)//相同
				{
				sum_count = sum_count +8;

				}
				else
				{          //不相同         
					for (j = 17; j >= 0; j--)
					{
						if (card_stye_deal[1][i] == 1)
						{
						sum_count = sum_count +45;
						}
					}
				}
			}
		}
		else
		{
			sum_count = sum_count +1000;
		}
	
		}
	return	sum_count ;
}
		
double CalCardsValue1(int iPlaOnHand[])
{

	double sum_count=100,one_sum=0,two_sum=0,three_sum=0;//分
	     
	int  i;
	int  x;
    int j;
	int  card_stye_deal[3][17] = {-1}; //处理的牌
	int birst=0;//炸弹数量
	int one_cards_count = 0,two_cards_count=0,	Car_count=0;        

	for(i=0;i<15;i++)
	{
	card_stye_deal[0][i+3]=i+3;
	}//存储牌值3 4 5 6 .......
	for (i = 0; iPlaOnHand[i] >= 0; i++)  
	{//手中的牌
		sum_count = sum_count - 2   ;                //每多一张牌分数减2分
		x = iPlaOnHand[i] / 4 + 3;//判断牌是多少3 4 5 .......
		card_stye_deal[1][x]++;//判断牌值所对应的牌的张数
		Car_count++; //手中剩余牌的数量

	}
	//如果手中没牌，为最大估分，加10000  
	if (Car_count == 0)
	{
		sum_count =sum_count+ 1000000;
	}


	//  手中剩余牌的话

	else {
		if (card_stye_deal[1][14] > 0)         //A
		{
			if (card_stye_deal[1][14] == 1)//1张
			{
				sum_count +=3;
			}
			else if (card_stye_deal[1][14] == 2)//2张
			{
				sum_count+=5;
			}
			else if (card_stye_deal[1][11] == 3)//3张
			{
				sum_count+=8;
			}
		}
		if (card_stye_deal[1][15]>0)//2
		{
			if (card_stye_deal[1][15] == 1)   // 1张    
			{
				sum_count+=2;
			}
			else if (card_stye_deal[1][15] == 2)//2张
			{
				sum_count+=4;
			}
			else if (card_stye_deal[1][15] == 3)//3张
			{
			sum_count+=6;
			}

		}
		if (card_stye_deal[1][16]>0)                  //王
		{
			if (card_stye_deal[1][16] == 1)
			{
				sum_count+=5;             //一个王
			}
			else if (card_stye_deal[1][16] == 2)
			{
				sum_count+=10 ;  //两个王     
			}
		}
		//手中剩余大于5张牌
	if (Car_count>5)      //构成双顺后的单牌统计
			{
				for (i = 0; i<5; i++)
				{
				if (card_stye_deal[1][i] == 4)        //炸弹的数量
				{
					birst++;
				}
					card_stye_deal[2][i] = card_stye_deal[1][i] - 2;//比较是否是双以上
					if (card_stye_deal[2][i] == 1)//三个一样的个数
					{
						two_cards_count++;
					}
				
				if (card_stye_deal[1][i]>1 && card_stye_deal[1][i + 1]>1 && card_stye_deal[1][i + 2]>1)  //双顺  
				{
					two_sum = 	two_sum+30;//3个
					if (card_stye_deal[1][i + 3]>1)       //4个顺
					{
						two_sum = 	two_sum+40;
						if (card_stye_deal[1][i + 4]>1)   
						{
						two_sum = 	two_sum+50;
						}
					}
				}


				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //单顺估值
					{

						one_sum = one_sum + 5.5;				   
						if (card_stye_deal[1][i + 5]>0)         
						{

				        	one_sum = one_sum + 6.5;
							if (card_stye_deal[1][i + 6]>0)    
							{

							one_sum = one_sum + 7;
	                        if(card_stye_deal[1][i + 7]>0)
							{

									one_sum = one_sum +8;
									if(card_stye_deal[1][i + 8]>0)
									{
                                    one_sum = one_sum +10;

							       if(card_stye_deal[1][i + 9]>0)
								   {
								    one_sum = one_sum +13;
									}
									}
							}

							





							}
						}
					}
				sum_count=two_sum+sum_count+birst*25+sum_count+one_sum*2;	
				}
				//sum_count=two_sum+sum_count+birst*25;

			}
			

		if (Car_count>4)       //手中的牌大 于五张，可以构成单顺
		{

			for (i = 0; i<15; i++)            //分类估分前的准备    
			{
				if (card_stye_deal[1][i] == 4)        //炸弹的数量
				{
					birst++;
				}
			
			   card_stye_deal[2][i] =card_stye_deal[1][i] - 1;      //除去构成单顺的可能  Paid[2][i]为独牌的情况
					if (card_stye_deal[2][i] == 1)
					{
						one_cards_count ++;//单独的牌的数量
					}
					sum_count =sum_count+one_cards_count *1.5+birst*25;  
			
			}
		
   
			for (i = 0; i<15; i++)    //只用考虑 3~A
			{
				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //单顺估值
					{

						one_sum = one_sum + 5.5;				   
						if (card_stye_deal[1][i + 5]>0)         
						{

				        	one_sum = one_sum + 6.5;
							if (card_stye_deal[1][i + 6]>0)    
							{

							one_sum = one_sum + 7;
							if(card_stye_deal[1][i + 7]>0)
							{

									one_sum = one_sum +8;
									if(card_stye_deal[1][i + 8]>0)
									{
                                    one_sum = one_sum +10;

							       if(card_stye_deal[1][i + 9]>0)
								   {
								    one_sum = one_sum +13;
									}
									}
							}

							}
						
						}
					}
				sum_count=sum_count+one_sum*2;	

			}
			
		}

		/*

		residue_card_count14(int iPlaOnHand[]);//剩余14以上张牌时

	residue_card_coun10(int iPlaOnHand[]);//剩余10以上张牌时
		residue_card_count7(int iPlaOnHand[]);//剩余7以上张牌时
				residue_card_count5(int iPlaOnHand[]);//剩余5以上张牌时
				residue_card_count3(int iPlaOnHand[]);//剩余3以上张牌时
					residue_card_count0(int iPlaOnHand[]);//剩余  0以上张牌时




*/

	else if (Car_count == 3)  
		{
			int remain_count = 0;
			int  three_cards_same=0;
			int  two_cards_same=0;
			int  one_cards_same=0;
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 3)//最后三张一样
				{
			          remain_count=remain_count+13;
				}
				else if (card_stye_deal[1][i] == 2)//有两张一样
				{
		             	remain_count=remain_count+11;
				}

		     	else
				{                    //三张各不相同
	
			      	if (card_stye_deal[0][i]<10) //牌小于10 
					{
					  remain_count=remain_count + 5 ;
	
					}
				    else
					{        //牌大于10
					
					remain_count=remain_count +47;
					}
				}
					sum_count=remain_count;
			}
	
		}

		

else if (Car_count == 2)//手牌剩余2张时
		{
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 2)//相同
				{
				sum_count = sum_count +8;

				}
				else
				{          //不相同         
					for (j = 17; j >= 0; j--)
					{
						if (card_stye_deal[1][i] == 1)
						{
						sum_count = sum_count +45;
						}
					}
				}
			}
		}
		else
		{
			sum_count = sum_count +1000;
		}
	
		}
	return	sum_count ;
}





double CalCardsValue2(int iPlaOnHand[])
{

	double  dSum = 100, dSum1 = 0, dSum2 = 0, dSum3 = 0;     
	int  i;
	int  x;
	int  j;
	int  Pai[3][14] = { 0 };                    //处理后的牌
	int  Zd = 0, Dz1 = 0, Dz2 = 0;     //Zd:炸弹的数量，Dz1：统计后的单牌的数量，Dz2：为统计后的双牌的后剩余单牌的数量
	int   Car_count = 0;               //手中剩余牌的数量
	for (i = 0; i<14; i++)            //初始赋值
	{
		Pai[0][i] = i + 3;

	}
	for (i = 0; iPlaOnHand[i] >= 0; i++)     //统计手中的牌（存入数组）
	{
		dSum = dSum - 3;                   //每多一张牌分数减 3
		x = iPlaOnHand[i] / 4 + 3;
		Pai[1][x]++;
		Car_count++;

	}
	//如果手中没牌，为最大估分，加10000  
	if (Car_count == 0)
	{
		dSum = dSum + 10000;
	}

	//  手中剩余牌的话

	else {
		if (Pai[1][11] > 0)         //A：每次加2；
		{
			if (Pai[1][11] == 1)
			{
				dSum = dSum + 4;
			}
			else if (Pai[1][11] == 2)
			{
				dSum = dSum + 2;
			}
			else if (Pai[1][11] == 3)
			{
				dSum = dSum + 1;
			}
		}
		if (Pai[1][12]>0)
		{
			if (Pai[1][12] == 1)         //2：每次加3
			{
				dSum = dSum + 3;
			}
			else if (Pai[1][12] == 2)
			{
				dSum = dSum + 1;
			}
			else if (Pai[1][12] == 3)
			{
				dSum = dSum +0.7;
			}

		}
		if (Pai[1][13]>0)                  //王:每次加5分
		{
			if (Pai[1][13] == 1)
			{
				dSum = dSum + 15;             //一个王
			}
			else if (Pai[1][13] == 2)
			{
				dSum = dSum + 25;      //两个王     
			}
		}

		


		if (Car_count>4)       //手中的牌大 于五张，可以构成单顺
		{

			for (i = 0; i<13; i++)            //分类估分前的准备    
			{
				if (Pai[1][i] == 4)        //炸弹的数量(满足四张牌)
				{
					Zd++;
				}
				if (i<12)                   //只对小于A的牌分析
				{
					Pai[2][i] = Pai[1][i] - 1;      //除去构成单顺的可能  Paid[2][i]为独牌的情况
					if (Pai[2][i] == 1)
					{
						Dz1++;     //单独的牌
					}
				}
			}
			dSum = dSum + Zd * 11;   //估分加上炸弹
			dSum1 = dSum2 = dSum3 = dSum;


			for (i = 0; i<12; i++)    //只用考虑 3~A
			{
				if (i<8)  //但顺最少5张牌
				{
					if (Pai[1][i]>0 && Pai[1][i + 1]>0 && Pai[1][i + 2]>0 && Pai[1][i + 3] && Pai[1][i + 4]>0) //单顺估值
					{

						dSum1 = dSum1 + 5;				     // 至少构成五顺 +5；
						if (i<12 && Pai[1][i + 5]>0)           //构成六顺 加3；
						{

							dSum1 = dSum1 + 3;
							if (i<12 && Pai[1][i + 6]>0)     //构成七顺 再加 3；
							{

								dSum1 = dSum1 + 3;
							}
						}
					}
				}
			}
			dSum1 = dSum1 - Dz1 * 4;  //单顺的得分


			if (Car_count>5)      //构成双顺后的单牌统计
			{
				for (i = 0; i<12; i++)
				{
					Pai[2][i] = Pai[1][i] - 2;
					if (Pai[2][i] == 1)
					{
						Dz2++;
					}
				}
				if (Pai[1][i]>1 && Pai[1][i + 1]>1 && Pai[1][i + 2]>1)    //3AA
				{
					dSum2 = dSum2 + 10;
					if (Pai[1][i + 3]>1)       //4AA
					{
						dSum2 = dSum2 + 6;
						if (Pai[1][i + 4]>1)   //5AA 目前只考虑到最大5连顺的情况
						{
							dSum2 = dSum2 + 6;
						}
					}
				}
				dSum2 = dSum2 - Dz2 * 4;
				if (Dz1<Dz2)   //剩余牌最少为优
				{
					dSum = dSum1;

				}
				else if (Dz1>Dz2)
				{
					dSum = dSum2;

				}
				else   //如果剩余牌的数量一样，估分最好的为优
				{
					if (dSum1>dSum2)
					{
						dSum = dSum1;
					}
					else
					{
						dSum = dSum2;
					}
				}

			}
			else   //如果不能构成双顺
			{
				dSum = dSum1;
			}
		}
		else

		if (Car_count == 4)                      //手中的牌数少于5张牌时，为决定牌局胜负的关键，因此格外注意
		{
			int  L1 = 0;                     //L1为小牌的数量
			int  sum4 = 0;
			int  sum3 = 0;
			int  sum2 = 0;
			for (i = 0; i < 14; i++)
			{
				if (Pai[1][i] == 4)      //如果最后四张牌是炸弹
				{
					sum4++;
				}
				else  if (Pai[1][i] == 3)  //如果最后三张牌是AAA型
				{
					sum3++;
				}
				else if (Pai[1][i] == 2)  //如果最后四张牌中含有双
				{
					sum2++;
				}
			}
			if (sum4 > 0)        //如果有炸弹，估份最高 
			{
				dSum = dSum *20;
			}
			else if (sum3 > 0)  //如果有AAA，估分次高
			{
				dSum = dSum * 15;
			}
			else if (sum2 > 0)  //如果含双，估分第三高
			{
				dSum = dSum * 10;
			}
			else {                //以上情况都不存在的话
				for (i = 0; i < 14; i++)
				{
					if (i < 11)   //小于10（小牌）
					{
						L1++;
					}
				}
				if (L1 >= 2)     // 小牌多（建议先出小牌）三张或两张
				{
					for (i = 0; i < 14; i++)
					{
						if (Pai[1][i] == 1)
							dSum = dSum + i * 15;
					}
				}
				else  {
					for (i = 10; i < 14; i++)
					{
						if (Pai[1][i] == 1)
						{
							dSum = dSum + (14 - i) * 12;
						}
					}
				}
			}
		}

		else if (Car_count == 3)   //剩余三张牌	
		{
			int sum3 = 0;
			int sum2 = 0;
			int L = 0;
			for (i = 0; i < 14; i++)
			{
				if (Pai[1][i] == 3)
				{
					sum3++;
				}
				else if (Pai[1][i] == 2)
				{
					sum2++;
				}
			}
			if (sum3 > 0)
			{
				dSum = dSum * 3;
			}
			else if (sum2 > 0)
			{
				dSum = dSum * 2;
			}
			else {                     //三张独牌
				for (i = 0; i < 10; i++)
				{
					L++;
				}
				if (L == 3 || L == 2)  //三张小牌，从小到大出
				{
					for (i = 0; i < 10; i++)
					{
						if (Pai[1][i] == 1) //（小牌估分高）
						{
							dSum = dSum + 10 * (L - 1);
							break;
						}
					}
				}
				else {         //从大往小出  (大牌估分低)
					for (i = 13; i >= 0; i--)
					{
						if (Pai[1][i] == 1)
						{
							dSum = dSum + 5 * (L - 1);
						}
					}
				}
			}
		}
		else if (Car_count == 2)
		{
			for (i = 0; i < 14; i++)
			{
				if (Pai[1][i] == 2)
				{
					dSum = dSum * 3;

				}
				else {                    //最大的先出(估分低)
					for (j = 13; j >= 0; j--)
					{
						if (Pai[1][i] == 1)
						{
							dSum = dSum + dSum*i;
						}
					}
				}
			}
		}
		else
		{
			dSum = dSum * 1000;
		}
	}
	return dSum;
}



//叫分策略
//修订者:KL
//2016 8 16 9:15

int CalBid(struct Ddz * pDdz)
{
int iMyBid=0;
	int i,j=0;
		
	int sum = 0;
	int count=0;
	int first_hand_cards[17];
	for (i = 0; i < 17; i++)
	{
		first_hand_cards[i] = pDdz->iOnHand[i];
	}        

	for (i = 0; i < 17;i++)
	{
		if (first_hand_cards[i] == 52 && first_hand_cards[i+1]== 53)//火箭 
		{
			sum = sum + 10;
		}

		else if (first_hand_cards[i] / 4 == first_hand_cards[i + 1] / 4 && first_hand_cards[i + 1] / 4 == first_hand_cards[i + 2] / 4 &&    
			first_hand_cards[i + 2] / 4 ==first_hand_cards[i + 3] / 4 )
		{
			sum = sum + 6;
		}
		else  if (first_hand_cards[i] == 48 || first_hand_cards[i] == 49 || first_hand_cards[i] == 50 || first_hand_cards[i] == 51)  //2的张数
		{
			sum = sum + 2;
		}
		else if (first_hand_cards[i] == 52 || first_hand_cards[i] == 53)       //大或小王
		{
			sum = sum + 3;
		}
	}

     if (sum >= 8)
	{
		count = 3;
	}

	else if (sum >= 6)
	{
		count= 2;
	}
	else  if (sum >= 3)
	{
count= 1;
	}
	
	else  {
	count = 0;
	}


    for(j=0;j<3;j++)
	{
	if (pDdz->iBid[i] >= count)
	{
    	count= 0;
     goto bdgi;
   }
	bdgi:iMyBid=count;
	}

	return iMyBid;
}


//I02-END



void CalPla(struct Ddz * pDdz	)//计算出牌方法	
{


    two_other_already(pDdz);

different_select(pDdz,last_landowner,next_landowner,my_landwoner);



}



int	main( )	
{
	
	struct Ddz tDdz, *pDdz=&tDdz;
	InitTurn(pDdz);			//初始化数据
	while(pDdz->iStatus!=0)
	{
		InputMsg(pDdz);			//输入信息
		AnalyzeMsg(pDdz);		//分析处理信息
		OutputMsg(pDdz);		//输出信息
		CalOthers(pDdz);		//计算其它数据
	}
	return 0;
}