#include "Compute3D.h"

int Compute3D::sampleNum = 24;

void Compute3D::init(double N, double F){
	double a = 2*N*F/(N - F);
	double b = (N+F)/(F-N);
    
	u = a;
	v = 0-b;
	n = u/N;
    
	t = u/n;
	zr = -0.1;
}

std::vector<Vector3D> Compute3D::calcAxes(double *x, double *y){
    double c[4][4];
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            c[i][j] = x[i]*x[j] + y[i]*y[j] + t*t;  
        }
    } 
    int m = 1, n=2, l=3, r=0;   
    double A = c[r][r]*c[r][r]*c[n][l] - c[r][r]*c[r][n]*c[r][l];
    double B = -2*(c[m][r]*c[n][l]*c[r][r] - c[m][r]*c[n][r]*c[l][r]);
    double C = c[r][m]*c[r][m]*c[n][l] - c[r][l]*c[r][m]*c[n][m] - c[r][n]*c[r][m]*c[l][m] + c[r][r]*c[l][m]*c[n][m];
    
    double z[4];
    z[0] =zr + v;
    
    B *= z[r];
    C *= z[r]*z[r];
    
    double dd = B*B - 4*A*C;
	if (dd < 0){
		//printf("dd = %.21f\n", dd);
		printf("no resolution\n");
		std::vector<Vector3D> v;
		return v;
	}
	//system("pause");
    z[1] = -B - sqrt( dd);
    z[1] /= 2*A;
    
    m = 3;  n = 1; l = 2;
    z[m] = (c[m][n]*z[r]*z[r] - c[m][r]*z[r]*z[n])/(c[n][r]*z[r] - c[r][r]*z[n]);
    
    m = 2;  n = 3; l = 1;
    z[m] = (c[m][n]*z[r]*z[r] - c[m][r]*z[r]*z[n])/(c[n][r]*z[r] - c[r][r]*z[n]);
    
    double X[4], Y[4], Z[4];
    for (int i=0; i<4; i++){
        X[i] = n*x[i]/z[i];
        Y[i] = n*y[i]/z[i];
        Z[i] = u/z[i];
        printf("(%.2lf, %.2lf, %.2lf)\n", X[i], Y[i], Z[i]);     
    }
    
    double vx[3], vy[3], vz[3];
    for (int i=0; i<4; i++){
        vx[i] = X[i+1] - X[0];    
        vy[i] = Y[i+1] - Y[0];
        vz[i] = Z[i+1] - Z[0];
        double R = vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
        R = sqrt(R);
        vx[i] /= R;
        vy[i] /= R;
        vz[i] /= R;
    }
    for (int i=0; i< 3; i++){
        double res = vx[i]*vx[(i+1)%3] + vy[i]*vy[(i+1)%3] + vz[i]*vz[(i+1)%3];
        printf("%.2lf \n", acos(res)*180/3.14159);
    } 
	
	std::vector<Vector3D> res;
	for (int i=0; i<4; i++){
		res.push_back(Vector3D(X[i], Y[i], Z[i]));
	}
	return res;
}     