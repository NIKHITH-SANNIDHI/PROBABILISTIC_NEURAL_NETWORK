#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main()
{
	int x,c=3;
	ifstream infile;
	infile.open("testdata.txt");
	
	vector<float> test;
	vector<float> data;

	
	while(!infile.eof())
	{
		infile>>x;
		test.push_back((float)x);
	}
	
	vector<float>::iterator titer;
	vector<float>::iterator diter;


	for(titer=test.begin();titer!=test.end();titer++)
		cout<<*titer<<endl;
		
	infile.close();	

	int a=test.size();	
	
	float n;
	float avg[c];
	
	float dr=0;
	

	for(titer=test.begin();titer!=test.end();titer++)
		dr+=(*titer)*(*titer),cout<<"*iter= "<<*titer<<endl;
		dr=sqrt(dr);	
	cout<<"dr="<<dr<<endl;
	
	for(titer=test.begin();titer!=test.end();titer++)		//normalizing test data
	{cout<<"titer = "<<*titer;
		*titer=*titer/dr;
		cout<<"  normalized test data"<<*titer<<endl;
	}
		
	//now test<> contains the normalized values
	
	//opening every file of one category and then find sum
	
	
	
	for(int i=0;i<c;i++)	//for every class
	{
	
	
		n=5;	//n is amount of training dataset of each class
		
		
		float final_sum=0.0;
		
		
		for(int j=0;j<n;j++)	//in every file of a particular class
		{
			dr=0;	
		
			string fname;
			
			stringstream out,out1;
			out << i;
			fname = out.str();
			
			fname+="_";
			out1<<j;
			fname  += out1.str();

			fname+=".txt";
			
			infile.open(fname.c_str());
			
			
			while(!infile.eof())
			{
				infile>>x;
				data.push_back((float)x);
				dr+=x*x;	
			}
			
			
	
			//Normalizing the data 
			float sum=0;
			dr=sqrt(dr);
		
			for(diter=data.begin();diter!=data.end();diter++)
				{	cout<<"*diter = "<<*diter;
					*diter=*diter/dr;
					cout<<" normalized data = "<<*diter<<endl;
				}
				
			for(diter=data.begin(),titer=test.begin(); diter!=data.end(),titer!=test.end(); diter++,titer++)
			{
				cout<<"data= "<<*diter<<"test = "<<*titer<<endl;
				sum+=(*diter)*(*titer);			
			}
			cout<<"sum= "<<sum<<endl;
			float sigma=1.0;
			sum=(sum-1)/(sigma*sigma);
			cout<<"sum="<<sum<<" exp = "<<exp(sum);
			final_sum+=exp(sum);
		
			data.clear();
			infile.close();
		}
		avg[i]=final_sum/n; 
		cout<<"final_sum="<<final_sum<<"avg="<<avg[i]<<endl;
	}
	
	for(int i=0;i<c;i++)
	{
		avg[i]=abs(avg[i]-1);
	}
	
	float smallest=99999;
	int index;
	for(int i=0;i<c;i++)
	{
		if(avg[i]<smallest)
		{
			smallest=avg[i];
			index=i;
		}
	}

	cout<<"the test data falls under class "<<index;
	
	return 0;
}
