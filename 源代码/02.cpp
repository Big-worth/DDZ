#define kPlayerName "����ֹ��"
#define kPlaMax 500
#include "DdzV200.h"

char last_landowner='A';//��ʼ��
char next_landowner='A';
char my_landwoner='A';

int other_statistics=1;//ͳ�Ʒ��ʴ���Ϊ���жϵ���λ��
void different_select(struct Ddz * pDdz,char last_landowner,char next_landowner,char my_landowner);//��������λ�ò�ͬ��ȡ��ͬ���Ʒ�ʽ
void last_landowner_come_method(struct Ddz * pDdz);//��һ���ǵ����ĳ��Ʒ���
void next_landowner_come_method(struct Ddz * pDdz);//��һ���ǵ����ĳ��Ʒ���
void my_landowner_come_method(struct Ddz * pDdz);//�Լ��ǵ����ĳ��Ʒ���

void two_other_already(struct Ddz * pDdz);//�жϵ���λ��
double CalCardsValue(int iPlaOnHand[]);//��һ���ǵ����Ĺ�ֵ����
double CalCardsValue1(int iPlaOnHand[]);//��һ���ǵ����Ĺ�ֵ����
double CalCardsValue2(int iPlaOnHand[]);//�Լ��ǵ����Ĺ�ֵ����		



void two_other_already(struct Ddz * pDdz)//�жϵ���λ��
{
	
	while(other_statistics==1)
	{
          if(pDdz->iLastPassCount==0&&pDdz->iOTmax==1)//�Լ���һ���ǵ���
		  {
           last_landowner=pDdz->cLandlord;//�޸�ȫ�ֱ���ֵ
		  
		  }
      else if(pDdz->iLastPassCount==0&&pDdz->iOTmax==2||pDdz->iLastPassCount==1&&pDdz->iOTmax==1)//�Լ���һ���ǵ���
		{
        next_landowner=pDdz->cLandlord;
	

		}
	  else
	  {
		  my_landwoner=pDdz->cLandlord;
		
	  }
       other_statistics++;//�ı�ȫ�ֱ���

	}
other_statistics=1;
/*
	if(pDdz->iStatus<1)//	int  iStatus;			//����״̬-1����,0����,1��ʼ
	{

	 other_statistics=1;//һ�ֽ����������ݽ�����һ��
	}*/
}


void different_select(struct Ddz * pDdz,char last_landowner,char next_landowner,char my_landowner)//����λ�ò�ͬѡ��ͬ�ĳ��Ʒ���
{
   if(last_landowner==pDdz->cLandlord)//��һ���ǵ����ĳ��Ʒ���
	{
	 last_landowner_come_method(pDdz);

	}
   else if(next_landowner==pDdz->cLandlord)//��һ���ǵ����ĳ��Ʒ���
	{
	next_landowner_come_method(pDdz);

	}
	else if(my_landowner==pDdz->cLandlord)//�Լ��ǵ����ĳ��Ʒ���
	{
		my_landowner_come_method(pDdz);

	}

}





void last_landowner_come_method(struct Ddz * pDdz)//��һ���ǵ����ĳ��Ʒ�ʽ���ù�ֵ��
{
		int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//��Ҫ�����Ƽ�����pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//����ȡ���˵�i���ƣ���ʣ����Ʒ���pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue(pDdz->iPlaOnHand);			//�������ƹ�ֵ
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}
	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];
	pDdz->iToTable[i] = -1;

		if(pDdz->iOTmax<22)//���ִ�����22����ʱ��������
		 {
				 for(int j=0;j<iMax;j++)
				 {
		            if(pDdz->iPlaArr[j][0]/4==pDdz->iPlaArr[j][1]/4&&pDdz->iPlaArr[j][1]/4==pDdz->iPlaArr[j][2]/4&&pDdz->iPlaArr[j][2]/4==pDdz->iPlaArr[j][3]/4)//����Ƽ��ĳ�����ը��
						 {
                                
                                for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//����ȫ����Ϊ-1
								goto end;
						 }
					else if(pDdz->iPlaArr[j][0]/4==13&&pDdz->iPlaArr[j][1]/4==13)//�Ƽ�����Ϊ��С��
					{
						  for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//����ȫ����Ϊ-1
						  goto end;
					}
				 

			 }
	  }


