//
//  Previous.hpp
//  CS32_project1
//
//  Created by wy24iiiiiii on 2022/6/27.
//

#ifndef Previous_hpp
#define Previous_hpp
#include "globals.h"
class Previous
{
    public:
        Previous(int nRows, int nCols);
        bool dropACrumb(int r, int c);
        void showPreviousMoves() const;
    private:
        int m_rows;
        int m_cols;
    int m_arenaHistory[MAXROWS][MAXCOLS]={0};
};
#endif /* Previous_hpp */
