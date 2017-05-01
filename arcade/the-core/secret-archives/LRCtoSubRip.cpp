std::vector<std::string> lrc2subRip(std::vector<std::string> lrcLyrics, std::string songLength) 
{
    vector<string> ans;
    int count = 1;
    
    for(int i=0; i<lrcLyrics.size(); i++)
    {
        ans.push_back(to_string(count));
        
        string line = lrcLyrics[i];
        string time_a = "00:" + line.substr(1, line.find(']')-1)+'0';
        string time_b;
        line = line.substr(line.find(' ')+1);
                
        time_a[time_a.rfind('.')] = ',';        
        time_b = (i==lrcLyrics.size()-1) ? songLength+",000" : "00:"+lrcLyrics[i+1].substr(1, lrcLyrics[i+1].find(']')-1)+'0';
        time_b[time_b.rfind('.')] = ',';
        
        
        if(stoi(time_a.substr(3, 2)) >= 60)
        {
            int mins = stoi(time_a.substr(3, 2));
            int hours = (mins/60);
            mins %= 60;
            string m = to_string(mins), h = to_string(hours);
            
            if(m.length()==1) m.insert(0, 1, '0');
            if(h.length()==1) h.insert(0, 1, '0');
            
            time_a[0]=h[0];
            time_a[1]=h[1];
            time_a[3]=m[0];
            time_a[4]=m[1];
        }
        
        if(stoi(time_b.substr(3, 2)) >= 60)
        {
            int mins = stoi(time_b.substr(3, 2));
            int hours = (mins/60);
            mins %= 60;
            string m = to_string(mins), h = to_string(hours);
            
            if(m.length()==1) m.insert(0, 1, '0');
            if(h.length()==1) h.insert(0, 1, '0');
            
            time_b[0]=h[0];
            time_b[1]=h[1];
            time_b[3]=m[0];
            time_b[4]=m[1];
        }
        ans.push_back(time_a + " --> " + time_b);
        
        if(line.front() != '[') ans.push_back(line);
        else ans.push_back("");
        
        if(i < lrcLyrics.size()-1) ans.push_back("");
        
        cout << time_b << endl;
        cout << time_a << " --> " << time_b << endl << line << endl << "--------------" << endl;
        
        count++;
    }
    return ans;
}