end:	pDdz->iToTable[i] = -1;
}


void next_landowner_come_method(struct Ddz * pDdz)//��һ���ǵ����ĳ��Ʒ�ʽ
{
	
        
	int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//��Ҫ�����Ƽ�����pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//����ȡ���˵�i���ƣ���ʣ����Ʒ���pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue1(pDdz->iPlaOnHand);
		//�������ƹ�ֵ
	
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}
	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)

		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];//�õ���Ҫ������
  	
	 
	
	



}


void my_landowner_come_method(struct Ddz * pDdz)//�Լ��ǵ����ĳ��Ʒ�ʽ
{

 	int i;
	double dValueNow;
	double dValueMax=-9999;
	int iMax = 0;
	HelpPla(pDdz);				//��Ҫ�����Ƽ�����pDdz->iPlaArr[],pDdz->iPlaCount
	for(i=0;i<pDdz->iPlaCount;i++)
	{
		HelpTakeOff(pDdz,i);	//����ȡ���˵�i���ƣ���ʣ����Ʒ���pDdz->iPlaOnHand[]
		dValueNow = CalCardsValue2(pDdz->iPlaOnHand);			//�������ƹ�ֵ
		if (dValueNow > dValueMax)
		{
			dValueMax = dValueNow;
			iMax = i;
		}
	}

	for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
		pDdz->iToTable[i] = pDdz->iPlaArr[iMax][i];


	if(pDdz->iOTmax<22)//���ִ�����22����ʱ��������
		 {
				 for(int j=0;j<iMax;j++)
				 {
		            if(pDdz->iPlaArr[j][0]/4==pDdz->iPlaArr[j][1]/4&&pDdz->iPlaArr[j][1]/4==pDdz->iPlaArr[j][2]/4&&pDdz->iPlaArr[j][2]/4==pDdz->iPlaArr[j][3]/4)//����Ƽ��ĳ�����ը��
						 {
                                
                                for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//����ȫ����Ϊ-1
								goto end;
						 }
					else if(pDdz->iPlaArr[j][0]/4==13&&pDdz->iPlaArr[j][1]/4==13)//�Ƽ�����Ϊ��С��
					{
						  for (i = 0;pDdz->iPlaArr[iMax][i] >= 0; i++)
                             pDdz->iToTable[i] = -1;//����ȫ����Ϊ-1
						  goto end;
					}
				 

			 }
	  }


end:	pDdz->iToTable[i] = -1;


}



