//
//  MatrixVectorOperation.h
//  raysn
//
//  Created by Jooil Yoon on 11/6/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef __raysn__MatrixVectorOperation__
#define __raysn__MatrixVectorOperation__

#include "../pch.h"

class MatrixVectorOperation {

public:
	MatrixVectorOperation();
	virtual ~MatrixVectorOperation();
	
	template <int M>
	static void solveLinearSystem(double (&matrix)[M][M], double (&rhs)[M], double (&solution)[M]) {
		int size = M;
	
		int pivot[size];
		for (int i=0; i<size; i++) pivot[i] = i;
	
		// forward elimination
		for(int j=0; j<size-1; j++) {
			double max = std::abs(matrix[pivot[j]][j]);
			int imax = j;
			for (int i=j+1; i<size; i++) {
				if(abs(matrix[pivot[i]][j]) > max) {
					max  = std::abs(matrix[pivot[i]][j]);
					imax = i;
				}
			}
			
			int ipiv = pivot[imax];
			pivot[imax]=pivot[j];
			pivot[j] = ipiv;
			
			
			for (int i=j+1; i<size; i++) {
				
				double fm = matrix[pivot[i]][j] / matrix[pivot[j]][j];
				if(fm == 0.0) continue;
				
				for(int k=j; k<size; k++) {
					matrix[pivot[i]][k] = matrix[pivot[i]][k] - fm*matrix[pivot[j]][k];
				}
				
				rhs[pivot[i]] -= fm*rhs[pivot[j]];
				
			}
			
		}
	
		// backward elimination
		solution[pivot[size-1]] = rhs[pivot[size-1]] / matrix[pivot[size-1]][size-1];
	
		for(int j=size-2; j>=0; j--) {
			double sum = 0;
			for(int i=j+1; i<size; i++) {
				sum += matrix[pivot[j]][i]*solution[pivot[i]];
			}
			
			solution[pivot[j]] = (rhs[pivot[j]]-sum)/matrix[pivot[j]][j];
		}
		
	}
};

#endif /* defined(__raysn__MatrixVectorOperation__) */
