#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Eigen/Eigen"

using namespace Eigen;
using namespace std;

//notes from the exercice class of 26/03/2025 
//SAMUEL CORIAT S307195  Exercices are line__75 



// Fonction d'affichage de matrices de base
int welcome__matrix() {
    Matrix4d A = Matrix4d::Identity(); // Matrice identité 4x4
    Matrix4d B = Matrix4d::Zero();      // Matrice 4x4 de zéros
    MatrixXd C = MatrixXd::Ones(3, 3);  // Matrice 3x3 remplie de 1

    cout << "Matrice A (Identity) :\n" << A << endl;//printing 
    cout << "Matrice B (Zero) :\n" << B << endl;
    cout << "Matrice C (Ones 3x3) :\n" << C << endl;

    Vector2d w = Vector2d::Zero(); // Vecteur de 2 éléments, initialisé à 0
    VectorXd w1 = VectorXd::Ones(2); // Vecteur de 2 éléments, initialisé à 1

    cout << "Vecteur w (Zero) :\n" << w.transpose() << endl;
    cout << "Vecteur w1 (Ones 2) :\n" << w1.transpose() << endl;

    return 0;
}

// Fonction qui crée une matrice remplie avec une séquence de nombres
int creation__matrice(unsigned int n) {
    VectorXd v = VectorXd::LinSpaced(n * n, 1, n * n); // Vecteur de n*n éléments de 1 à n*n
    MatrixXd A = Map<MatrixXd>(v.data(), n, n).transpose(); // Conversion en matrice n x n

    cout << "Matrice créée :\n" << A << endl;
    return 0;
}

//EXO 2 
int random__matrix(unsigned int n) {// je veux matrixe aleatoire nombre entre 0,2
    MatrixXd A = MatrixXd::Random(n, n) + MatrixXd::Ones(n, n); // Matrice aléatoire (nombre entre -1 et 1) + 1
    cout << "Matrice aléatoire :\n" << A << endl;
    return 0;
}


int matrice_de__hilbert(unsigned int n) { // rappell,  hilbert squared matrix <=>  A[i, j] = 1 / (1 + i + j).
    MatrixXd A = MatrixXd::Zero(n, n);
    
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            A(i, j) = 1.0 / (1 + i + j); 
        }
    }

    cout << "Matrice de Hilbert :\n" << A << endl;

    double d=A.determinant();// calcul du det 
    cout<<"det de matrice hilb="<<d<<endl;

    if(abs(d)<1.0e-12){
        cout<<" pas inversible"<<endl;
    }
    else{
        cout<<"inversible"<<endl;
    }

    return 0;
}

/*_____________________________________________


hello this is my soltion to the probleme
we have a matrix A and a vector b in input and we want to find the sol to Ax=b using Qr and PALU decomposition 
if you want to print the matrix just change the parameter to true ! 

*/



void solve_QR(const MatrixXd &A, const VectorXd &b) {
    //sanitizing the input cause it can be possible that the size of the matrix and the vectore are different !!!  
    if (A.rows() != b.size()) {
        cerr << "Error: Incompatible dimensions between A and b." << endl;
        return;
    }

    // Compute the QR decomposition
    HouseholderQR<MatrixXd> qr(A);
    MatrixXd Q = qr.householderQ();  // q if we want to print it 
    MatrixXd R = qr.matrixQR().triangularView<Upper>(); 

    // solve the system Ax = b
    VectorXd x = qr.solve(b);

    // show the solution
    cout << "Solution x for the system Ax = b using QR decomposition:\n" << x << endl;

    bool printQR = false; // change to true if you want to display the matrix 
    if (printQR==true) {
        cout << "\nMatrix Q (Orthogonal):\n" << Q << endl;
        cout << "\nMatrix R (Upper Triangular):\n" << R << endl;
    }
}

// part 2 of the probleme 
//solution of the systeme AX=b using PALU decomposition 

void solve_PLU(const MatrixXd &A, const VectorXd &b) {
    if (A.rows() != b.size()) {
        cerr << "Error: Incompatible dimensions between A and b." << endl;
        return;
    }

    // calculate the LU decomposition with partial pivoting
    FullPivLU<MatrixXd> lu(A);
    MatrixXd P = lu.permutationP();  // extract permutation the matrix (for printing it )
    MatrixXd L = lu.matrixLU().triangularView<Lower>();  
    MatrixXd U = lu.matrixLU().triangularView<Upper>();  
    // Solve the system Ax = b
    VectorXd x = lu.solve(b);

    // show the solution
    cout << "Solution x for the system Ax = b using LU decomposition:\n" << x << endl;
    bool printPLU = false;
    // show the matrices
    if (printPLU==true) {
        cout << "\nMatrix P (Permutation):\n" << P << endl;
        cout << "\nMatrix L (Lower Triangular):\n" << L << endl;
        cout << "\nMatrix U (Upper Triangular):\n" << U << endl;
    }
}


int solve_1() {

    MatrixXd A(2, 2);
    A <<  5.547001962252291e-01, -3.770900990025203e-02,
          8.320502943378437e-01, -9.992887623566787e-01;

    
    VectorXd b(2);
    b << -5.169911863249772e-01,
          1.672384680188350e-01;

    cout << "Solving using QR decomposition :\n"<<endl;
    solve_QR(A, b); 

    cout << "\nSolving using LU decomposition:\n"<<endl;
    solve_PLU(A, b);


    return 0;
}


int solve_2() {

    MatrixXd A(2, 2);
    A <<  5.547001962252291e-01, -5.540607316466765e-01,
          8.320502943378437e-01,-8.324762492991313e-01;

    
    VectorXd b(2);
    b << -6.394645785530173e-04,
          4.259549612877223e-04;

    cout << "Solving using QR decomposition the sol of systeme 2 is :\n"<<endl;
    solve_QR(A, b); 

    cout << "\nSolving using LU decomposition:the sol of systeme 2 is\n"<<endl;
    solve_PLU(A, b);


    return 0;
}






int solve_3() {

    MatrixXd A(2, 2);
    A <<  5.547001962252291e-01, -5.547001955851905e-01,
          8.320502943378437e-01,-8.320502947645361e-01;

    
    VectorXd b(2);
    b << -6.400391328043042e-10,
         4.266924591433963e-10;

    cout << "Solving using QR decomposition the sol of systeme 2 is :\n"<<endl;
    solve_QR(A, b); 

    cout << "\nSolving using LU decomposition:the sol of systeme 2 is\n"<<endl;
    solve_PLU(A, b);


    return 0;
}


int main(){
    
    solve_1();

    solve_2();
    
    solve_3();

    return 0;
}

