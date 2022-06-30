 //2-dimensoional arrays for rows and columns pins 
char Row[8]={2,7,A5,5,13,A4,12,A2}; // Arduino pin numbers
char Col[8]={6,11,10,3,A3,4,8,9};   // Arduino pin numbers

int i=0; // row 
int j=0; // columne

int carry=0, eat=0, random_num1=0,random_num2=0;
int direct=0; // direction
int head_x=0,head_y=2;
int tail_x=0,tail_y=0;
void directions();
void game(char mat[8][8]);
void clear();

const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output



char start[8][8]=
{
  5,0,0,0,0,0,0,0,
  4,0,0,0,0,0,0,0,
  3,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

char over[8][8]=
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  0,1,1,0,0,1,1,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,1,1,1,0,0,
  0,1,0,0,0,0,1,0,
  1,0,0,0,0,0,0,1,
};

void setup() {
  // set pins as outputs and set them to low
  for(int i=0; i<8; i++)
   {
    pinMode(Row[i],OUTPUT);
    pinMode(Col[i],OUTPUT);
    digitalWrite(Row[i],LOW);
    digitalWrite(Col[i],HIGH);
   }
  Serial.begin(115200);

  // -----------------------------------------------------------------------------------------------------------------------------

}

void loop()
{

  for(int i=0; i<13; i++) // display the matrix
    {
      Display(start);
    }



      directions();
     
      if(direct==1) //down
    {
      down(start);
      if(eat==0)
      {
        tail(start);
      }
       else
       {
        random_food(start);
         eat--;
       }

    }

    else if(direct==2) //up
    {
     up(start);
      if(eat==0)
      {
        tail(start);
      }
       else
       {
        random_food(start);
         eat--;
       }

    }

   else if(direct==3) // left
 {
    left(start);
      if(eat==0)
      {
        tail(start);
      }
       else
       {
        random_food(start);
         eat--;
       }

 }

   else if(direct==4) // right
 {
    right(start);
      if(eat==0)
      {
        tail(start);
      }
       else
       {
        random_food(start);
         eat--;
       }

 }
    
}

//----------------------------------------------------------------------------------------------------------------------


   
void Display(char mat[8][8])
{
  for(int i=0; i<8; i++)
  {
    digitalWrite(Col[i],LOW);
    for(int j=0; j<8; j++)
    {
      digitalWrite(Row[j],mat[j][i]);
       Serial.println(mat[j][i]);
    }
    delay(1);
    clear();
  }
}





void tail(char mat[8][8])
{
 
  if(mat[tail_y+1][tail_x]== (mat[tail_y][tail_x]-1)) // down
  {
    mat[tail_y][tail_x]=0;
    tail_y++;
    return;
  }
  
  else if (mat[tail_y-1][tail_x]==(mat[tail_y][tail_x]-1)) // up
  {
    mat[tail_y][tail_x]=0;
    tail_y--;
     return;
  }

    else if (mat[tail_y][tail_x-1]==(mat[tail_y][tail_x]-1)) // left
  {
    mat[tail_y][tail_x]=0;
    tail_x--;
     return;
  }
    else if (mat[tail_y][tail_x+1]==(mat[tail_y][tail_x]-1))  // right
  {
    mat[tail_y][tail_x]=0;
    tail_x++;
     return;
  }

   if(tail_y==7 && carry==1)  // wall down
  {
    mat[tail_y][tail_x]=0;
    tail_y=0;
    carry=0;
  }
    else if(tail_x==7 && carry==1) // wall right
  {
    mat[tail_y][tail_x]=0;
    tail_x=0;
    carry=0;
  }

  else if(tail_x==0 && carry==1)  //wall left
  {
    mat[tail_y][tail_x]=0;
    tail_x=7;
    carry=0;
  }
  
  else if(tail_y==0 && carry==1) // wall up
  {
    mat[tail_y][tail_x]=0;
    tail_y=7;
    carry=0;
  }

}





void down(char mat[8][8])
{
  if( mat[head_y+1][head_x]==1)
  eat++;
  
   else if( mat[head_y+1][head_x]>2)
   game(over);
  
  head_y++;
  
  if(head_y>7)
  {
      head_y=0;
      carry=1;
        if( mat[head_y][head_x]==1)
          eat++;
  }

  mat[head_y][head_x]=2;
  add_one(start);
}


void up(char mat[8][8])
{
    if( mat[head_y-1][head_x]==1)
        eat++; 

   else if( mat[head_y-1][head_x]>2)
   game(over);
  
  head_y--;
  
  if(head_y<0)
    {
       head_y=7;
       carry=1;
        if( mat[head_y][head_x]==1)
          eat++;
    }
    
  mat[head_y][head_x]=2;
  add_one(start);
}

void left(char mat[8][8])
{
    if( mat[head_y][head_x-1]==1)
        eat++;

    else if( mat[head_y][head_x-1]>2)
        game(over);
  
  head_x--;
  
  if(head_x<0)
    {
       head_x=7;
       carry=1;
        if( mat[head_y][head_x]==1)
          eat++;
    }

  mat[head_y][head_x]=2;
  add_one(start);
}

void right(char mat[8][8])
{
  if( mat[head_y][head_x+1]==1)
      eat++;

   else if( mat[head_y][head_x+1]>2)
   game(over);
  
  head_x++;
  
  if(head_x>7)
    {
       head_x=0;
       carry=1;
        if( mat[head_y][head_x]==1)
          eat++;
    }

  mat[head_y][head_x]=2;
  add_one(start);
}
//-------------------------------------------------------------------------------------------------------

void directions()
{
       if(analogRead(X_pin)>615 && direct!=2)
   {
     direct=1;
     return;
   }
 
    else if(analogRead(X_pin)<400 && direct!=1 )
    {
      direct=2;
      return;
    }
     else if(analogRead(Y_pin)<415 && direct!=4)
    {
      direct=3;
      return;
    }
     
   else if(analogRead(Y_pin)>630 && direct!=3)
    {
      direct=4;
      return;
    }
}




void random_food(char mat[8][8])
{
  while(1)
  {
    random_num1=random(0,7);
    random_num2=random(0,7);
     if(mat[random_num1][random_num2]!=2)
    {
       mat[random_num1][random_num2]=1;
       break;
    }
  }

   // -----------------------------------------------------------------------------------------------------------------------------

}   

 void game(char mat[8][8])    // display game over :(

 {
    while(1) // display the matrix
    {
      Display(over);
    }
 }


 void add_one(char mat[8][8])  // increase by one every digit larger than one
 {
    for(int k=0; k<8; k++)
  {
       for(int s=0; s<8; s++)
     {
        int x=mat[s][k];
        if (x>1)
         mat[s][k]+=1;
     }
  }
 }


 
void clear()
{

  for(int i=0; i<8; i++)
   {
    digitalWrite(Row[i],LOW);
    digitalWrite(Col[i],HIGH);
   }
}
