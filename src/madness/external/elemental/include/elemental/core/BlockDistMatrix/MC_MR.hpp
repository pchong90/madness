/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_BLOCKDISTMATRIX_MC_MR_DECL_HPP
#define ELEM_BLOCKDISTMATRIX_MC_MR_DECL_HPP

namespace elem {

// Partial specialization to A[MC,MR].
//
// The columns of these matrices will be distributed among columns of the
// process grid, and the rows will be distributed among rows of the process
// grid.

template<typename T>
class BlockDistMatrix<T,MC,MR> : public GeneralBlockDistMatrix<T,MC,MR>
{
public:
    // Typedefs
    // ========
    typedef AbstractBlockDistMatrix<T> absType;
    typedef GeneralBlockDistMatrix<T,MC,MR> genType;
    typedef BlockDistMatrix<T,MC,MR> type;

    // Constructors and destructors
    // ============================

    // Inherited constructors are part of C++11 but not yet widely supported.
    //using GeneralBlockDistMatrix<T,MC,MR>::GeneralBlockDistMatrix;

    // Create a 0 x 0 distributed matrix with default (and unpinned) block size
    BlockDistMatrix( const elem::Grid& g=DefaultGrid(), Int root=0 );
    // Create a 0 x 0 distributed matrix with fixed block size
    BlockDistMatrix
    ( const elem::Grid& g, Int blockHeight, Int blockWidth, Int root=0 );
    // Create a height x width distributed matrix with default block size
    BlockDistMatrix
    ( Int height, Int width, const elem::Grid& g=DefaultGrid(), Int root=0 );
    // Create a height x width distributed matrix with fixed block size
    BlockDistMatrix
    ( Int height, Int width, const elem::Grid& g,
      Int blockHeight, Int blockWidth, Int root=0 );
    // Create a copy of distributed matrix A (redistributing if necessary)
    BlockDistMatrix( const type& A );
    template<Dist U,Dist V> BlockDistMatrix( const BlockDistMatrix<T,U,V>& A );
    template<Dist U,Dist V> BlockDistMatrix( const DistMatrix<T,U,V>& A );
    // Move constructor
    BlockDistMatrix( type&& A ) ELEM_NOEXCEPT;
    // Destructor
    ~BlockDistMatrix();

    // Assignment and reconfiguration
    // ==============================
    template<Dist U,Dist V> type& operator=( const DistMatrix<T,U,V>& A );
    type& operator=( const BlockDistMatrix<T,MC,  MR  >& A );
    type& operator=( const BlockDistMatrix<T,MC,  STAR>& A );
    type& operator=( const BlockDistMatrix<T,STAR,MR  >& A );
    type& operator=( const BlockDistMatrix<T,MD,  STAR>& A );
    type& operator=( const BlockDistMatrix<T,STAR,MD  >& A );
    type& operator=( const BlockDistMatrix<T,MR,  MC  >& A );
    type& operator=( const BlockDistMatrix<T,MR,  STAR>& A );
    type& operator=( const BlockDistMatrix<T,STAR,MC  >& A );
    type& operator=( const BlockDistMatrix<T,VC,  STAR>& A );
    type& operator=( const BlockDistMatrix<T,STAR,VC  >& A );
    type& operator=( const BlockDistMatrix<T,VR,  STAR>& A );
    type& operator=( const BlockDistMatrix<T,STAR,VR  >& A );
    type& operator=( const BlockDistMatrix<T,STAR,STAR>& A );
    type& operator=( const BlockDistMatrix<T,CIRC,CIRC>& A );
    // Move assignment
    type& operator=( type&& A );

    // Basic queries
    // =============
    elem::BlockDistData DistData() const override;
    mpi::Comm DistComm() const override;
    mpi::Comm CrossComm() const override;
    mpi::Comm RedundantComm() const override;
    mpi::Comm ColComm() const override;
    mpi::Comm RowComm() const override;
    Int ColStride() const override;
    Int RowStride() const override;
    Int DistSize() const override;
    Int CrossSize() const override;
    Int RedundantSize() const override;

private:
    // Redistribute from a different process grid
    // ==========================================
    void CopyFromDifferentGrid( const type& A );

    // Friend declarations
    // ===================
    template<typename S,Dist U,Dist V> friend class DistMatrix;
    template<typename S,Dist U,Dist V> friend class BlockDistMatrix;
};

} // namespace elem

#endif // ifndef ELEM_BLOCKDISTMATRIX_MC_MR_DECL_HPP
