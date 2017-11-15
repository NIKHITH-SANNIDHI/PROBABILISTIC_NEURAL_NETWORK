#include<bits/stdc++.h>
#include<fstream>
using namespace std;

vector<int>actual;

void confusion_matrix_func(int mat[3][3],int pred,int present)
{
	
	int act=actual[present];
	
	cout<<"act = "<<act<<"  predicted = "<<pred<<"count value = "<<present<<endl;
	

	if     (act==1 && pred==1)
		mat[0][0]++;	
	else if(act==1 && pred==2)
		mat[0][1]++;
	else if(act==1 && pred==3)
		mat[0][2]++;
	
		
	else if(act==2 && pred==1)
		mat[1][0]++;
	else if(act==2 && pred==2)
		mat[1][1]++;
	else if(act==2 && pred==3)
		mat[1][2]++;
		
	
	else if(act==3 && pred==1)
		mat[2][0]++;
	else if(act==3 && pred==2)
		mat[2][1]++;
	else if(act==3 && pred==3)
		mat[2][2]++;
		
		
	else 
		cout<<"ERROR"<<endl;
		
	
	
}	




int main()
{
	ifstream inactual;
	inactual.open("actual.txt");
	int act;
	while(inactual>>act)actual.push_back(act);
	
	inactual.close();	
	vector<int>::iterator it;
	
	for(it=actual.begin();it!=actual.end();it++)
		cout<<" "<<*it;
	
	
	int c,a;
	ifstream infile;
	ifstream intest;
	infile.open("irisdataset_40-10.txt");
	intest.open("testdata.txt");
	infile>>c;
	infile>>a;
	cout<<"c= "<<c<<" a= "<<a<<endl;
	float n;
	float data[a];	
	float avg[c];
	
	float test[a],dr,count=0;
	
	
	vector<int>results;
	
	int confusionMat[3][3];
	
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			confusionMat[i][j]=0;
	
	
	
	
	
	while(true)
	{
		dr=0;
		for(int i=0;i<a;i++)
			intest>>test[i],dr+=test[i]*test[i],cout<<"  "<<test[i];
			cout<<endl;
			dr=sqrt(dr);
//			cout<<"test dr = "<<dr<<endl;
		
		//taking test data  correctly
		
			
		for(int k=0;k<a;k++)		//normalizing test data
		{
			test[k]=test[k]/dr;
			
		}
			//now test[] contains the normalized values
			
	
		for(int i=0;i<c;i++)
		{
			infile>>n;
			float final_sum=0.0;
				
			for(int j=0;j<n;j++)
			{
				dr=0;	
				for(int k=0;k<a;k++)
				{
					infile>>data[k];		
					dr+=data[k]*data[k];	
				}
		
		
				//Normalizing the data 
				float sum=0;
				dr=sqrt(dr);
			
				for(int k=0;k<a;k++)
				{
					data[k]=data[k]/dr;
				}
					
			
				for(int j=0;j<a;j++)
				{
				sum+=data[j]*test[j];			
				}

			//	cout<<"sum = "<<sum<<endl;

				float sigma=1.0;     // we want only the difference that is there in the numerator. To achieve only this, we put the denomintor's sigma value as  1
				sum=(sum-1)/(sigma*sigma);
				final_sum+=exp(sum);
									
			}
			avg[i]=final_sum/n; 
//			cout<<"final_sum="<<final_sum<<"avg="<<avg[i]<<endl;
		}
	
		float largest=-1;
		int index;
		for(int i=0;i<c;i++)
		{
			if(avg[i]>largest)
			{
				largest=avg[i];
				index=i;
			}
		}
	
		cout<<"the test data falls under class "<<index+1<<endl;

		
		confusion_matrix_func(confusionMat,index+1,count);
		count++;
		
		infile.seekg(4,ios::beg);
	
		
		if(intest.eof())break;
	}


	cout<<"THE CONFUSION MATRIX WILL BE "<<endl;
	
	for(int i=0;i<c;i++)
		{
			for(int j=0;j<c;j++)
				cout<<confusionMat[i][j]<<" ";
			cout<<endl;	
		}	
	 
	cout<<"-----------------------------------------"<<endl;
	
	
	
	
	infile.close();
	intest.close();
	return 0;
}
