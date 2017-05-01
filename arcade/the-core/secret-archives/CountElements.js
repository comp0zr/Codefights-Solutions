function countElements(inputString) 
{
    inputString = inputString.split('')
    var quote = false;
    
    for(var i=0; i<inputString.length; i++)
    {
        if(inputString[i] === '\"') 
        {
            quote = !quote;
        }
        if(inputString[i] === ',' || inputString[i] === ']' || inputString[i] === '[')
        {
            if(quote) inputString[i] = ' ';
        }
    }
    
    var a = inputString.join('').split(",")
    var count = 0;
    
    for(var i of a)
    {
        var s = i.substr(i.lastIndexOf('[')+1).trim()
        var num = parseInt(s);                
        
        if(Number(num).toString() !== 'NaN')
        {
            count++;
        }
        else
        {
            if(s.indexOf(']') !== -1) s = s.substr(0, s.indexOf(']'));
            s = s.trim();            
            
            if(s[0] === '\"' && s[s.length-1] === '\"') count++;
            else if(s === "true" || s === "false") count++;            
        }
    }
    console.log(a)
    return count;
}
