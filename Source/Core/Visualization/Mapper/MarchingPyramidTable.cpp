/****************************************************************************/
/**
 *  @file MarchingPyramidTable.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "MarchingPyramidTable.h"


namespace kvs
{

namespace MarchingPyramidTable
{

const int TriangleID[36][13] =
{
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 0, 2, 3, -1, -1, -1, -1, -1, -1, -1},
    {0, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 4, 7, 1, 3, 4, 1, 2, 3, -1, -1, -1, -1},
    {1, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 3, 0, 2, 4, 2, 4, 5, -1, -1, -1, -1},
    {0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
    {2, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 1, 3, 6, 1, 5, 6, -1, -1, -1, -1},
    {0, 4, 7, 2, 5, 6, -1, -1, -1, -1, -1, -1, -1},
    {1, 4, 5, 3, 6, 7, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 6, 1, 4, 6, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 0, 2, 7, 2, 6, 7, -1, -1, -1, -1},
    {3, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 0, 2, 7, 2, 6, 7, -1, -1, -1, -1},
    {0, 3, 4, 3, 4, 6, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 6, 1, 4, 6, -1, -1, -1, -1, -1, -1, -1},
    {1, 4, 5, 3, 6, 7, -1, -1, -1, -1, -1, -1, -1},
    {0, 4, 7, 2, 5, 6, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 1, 3, 6, 1, 5, 6, -1, -1, -1, -1},
    {2, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 0, 5, 7, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 3, 0, 2, 4, 2, 4, 5, -1, -1, -1, -1},
    {1, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 3, 1, 3, 4, 3, 4, 7, -1, -1, -1, -1},
    {0, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 6, 0, 6, 7, 0, 2, 4, 2, 4, 5, -1},
    {1, 3, 4, 3, 4, 7, 1, 3, 6, 1, 5, 6, -1},
    {1, 3, 4, 3, 4, 7, 1, 3, 6, 1, 5, 6, -1},
    {0, 2, 6, 0, 6, 7, 0, 2, 4, 2, 4, 5, -1}
};

const int VertexID[8][2] =
{
    { 0, 1 },
    { 0, 2 },
    { 0, 3 },
    { 0, 4 },
    { 1, 2 },
    { 2, 3 },
    { 3, 4 },
    { 4, 1 }
};

} // end of namespace MarchingPyramidTable

} // end of namespace kvs
