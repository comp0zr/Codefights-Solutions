vector<vector<string>> piece;
vector<pair<int, int>> startPos;
vector<int> blockCount;

map<vector<string>, vector<vector<string>>> rotations; 

string emptyLine = string(10, '.');
int score = 0;

vector<pair<int, int>> GetPositions(vector<string> &board, vector<string> &piece)
{
    string ws(piece.size(), '.');
    
    vector<pair<int, int>> position;
    bool found = false;
    int start = 0;
    
    for(int i=0; i <= 10-piece[0].size(); i++)
    {        
        for(int j = start; j <= 20-piece.size(); j++)
        {                   
            if(!found)
            { 
                if(j + piece.size() == 19) 
                {                    
                    for(int x = 0; x <= 10-piece[0].size(); x++)
                    {
                        position.push_back({19, x});
                    }
                    goto out;                 
                }
                else if(board[j + piece.size()] != emptyLine)
                {
                    found = true;
                    start = j;
                }
                else continue;
            }
            
            for(int y = piece.size()-1; y >= 0; y--)
            {
                if(board[j+y] == ws) continue;
                
                for(int x = 0; x < piece[y].size(); x++)
                {
                    if(piece[y][x] == '#')
                    {
                        if(j+y+1 == 20)
                        {
                            position.push_back({19, i});                            
                            goto next_column;
                        }
                        
                        char current = board[j+y][i+x],
                                next = board[j+y+1][i+x];
                        
                        if(current == '#') goto next_column;
                        else if(next == '#')
                        {
                            position.push_back({j+y, i});                            
                            goto next_column;
                        }
                    }                    
                }
            }
        }
        next_column:      
        continue;
    }  
    out:
    
    blockCount.clear();
    blockCount.resize(position.size());
    int index = 0;
    
    for(auto it : position)
    {
        int count = 0;

        for(int i=0; i<20; i++)
        {
            if(i >= (it.first - piece.size()) && i < it.first)
            {
                for(int j=0; j<10; j++)
                {
                    if(j >= it.second && j < it.second + piece[0].size())
                    {
                        if(board[i][j] == '#') count++;
                        else if(piece[piece.size() - ((it.first - i))][j - it.second] == '#') 
                        {
                            count++;
                        }
                    }                    
                }
            }        
        }        
        blockCount[index] = count;
        index++;
    }   
    return position;
}



void UpdateBoard(vector<string> &board, vector<string> &piece, pair<int, int> &pos)
{
    for(int i = (pos.first - piece.size()) + 1 ; i <= pos.first; i++)
    {        
        for(int j = pos.second; j < pos.second + piece[0].size(); j++)
        {     
            if(piece[piece.size() - ((pos.first - i)+1)][j - pos.second] == '#') board[i][j] = '#';
        }        
    }
    
    for(int i = 19; i>=0; i--)
    {
        if(board[i] == string(10, '#'))
        {
            score++;
            board.erase(board.begin()+i);
            board.insert(board.begin(), emptyLine);
            i = 20;
            continue;
        }
    }
}


void GetRotations(vector<string> &piece)
{
    vector<vector<string>> rot(4);
    rot[0] = piece;
    rotations[piece].push_back(piece);    
    
    for(int r=0; r<3; r++)
    {
        vector<string> R;

        if(r > 0)
        {
            R = (r==1) ? rot[0] : rot[1];

            for(auto it : R)
            {
                reverse(it.begin(), it.end());                    
            }
            reverse(R.begin(), R.end());   
            rot[r+1] = R;
            
            if(std::count(rotations[piece].begin(), rotations[piece].end(), R) == 0)
            {
                rotations[piece].push_back(R);
            }
            continue;
        }

        for(int i=0; i<piece[0].size(); i++)
        {             
            string s = "";

            for(int j=0; j<piece.size(); j++) 
            {
                s += piece[j][i];
            }            
            R.push_back(s);
        }
        rot[1] = R;
        rotations[piece].push_back(R);
    }    
}


int tetrisGame(std::vector<std::vector<std::vector<char>>> pieces) 
{
    vector<string> board(20, string(10, '.'));
 
    for(int i=0; i<pieces.size(); i++)
    {
        vector<string> P;
        
        for(int y=0; y<pieces[i].size(); y++)
        {
            string line = string(pieces[i][y].begin(), pieces[i][y].end());
            P.push_back(line);
        }
        piece.push_back(P);
        if(rotations.count(P) == 0) GetRotations(P);
    }
    
    
    for(auto it : piece)
    {       
        pair<int, int> move;
        vector<string> chosenRot;  
                
        int maxBlocks = -999999, lowestRow = -1; 

        for(auto rot : rotations[it])
        {                        
            startPos = GetPositions(board, rot);
            
            if(!startPos.empty())
            {                    
                int maxVal = *max_element(blockCount.begin(), blockCount.end());
                
                if(maxVal < maxBlocks) continue;                              
                maxBlocks = max(maxBlocks, maxVal);
                
                for(int i=0; i<startPos.size(); i++)
                {
                    if(blockCount[i] == maxBlocks && startPos[i].first > lowestRow)
                    {
                        lowestRow = startPos[i].first;             
                        move = startPos[i];
                        chosenRot = rot;
                    }
                }
            }
        }
        UpdateBoard(board, chosenRot, move);
    }
    return (score == 0) ? 1 : score;
}