double CalCardsValue(int iPlaOnHand[])	
{

	double sum_count=100,one_sum=0,two_sum=0,three_sum=0;//��
	     
	int  i;
	int  x;
    int j;
	int  card_stye_deal[3][17] = {-1}; //�������
	int birst=0;//ը������
	int one_cards_count = 0,two_cards_count=0,	Car_count=0;        

	for(i=0;i<15;i++)
	{
	card_stye_deal[0][i+3]=i+3;
	}//�洢��ֵ3 4 5 6 .......
	for (i = 0; iPlaOnHand[i] >= 0; i++)  
	{//���е���
		sum_count = sum_count - 2 ;                  //ÿ��һ���Ʒ�����2��
		x = iPlaOnHand[i] / 4 + 3;//�ж����Ƕ���3 4 5 .......
		card_stye_deal[1][x]++;//�ж���ֵ����Ӧ���Ƶ�����
		Car_count++; //����ʣ���Ƶ�����

	}
	//�������û�ƣ�Ϊ�����֣���10000  
	if (Car_count == 0)
	{
		sum_count =sum_count+ 1000000;
	}


	//  ����ʣ���ƵĻ�

	else {
		if (card_stye_deal[1][14] > 0)         //A
		{
			if (card_stye_deal[1][14] == 1)//1��
			{
				sum_count +=2;
			}
			else if (card_stye_deal[1][14] == 2)//2��
			{
				sum_count+=4;
			}
			else if (card_stye_deal[1][11] == 3)//3��
			{
				sum_count+=6;
			}
		}
		if (card_stye_deal[1][15]>0)//2
		{
			if (card_stye_deal[1][15] == 1)   // 1��    
			{
				sum_count+=3;
			}
			else if (card_stye_deal[1][15] == 2)//2��
			{
				sum_count+=5;
			}
			else if (card_stye_deal[1][15] == 3)//3��
			{
			sum_count+=7;
			}

		}
		if (card_stye_deal[1][16]>0)                  //��
		{
			if (card_stye_deal[1][16] == 1)
			{
				sum_count+=5;             //һ����
			}
			else if (card_stye_deal[1][16] == 2)
			{
				sum_count+=10 ;  //������     
			}
		}
		//����ʣ�����5����
	if (Car_count>5)      //����˫˳��ĵ���ͳ��
			{
				for (i = 0; i<5; i++)
				{
				if (card_stye_deal[1][i] == 4)        //ը��������
				{
					birst++;
				}
					card_stye_deal[2][i] = card_stye_deal[1][i] - 2;//�Ƚ��Ƿ���˫����
					if (card_stye_deal[2][i] == 1)//����һ���ĸ���
					{
						two_cards_count++;
					}
				
				if (card_stye_deal[1][i]>1 && card_stye_deal[1][i + 1]>1 && card_stye_deal[1][i + 2]>1)  //˫˳  
				{
					two_sum = 	two_sum+30;//3��
					if (card_stye_deal[1][i + 3]>1)       //4��˳
					{
						two_sum = 	two_sum+40;
						if (card_stye_deal[1][i + 4]>1)   //5��˳
						{
						two_sum = 	two_sum+50;
						}
					}
				}


				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //��˳��ֵ
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
			

		if (Car_count>5)       //���е��ƴ� �����ţ����Թ��ɵ�˳
		{

			for (i = 0; i<15; i++)            //�������ǰ��׼��    
			{
				if (card_stye_deal[1][i] == 4)        //ը��������
				{
					birst++;
				}
			
			   card_stye_deal[2][i] =card_stye_deal[1][i] - 1;      //��ȥ���ɵ�˳�Ŀ���  Paid[2][i]Ϊ���Ƶ����
					if (card_stye_deal[2][i] == 1)
					{
						one_cards_count ++;//�������Ƶ�����
					}
					sum_count =sum_count+one_cards_count *1.5+birst*25;  
			
			}
		
   
			for (i = 0; i<15; i++)    //ֻ�ÿ��� 3~A
			{
				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //��˳��ֵ
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

		residue_card_count14(int iPlaOnHand[]);//ʣ��14��������ʱ

	residue_card_coun10(int iPlaOnHand[]);//ʣ��10��������ʱ
		residue_card_count7(int iPlaOnHand[]);//ʣ��7��������ʱ
				residue_card_count5(int iPlaOnHand[]);//ʣ��5��������ʱ
				residue_card_count3(int iPlaOnHand[]);//ʣ��3��������ʱ
					residue_card_count0(int iPlaOnHand[]);//ʣ��  0��������ʱ




*/

	else if (Car_count == 3)  
		{
			int remain_count = 0;
			int  three_cards_same=0;
			int  two_cards_same=0;
			int  one_cards_same=0;
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 3)//�������һ��
				{
			          remain_count=remain_count+13;
				}
				else if (card_stye_deal[1][i] == 2)//������һ��
				{
		             	remain_count=remain_count+11;
				}

		     	else
				{                    //���Ÿ�����ͬ
	
			      	if (card_stye_deal[0][i]<10) //��С��10 
					{
					  remain_count=remain_count + 5 ;
	
					}
				    else
					{        //�ƴ���10
					
					remain_count=remain_count +47;
					}
				}
					sum_count=remain_count;
			}
	
		}

		

else if (Car_count == 2)//����ʣ��2��ʱ
		{
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 2)//��ͬ
				{
				sum_count = sum_count +8;

				}
				else
				{          //����ͬ         
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

	double sum_count=100,one_sum=0,two_sum=0,three_sum=0;//��
	     
	int  i;
	int  x;
    int j;
	int  card_stye_deal[3][17] = {-1}; //�������
	int birst=0;//ը������
	int one_cards_count = 0,two_cards_count=0,	Car_count=0;        

	for(i=0;i<15;i++)
	{
	card_stye_deal[0][i+3]=i+3;
	}//�洢��ֵ3 4 5 6 .......
	for (i = 0; iPlaOnHand[i] >= 0; i++)  
	{//���е���
		sum_count = sum_count - 2   ;                //ÿ��һ���Ʒ�����2��
		x = iPlaOnHand[i] / 4 + 3;//�ж����Ƕ���3 4 5 .......
		card_stye_deal[1][x]++;//�ж���ֵ����Ӧ���Ƶ�����
		Car_count++; //����ʣ���Ƶ�����

	}
	//�������û�ƣ�Ϊ�����֣���10000  
	if (Car_count == 0)
	{
		sum_count =sum_count+ 1000000;
	}


	//  ����ʣ���ƵĻ�

	else {
		if (card_stye_deal[1][14] > 0)         //A
		{
			if (card_stye_deal[1][14] == 1)//1��
			{
				sum_count +=3;
			}
			else if (card_stye_deal[1][14] == 2)//2��
			{
				sum_count+=5;
			}
			else if (card_stye_deal[1][11] == 3)//3��
			{
				sum_count+=8;
			}
		}
		if (card_stye_deal[1][15]>0)//2
		{
			if (card_stye_deal[1][15] == 1)   // 1��    
			{
				sum_count+=2;
			}
			else if (card_stye_deal[1][15] == 2)//2��
			{
				sum_count+=4;
			}
			else if (card_stye_deal[1][15] == 3)//3��
			{
			sum_count+=6;
			}

		}
		if (card_stye_deal[1][16]>0)                  //��
		{
			if (card_stye_deal[1][16] == 1)
			{
				sum_count+=5;             //һ����
			}
			else if (card_stye_deal[1][16] == 2)
			{
				sum_count+=10 ;  //������     
			}
		}
		//����ʣ�����5����
	if (Car_count>5)      //����˫˳��ĵ���ͳ��
			{
				for (i = 0; i<5; i++)
				{
				if (card_stye_deal[1][i] == 4)        //ը��������
				{
					birst++;
				}
					card_stye_deal[2][i] = card_stye_deal[1][i] - 2;//�Ƚ��Ƿ���˫����
					if (card_stye_deal[2][i] == 1)//����һ���ĸ���
					{
						two_cards_count++;
					}
				
				if (card_stye_deal[1][i]>1 && card_stye_deal[1][i + 1]>1 && card_stye_deal[1][i + 2]>1)  //˫˳  
				{
					two_sum = 	two_sum+30;//3��
					if (card_stye_deal[1][i + 3]>1)       //4��˳
					{
						two_sum = 	two_sum+40;
						if (card_stye_deal[1][i + 4]>1)   
						{
						two_sum = 	two_sum+50;
						}
					}
				}


				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //��˳��ֵ
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
			

		if (Car_count>4)       //���е��ƴ� �����ţ����Թ��ɵ�˳
		{

			for (i = 0; i<15; i++)            //�������ǰ��׼��    
			{
				if (card_stye_deal[1][i] == 4)        //ը��������
				{
					birst++;
				}
			
			   card_stye_deal[2][i] =card_stye_deal[1][i] - 1;      //��ȥ���ɵ�˳�Ŀ���  Paid[2][i]Ϊ���Ƶ����
					if (card_stye_deal[2][i] == 1)
					{
						one_cards_count ++;//�������Ƶ�����
					}
					sum_count =sum_count+one_cards_count *1.5+birst*25;  
			
			}
		
   
			for (i = 0; i<15; i++)    //ֻ�ÿ��� 3~A
			{
				
					if (card_stye_deal[1][i]>0 && card_stye_deal[1][i + 1]>0 &&card_stye_deal[1][i + 2]>0 && card_stye_deal[1][i + 3] && card_stye_deal[1][i + 4]>0) //��˳��ֵ
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

		residue_card_count14(int iPlaOnHand[]);//ʣ��14��������ʱ

	residue_card_coun10(int iPlaOnHand[]);//ʣ��10��������ʱ
		residue_card_count7(int iPlaOnHand[]);//ʣ��7��������ʱ
				residue_card_count5(int iPlaOnHand[]);//ʣ��5��������ʱ
				residue_card_count3(int iPlaOnHand[]);//ʣ��3��������ʱ
					residue_card_count0(int iPlaOnHand[]);//ʣ��  0��������ʱ




*/

	else if (Car_count == 3)  
		{
			int remain_count = 0;
			int  three_cards_same=0;
			int  two_cards_same=0;
			int  one_cards_same=0;
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 3)//�������һ��
				{
			          remain_count=remain_count+13;
				}
				else if (card_stye_deal[1][i] == 2)//������һ��
				{
		             	remain_count=remain_count+11;
				}

		     	else
				{                    //���Ÿ�����ͬ
	
			      	if (card_stye_deal[0][i]<10) //��С��10 
					{
					  remain_count=remain_count + 5 ;
	
					}
				    else
					{        //�ƴ���10
					
					remain_count=remain_count +47;
					}
				}
					sum_count=remain_count;
			}
	
		}

		

else if (Car_count == 2)//����ʣ��2��ʱ
		{
			for (i = 0; i < 18; i++)
			{
				if (card_stye_deal[1][i] == 2)//��ͬ
				{
				sum_count = sum_count +8;

				}
				else
				{          //����ͬ         
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
	int  Pai[3][14] = { 0 };                    //��������
	int  Zd = 0, Dz1 = 0, Dz2 = 0;     //Zd:ը����������Dz1��ͳ�ƺ�ĵ��Ƶ�������Dz2��Ϊͳ�ƺ��˫�Ƶĺ�ʣ�൥�Ƶ�����
	int   Car_count = 0;               //����ʣ���Ƶ�����
	for (i = 0; i<14; i++)            //��ʼ��ֵ
	{
		Pai[0][i] = i + 3;

	}
	for (i = 0; iPlaOnHand[i] >= 0; i++)     //ͳ�����е��ƣ��������飩
	{
		dSum = dSum - 3;                   //ÿ��һ���Ʒ����� 3
		x = iPlaOnHand[i] / 4 + 3;
		Pai[1][x]++;
		Car_count++;

	}
	//�������û�ƣ�Ϊ�����֣���10000  
	if (Car_count == 0)
	{
		dSum = dSum + 10000;
	}

	//  ����ʣ���ƵĻ�

	else {
		if (Pai[1][11] > 0)         //A��ÿ�μ�2��
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
			if (Pai[1][12] == 1)         //2��ÿ�μ�3
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
		if (Pai[1][13]>0)                  //��:ÿ�μ�5��
		{
			if (Pai[1][13] == 1)
			{
				dSum = dSum + 15;             //һ����
			}
			else if (Pai[1][13] == 2)
			{
				dSum = dSum + 25;      //������     
			}
		}

		


		if (Car_count>4)       //���е��ƴ� �����ţ����Թ��ɵ�˳
		{

			for (i = 0; i<13; i++)            //�������ǰ��׼��    
			{
				if (Pai[1][i] == 4)        //ը��������(����������)
				{
					Zd++;
				}
				if (i<12)                   //ֻ��С��A���Ʒ���
				{
					Pai[2][i] = Pai[1][i] - 1;      //��ȥ���ɵ�˳�Ŀ���  Paid[2][i]Ϊ���Ƶ����
					if (Pai[2][i] == 1)
					{
						Dz1++;     //��������
					}
				}
			}
			dSum = dSum + Zd * 11;   //���ּ���ը��
			dSum1 = dSum2 = dSum3 = dSum;


			for (i = 0; i<12; i++)    //ֻ�ÿ��� 3~A
			{
				if (i<8)  //��˳����5����
				{
					if (Pai[1][i]>0 && Pai[1][i + 1]>0 && Pai[1][i + 2]>0 && Pai[1][i + 3] && Pai[1][i + 4]>0) //��˳��ֵ
					{

						dSum1 = dSum1 + 5;				     // ���ٹ�����˳ +5��
						if (i<12 && Pai[1][i + 5]>0)           //������˳ ��3��
						{

							dSum1 = dSum1 + 3;
							if (i<12 && Pai[1][i + 6]>0)     //������˳ �ټ� 3��
							{

								dSum1 = dSum1 + 3;
							}
						}
					}
				}
			}
			dSum1 = dSum1 - Dz1 * 4;  //��˳�ĵ÷�


			if (Car_count>5)      //����˫˳��ĵ���ͳ��
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
						if (Pai[1][i + 4]>1)   //5AA Ŀǰֻ���ǵ����5��˳�����
						{
							dSum2 = dSum2 + 6;
						}
					}
				}
				dSum2 = dSum2 - Dz2 * 4;
				if (Dz1<Dz2)   //ʣ��������Ϊ��
				{
					dSum = dSum1;

				}
				else if (Dz1>Dz2)
				{
					dSum = dSum2;

				}
				else   //���ʣ���Ƶ�����һ����������õ�Ϊ��
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
			else   //������ܹ���˫˳
			{
				dSum = dSum1;
			}
		}
		else

		if (Car_count == 4)                      //���е���������5����ʱ��Ϊ�����ƾ�ʤ���Ĺؼ�����˸���ע��
		{
			int  L1 = 0;                     //L1ΪС�Ƶ�����
			int  sum4 = 0;
			int  sum3 = 0;
			int  sum2 = 0;
			for (i = 0; i < 14; i++)
			{
				if (Pai[1][i] == 4)      //��������������ը��
				{
					sum4++;
				}
				else  if (Pai[1][i] == 3)  //��������������AAA��
				{
					sum3++;
				}
				else if (Pai[1][i] == 2)  //�������������к���˫
				{
					sum2++;
				}
			}
			if (sum4 > 0)        //�����ը����������� 
			{
				dSum = dSum *20;
			}
			else if (sum3 > 0)  //�����AAA�����ִθ�
			{
				dSum = dSum * 15;
			}
			else if (sum2 > 0)  //�����˫�����ֵ�����
			{
				dSum = dSum * 10;
			}
			else {                //��������������ڵĻ�
				for (i = 0; i < 14; i++)
				{
					if (i < 11)   //С��10��С�ƣ�
					{
						L1++;
					}
				}
				if (L1 >= 2)     // С�ƶࣨ�����ȳ�С�ƣ����Ż�����
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

		else if (Car_count == 3)   //ʣ��������	
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
			else {                     //���Ŷ���
				for (i = 0; i < 10; i++)
				{
					L++;
				}
				if (L == 3 || L == 2)  //����С�ƣ���С�����
				{
					for (i = 0; i < 10; i++)
					{
						if (Pai[1][i] == 1) //��С�ƹ��ָߣ�
						{
							dSum = dSum + 10 * (L - 1);
							break;
						}
					}
				}
				else {         //�Ӵ���С��  (���ƹ��ֵ�)
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
				else {                    //�����ȳ�(���ֵ�)
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



//�зֲ���
//�޶���:KL
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
		if (first_hand_cards[i] == 52 && first_hand_cards[i+1]== 53)//��� 
		{
			sum = sum + 10;
		}

		else if (first_hand_cards[i] / 4 == first_hand_cards[i + 1] / 4 && first_hand_cards[i + 1] / 4 == first_hand_cards[i + 2] / 4 &&    
			first_hand_cards[i + 2] / 4 ==first_hand_cards[i + 3] / 4 )
		{
			sum = sum + 6;
		}
		else  if (first_hand_cards[i] == 48 || first_hand_cards[i] == 49 || first_hand_cards[i] == 50 || first_hand_cards[i] == 51)  //2������
		{
			sum = sum + 2;
		}
		else if (first_hand_cards[i] == 52 || first_hand_cards[i] == 53)       //���С��
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



void CalPla(struct Ddz * pDdz	)//������Ʒ���	
{


    two_other_already(pDdz);

different_select(pDdz,last_landowner,next_landowner,my_landwoner);



}



int	main( )	
{
	
	struct Ddz tDdz, *pDdz=&tDdz;
	InitTurn(pDdz);			//��ʼ������
	while(pDdz->iStatus!=0)
	{
		InputMsg(pDdz);			//������Ϣ
		AnalyzeMsg(pDdz);		//����������Ϣ
		OutputMsg(pDdz);		//�����Ϣ
		CalOthers(pDdz);		//������������
	}
	return 0;
}