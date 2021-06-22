/*
Code to convert 1m OHLC financial data to different time frame OHLC like 5m or 15m.
Uses the 1m data from https://www.histdata.com/ in the "Generic ASCII" format.
Outputs data in the required period in the same format as the 1m data;
date time;open;high;low;close;0

See example output at end of code.

Note that the code starts at the first data point and counts forward from there.
So if 5m is chosen and the data starts at 16:33, then the OHLC will run as;
date 163300;open;high;low;close;0
data 163800;open;high;low;close;0
date 164300;open;high;low;close;0
date 164800;open;high;low;close;0

See data_example.png to see the candlestick graphs of the example output given below.

For any questions or comments, you can message my reddit account: s1123581321
*/



#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //Reading the data out of the file
    //Data from https://www.histdata.com/ in the "Generic ASCII" format
    ifstream data_file("data2020.csv");
    string entry;
    int line=0;

    //Finds the total number of lines in the file
    while(getline(data_file,entry)){
        line=line+1;
    }
    data_file.clear();
    data_file.seekg(0);

    //Period wanted, for 5m OHCL input, 5, for 15m OHLC input, 15, for 1day OHLC input, 1440
    int form=5;

    float high_,low_;   //Temporary high and low variables for for loop
    int len=line/form;  //The number of lines that will be in the output file
    float open,high,low,close;  //The variables to be outputted
    int date,time;  //More output variables
    char semi=';';  //Output again
    int vol;    //Output again
    float dud;  //Dud variable to read unnecessary data into

    ofstream output_file("output.txt");

    //Finds the relevant date, time and OHLC and writes them to a file
    for(int i=0;i<len;++i){
        high=0;
        low=10;
        for(int j=form*i;j<(form*(i+1));++j){
            if(j==form*i){
                data_file>>date>>time>>semi>>open>>semi>>high_>>semi>>low_>>semi>>dud>>semi>>vol;
            }else if(j==((form*(i+1))-1)){
                data_file>>dud>>dud>>semi>>dud>>semi>>high_>>semi>>low_>>semi>>close>>semi>>vol;
            }else{
                data_file>>dud>>dud>>semi>>dud>>semi>>high_>>semi>>low_>>semi>>dud>>semi>>vol;
            }
            if(high_>high){
                high=high_;
            }
            if(low_<low){
                low=low_;
            }
        }
        output_file<<date<<" "<<time<<semi<<open<<semi<<high<<semi<<low<<semi<<close<<semi<<vol<<endl;
    }

    data_file.close();
    output_file.close();

    return 0;
}


/*
Output example;
20200101 172000;1.12144;1.12153;1.12137;1.12146;0
20200101 172500;1.12146;1.12147;1.12139;1.12146;0
20200101 173000;1.12147;1.12152;1.12138;1.12147;0
20200101 173500;1.12148;1.12155;1.12147;1.12152;0

corresponds to the input;
20200101 172000;1.121440;1.121450;1.121380;1.121400;0
20200101 172100;1.121390;1.121490;1.121370;1.121470;0
20200101 172200;1.121470;1.121470;1.121470;1.121470;0
20200101 172300;1.121510;1.121510;1.121450;1.121450;0
20200101 172400;1.121460;1.121530;1.121460;1.121460;0
20200101 172500;1.121460;1.121460;1.121460;1.121460;0
20200101 172600;1.121460;1.121470;1.121410;1.121410;0
20200101 172700;1.121410;1.121410;1.121410;1.121410;0
20200101 172800;1.121420;1.121420;1.121390;1.121390;0
20200101 172900;1.121390;1.121460;1.121390;1.121460;0
20200101 173000;1.121470;1.121510;1.121380;1.121460;0
20200101 173100;1.121460;1.121480;1.121440;1.121470;0
20200101 173200;1.121470;1.121520;1.121470;1.121480;0
20200101 173300;1.121480;1.121480;1.121450;1.121450;0
20200101 173400;1.121510;1.121510;1.121460;1.121470;0
20200101 173500;1.121480;1.121530;1.121470;1.121500;0
20200101 173600;1.121500;1.121500;1.121500;1.121500;0
20200101 173700;1.121540;1.121540;1.121510;1.121510;0
20200101 173800;1.121540;1.121550;1.121520;1.121530;0
20200101 173900;1.121530;1.121530;1.121520;1.121520;0

See data_example.png to see the candlestick graphs of this example output.
*/
