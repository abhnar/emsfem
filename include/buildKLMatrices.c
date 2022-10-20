// Filename: buildKLMatrices.c
// Author:   Abhijith B N
// email:    abhijithbn@gmail.com
// Desc:     Faster way to assemble KL expansion eigen value problem matrics.

#include <math.h>
#include<stdio.h>
#include "mex.h"
#define vale prhs[0]
#define coordmat prhs[1]
#define NT prhs[2]
#define NP prhs[3]
#define NN prhs[4]
#define tt prhs[5]
#define cl prhs[6]




/* Output Arguments */

#define YP_OUT plhs[0]


void printprogress(int curr, int total);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])

{
#if MX_HAS_INTERLEAVED_COMPLEX
    mxDouble* yp, *yp1,*yp2, *yp3, *yp4, *yp5, *yp6, *yp7, *yp8 ;
    mxDouble *val, *coord, *nt, *np, *nn, *tet, *cll;
#else
    double* yp, *yp1,*yp2, *yp3, *yp4, *yp5, *yp6, *yp7, *yp8;
    double *val, *coord, *nt, *np, *nn, *tet, *cll;
#endif
    size_t nodes_m, nodes_n, tets_m, tets_n;
    
    /* Check for proper number of arguments */

    if (nrhs != 7) {
        mexErrMsgIdAndTxt("MATLAB:yprime:invalidNumInputs", "Seven input arguments required.");
    } else if (nlhs > 1) {
        mexErrMsgIdAndTxt("MATLAB:yprime:maxlhs", "Too many output arguments.");
    }

    /* check to make sure the first input argument is a real matrix */
    if (!mxIsDouble(vale) || mxIsComplex(vale)) {
        mexErrMsgIdAndTxt("MATLAB:yprime:invalidT", "First input argument must be a real matrix.");
    }

   

    const mwSize *pDims;
    pDims = mxGetDimensions(vale);
    size_t nDimNum;
    nDimNum = mxGetNumberOfDimensions(vale);
    
    mwSize  s1 ,s2 , s3, t1 , t2, t3;
    s1 = pDims[0];
    
    s2 = pDims[1];
    
    s3 = pDims[2];
    
    
    
    val = mxGetPr(vale);
    
    
    
    
        
    //printf("%f\t", pD[i + j * s1 + k * (s1 * s2)]);
        
    
    pDims = mxGetDimensions(coordmat);
    t1 = pDims[0];
    
    t2 = pDims[1];
    
    t3 = pDims[2];
    
    coord = mxGetPr(coordmat);
    nt = mxGetPr(NT);
    np = mxGetPr(NP);
    nn = mxGetPr(NN);
    tet = mxGetPr(tt);
    cll = mxGetPr(cl);
   
    
    
    int ntet = (int)nt[0];
    int npts = (int)np[0];
    int nnodes = (int)nn[0];
    double covlen = cll[0];
    mxArray* yy1 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp1 = mxGetPr(yy1);

    mxArray* yy2 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp2 = mxGetPr(yy2);

    mxArray* yy3 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp3 = mxGetPr(yy3);

    mxArray* yy4 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp4 = mxGetPr(yy4);

    mxArray* yy5 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp5 = mxGetPr(yy5);

    mxArray* yy6 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp6 = mxGetPr(yy6);

    mxArray* yy7 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp7 = mxGetPr(yy7);

    mxArray* yy8 = mxCreateDoubleMatrix((mwSize)nnodes, (mwSize)nnodes, mxREAL);
    yp8 = mxGetPr(yy8);

    //printf("%d, %d, %d, %d\n",s1,s2,s3,nDimNum);
    //printf("%d, %d, %d, %d\n",t1,t2,t3,nDimNum);
    //printf("%d %d %d\n",ntet, npts, nnodes);
    double dx, dy, dz, dl, dl1, dl2, dl3,dl4,dl5,dl6,dl7,dl8;
    dl = 0;
    
    const char* c1 = "Hello";
    mxArray* m1 = mxCreateString(c1);
    YP_OUT = mxCreateCellMatrix(1, 8);

    mxSetCell(YP_OUT, 0, yy1);
    mxSetCell(YP_OUT, 1, yy2);
    mxSetCell(YP_OUT, 2, yy3);
    mxSetCell(YP_OUT, 3, yy4);
    mxSetCell(YP_OUT, 4, yy5);
    mxSetCell(YP_OUT, 5, yy6);
    mxSetCell(YP_OUT, 6, yy7);
    mxSetCell(YP_OUT, 7, yy8);


    for(int e = 0;e<ntet;e++){
        printprogress(e,ntet);
        for(int f = 0;f<ntet;f++){
            for(int p = 0;p<npts;p++){
                for(int q = 0;q<npts;q++){
                    dx = coord[e + 0 * t1 + p * (t1 * t2)] - coord[f + 0 * t1 + q * (t1 * t2)];
                    dy = coord[e + 1 * t1 + p * (t1 * t2)] - coord[f + 1 * t1 + q * (t1 * t2)];
                    dz = coord[e + 2 * t1 + p * (t1 * t2)] - coord[f + 2 * t1 + q * (t1 * t2)];
                    dl = sqrt(dx*dx + dy*dy + dz*dz);
                    
                    dl1 = exp(-dl/covlen/0.1);
                    dl2 = exp(-dl/covlen/0.25);
                    dl3 = exp(-dl/covlen/0.5);
                    dl4 = exp(-dl/covlen/0.75);
                    dl5 = exp(-dl/covlen/1);
                    dl6 = exp(-dl/covlen/2);
                    dl7 = exp(-dl/covlen/5);
                    dl8 = exp(-dl/covlen/10);
                    
                    for(int j=0;j<4;j++){
                        int ix_i = (int)tet[e+j*ntet];
                        
                        for(int k=0;k<4;k++){
                            int ix_j = (int)tet[f+k*ntet];
                                yp1[ix_i-1 + (ix_j-1)*nnodes] = yp1[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl1;
                                yp2[ix_i-1 + (ix_j-1)*nnodes] = yp2[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl2;
                                yp3[ix_i-1 + (ix_j-1)*nnodes] = yp3[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl3;
                                yp4[ix_i-1 + (ix_j-1)*nnodes] = yp4[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl4;
                                yp5[ix_i-1 + (ix_j-1)*nnodes] = yp5[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl5;
                                yp6[ix_i-1 + (ix_j-1)*nnodes] = yp6[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl6;
                                yp7[ix_i-1 + (ix_j-1)*nnodes] = yp7[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl7;
                                yp8[ix_i-1 + (ix_j-1)*nnodes] = yp8[ix_i-1 + (ix_j-1)*nnodes] + val[j + e * s1 + p * (s1 * s2)]*val[k + f * s1 + q * (s1 * s2)]*dl8;
  
                        }

                        
                    }
                     
                    
                }
            }
        }
        
       
        
    }

     

    return;
}

void printprogress(int curr, int total){
    int n = (double)curr*10.0/(double)(total-1);
    double prog = (double)curr*100.0/(double)(total-1);
    char str1[50], str2[50];

    str1[0] = '[';
    for(int i=0;i<n;i++)
        str1[i+1] = '#';
    str1[n+1] = '>';
    for(int i=n;i<10;i++)
        str1[i+2] = '|';
    str1[12] = ']';
    str1[13] = '\0';

    if (curr==0)
        printf("Progress %3.0f%% %s",prog,str1);
    
    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bProgress %3.0f%% %s",prog,str1);
    
    if(curr==total-1)
        printf("\n");
        
     /*if (curr==0)
        printf("%s",str1);
     printf("\b\b\b\b\b\b\b\b\b\b\b\b\b%s",str1);
     if(curr==total-1)
        printf("\n");*/
    


}
//mex buldklmat.c;load('input.mat');buldklmat(vale,coordmat,NT,NP,NN,tet)