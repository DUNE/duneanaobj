////////////////////////////////////////////////////////////////////////
/// \file    SRLorentzVector3D.h
/// \brief   4-vector class with more efficient storage than TLorentzVector.
///          Ported from NOvA StandardRecord.
/// \author  C. Backhouse <c.backhouse@ucl.ac.uk>
/// \date    Sept. 2021
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRLORENTZVECTOR_H
#define DUNEANAOBJ_SRLORENTZVECTOR_H

#if !defined(__GCCXML__) && !defined(__castxml__)

#include <cmath>
#include <limits>

#include "TMath.h"
#include "TLorentzVector.h"
#include "TVector3.h"

#endif



namespace caf
{
  class SRLorentzVector
  {
    public:
      SRLorentzVector();
      virtual ~SRLorentzVector() = default;

      SRLorentzVector(const TLorentzVector& v);

      /// Recommend users convert back to TLorentzVector for boosts etc
      operator TLorentzVector() const;

      SRLorentzVector & operator=(const TLorentzVector& vec);

      // For access as a position vector. For momentum use the member variables
      // directly.
      float T() const {return E;}
      float X() const {return px;}
      float Y() const {return py;}
      float Z() const {return pz;}
      float Mag() const {return sqrt(px*px + py*py + pz*pz);}
      float Beta() const {return Mag()/E;}
      float Gamma() const {return 1.0/sqrt(1-Beta()*Beta());}

      TVector3 Vect() const {return TVector3(px, py, pz);}

      float E;
      float px;
      float py;
      float pz;
  };

}
#endif //DUNEANAOBJ_SRLORENTZVECTOR_H
