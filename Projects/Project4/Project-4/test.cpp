/*
#include "DiskMultiMap.h"
#include "IntelWeb.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    
    IntelWeb I;
    I.createNew("test2", 10000);
    if(!I.ingest("telemetry.txt"))
        cout << "ERROR" << endl;

    vector<string> bad;
    vector<string> indicators;
    vector<InteractionTuple> interactions;
    
    indicators.push_back("http://www.foo.com/bar");
    indicators.push_back("qqqqqa.exe");
    indicators.push_back("qqqqqb.exe");
    indicators.push_back("http://www.bar.com/bletch");
    indicators.push_back("explorer.exe");
    
    I.crawl(indicators, 10, bad, interactions);
    
    for (int i = 0; i < bad.size(); i++)
        cout << bad[i] << endl;
    
    cout << endl;
    
    for (int i = 0; i < indicators.size(); i++)
        cout << "--- " << indicators[i] << " ---" << endl;
    
    cout << endl;
    
    for (int i = 0; i < interactions.size(); i++)
        cout << interactions[i].context << " " << interactions[i].from << " " << interactions[i].to << endl;
    
    cout << endl;
    
    I.purge("explorer.exe");
    
    I.crawl(indicators, 10, bad, interactions);
    
    for (int i = 0; i < bad.size(); i++)
        cout << bad[i] << endl;
    
    cout << endl;
    
    for (int i = 0; i < indicators.size(); i++)
        cout << "--- " << indicators[i] << " ---" << endl;
    
    cout << endl;
    
    for (int i = 0; i < interactions.size(); i++)
        cout << interactions[i].context << " " << interactions[i].from << " " << interactions[i].to << endl;
    
    cout << endl;
    
    /*
    DiskMultiMap DMM1;
    DMM1.createNew("testdata.txt", 20);
    if(DMM1.erase("John", "Jim", "Jake"))
        cout << "ERASED" << endl;
    
    DMM1.insert("John", "Jim", "Jake");
    DiskMultiMap::Iterator IT = DMM1.search("John");
    if (IT.isValid())
        cout << "FOUND" << endl;
    
    DMM1.close();
    
    DMM1.openExisting("testdata.txt");
    DiskMultiMap::Iterator IT2 = DMM1.search("John");
    if (IT2.isValid())
        cout << "FOUND" << endl;
    
    DMM1.insert("John", "Kyle", "Kim");
    ++IT2;
    if (IT2.isValid())
        cout << "FOUND ANOTHER" << endl;
    
    ++IT2;
    if (!IT2.isValid())
        cout << "WOOPS" << endl;
    
    DiskMultiMap::Iterator IT3(IT);
    MultiMapTuple MMT = *IT3;
    cout << MMT.key << " " << MMT.value << " " << MMT.context << endl;
    
    ++IT3;
    MMT = *IT3;
    cout << MMT.key << " " << MMT.value << " " << MMT.context << endl;
    
    ++IT3;
    MMT = *IT3;
    cout << MMT.key << " " << MMT.value << " " << MMT.context << endl;
    
    IT3 = IT;
    MMT = *IT3;
    cout << MMT.key << " " << MMT.value << " " << MMT.context << endl;
 
}
*/