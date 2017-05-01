struct Tile
{
    int x, y;
    int value;    
    bool hasMerged;
    char d = '-';
} 
blank{0,0,0,false,dir};

string directions = "LRUD";
char dir = '-';

void GetNextPos(int &x, int &y, int i, int j)
{    
    switch(dir)
    {
        case 'U': y = 3 - j; 
                  x = i; 
                  break;
            
        case 'D': y = j; 
                  x = i;
                  break;
        
        case 'L': y = i;
                  x = 3 - j;
                  break;
        
        case 'R': y = i;
                  x = j;
                  break;
    }    
}


vector<deque<Tile>> GetLines(vector<vector<int>> &grid)
{
    vector<deque<Tile>> lines;
    
    
    for(int i=0; i<4; i++)
    {        
        deque<Tile> line;
        
        for(int j=0; j<4; j++)
        {                         
            int x, y;
            
            GetNextPos(x, y, i, j);            
            Tile tile{x, y, grid[y][x], false, dir};
                        
            if(tile.value == 0) continue;
            line.push_back(tile);
        }
        while(line.size() < 4) line.push_back(blank);        
        lines.push_back(line);
    }    
    return lines;
}

void SlideTiles(deque<Tile> &line)
{
    deque<Tile> mergedLine;
    Tile prev = line.back(), curr;// = line[1];
    
    line.pop_back();
    
    while(!line.empty())
    {        
        curr = line.back();

        if(!prev.hasMerged) 
        {
            if(curr.value == prev.value)
            {
                Tile merged{prev.x, prev.y, prev.value + curr.value, true, dir};
                mergedLine.push_front(merged);   
                curr = merged;
            }        
            else
            {
                mergedLine.push_front(prev);                
            } 
        }
        prev = curr;                    
        line.pop_back();        
    }
    if(!prev.hasMerged) mergedLine.push_front(prev);
       
    while(mergedLine.size() < 4) 
    {                
        mergedLine.push_front(blank);
    }
    line = mergedLine;
}

std::vector<std::vector<int>> game2048(std::vector<std::vector<int>> grid, std::string path) 
{
    for(auto move : path)
    {
        dir = move;
        vector<deque<Tile>> lines = GetLines(grid);        
                        
        for(auto row = lines.begin(); row != lines.end(); ++row)
        {            
            SlideTiles(*row);
            
            int timer = 0;

            while(timer < 4 && !(*row).empty() && (*row).back().value == 0)
            {                
                if((*row).back().value  == 0) (*row).pop_back();
                (*row).push_front(blank);                
                timer++;
            }            
        }                
        vector<vector<int>> newGrid(4, vector<int>(4));
        
        for(int i=0; i<grid.size(); i++)
        {            
            auto it = lines[i].begin();            
                        
            for(int j=0; j<grid[i].size(); j++)
            {
                Tile t = *it;                 
                int x, y;
                
                GetNextPos(x, y, i, j);                                
                newGrid[y][x] = t.value;
                ++it;
            }
        }
        grid = newGrid;
    }  
    return grid;
}
