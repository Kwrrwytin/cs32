//
//  Previous.cpp
//  CS32_project1
//
//  Created by wy24iiiiiii on 2022/6/27.
//

#include "Previous.h"
#include "globals.h"
#include <iostream>
using namespace std;

Previous::Previous(int nRows, int nCols){
    m_rows=nRows;
    m_cols=nCols;
}

bool Previous::dropACrumb(int r, int c){
    if(r<=0 || c<=0 || r>m_rows || c>m_cols)
        return false;
    m_arenaHistory[r-1][c-1]++;
    return true;
}

void Previous::showPreviousMoves() const{
    clearScreen();
    
    int r,c;
    char displayPrevious[MAXROWS][MAXCOLS];
    for(r=1;r<=m_rows;r++){
        for(c=1;c<=m_cols;c++){
            int count=m_arenaHistory[r-1][c-1];
            if(count==0)
                displayPrevious[r-1][c-1]='.';
            else if(count>=26)
                displayPrevious[r-1][c-1]='Z';
            else
                displayPrevious[r-1][c-1]=64+count;
        }
    }
    for(r=1;r<=m_rows;r++){
        for(c=1;c<=m_cols;c++){
            cout<<displayPrevious[r-1][c-1];
        }
        cout<<endl;
    }
    cout<<endl;
}
